/**
 * @file BloodViscosity.h
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

#ifndef _CCOLAB_TREE_INTERFACE_BLOODVISCOSITY_H
#define _CCOLAB_TREE_INTERFACE_BLOODVISCOSITY_H
class BloodViscosity {
 public:
  /**
   * @brief Construct a new Blood Viscosity object.
   * 
   */
  BloodViscosity() {}

  /**
   * @brief Destroy the Blood Viscosity object.
   * 
   */
  ~BloodViscosity() {}

  /**
   * @brief Evaluate the blood viscosity for the given segement.
   * 
   * @param segmentID The segment index.
   * @return The blood viscosity.
   */
  virtual double eval(int segmentID) = 0;
};
#endif //_CCOLAB_TREE_INTERFACE_BLOODVISCOSITY_H
