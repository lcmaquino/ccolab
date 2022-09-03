/**
 * @file TreeMorphometry.h
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
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

#include "domain/interface/Domain.h"
#include "geometry/Geometry.h"
#include "tree/interface/TreeModel.h"

using std::string;
using std::ofstream;
using std::cout;
using std::endl;

#ifndef _CCOLAB_MORPHOMETRY_TREEMORPHOMETRY_H
#define _CCOLAB_MORPHOMETRY_TREEMORPHOMETRY_H
class TreeMorphometry {
 private:
  /**
   * @brief The vector of trees.
   * 
   */
  TreeModel *_tree;

  /**
   * @brief The vector of length for each segment. 
   * 
   */
  double *_length;

  /**
   * @brief The vector of radius for each segment.
   * 
   */
  double *_radius;
  
  /**
   * @brief The vector of bifurcation level for each segment.
   * 
   */
  int *_level;

  /**
   * @brief The vector of Strahler order for each segment.
   * 
   */
  int *_strahlerOrder;

 public:
  /**
   * @brief Construct a new Tree Morphometry object.
   * 
   */
  TreeMorphometry() {}

  /**
   * @brief Destroy the Tree Morphometry object.
   * 
   */
  ~TreeMorphometry() {}

  /**
   * @brief Set the tree.
   * 
   * @param tree 
   */
  void setTree(TreeModel *tree) { _tree = tree; }

  /**
   * @brief Evaluate the length, radius, bifurcation level, and Strahler order
   * for each segment.
   * 
   */
  void analytics();

  /**
   * @brief Write the comma-separated values (CSV) file for the length,
   * radius, bifurcation level, and Strahler order for the segments on the
   * tree.
   * 
   * Each row has the length, radius, bifurcation level, and Strahler order
   * (in respective column "LENGTH", "RADIUS", "LEVEL", and "STRAHLER_ORDER").
   * 
   * @param filename The filename.
   * @param delimiter The delimiter for the columns. Defaults to one space.
   */
  void save(string filename, string delimiter = " ");

  /**
   * @brief Get the tree.
   * 
   * @return The tree. 
   */
  TreeModel *tree() { return _tree; }
};
#endif //_CCOLAB_MORPHOMETRY_TREEMORPHOMETRY_H
