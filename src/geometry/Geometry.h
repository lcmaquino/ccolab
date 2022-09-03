/**
 * @file Geometry.h
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

#ifndef _CCOLAB_GEOMETRY_GEOMETRY_H
#define _CCOLAB_GEOMETRY_GEOMETRY_H
class Geometry {
 private:
  /**
   * @brief The dimesion of the points.
   * 
   */
  int _dimension = 3;

 public:
  /**
   * @brief Construct a new Geometry object.
   * 
   * @param dimension The dimension of the points.
   */
  explicit Geometry(int dimension);

  /**
   * @brief Destroy the Geometry object.
   * 
   */
  ~Geometry() {}

  /**
   * @brief The tolerance constant.
   * 
   */
  const double _TOLERANCE = 1e-6;

  /**
   * @brief Evaluate the Euclidian distance between points A and B.
   * 
   * @param pointA The point A.
   * @param pointB The point B.
   * @return The Euclidian distance between points A and B. 
   */
  double distance(Point pointA, Point pointB);

  /**
   * @brief Evaluate the critic distance between a point and a segment.
   * 
   * @param point The point.
   * @param proximalPoint The proximal point of the segment.
   * @param distalPoint The distal point of the segment.
   * @return The critic distance between a point and a segment.
   */
  double distanceFromSegment(Point point, Point proximalPoint,
                             Point distalPoint);

  /**
   * @brief Evaluate the critic distance between a point and a segment for
   * two dimensional space.
   * 
   * @param point The point.
   * @param proximalPoint The proximal point of the segment.
   * @param distalPoint The distal point of the segment.
   * @return The critic distance between a point and a segment.
   */
  double distanceFromSegment2D(Point point, Point proximalPoint,
                               Point distalPoint);

  /**
   * @brief Evaluate the critic distance between a point and a segment for
   * three dimensional space.
   * 
   * @param point The point.
   * @param proximalPoint The proximal point of the segment.
   * @param distalPoint The distal point of the segment.
   * @return The critic distance between a point and a segment.
   */
  double distanceFromSegment3D(Point point, Point proximalPoint,
                               Point distalPoint);

  /**
   * @brief Add two points.
   * 
   * @param pointA The point A.
   * @param pointB The point B.
   * @return The sum of the two points.
   */
  Point add(Point pointA, Point pointB);

  /**
   * @brief Subtract two points.
   * 
   * @param pointA The point A.
   * @param pointB The point B.
   * @return The subtraction of the two points.
   */
  Point subtract(Point pointA, Point pointB);

  /**
   * @brief Evaluate the dot product between two vectors.
   * 
   * @param u The vector u.
   * @param v The vector v.
   * @return The dot product between two vectors.
   */
  double dot(Point u, Point v);

  /**
   * @brief Evaluate the norm of the vector.
   * 
   * @param v The vector v.
   * @return The norm of the vector v.
   */
  double norm(Point v);

  /**
   * @brief Evaluate the cross product between two vectors.
   * 
   * @param u The vector u.
   * @param v The vector v.
   * @return The cross product between two vectors.
   */
  Point crossProduct(Point u, Point v);

  /**
   * @brief Evaluate the scalar product between the scalar and the vector.
   * 
   * @param scalar The scalar value.
   * @param v The vector v.
   * @return The scalar product between the scalar value and the vector v.
   */
  Point scalarProduct(double scalar, Point v);

  /**
   * @brief Evaluate the unit vector respective to the vector with
   * proximal point A and distal point B.
   * 
   * @param pointA The proximal point A.
   * @param pointB The distal point B.
   * @return The unit vector respective to the vector with proximal point A and
   * distal point B.
   */
  Point unitVector(Point pointA, Point pointB);

  /**
   * @brief Evaluate the angle between two vectors.
   * 
   * @param u The vector u.
   * @param v The vector v.
   * @return The angle between two vectors.
   */
  double angle(Point u, Point v);

  /**
   * @brief Evaluate the middle point of the segment with endpoints A and B.
   * 
   * @param pointA The point A.
   * @param pointB The point B.
   * @return The middle point of the segment with endpoints A and B.
   */
  Point middle(Point pointA, Point pointB);

  /**
   * @brief Check if the segment AB intersects the segment CD.
   * 
   * @param pointA Proximal point of the segment AB.
   * @param pointB Distal point of the segment AB.
   * @param pointC Proximal point of the segment CD.
   * @param pointD Distal point of the segment CD.
   * @param tolerance The tolerance to be considered.
   * @return Returns true if the segment AB intersects the segment CD. Returns
   * false othewise.
   */
  bool hasIntersection(Point pointA, Point pointB, Point pointC, Point pointD,
                       double tolerance);

  /**
   * @brief Check if the segment AB intersects the segment CD for two
   * dimensional spaces.
   * 
   * @param pointA Proximal point of the segment AB.
   * @param pointB Distal point of the segment AB.
   * @param pointC Proximal point of the segment CD.
   * @param pointD Distal point of the segment CD.
   * @param tolerance The tolerance to be considered.
   * @return Returns true if the segment AB intersects the segment CD. Returns
   * false othewise.
   */
  bool hasIntersection2D(Point pointA, Point pointB, Point pointC, Point pointD,
                         double tolerance);

  /**
   * @brief Check if the segment AB intersects the segment CD for three
   * dimensional spaces.
   * 
   * @param pointA Proximal point of the segment AB.
   * @param pointB Distal point of the segment AB.
   * @param pointC Proximal point of the segment CD.
   * @param pointD Distal point of the segment CD.
   * @param tolerance The tolerance to be considered.
   * @return Returns true if the segment AB intersects the segment CD. Returns
   * false othewise.
   */
  bool hasIntersection3D(Point pointA, Point pointB, Point pointC, Point pointD,
                         double tolerance);
};
#endif //_CCOLAB_GEOMETRY_GEOMETRY_H
