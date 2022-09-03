/**
 * @file ConnectionEvaluationTable.cc
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
#include "ConnectionEvaluationTable.h"

#include <algorithm>
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

ConnectionEvaluationTable::ConnectionEvaluationTable(TreeModel *tree,
                                                     int numberOfConnections) {
  _tree = tree;
  _numberOfConnections = numberOfConnections;
  /**
   *  Allocate all connections once. It speed up the code because later it wont
   *  need to create/destroy objects as the tree grows.
   * */
  _connections = new Connection[numberOfConnections];
  _reasonableConnections = new int[numberOfConnections];
  withoutIntersection = new WithoutIntersection(_tree);
}

ConnectionEvaluationTable::~ConnectionEvaluationTable() {
  delete[] _connections;
  delete[] _reasonableConnections;
}

TreeModel *ConnectionEvaluationTable::tree() { return _tree; }

void ConnectionEvaluationTable::setTree(TreeModel *tree) { _tree = tree; }

void ConnectionEvaluationTable::reduce() {
  int i, j, ID;
  Segment *bifurcationSegment,
      updatedBifurcationSegment(_tree->dimension()),
      newSegment(_tree->dimension());
  bool passGeometricRestriction;
  _currentNumberOfReasonableConnections = 0;

  for (i = 0; i < _currentNumberOfConnections; i++) {
    passGeometricRestriction = true;

    /* Do the connection. */
    bifurcationSegment = _tree->segment(_connections[i].bifurcationSegmentID());
    newSegment = _connections[i].newSegment();
    updatedBifurcationSegment = _tree->growSegment(
        _connections[i].bifurcationPoint(), *bifurcationSegment, newSegment);

    /* Check for intersections. */
    if (withoutIntersection->pass(updatedBifurcationSegment)) {
      _reasonableConnections[_currentNumberOfReasonableConnections] = i;
      _currentNumberOfReasonableConnections++;
    }

    /* Undo the connection. */
    _tree->remove(newSegment);
  }
}

void ConnectionEvaluationTable::copy(Connection source,
                                     Connection *destination) {
  destination->setBifurcationSegmentID(source.bifurcationSegmentID());
  destination->setBifurcationPoint(source.bifurcationPoint());
  destination->setNewSegment(source.newSegment());
  destination->setTargetFunctionValue(source.targetFunctionValue());
}

Connection *ConnectionEvaluationTable::connections() { return _connections; }

Connection ConnectionEvaluationTable::optimalReasonableConnection() {
  int i, connectionID, optimalConnectionID;
  double targetFunctionValue = 1e15;

  for (i = 0; i < _currentNumberOfReasonableConnections; i++) {
    connectionID = _reasonableConnections[i];
    if (_connections[connectionID].targetFunctionValue() <
        targetFunctionValue) {
      optimalConnectionID = connectionID;
      targetFunctionValue = _connections[connectionID].targetFunctionValue();
    }
  }

  return _connections[optimalConnectionID];
}

void ConnectionEvaluationTable::add(Connection connection) {
  if (_currentNumberOfConnections < _numberOfConnections) {
    copy(connection, &_connections[_currentNumberOfConnections]);
    _currentNumberOfConnections++;
  }
}

void ConnectionEvaluationTable::reset() { _currentNumberOfConnections = 0; }

int *ConnectionEvaluationTable::reasonableConnections() {
  return _reasonableConnections;
}

int ConnectionEvaluationTable::currentNumberOfConnections() {
  return _currentNumberOfConnections;
}

int ConnectionEvaluationTable::currentNumberOfReasonableConnection() {
  return _currentNumberOfReasonableConnections;
}
