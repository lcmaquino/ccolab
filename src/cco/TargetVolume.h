/**
 * @file TargetVolume.h
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
#include "interface/TargetFunction.h"

#ifndef _CCOLAB_CCO_TARGETVOLUME_H
#define _CCOLAB_CCO_TARGETVOLUME_H
class TargetVolume : public TargetFunction {
 private:
  /**
   * @brief The expoent for the segment radius on target function expression.
   * 
   */
  double _radiusExpoent;

  /**
   * @brief The expoent for the segment length on target function expression.
   * 
   */
  double _lengthExpoent;

 public:
  /**
   * @brief Construct a new Target Volume object.
   * 
   * @param tree The tree to evaluate the target function.
   * @param radiusExpoent The expoent for the segment radius on target function
   * expression.
   * @param lengthExpoent The expoent for the segment length on target function
   * expression.
   */
  TargetVolume(TreeModel *tree, double radiusExpoent = 2.0,
               double lengthExpoent = 1.0);

  /**
   * @brief Destroy the Target Volume object.
   * 
   */
  ~TargetVolume() {}

  /**
   * @brief Evaluate the target function.
   * 
   * @return The target function value. 
   */
  virtual double eval();
};
#endif //_CCOLAB_CCO_TARGETVOLUME_H
