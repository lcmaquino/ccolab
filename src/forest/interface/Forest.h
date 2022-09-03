/**
 * @file Forest.h
 *
 *  Copyright 2022 Luiz C. M. de Aquino.
 *
 *  This file is part of CCOLab.
 *
 *  CCOLab is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  CCOLab is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with CCOLab.  If not, see <https://www.gnu.org/licenses/>
 *
 */

/**
 * @author Luiz Cláudio Mesquita de Aquino (luiz.aquino@ufvjm.edu.br)
 * @brief
 * @version 1.0
 * @date 2022-05-18
 */
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "ForestConnectionSearch.h"
#include "ForestConstantTerminalFlow.h"
#include "ForestIntersection.h"
#include "cco/ClassicDistanceCriterion.h"
#include "cco/Connection.h"
#include "cco/ConnectionEvaluationTable.h"
#include "cco/SimpleOptimization.h"
#include "cco/TargetVolume.h"
#include "cco/interface/GeometricOptimization.h"
#include "cco/interface/TargetFunction.h"
#include "cco/interface/TerminalFlowFunction.h"
#include "domain/interface/Domain.h"
#include "geometry/Geometry.h"
#include "progress/Progress.h"
#include "tree/TreeConnectionSearch.h"
#include "tree/TreeFile.h"
#include "tree/interface/TreeModel.h"

using std::cout;
using std::endl;
using std::numeric_limits;
using std::setprecision;

#ifndef _CCOLAB_FOREST_INTERFAC_FOREST_H
#define _CCOLAB_FOREST_INTERFAC_FOREST_H
class Forest {
 public:
  /**
   * @brief The number of terminals.
   * 
   */
  int _numberOfTerminals;

  /**
   * @brief The total number of segments.
   * 
   */
  int _totalNumberOfSegments;

  /**
   * @brief The number of trees.
   * 
   */
  int _numberOfTrees;

  /**
   * @brief The maximum number of attempts.
   * 
   */
  int _maximumNumberOfAttempts;
 
  /**
   * @brief The number of connections.
   * 
   */
  int _numberOfConnections;

  /**
   * @brief The index of the tree with largest perfusion flow.
   * 
   */
  int _largestTreePerfusionFlow;

  /**
   * @brief The index of the closest neighbor.
   * 
   */
  int *_closestNeighbor;

  /**
   * @brief The maximum root length.
   * 
   */
  double *_maximumRootLength;
  
  /**
   * @brief The vector of target perfusion flows.
   * 
   */
  double *_targetPerfusionFlow;

  /**
   * @brief The vector of target relative perfusion flows.
   * 
   */
  double *_targetRelativeFlow; 

  /**
   * @brief The vector of current perfusion flows.
   * 
   */
  double *_currentRelativeFlow;

  /**
   * @brief The expoent for the segment radius on target function expression.
   * 
   */
  double _radiusExpoent;

  /**
   * @brief The expoent for the segment length on target function expression.
   * 
   */
  double _lengthExpoent;

  /**
   * @brief The vector flaging the status of a tree.
   * 
   */
  bool *_active;

  /**
   * @brief The domain.
   * 
   */
  Domain *_domain;

  /**
   * @brief The vector of trees.
   * 
   */
  TreeModel **_trees;

  /**
   * @brief The vector of target functions.
   * 
   */
  TargetFunction **_targetFunction;

  /**
   * @brief The vector of terminal flow functions.
   * 
   */
  TerminalFlowFunction **_terminalFlowFunction;

  /**
   * @brief The vector of geometric optimization objects.
   * 
   */
  GeometricOptimization **_geometricOptimization;

  /**
   * @brief The vector of distance criterion objects.
   * 
   */
  DistanceCriterion **_distanceCriterion;

