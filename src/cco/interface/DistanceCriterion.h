/**
 * @file DistanceCriterion.h
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
 * @brief Define the distance criterion interface.
 * @version 1.0
 * @date 2022-05-18
 *
 */

#include <string>

#include "tree/interface/TreeModel.h"

using std::cout;
using std::endl;

#ifndef _CCOLAB_CCO_INTERFACE_DISTANCECRITERION_H_
#define _CCOLAB_CCO_INTERFACE_DISTANCECRITERION_H_
/**
 * @brief
 *
 */
class DistanceCriterion {
 private:
  /**
   * @brief The tree to evaluate the distance criterion.
   *
   */
  TreeModel *_tree;

  /**
   * @brief The distance criterion value.
   *
   */
  double _minimumCriterionDistance;

 public:
  /**
   * @brief Construct a new Distance Criterion object
   *
   */
  DistanceCriterion() {}

  /**
   * @brief Construct a new Distance Criterion object
   *
   * @param tree The tree to evaluate distance.
   */
  explicit DistanceCriterion(TreeModel *tree) : _tree(tree) {}

  /**
   * @brief Destroy the Distance Criterion object
   *
   */
  ~DistanceCriterion() {}

  /**
   * @brief Set the Tree object
   *
   * @param tree The tree to be set.
   */
  virtual void setTree(TreeModel *tree) { _tree = tree; }

  /**
   * @brief Get the tree.
   *
   * @return TreeModel* the tree being evaluated.
   */
  virtual TreeModel *tree() { return _tree; }

  /**
   * @brief Evaluate if a point follows the distance criterion.
   *
   * @param point The point to evaluate.
   * @return Returns true if the distance between the point and the tree
   * is higher than distance criterion. Returns false otherwise.
   */
  virtual bool eval(Point point) = 0;

  /**
   * @brief The factor to relax the distance criterion.
   *
   * @param factor The factor in (0.0, 1.0] to apply to distance criterion.
   * @return Returns the factor times distance criterion.
   */
  virtual double relax(double factor = 0.9) = 0;

  /**
   * @brief Updates the distance criterion.
   *
   * @param numberOfTerminals The tree number of terminals
   * @return The updated distance criterion.
   */
  virtual double update(int numberOfTerminals) = 0;

  /**
   * @brief Get the minimum distance criterion.
   *
   * @return The distance criterion value.
   */
  virtual double minimumDistanceCriterion() = 0;
};
#endif  //_CCOLAB_CCO_INTERFACE_DISTANCECRITERION_H_
