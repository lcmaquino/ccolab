/**
 * @file ForestCcoInvasion.cc
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
#include "ForestCcoInvasion.h"

ForestCcoInvasion::ForestCcoInvasion(Domain *domain, TreeModel **trees,
                                     int numberOfTrees, int numberOfTerminals,
                                     double invasionCoefficient,
                                     double *targetPerfusionFlow,
                                     double radiusExpoent, double lengthExpoent)
    : Forest(domain, trees, numberOfTrees, numberOfTerminals,
             targetPerfusionFlow, radiusExpoent, lengthExpoent) {
  int i, t, intervalDivision = 10;
  double distanceClosestNeighbor, d;
  Geometry geometry(domain->dimension());
  _invasionCoefficient = invasionCoefficient;
  _largestTreePerfusionFlow = 0;
  _closestNeighbor = new int[_numberOfTrees];
  _targetPerfusionFlow = targetPerfusionFlow;
  _targetRelativeFlow = new double[_numberOfTrees];
  _currentRelativeFlow = new double[_numberOfTrees];
  _maximumRootLength = new double[_numberOfTrees];
  _active = new bool[_numberOfTrees];
  _distanceCriterion = new DistanceCriterion *[1];
  _distanceCriterion[0] = new ClassicDistanceCriterion(_trees[0]);
  _terminalFlowFunction = new TerminalFlowFunction *[_numberOfTrees];
  _targetFunction = new TargetFunction *[_numberOfTrees];
  _geometricOptimization = new GeometricOptimization *[_numberOfTrees];

  for (t = 0; t < _numberOfTrees; t++) {
    _active[t] = true;

    /* Default functions */
    _terminalFlowFunction[t] = new ForestConstantTerminalFlow(
        _trees, _numberOfTrees, numberOfTerminals);
    _targetFunction[t] =
        new TargetVolume(_trees[t], _radiusExpoent, _lengthExpoent);
    _geometricOptimization[t] = new SimpleOptimization(
        _domain, _trees[t], _targetFunction[t], intervalDivision);

    if (_targetPerfusionFlow[t] >
        _targetPerfusionFlow[_largestTreePerfusionFlow]) {
      _largestTreePerfusionFlow = t;
    }

    _closestNeighbor[t] = (t == _numberOfTrees - 1) ? 0 : t + 1;
  }

  if (_numberOfTrees == 1) {
    _targetRelativeFlow[0] = 1.0;
    if (_domain->dimension() == 2) {
      _maximumRootLength[0] = sqrt(_trees[0]->perfusionVolume() /
                                   (_trees[0]->numberOfTerminals() * M_PI));
    } else {
      _maximumRootLength[0] =
          cbrt(3.0 * _trees[0]->perfusionVolume() /
               (4.0 * _trees[0]->numberOfTerminals() * M_PI));
    }
  } else {
    for (t = 0; t < _numberOfTrees; t++) {
      _targetRelativeFlow[t] = _targetPerfusionFlow[t] /
                               _targetPerfusionFlow[_largestTreePerfusionFlow];
      for (i = 0; i < _numberOfTrees; i++) {
        if (t != i) {
          distanceClosestNeighbor = geometry.distance(
              _trees[t]->seed(), _trees[_closestNeighbor[t]]->seed());
          d = geometry.distance(_trees[t]->seed(), _trees[i]->seed());
          if ((d < distanceClosestNeighbor) ||
              (d == distanceClosestNeighbor &&
               _targetPerfusionFlow[i] <
                   _targetPerfusionFlow[_closestNeighbor[t]])) {
            _closestNeighbor[t] = i;
          }
        }
      }

      _maximumRootLength[t] =
          geometry.distance(_trees[t]->seed(),
                            _trees[_closestNeighbor[t]]->seed()) *
          _targetPerfusionFlow[t] /
          (_targetPerfusionFlow[_closestNeighbor[t]] + _targetPerfusionFlow[t]);
    }
  }
}

void ForestCcoInvasion::growRoot() {
  int t;
  Geometry geometry(_domain->dimension());
  Point point, seed;

  for (t = 0; t < _numberOfTrees; t++) {
    Segment root(_trees[t]->dimension());
    seed = _trees[t]->seed();

    while (_domain->hasAvailablePoint()) {
      /* Get a random point in Domain */
      point = _domain->point();

      /*
       *   Check if the point is in the supporting circle (sphere)
       *   and the root segment is in domain.
       */
      if (geometry.distance(point, seed) < _maximumRootLength[t] &&
          _domain->isIn(seed, point)) {
        break;
      }
    }

    if (!_domain->hasAvailablePoint()) {
      _domain->reset();
    }

    root.setPoint(point);
    root.setFlow(_terminalFlowFunction[t]->eval(root));
    _trees[t]->growRoot(root);
  }

  _distanceCriterion[0]->update(_numberOfTrees);
}

