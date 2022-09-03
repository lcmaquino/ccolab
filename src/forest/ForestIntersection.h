/**
 * @file ForestIntersection.h
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

#include "cco/interface/GeometricRestriction.h"
#include "geometry/Geometry.h"
using std::cout;
using std::endl;

#ifndef _CCOLAB_FOREST_FORESTINTERSECTION_H
#define _CCOLAB_FOREST_FORESTINTERSECTION_H
class ForestIntersection : public GeometricRestriction {
 private:
  /**
   * @brief The number of trees.
   * 
   */
  int _numberOfTrees;
  /**
   * @brief The index of the tree.
   * 
   */
  int _treeID;

  /**
   * @brief The vector of trees.
   * 
   */
  TreeModel **_trees;

  /**
   * @brief The Geometry object to do some geometric calculations.
   * 
   */
  Geometry *_geometry;

 public:
  /**
   * @brief Construct a new Forest Intersection object.
   * 
   * @param numberOfTress The number of trees.
   * @param trees The vector of trees.
   */
  ForestIntersection(int numberOfTress, TreeModel **trees);

  /**
   * @brief Destroy the Forest Intersection object.
   * 
   */
  ~ForestIntersection() {}

  /**
   * @brief Check if a given segment (or its descendents) intersects other
   * segment on the tree.
   * 
   * @param segment The segment to be checked.
   * @return Returns true if the segment (and its descendents) do not 
   * intersects other segment on the tree. Returns false otherwise.
   */
  virtual bool pass(Segment segment);

  /**
   * @brief Set the tree index.
   * 
   * @param value The tree index.
   */
  void setTreeID(int value);
};
#endif //_CCOLAB_FOREST_FORESTINTERSECTION_H
