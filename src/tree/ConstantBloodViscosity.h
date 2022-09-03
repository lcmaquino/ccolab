/**
 * @file ConstantBloodViscosity.h
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
#include "interface/BloodViscosity.h"

#ifndef _CCOLAB_TREE_CONSTANTBLOODVISCOSITY_H
#define _CCOLAB_TREE_CONSTANTBLOODVISCOSITY_H
class ConstantBloodViscosity : public BloodViscosity {
 private:
  /**
   * @brief The blood viscosity. Defaults to 0.0036 (N/m^2)·s (ie, 3.6 cP).
   * 
   */
  double _bloodViscosity = 0.0036;

 public:
  /**
   * @brief Construct a new Constant Blood Viscosity object.
   * 
   */
  ConstantBloodViscosity() : BloodViscosity(){}

  /**
   * @brief Construct a new Constant Blood Viscosity object.
   * 
   * @param bloodViscosity The blood viscosity.
   */
  explicit ConstantBloodViscosity(double bloodViscosity);

  /**
   * @brief Destroy the Constant Blood Viscosity object.
   * 
   */
  ~ConstantBloodViscosity() {}

  /**
   * @brief Evaluate the blood viscosity for the given segment.
   * 
   * @param segmentID The index of the segment.
   * @return The blood viscosity.
   */
  virtual double eval(int segmentID);
};
#endif //_CCOLAB_TREE_CONSTANTBLOODVISCOSITY_H
