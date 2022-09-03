/**
 * @file ConstantBifurcationExpoent.h
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
#include "interface/BifurcationExpoentLaw.h"

#ifndef _CCOLAB_TREE_CONSTANTBIFURCATIONEXPOENT_H
#define _CCOLAB_TREE_CONSTANTBIFURCATIONEXPOENT_H
class ConstantBifurcationExpoent : public BifurcationExpoentLaw {
 private:
  /**
   * @brief The bifurcation expoent. Defaults to 3.0.
   * 
   */
  double _expoent = 3.0;

 public:
  /**
   * @brief Construct a new Constant Bifurcation Expoent object,
   * 
   * @param expoent The bifurcation expoent.
   */
  explicit ConstantBifurcationExpoent(double expoent);

  /**
   * @brief Destroy the Constant Bifurcation Expoent object.
   * 
   */
  ~ConstantBifurcationExpoent(){}

  /**
   * @brief Evaluate the bifurction expoent for the segments in the given
   * bifurcation level.
   * 
   * @param segmentLevel The bifurcation level.
   * @return The bifurction expoent.
   */
  virtual double eval(int segmentLevel);
};
#endif //_CCOLAB_TREE_CONSTANTBIFURCATIONEXPOENT_H