  /**
   * @brief Construct a new Forest object.
   * 
   * @param domain The domain.
   * @param trees The vector of trees.
   * @param numberOfTrees The number of trees.
   * @param numberOfTerminals The desired number of terminals.
   * @param targetPerfusionFlow The vector of target perfusion flows.
   * @param radiusExpoent The expoent for the segment radius on target
   * function expression. 
   * @param lengthExpoent The expoent for the segment length on target
   * function expression.
   */
  Forest(Domain *domain, TreeModel **trees, int numberOfTrees,
         int numberOfTerminals, double *targetPerfusionFlow,
         double radiusExpoent, double lengthExpoent) {
    _domain = domain;
    _trees = trees;
    _numberOfTrees = numberOfTrees;
    _numberOfTerminals = numberOfTerminals;
    _totalNumberOfSegments = 2 * _numberOfTerminals - 1;
    _targetPerfusionFlow = targetPerfusionFlow;
    _radiusExpoent = radiusExpoent;
    _lengthExpoent = lengthExpoent;
    _maximumNumberOfAttempts = 10;
    _numberOfConnections = 20;
  }

  /**
   * @brief Destroy the Forest object.
   * 
   */
  ~Forest() {}

  /**
   * @brief Set the trees.
   * 
   * @param trees The vector of trees.
   */
  virtual void setTrees(TreeModel **trees) {
    int i, intervalDivision = 10;
    _trees = trees;

    for (i = 0; i < _numberOfTrees; i++) {
      _distanceCriterion[i] = new ClassicDistanceCriterion(_trees[i]);
      /* Default functions */
      _terminalFlowFunction[i] = new ForestConstantTerminalFlow(
          _trees, _numberOfTrees, _numberOfTerminals);
      _targetFunction[i] =
          new TargetVolume(_trees[i], _radiusExpoent, _lengthExpoent);
      _geometricOptimization[i] = new SimpleOptimization(
          _domain, _trees[i], _targetFunction[i], intervalDivision);
    }
  }

  /**
   * @brief Get the tree with index treeID.
   * 
   * @param treeID The index of the tree.
   * @return The tree with index treeID.
   */
  virtual TreeModel *tree(int treeID) { return _trees[treeID]; }

  /**
   * @brief Get the target perfusion flow for the treeID tree.
   * 
   * @param treeID The index of the tree.
   * @return  The target perfusion flow for the treeID tree.
   */
  virtual double targetPerfusionFlow(int treeID) {
    return _targetPerfusionFlow[treeID];
  }

  /**
   * @brief Get the vector of target relative flows.
   * 
   * @return The vector of target relative flows.
   */
  virtual double *targetRelativeFlow() { return _targetRelativeFlow; }

  /**
   * @brief Get the vector of current relative flows.
   * 
   * @return The vector of current relative flows.
   */
  virtual double *currentRelativeFlow() { return _currentRelativeFlow; }

  /**
   * @brief Calculate the current relative flow.
   * 
   */
  virtual void calculateCurrentRelativeFlow() {
    int i;
    double flow, largestFlow = _trees[0]->flow();

    for (i = 0; i < _numberOfTrees; i++) {
      flow = _trees[i]->flow();
      if (flow > largestFlow) {
        largestFlow = flow;
      }
    }

    for (i = 0; i < _numberOfTrees; i++) {
      _currentRelativeFlow[i] = _trees[i]->flow() / largestFlow;
    }
  }

  /**
   * @brief Check if a given tree is active.
   * 
   * @param treeID The index of the tree to be checked.
   * @return Returns true if the tree with index treeID is active.
   * Return false otherwise.
   */
  virtual bool isActive(int treeID) { return _active[treeID]; }

  /**
   * @brief Set the values of the vector flaging the status of the trees.
   * 
   */
  virtual void setActive() {
    int t;
    calculateCurrentRelativeFlow();

    for (t = 0; t < _numberOfTrees; t++) {
      if (t == _largestTreePerfusionFlow) {
        _active[t] = (_trees[t]->perfusionFlow() >= _trees[t]->flow());
      } else {
        _active[t] = (_targetRelativeFlow[t] >= _currentRelativeFlow[t]);
      }
    }
  }

  /**
   * @brief Get the total number of terminals.
   * 
   * @return The total number of terminals.
   */
  virtual int numberOfTerminals() { return _numberOfTerminals; }

