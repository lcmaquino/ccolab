/**
 * @file Connection.cc
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
#include "Connection.h"

Connection::Connection(int segmentID, Point bifurcationPoint,
                       Segment newSegment, double targetFunctionValue) {
  _bifurcationSegmentID = segmentID;
  _bifurcationPoint = bifurcationPoint;
  _newSegment = newSegment;
  _targetFunctionValue = targetFunctionValue;
}

int Connection::bifurcationSegmentID() { return _bifurcationSegmentID; }

Point Connection::bifurcationPoint() { return _bifurcationPoint; }

Segment Connection::newSegment() { return _newSegment; }

double Connection::targetFunctionValue() { return _targetFunctionValue; }

void Connection::setBifurcationSegmentID(int segmentID) {
  _bifurcationSegmentID = segmentID;
}

void Connection::setBifurcationPoint(Point point) { _bifurcationPoint = point; }

void Connection::setNewSegment(Segment segment) { _newSegment = segment; }

void Connection::setTargetFunctionValue(double value) {
  _targetFunctionValue = value;
}

bool Connection::empty() { return _bifurcationSegmentID < 0; }

void Connection::print() {
  cout << "_bifurcationSegmentID: " << _bifurcationSegmentID << endl;
  _bifurcationPoint.print();
  _newSegment.print();
  cout << "_targetFunctionValue: " << _targetFunctionValue << endl;
  cout << "---" << endl;
}
