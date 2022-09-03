/**
 * @file CompetingOptimizedArterialTrees.cc
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
#include "CompetingOptimizedArterialTrees.h"

CompetingOptimizedArterialTrees::CompetingOptimizedArterialTrees(
    Domain *domain, TreeModel **trees, int numberOfTrees, int numberOfTerminals,
    double firstStage, double *targetPerfusionFlow, double radiusExpoent,
    double lengthExpoent)
    : Forest(domain, trees, numberOfTrees, numberOfTerminals,
             targetPerfusionFlow, radiusExpoent, lengthExpoent) {
  int i, t, intervalDivision = 5;
  double distanceClosestNeighbor, d;
  Geometry geometry(domain->dimension());
  _firstStage = firstStage;
  _largestTreePerfusionFlow = 0;
  _closestNeighbor = new int[_numberOfTrees];
  _targetPerfusionFlow = targetPerfusionFlow;
  _targetRelativeFlow = new double[_numberOfTrees];
  _currentRelativeFlow = new double[_numberOfTrees];
  _maximumRootLength = new double[_numberOfTrees];
  _active = new bool[_numberOfTrees];
  _distanceCriterion = new DistanceCriterion *[1];
  _terminalFlowFunction = new TerminalFlowFunction *[_numberOfTrees];
  _targetFunction = new TargetFunction *[_numberOfTrees];
  _geometricOptimization = new GeometricOptimization *[_numberOfTrees];

  _distanceCriterion[0] = new ClassicDistanceCriterion(_trees[0]);
  for (t = 0; t < _numberOfTrees; t++) {
    _active[t] = true;

    /* Default functions */
    _terminalFlowFunction[t] = new ForestConstantTerminalFlow(
        _trees, numberOfTrees, numberOfTerminals);
    _targetFunction[t] =
        new TargetVolume(_trees[t], _radiusExpoent, _lengthExpoent);
    _geometricOptimization[t] = new SimpleOptimization(
        _domain, _trees[t], _targetFunction[t], intervalDivision, 0.0);

    if (_targetPerfusionFlow[t] >
        _targetPerfusionFlow[_largestTreePerfusionFlow]) {
      _largestTreePerfusionFlow = t;
    }

    _closestNeighbor[t] = (t + 1 < _numberOfTrees) ? t + 1 : 0;
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

void CompetingOptimizedArterialTrees::growRoot() {
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
      throw invalid_argument("Oops! No more points on domain file.");
    }

    root.setPoint(point);
    root.setFlow(_terminalFlowFunction[t]->eval(root));
    _trees[t]->growRoot(root);
  }

  _distanceCriterion[0]->update(_numberOfTrees);
}

void CompetingOptimizedArterialTrees::grow() {
  int dimension = _domain->dimension();
  int i, j, s, t, treeID, segmentID, Kterm, attempt, totalAttempts,
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
  factor = 0.99;
  /* Grow the first tree stage. */
  while (Kterm < _numberOfTerminals) {
    /* Set the activity for each tree. */
    for (t = 0; t < _numberOfTrees; t++) {
      _active[t] =
          (_trees[t]->flow() < _firstStage * _trees[t]->perfusionFlow());
    }

    attempt = 0;

    while (_domain->hasAvailablePoint()) {
      /* Get a random point in Domain */
      point = _domain->point();

      /* Check distance criterion */
      pass = true;
      for (t = 0; t < _numberOfTrees; t++) {
        _distanceCriterion[0]->setTree(_trees[t]);
        if (isActive(t) &&
            geometry.distance(point, _trees[t]->seed()) <=
                _maximumRootLength[t] &&
            !_distanceCriterion[0]->eval(point)) {
          pass = false;
          break;
        }
      }

      if (pass) {
        break;
      }

      attempt++;
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
      if (geometry.distance(point, _trees[treeID]->seed()) >
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

    /* Check the first stage and reset Connection Evaluation Table. */
    pass = true;
    for (t = 0; t < _numberOfTrees; t++) {
      connectionEvaluationTable[t]->reset();
      if (_trees[t]->flow() < _firstStage * _trees[t]->perfusionFlow()) {
        pass = false;
      }
    }

    if (pass) {
      break;
    }
  }

  /* Separate the subdomains. */
  _domainVoronoi = new DomainVoronoi(_domain, _trees, _targetPerfusionFlow,
                                    _numberOfTrees, 0.5);

  /* Grow the second tree stage. */
  for (s = 0; s < _numberOfTrees; s++) {
    _domain->reset();
    factor = 0.9;
    _distanceCriterion[0]->setTree(_trees[s]);
    // _distanceCriterion[0]->update(_trees[s]->currentNumberOfTerminals());
    while (Kterm < _numberOfTerminals) {
      /* Set the activity for each tree. */
      _active[s] = (_trees[s]->perfusionFlow() > _trees[s]->flow());
      if (!_active[s]) {
        break;
      }

      attempt = 0;

      while (_domain->hasAvailablePoint()) {
        /* Get a random point in Domain */
        point = _domain->point();
        treeID = _domainVoronoi->inSubset(point);

        if (treeID != s) {
          continue;
        }

        /* Check distance criterion */
        if (_distanceCriterion[0]->eval(point)) {
          break;
        }

        attempt++;
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
      closestSegments = vicinity.atPoint(point, treeID);

      for (i = 0; i < vicinity.currentNumberOfConnections(); i++) {
        segmentID = closestSegments[2 * i + 1];

        /* Do the connection. */
        bifurcationSegment = _trees[treeID]->segment(segmentID);
        middle = geometry.middle(_trees[treeID]->proximalPoint(segmentID),
                                 _trees[treeID]->distalPoint(segmentID));
        newSegment.setPoint(point);

        newSegment.setFlow(_terminalFlowFunction[treeID]->eval(newSegment));
        updatedBifurcationSegment = _trees[treeID]->growSegment(
            middle, *bifurcationSegment, newSegment);
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

      /* Reduce bifurcations to reasonable connections. */
      connectionEvaluationTable[treeID]->reduce();

      /*  Structural optimization. */
      if (connectionEvaluationTable[treeID]
              ->currentNumberOfReasonableConnection() > 0) {
        /**
         *  Get the reasonable connection that has the minimum value for
         *  the target function.
         */
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
      connectionEvaluationTable[s]->reset();
    }
  }
}
