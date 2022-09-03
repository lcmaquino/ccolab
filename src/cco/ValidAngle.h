/**
 * @file ValidAngle.h
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
#include "interface/GeometricRestriction.h"

#ifndef _CCOLAB_CCO_VALIDANGLE_H
#define _CCOLAB_CCO_VALIDANGLE_H
class ValidAngle : public GeometricRestriction {
 private:
  /**
   * @brief Minimum angle value.
   * 
   */
  double _minumumAngle;

  /**
   * @brief Maximum angle value.
   * 
   */
  double _maximumAngle;

  /**
   * @brief Geometry object to do some geometric calculations.
   * 
   */
  Geometry *_geometry;

 public:
  /**
   * @brief Construct a new Valid Angle object.
   * 
   * @param tree The tree.
   * @param minumumAngle The minimum angle value.
   * @param maximumAngle The maximum angle value.
   */
  ValidAngle(TreeModel *tree, double minumumAngle, double maximumAngle);

  /**
   * @brief Destroy the Valid Angle object.
   * 
   */
  ~ValidAngle() {}

  /**
   * @brief Check if the segment descendents has valid angles.
   * 
   * @param segment The segment to be checked.
   * @return Returns true if the segment descendents has valid angles 
   * (ie, between the minimum and maximum angle values). Returns false
   * otherwise.
   */
  virtual bool pass(Segment segment);
};
#endif //_CCOLAB_CCO_VALIDANGLE_H
