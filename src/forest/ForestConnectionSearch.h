/**
 * @file ForestConnectionSearch.h
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

#include "geometry/Geometry.h"
#include "tree/interface/TreeModel.h"
using std::cout;
using std::endl;

#ifndef _CCOLAB_FOREST_FORESTCONNECTIONSEARCH_H
#define _CCOLAB_FOREST_FORESTCONNECTIONSEARCH_H
class ForestConnectionSearch {
 private:
  /**
   * @brief The vector of trees.
   * 
   */
  TreeModel **_trees;

  /**
   * @brief The vector flaging the status of a tree.
   * 
   */
  bool *_active;

  /**
   * @brief The total number of connections.
   * 
   */
  int _numberOfConnections;

  /**
   * @brief The number of trees.
   * 
   */
  int _numberOfTrees;

  /**
   * @brief The current number of connections.
   * 
   */
  int _currentNumberOfConnections;

  /**
   * @brief The current number of segments.
   * 
   */
  int _currentNumberOfSegments;

  /**
   * @brief Vector of distances between the new point and the segments
   * on the trees.
   * 
   */
  double *_segmentDistance;

  /**
   * @brief Vector of the segments indexes.
   * 
   */
  int *_segmentID;

  /**
   * @brief Vector of the trees indexes.
   * 
   */
  int *_treeID;

  /**
   * @brief Vector of the segments indexes and its respective trees indexes.
   * 
   */
  int *_closestSegments;

  /**
   * @brief The Geometry object to do some geometric calcultions.
   * 
   */
  Geometry *_geometry;

  /**
   * @brief Ascendent sort of the segment distance between the new point and
   * the segments on the trees.
   * 
   */
  void sort();

 public:
  /**
   * @brief Construct a new Forest Connection Search object.
   * 
   * @param numberOfConnections The number of connections.
   * @param trees The vector of trees.
   * @param numberOfTrees The number of trees.
   * @param active The vector flaging the status of a tree.
   * @param totalNumberOfSegments The total number of segments.
   * @param dimension The dimension of the points in domain.
   */
  ForestConnectionSearch(int numberOfConnections, TreeModel **trees,
                         int numberOfTrees, bool *active,
                         int totalNumberOfSegments, int dimension);

  /**
   * @brief Destroy the Forest Connection Search object.
   * 
   */
  ~ForestConnectionSearch();

  /**
   * @brief Set the vector of trees.
   * 
   * @param trees The vector of trees.
   */
  void setTrees(TreeModel **trees);

  /**
   * @brief Get the vector of trees.
   * 
   * @return The vector of trees.
   */
  TreeModel **trees();

  /**
   * @brief Get the current number of connections.
   * 
   * @return The current number of connections.
   */
  int currentNumberOfConnections();

  /**
   * @brief Get the vector of segments indexes and its respective tree index
   * that are close to the new point.
   * 
   * @param point The new point.
   * @return The vector of indexes such that index[2*i] is the tree index and
   * index[2*i + 1] is the respective segment index that is close to the new 
   * point.
   */
  int *atPoint(Point point);

  /**
   * @brief Get the vector of segments indexes and its respective tree index
   * that are close to the new point.
   * 
   * @param point The new point.
   * @param treeID The tree index.
   * @return The vector of indexes such that index[2*i] is equal to treeID and
   * index[2*i + 1] is the respective segment index that is close to the new 
   * point.
   */
  int *atPoint(Point point, int treeID);
};
#endif //_CCOLAB_FOREST_FORESTCONNECTIONSEARCH_H
