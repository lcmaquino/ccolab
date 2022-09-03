/**
 * @file TargetFunction.h
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
 *
 */
#include "tree/interface/TreeModel.h"

#ifndef _CCOLAB_CCO_INTERFACE_TARGET_FUNCTION_CLASS_H
#define _CCOLAB_CCO_INTERFACE_TARGET_FUNCTION_CLASS_H
class TargetFunction {
 private:
  /**
   * @brief The tree.
   *
   */
  TreeModel *_tree;

 public:
  /**
   * @brief Construct a new Target Function object.
   *
   * @param tree The tree.
   */
  TargetFunction(TreeModel *tree) : _tree(tree) {}

  /**
   * @brief Destroy the Target Function object.
   *
   */
  ~TargetFunction() {}

  /**
   * @brief Evaluate the target function.
   *
   * @return The value of the target function.
   */
  virtual double eval() = 0;

  /**
   * @brief Set the Tree object.
   *
   * @param tree The tree.
   */
  virtual void setTree(TreeModel *tree) { _tree = tree; }

  /**
   * @brief Get the Tree objetc.
   *
   * @return TreeModel*
   */
  virtual TreeModel *tree() { return _tree; }
};
#endif  //_CCOLAB_CCO_INTERFACE_TARGET_FUNCTION_CLASS_H
