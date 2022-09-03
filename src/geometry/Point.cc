/**
 * @file Point.cc
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

#include "Point.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;

Point::Point() { _dimension = 2; }

Point::Point(int dimension) { _dimension = dimension; }

Point::Point(double *point, int dimension) {
  _dimension = dimension;
  _x = point[0];
  _y = point[1];
  _z = _dimension == 3 ? point[2] : 0.0;
}

double Point::x() { return _x; }

double Point::y() { return _y; }

double Point::z() { return _z; }

int Point::dimension() { return _dimension; }

void Point::setX(double value) { _x = value; }

void Point::setY(double value) { _y = value; }

void Point::setZ(double value) { _z = value; }

void Point::set(double *point) {
  _x = point[0];
  _y = point[1];
  _z = _dimension == 3 ? point[2] : 0.0;
}

void Point::setDimension(int value) { _dimension = value; }

void Point::print() {
  cout << "(" << _x << ", " << _y;
  if (_dimension == 3) {
    cout << ", " << _z;
  }
  cout << ")" << endl;
}
