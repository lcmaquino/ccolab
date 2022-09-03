/**
 * @file Segment.h
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
#include <iostream>
#include <string>

#include "geometry/Point.h"
using std::cout;
using std::endl;

#ifndef _CCOLAB_TREE_INTERFACE_SEGMENT_H
#define _CCOLAB_TREE_INTERFACE_SEGMENT_H
class Segment {
 private:
  /**
   * @brief The segment index.
   * 
   */
  int _ID = -1;

  /**
   * @brief The segment distal point.
   * 
   */
  Point _point;

  /**
   * @brief The dimesion of the distal point.
   * 
   */
  int _dimension;

  /**
   * @brief The bifurcation ratio to multiply by the segement radius to evaluate
   * the radius of the left segment descendent.
   * 
   */
  double _bifurcationRatioLeft = 1.0;

  /**
   * @brief The bifurcation ratio to multiply by the segement radius to evaluate
   * the radius of the right segment descendent.
   * 
   */
  double _bifurcationRatioRight = 1.0;

  /**
   * @brief The blood flow passing through the segment.
   * 
   */
  double _flow = 0.0;

  /**
   * @brief The index of the ascendent (ie, parent) segment.
   * 
   */
  int _up = -1;

  /**
   * @brief The index of the left descendent segment.
   * 
   */
  int _left = -1;

  /**
   * @brief The index of the right descendent segment.
   * 
   */
  int _right = -1;

 public:
  /**
   * @brief Construct a new Segment Model object.
   * 
   */
  Segment() {}

  /**
   * @brief Construct a new Segment Model object.
   * 
   * @param dimension The dimension of the points on segment.
   */
  explicit Segment(int dimension) : _dimension(dimension) {}

  /**
   * @brief Construct a new Segment Model object.
   * 
   * @param point The distal point of the segment.
   * @param dimension The dimension of the points on segment.
   */
  Segment(Point point, int dimension)
      : _point(point), _dimension(dimension) {}

  /**
   * @brief Destroy the Segment Model object.
   * 
   */
  ~Segment() {}

  /**
   * @brief Get the dimension of the points on the segment.
   * 
   * @return The dimension of the points on the segment. 
   */
  int dimension();

  /**
   * @brief Get the segment index.
   * 
   * @return The segment index. 
   */
  int ID();

  /**
   * @brief Get the distal point of the segment.
   * 
   * @return The distal point of the segment.
   */
  Point point();

  /**
   * @brief Get the bifurcation ratio to multiply by the segement radius to
   * evaluate the radius of the left segment descendent.
   * 
   * @return The left bifurcation ratio.
   */
  double bifurcationRatioLeft();

  /**
   * @brief Get the bifurcation ratio to multiply by the segement radius to
   * evaluate the radius of the right segment descendent.
   * 
   * @return The right bifurcation ratio.
   */
  double bifurcationRatioRight();

  /**
   * @brief Get the blood flow passing through the segment.
   * 
   * @return The blood flow passing through the segment. 
   */
  double flow();

  /**
   * @brief Get the index of the ascendent (ie, parent) segment.
   * 
   * @return The index of the ascendent (ie, parent) segment.
   */
  int up();

  /**
   * @brief Get the index of the left descendent segment.
   * 
   * @return The index of the left descendent segment.
   */
  int left();

  /**
   * @brief Get the index of the right descendent segment.
   * 
   * @return The index of the right descendent segment.
   */
  int right();

  /**
   * @brief Get the dimension of the points on the segment.
   * 
   * @return The dimension of the points on the segment.
   */
  void setDimension(int dimension);

  /**
   * @brief Set the index of the segment.
   * 
   * @param ID The index of the segment.
   */
  void setID(int ID);

  /**
   * @brief Set the distal point of the segment.
   * 
   * @return point The distal point of the segment.
   */
  void setPoint(Point point);

  /**
   * @brief Set the bifurcation ratio to multiply by the segement radius to
   * evaluate the radius of the left segment descendent.
   * 
   * @param value The left bifurcation ratio.
   */
  void setBifurcationRatioLeft(double value);

  /**
   * @brief Set the bifurcation ratio to multiply by the segement radius to
   * evaluate the radius of the right segment descendent.
   * 
   * @param value The right bifurcation ratio.
   */
  void setBifurcationRatioRight(double value);

  /**
   * @brief Set the blood flow passing through the segment.
   * 
   * @param value The blood flow passing through the segment. 
   */
  void setFlow(double value);

  /**
   * @brief Set the index of the ascendent (ie, parent) segment.
   * 
   * @param segmentID The index of the ascendent (ie, parent) segment.
   */
  void setUp(int segmentID);

  /**
   * @brief Set the index of the left descendent segment.
   * 
   * @param segmentID the index of the left descendent segment.
   */
  void setLeft(int segmentID);

  /**
   * @brief Set the index of the right descendent segment.
   * 
   * @param segmentID the index of the right descendent segment.
   */
  void setRight(int segmentID);

  /**
   * @brief Print the index and distal point of the segment for debugging.
   * 
   */
  void print();

  /**
   * @brief Print the index, distal point, tree reduced resistance, length,
   * and radius of the segment for debugging.
   * 
   * @param reducedResitance The reduced resitance of the tree begining at 
   * the segment.
   * @param length The length of the segment.
   * @param radius The radius of the segment.
   */
  void print(double reducedResitance, double length, double radius);
};
#endif  //_CCOLAB_TREE_INTERFACE_SEGMENT_H
