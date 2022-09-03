/**
 * @file WithoutIntersection.h
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

#include "geometry/Geometry.h"
#include "interface/GeometricRestriction.h"

#ifndef _CCOLAB_CCO_WITHOUTINTERSECTION_H
#define _CCOLAB_CCO_WITHOUTINTERSECTION_H
class WithoutIntersection : public GeometricRestriction {
 private:
  /**
   * @brief The Geometry object to do some geometric calculations.
   * 
   */
  Geometry *_geometry;

  /**
   * @brief Check if two segments are relatives.
   * 
   * @param segmentA The segment to be checked.
   * @param segmentB The segment to be checked.
   * @return Returns true if the segments are relatives (ie, segment A is 
   * descendent of segment B or vice-versa). It also returns true if segment A
   * is equal to segment B. Returns false otherwise.
   */
  bool isRelative(Segment segmentA, Segment segmentB);

 public:
  /**
   * @brief Construct a new Without Intersection object.
   * 
   * @param tree The tree.
   */
  explicit WithoutIntersection(TreeModel *tree);

  /**
   * @brief Destroy the Without Intersection object.
   * 
   */
  ~WithoutIntersection() {}

  /**
   * @brief Check if a given segment (or its descendents) intersects other
   * segment on the tree.
   * 
   * @param segment The segment to be checked.
   * @return Returns true if the segment (and its descendents) do not 
   * intersects other segment on the tree. Returns false otherwise.
   */
  virtual bool pass(Segment segment);
};
#endif //_CCOLAB_CCO_WITHOUTINTERSECTION_H