  /**
   * @brief Get the total number of segments.
   * 
   * @return The total number of segments.
   */
  virtual int totalNumberOfSegments() { return _totalNumberOfSegments; }

  /**
   * @brief Get the current number of segments.
   * 
   * @return The current number of segments.
   */
  virtual int currentNumberOfSegments() {
    int i, n = 0;
    for (i = 0; i < _numberOfTrees; i++) {
      n += _trees[i]->currentNumberOfSegments();
    }

    return n;
  }

  /**
   * @brief Get the maximum number of attempts.
   * 
   * @return The maximum number of attempts.
   */
  virtual int maximumNumberOfAttempts() { return _maximumNumberOfAttempts; }

  /**
   * @brief Set the maximum number of attempts.
   * 
   * @param value The maximum number of attempts.
   */
  virtual void setMaximumNumberOfAttempts(int value) {
    _maximumNumberOfAttempts = value;
  }

  /**
   * @brief Get the number of connections.
   * 
   * @return The number of connections.
   */
  virtual int numberOfConnections() { return _numberOfConnections; }

  /**
   * @brief Set the number of connections.
   * 
   * @param value The number of connections.
   */
  virtual void setNumberOfConnections(int value) {
    _numberOfConnections = value;
  }

  /**
   * @brief Write the comma-separated values (CSV) file for the 
   * forest attained flow.
   * 
   * Each row has the tree index (in column "TREE"), the target flow
   * (in column "TARGET_FLOW"), and the attained flow (in column
   * "ATTAINED_FLOW").
   * 
   * @param filename The filename.
   * @param delimiter The column delimiter. Defaults to one space.
   */
  virtual void attainedFlow(string filename, string delimiter = " ") {
    int t;
    double forestPerfusionFlow = 0.0;
    ofstream flowFile;
    flowFile.open(filename);
    if (flowFile.is_open()) {
      for (t = 0; t < _numberOfTrees; t++) {
        forestPerfusionFlow += _trees[t]->perfusionFlow();
      }

      flowFile << "TREE" << delimiter << "TARGET_FLOW" << delimiter
               << "ATTAINED_FLOW" << endl;
      for (t = 0; t < _numberOfTrees; t++) {
        flowFile << t << delimiter << 100.0 * _targetPerfusionFlow[t]
                 << delimiter << 100.0 * _trees[t]->flow() / forestPerfusionFlow
                 << endl;
      }

      flowFile.close();
    } else {
      cout << "Unable to open: \"" << filename << "\"." << endl;
    }
  }

  /**
   * @brief Write the comma-separated values (CSV) file for the 
   * volume of the trees.
   * 
   * Each row has the tree index (in column "TREE"), the tree volume
   * (in column "VOLUME"), and the tree radius root (in column
   * "RADIUS_ROOT").
   * 
   * @param filename The filename.
   * @param delimiter The column delimiter. Defaults to one space.
   */
  virtual void volumes(string filename, string delimiter = " ") {
    int t;
    ofstream volumeFile;
    volumeFile.open(filename);
    if (volumeFile.is_open()) {
      volumeFile << "TREE" << delimiter << "VOLUME" << delimiter
                 << "RADIUS_ROOT" << endl;
      for (t = 0; t < _numberOfTrees; t++) {
        volumeFile << t << delimiter
                   << setprecision(numeric_limits<double>::digits10)
                   << _trees[t]->volume() << delimiter
                   << setprecision(numeric_limits<double>::digits10)
                   << _trees[t]->radius(_trees[t]->root().ID()) << endl;
      }

      volumeFile.close();
    } else {
      cout << "Unable to open: \"" << filename << "\"." << endl;
    }
  }

  /**
   * @brief Grow the root segment for each tree on the forest.
   * 
   */
  virtual void growRoot() = 0;

  /**
   * @brief Grow the segments for each tree on the forest.
   * 
   */
  virtual void grow() = 0;
};
#endif  //_CCOLAB_FOREST_INTERFAC_FOREST_H
