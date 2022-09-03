/**
 * @file TreeConnectionSearch.h
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
#include "geometry/Geometry.h"
#include "interface/TreeModel.h"

#ifndef _CCOLAB_TREE_TREECONNECTIONSEARCH_H
#define _CCOLAB_TREE_TREECONNECTIONSEARCH_H
class TreeConnectionSearch {
 private:
  TreeModel *_tree;
  int _numberOfConnections;
  int _currentNumberOfConnections;
  int _currentNumberOfSegments;
  double *_segmentDistance;
  int *_segmentID;
  int *_closestSegments;
  Geometry *_geometry;
  void sort();

 public:
  TreeConnectionSearch(int numberOfConnections, int totalNumberOfSegments,
                       int dimension);
  TreeConnectionSearch(TreeModel *tree, int numberOfConnections);
  ~TreeConnectionSearch();
  void setTree(TreeModel *tree);
  TreeModel *tree();
  int currentNumberOfConnections();
  int *atPoint(Point point);
};
#endif //_CCOLAB_TREE_TREECONNECTIONSEARCH_H
