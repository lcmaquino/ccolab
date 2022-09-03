/**
 * @file Segment.cc
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
 * @file Segment.cpp
 * @author Luiz Cláudio Mesquita de Aquino (luiz.aquino@ufvjm.edu.br)
 * @brief
 * @version 1.0
 * @date 2022-05-18
 */
#include "Segment.h"

/**
 * @brief Get the dimension of the points on the segment.
 *
 * @return The dimension of the points on the segment.
 */
int Segment::dimension() { return _dimension; }

/**
 * @brief Get the segment index.
 *
 * @return The segment index.
 */
int Segment::ID() { return _ID; }

/**
 * @brief Get the distal point of the segment.
 *
 * @return The distal point of the segment.
 */
Point Segment::point() { return _point; }

/**
 * @brief Get the bifurcation ratio to multiply by the segement radius to
 * evaluate the radius of the left segment descendent.
 *
 * @return The left bifurcation ratio.
 */
double Segment::bifurcationRatioLeft() { return _bifurcationRatioLeft; }

/**
 * @brief Get the bifurcation ratio to multiply by the segement radius to
 * evaluate the radius of the right segment descendent.
 *
 * @return The right bifurcation ratio.
 */
double Segment::bifurcationRatioRight() { return _bifurcationRatioRight; }

/**
 * @brief Get the blood flow passing through the segment.
 *
 * @return The blood flow passing through the segment.
 */
double Segment::flow() { return _flow; }

/**
 * @brief Get the index of the ascendent (ie, parent) segment.
 *
 * @return The index of the ascendent (ie, parent) segment.
 */
int Segment::up() { return _up; }

/**
 * @brief Get the index of the left descendent segment.
 *
 * @return The index of the left descendent segment.
 */
int Segment::left() { return _left; }

/**
 * @brief Get the index of the right descendent segment.
 *
 * @return The index of the right descendent segment.
 */
int Segment::right() { return _right; }

/**
 * @brief Get the dimension of the points on the segment.
 *
 * @return The dimension of the points on the segment.
 */
void Segment::setDimension(int dimension) { _dimension = dimension; }

/**
 * @brief Set the index of the segment.
 *
 * @param ID The index of the segment.
 */
void Segment::setID(int ID) { _ID = ID; }

/**
 * @brief Set the distal point of the segment.
 *
 * @return point The distal point of the segment.
 */
void Segment::setPoint(Point point) { _point = point; }

/**
 * @brief Set the bifurcation ratio to multiply by the segement radius to
 * evaluate the radius of the left segment descendent.
 *
 * @param value The left bifurcation ratio.
 */
void Segment::setBifurcationRatioLeft(double value) {
  _bifurcationRatioLeft = value;
}

/**
 * @brief Set the bifurcation ratio to multiply by the segement radius to
 * evaluate the radius of the right segment descendent.
 *
 * @param value The right bifurcation ratio.
 */
void Segment::setBifurcationRatioRight(double value) {
  _bifurcationRatioRight = value;
}

/**
 * @brief Set the blood flow passing through the segment.
 *
 * @param value The blood flow passing through the segment.
 */
void Segment::setFlow(double value) { _flow = value; }

/**
 * @brief Set the index of the ascendent (ie, parent) segment.
 *
 * @param segmentID The index of the ascendent (ie, parent) segment.
 */
void Segment::setUp(int segmentID) { _up = segmentID; }

/**
 * @brief Set the index of the left descendent segment.
 *
 * @param segmentID the index of the left descendent segment.
 */
void Segment::setLeft(int segmentID) { _left = segmentID; }

/**
 * @brief Set the index of the right descendent segment.
 *
 * @param segmentID the index of the right descendent segment.
 */
void Segment::setRight(int segmentID) { _right = segmentID; }

/**
 * @brief Print the index and distal point of the segment for debugging.
 *
 */
void Segment::print() {
  if (_dimension == 2) {
    cout << "<" << _ID << "> (" << _point.x() << ", " << _point.y() << ") <"
         << _flow << ", " << _bifurcationRatioLeft << ", "
         << _bifurcationRatioRight << "> <" << _up << ", " << _left << ", "
         << _right << " >" << endl;
  } else {
    cout << "<" << _ID << "> (" << _point.x() << ", " << _point.y() << ", "
         << _point.z() << ") <" << _flow << ", " << _bifurcationRatioLeft
         << ", " << _bifurcationRatioRight << "> <" << _up << ", " << _left
         << ", " << _right << " >" << endl;
  }
}

/**
 * @brief Print the index, distal point, tree reduced resistance, length,
 * and radius of the segment for debugging.
 *
 * @param reducedResitance The reduced resitance of the tree begining at
 * the segment.
 * @param length The length of the segment.
 * @param radius The radius of the segment.
 */
void Segment::print(double reducedResitance, double length, double radius) {
  if (_dimension == 2) {
    cout << "<" << _ID << "> (" << _point.x() << ", " << _point.y() << ") <"
         << reducedResitance << ", " << _flow << ", " << _bifurcationRatioLeft
         << ", " << _bifurcationRatioRight << ">, r = " << radius
         << ", l = " << length << ", " << _up << ", " << _left << ", " << _right
         << " >" << endl;
  } else {
    cout << "<" << _ID << "> (" << _point.x() << ", " << _point.y() << ", "
         << _point.z() << ") <" << reducedResitance << ", " << _flow << ", "
         << _bifurcationRatioLeft << ", " << _bifurcationRatioRight
         << ">, r = " << radius << ", l = " << length << ", " << _up << ", "
         << _left << ", " << _right << " >" << endl;
  }
}