void ForestCcoInvasion::grow() {
  int dimension = _domain->dimension();
  int i, j, t, treeID, segmentID, Kterm, attempt, totalAttempts,
      *closestSegments;
  bool pass;
  double value, targetFunctionValue, factor;
  Progress progress(_numberOfTerminals, "Growing trees");
  Point point(dimension), middle(dimension);
  ForestIntersection forestIntersection(_numberOfTrees, _trees);
  ForestConnectionSearch vicinity(_numberOfConnections, _trees, _numberOfTrees,
                                  _active, _totalNumberOfSegments, dimension);
  Segment newSegment(dimension);
  Segment *bifurcationSegment, updatedBifurcationSegment(dimension);
  Geometry geometry(dimension);
  Connection connection, optimalConnection;

  /* Grow the root segment. */
  growRoot();
  Kterm = _numberOfTrees;

  ConnectionEvaluationTable **connectionEvaluationTable =
      new ConnectionEvaluationTable *[_numberOfTrees];
  for (t = 0; t < _numberOfTrees; t++) {
    connectionEvaluationTable[t] =
        new ConnectionEvaluationTable(_trees[t], _numberOfConnections);
    progress.next();
  }

  totalAttempts = 0;
  factor = 0.9;

  /* Grow the tree. */
  while (Kterm < _numberOfTerminals) {
    /* Set the activity for each tree. */
    setActive();

    attempt = 0;
    while (_domain->hasAvailablePoint()) {
      /* Get a random point in Domain */
      point = _domain->point();

      /* Check distance criterion */
      pass = true;
      for (t = 0; t < _numberOfTrees; t++) {
        _distanceCriterion[0]->setTree(_trees[t]);
        if (isActive(t) && !_distanceCriterion[0]->eval(point)) {
          pass = false;
          break;
        }
      }

      if (pass) {
        break;
      }

      attempt += 1;
      if (attempt > _maximumNumberOfAttempts) {
        /* Relax distance criterion. */
        _distanceCriterion[0]->relax(factor);
        attempt = 0;
      }
    }

    if (!_domain->hasAvailablePoint()) {
      _domain->reset();
    }

    /* Find the point's vicinity. */
    closestSegments = vicinity.atPoint(point);

    for (i = 0; i < vicinity.currentNumberOfConnections(); i++) {
      treeID = closestSegments[2 * i];
      segmentID = closestSegments[2 * i + 1];
      if (_trees[treeID]->flow() <
              _invasionCoefficient * _trees[treeID]->perfusionFlow() &&
          geometry.distance(point, _trees[treeID]->seed()) >
              _maximumRootLength[treeID]) {
        continue;
      }

      /* Do the connection. */
      bifurcationSegment = _trees[treeID]->segment(segmentID);
      middle = geometry.middle(_trees[treeID]->proximalPoint(segmentID),
                               _trees[treeID]->distalPoint(segmentID));
      newSegment.setPoint(point);
      newSegment.setFlow(_terminalFlowFunction[treeID]->eval(newSegment));
      updatedBifurcationSegment =
          _trees[treeID]->growSegment(middle, *bifurcationSegment, newSegment);
      newSegment = _trees[treeID]->right(updatedBifurcationSegment.ID());

      /* Geometric optimization. */
      connection = _geometricOptimization[treeID]->bifurcation(
          updatedBifurcationSegment);
      if (!connection.empty()) {
        connectionEvaluationTable[treeID]->add(connection);
      }

      /* Undo the connection. */
      _trees[treeID]->remove(newSegment);
    }

    treeID = -1;
    targetFunctionValue = 1.0e10;
    for (t = 0; t < _numberOfTrees; t++) {
      /* Reduce bifurcations to reasonable connections. */
      connectionEvaluationTable[t]->reduce();

      /*  Structural optimization. */
      if (connectionEvaluationTable[t]->currentNumberOfReasonableConnection() >
          0) {
        value = 0.0;
        for (i = 0; i < _numberOfTrees; i++) {
          if (i != t) {
            value += _targetFunction[i]->eval();
          }
        }

        /**
         *  Get the reasonable connection that has the minimum value for
         *  the target function.
         */
        Connection optimalConnection =
            connectionEvaluationTable[t]->optimalReasonableConnection();
        if (optimalConnection.targetFunctionValue() + value <
            targetFunctionValue) {
          treeID = t;
          targetFunctionValue = optimalConnection.targetFunctionValue() + value;
        }
      }
    }

    /*  Structural optimization. */
    if (treeID >= 0) {
      Connection optimalConnection =
          connectionEvaluationTable[treeID]->optimalReasonableConnection();

      /* Connect the new segment to the bifurcation segment. */
      newSegment = optimalConnection.newSegment();
      updatedBifurcationSegment = _trees[treeID]->growSegment(
          optimalConnection.bifurcationPoint(),
          *_trees[treeID]->segment(optimalConnection.bifurcationSegmentID()),
          newSegment);
      forestIntersection.setTreeID(treeID);
      if (forestIntersection.pass(updatedBifurcationSegment)) {
        Kterm++;

        /* Update distance criterion. */
        _distanceCriterion[0]->update(Kterm);

        totalAttempts = 0;

        /* Update progress bar */
        progress.next();
      } else {
        /* Undo the connection if the new segment intersects some tree at the
         * forest. */
        newSegment = _trees[treeID]->right(updatedBifurcationSegment.ID());
        _trees[treeID]->remove(newSegment);
      }
    }

    totalAttempts++;
    if (totalAttempts > _maximumNumberOfAttempts) {
      _distanceCriterion[0]->relax(factor);
      totalAttempts = 0;
    }

    /* Print progress bar */
    progress.print();

    /* Reset Connection Evaluation Table. */
    for (t = 0; t < _numberOfTrees; t++) {
      connectionEvaluationTable[t]->reset();
    }
  }
}
