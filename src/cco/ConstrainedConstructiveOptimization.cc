/**
 * @file ConstrainedConstructiveOptimization.cc
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
 * @copyright GPL-3.0
 * @version 1.0
 * @date 2022-05-18
 */
#include "ConstrainedConstructiveOptimization.h"

#include "ConstantTerminalFlow.h"
#include "SimpleOptimization.h"
#include "TargetVolume.h"
#include "geometry/Geometry.h"
#include "tree/TreeFile.h"

ConstrainedConstructiveOptimization::ConstrainedConstructiveOptimization(
    Domain *domain, TreeModel *tree, int numberOfTerminals,
    double radiusExpoent, double lengthExpoent, int numberOfConnections,
    int maximumNumberOfAttempts) {
  _domain = domain;
  _tree = tree;
  _numberOfTerminals = numberOfTerminals;
  _radiusExpoent = radiusExpoent;
  _lengthExpoent = lengthExpoent;
  _numberOfConnections = numberOfConnections;
  _maximumNumberOfAttempts = maximumNumberOfAttempts;

  int dimension = _tree->dimension(), intervalDivision = 5;

  _distanceCriterion = new ClassicDistanceCriterion(_tree);

  /* Default functions */
  _terminalFlowFunction = new ConstantTerminalFlow(_tree);
  _targetFunction = new TargetVolume(_tree, radiusExpoent, lengthExpoent);
  _geometricOptimization =
      new SimpleOptimization(_domain, _tree, _targetFunction, intervalDivision);
}

Domain *ConstrainedConstructiveOptimization::domain() { return _domain; }

void ConstrainedConstructiveOptimization::setDomain(Domain *domain) {
  _domain = domain;
}

TreeModel *ConstrainedConstructiveOptimization::tree() { return _tree; }

void ConstrainedConstructiveOptimization::setTree(TreeModel *tree) {
  _tree = tree;
}

DistanceCriterion *ConstrainedConstructiveOptimization::distanceCriterion() {
  return _distanceCriterion;
}

void ConstrainedConstructiveOptimization::setDistanceCriterion(
    DistanceCriterion *distanceCriterion) {
  _distanceCriterion = distanceCriterion;
}

double ConstrainedConstructiveOptimization::radiusExpoent() {
  return _radiusExpoent;
}

void ConstrainedConstructiveOptimization::setRadiusExpoent(double radius) {
  _radiusExpoent = radius;
}

double ConstrainedConstructiveOptimization::lengthExpoent() {
  return _lengthExpoent;
}

void ConstrainedConstructiveOptimization::setLengthExpoent(double length) {
  _lengthExpoent = length;
}

TargetFunction *ConstrainedConstructiveOptimization::targetFunction() {
  return _targetFunction;
}

void ConstrainedConstructiveOptimization::setTargetFunction(
    TargetFunction *targetFunction) {
  _targetFunction = targetFunction;
}

TerminalFlowFunction *
ConstrainedConstructiveOptimization::terminalFlowFunction() {
  return _terminalFlowFunction;
}

void ConstrainedConstructiveOptimization::setTerminalFlowFunction(
    TerminalFlowFunction *terminalFlowFunction) {
  _terminalFlowFunction = terminalFlowFunction;
}

GeometricOptimization *
ConstrainedConstructiveOptimization::geometricOptimization() {
  return _geometricOptimization;
}

void ConstrainedConstructiveOptimization::setGeometricOptimization(
    GeometricOptimization *geometricOptimization) {
  _geometricOptimization = geometricOptimization;
}

int ConstrainedConstructiveOptimization::maximumNumberOfAttempts() {
  return _maximumNumberOfAttempts;
}

void ConstrainedConstructiveOptimization::setMaximumNumberOfAttempts(
    int maximumNumberOfAttempts) {
  _maximumNumberOfAttempts = maximumNumberOfAttempts;
}

