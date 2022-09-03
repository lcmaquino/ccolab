/**
 * @file GeometricRestriction.h
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
 *  CCO Lab is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with CCOLab. If not, see <https://www.gnu.org/licenses/>
 *
 */

/**
 * @author Luiz Cláudio Mesquita de Aquino (luiz.aquino@ufvjm.edu.br)
 * @brief Define the GeometricRestriction intercafe.
 * @version 1.0
 * @date 2022-05-18
 *
 */
#include <cmath>

#include "tree/interface/TreeModel.h"

#ifndef _CCOLAB_CCO_INTERFACE_GEOMETRIC_RESTRICTION_H
#define _CCOLAB_CCO_INTERFACE_GEOMETRIC_RESTRICTION_H
class GeometricRestriction {
 private:
  /**
   * @brief The tree.
   *
   */
  TreeModel *_tree;

 public:
  /**
   * @brief Construct a new Geometric Restriction object.
   *
   */
  GeometricRestriction() {}

  /**
   * @brief Construct a new Geometric Restriction object.
   *
   * @param tree The tree.
   */
  explicit GeometricRestriction(TreeModel *tree) : _tree(tree) {}

  /**
   * @brief Destroy the Geometric Restriction object.
   *
   */
  ~GeometricRestriction() {}

  /**
   * @brief Set the Tree object.
   *
   * @param tree
   */
  virtual void setTree(TreeModel *tree) { _tree = tree; }

  /**
   * @brief Get the Tree object.
   *
   * @return TreeModel*
   */
  virtual TreeModel *tree() { return _tree; }

  /**
   * @brief Check if a segment pass the geometric restrictions.
   *
   * @param segment The segment to be checked.
   * @return Returns true if the segment pass the geometric restrictions.
   * Returns false otherwise.
   */
  virtual bool pass(Segment segment) = 0;
};
#endif  //_CCOLAB_CCO_INTERFACE_GEOMETRIC_RESTRICTION_H
