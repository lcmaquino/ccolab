/**
 * @file ClassicDistanceCriterion.h
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
#include <iostream>

#include "geometry/Geometry.h"
#include "interface/DistanceCriterion.h"
#include "tree/interface/TreeModel.h"

#ifndef _CCOLAB_CCO_CLASSICDISTANCECRITERION_H
#define _CCOLAB_CCO_CLASSICDISTANCECRITERION_H
class ClassicDistanceCriterion : public DistanceCriterion {
 private:
  /**
   * @brief Value of the minimum criterion distance.
   * 
   */
  double _minimumCriterionDistance;

  /**
   * @brief Peforme some geometry calculations. 
   * 
   */
  Geometry *_geometry;

 public:
  /**
   * @brief Construct a new Classic Distance Criterion object
   * 
   */
  ClassicDistanceCriterion();

  /**
   * @brief Construct a new Classic Distance Criterion object
   * 
   * @param tree 
   */
  explicit ClassicDistanceCriterion(TreeModel *tree);

  /**
   * @brief Destroy the Classic Distance Criterion object
   * 
   */
  ~ClassicDistanceCriterion() {}

  /**
   * @brief Evaluate the distance from point to tree.
   * 
   * @param point The point to evaluate the distance to tree.
   * @return Returns true if the distance from point to tree is greater
   * than the minimum distance. Returns false otherwise. 
   */
  virtual bool eval(Point point);

  /**
   * @brief Relax the minimum distance criterion.
   * 
   * @param factor The factor in (0, 1) to multiple by the minimum distance.
   * @return Returns the new minimum distance.
   */
  virtual double relax(double factor = 0.9);

  /**
   * @brief Update the number of terminals on the tree.
   * 
   * @param currentNumberOfTerminals Number of terminals on the tree.
   * @return Returns the new minimum distance. 
   */
  virtual double update(int currentNumberOfTerminals);

  /**
   * @brief Get the minimum distance.
   * 
   * @return Returns the minimum distance value.
   */
  virtual double minimumDistanceCriterion();
};
#endif //_CCOLAB_CCO_CLASSICDISTANCECRITERION_H