void ConstrainedConstructiveOptimization::growRoot() {
  Segment root(_tree->dimension());
  double factor = 0.9;
  double supportingRadius;
  Point point, seed = _tree->seed();
  Geometry geometry(_tree->dimension());

  if (_tree->dimension() == 2) {
    supportingRadius =
        sqrt(_tree->perfusionVolume() / (M_PI * _tree->numberOfTerminals()));
  } else {
    supportingRadius = cbrt(3.0 * _tree->perfusionVolume() /
                            (4.0 * M_PI * _tree->numberOfTerminals()));
  }

  while (_domain->hasAvailablePoint()) {
    /* Get a random point in Domain */
    point = _domain->point();

    /* Check if the point is in the supporting circle (sphere) */
    if (geometry.distance(point, seed) < supportingRadius) {
      break;
    }
  }

  if (!_domain->hasAvailablePoint()) {
    throw invalid_argument("Oops! No more points on domain file.");
  }

  root.setPoint(point);
  root.setFlow(_terminalFlowFunction->eval(root));
  _tree->growRoot(root);
  _distanceCriterion->update(1);
}

void ConstrainedConstructiveOptimization::grow() {
  Progress progress(_numberOfTerminals, "Growing tree");
  Point point(_tree->dimension()), middle(_tree->dimension());
  int i, Kterm, attempt, totalAttempts, *closestSegments;

  /* Grow the root segment. */
  growRoot();
  Kterm = 1;

  progress.next();

  TreeConnectionSearch vicinity(_tree, _numberOfConnections);
  ConnectionEvaluationTable connectionEvaluationTable(_tree,
                                                      _numberOfConnections);

  Segment *bifurcationSegment, newSegment(_tree->dimension()),
      updatedBifurcationSegment(_tree->dimension());
  Geometry geometry(_tree->dimension());
  Connection connection, optimalConnection;
  totalAttempts = 1;

  /* Grow the tree. */
  while (Kterm < _numberOfTerminals) {
    attempt = 0;
    /* Get a random point in Domain */
    while (_domain->hasAvailablePoint()) {
      point = _domain->point();

      /* Check distance criterion */
      if (_distanceCriterion->eval(point)) {
        break;
      }

      attempt += 1;
      /* Relax distance criterion. */
      if (attempt > _maximumNumberOfAttempts) {
        _distanceCriterion->relax();
        attempt = 0;
      }
    }

    if (!_domain->hasAvailablePoint()) {
      _domain->reset();
    }

    /* Find the point's vicinity. */
    closestSegments = vicinity.atPoint(point);

    for (i = 0; i < vicinity.currentNumberOfConnections(); i++) {
      /* Do the connection. */
      bifurcationSegment = _tree->segment(closestSegments[i]);
      middle = geometry.middle(_tree->proximalPoint(closestSegments[i]),
                               _tree->distalPoint(closestSegments[i]));
      newSegment.setPoint(point);
      newSegment.setFlow(_terminalFlowFunction->eval(newSegment));
      updatedBifurcationSegment =
          _tree->growSegment(middle, *bifurcationSegment, newSegment);
      newSegment = _tree->right(updatedBifurcationSegment.ID());

      /* Geometric optimization. */
      connection =
          _geometricOptimization->bifurcation(updatedBifurcationSegment);
      if (!connection.empty()) {
        connectionEvaluationTable.add(connection);
      }

      /* Undo the connection. */
      _tree->remove(newSegment);
    }

    /* Reduce bifurcations to reasonable connections. */
    connectionEvaluationTable.reduce();

    /*  Structural optimization. */
    if (connectionEvaluationTable.currentNumberOfReasonableConnection() > 0) {
      /**
       *  Get the reasonable connection that has the minimum value for
       *  the target function.
       */
      Connection optimalConnection =
          connectionEvaluationTable.optimalReasonableConnection();

      /* Connect the new segment to the bifurcation segment. */
      newSegment = optimalConnection.newSegment();
      _tree->growSegment(
          optimalConnection.bifurcationPoint(),
          *_tree->segment(optimalConnection.bifurcationSegmentID()),
          newSegment);

      Kterm++;

      /* Update distance criterion. */
      _distanceCriterion->update(Kterm);

      /* Update progress bar */
      progress.next();

      totalAttempts = 1;
    } else {
      totalAttempts++;
    }

    /* Print progress bar */
    progress.print();

    /* Reset Connection Evaluation Table. */
    connectionEvaluationTable.reset();
  }
}
