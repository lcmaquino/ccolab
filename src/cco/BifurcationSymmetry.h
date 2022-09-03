/**
 * @file BifurcationSymmetry.h
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
#include "interface/GeometricRestriction.h"

#ifndef _CCOLAB_CCO_BIFURCATION_SYMMETRY_H
#define _CCOLAB_CCO_BIFURCATION_SYMMETRY_H
/**
 * @brief Check the bifurcation symmetry.
 *
 */
class BifurcationSymmetry : public GeometricRestriction {
 private:
  /**
   * @brief Bifurcation symmetry index.
   *
   */
  double _degreeOfSymmetry;

 public:
  /**
   * @brief Construct a new Bifurcation Symmetry object
   *
   * @param tree
   * @param degreeOfSymmetry
   */
  BifurcationSymmetry(TreeModel *tree, double degreeOfSymmetry);

  /**
   * @brief Destroy the Bifurcation Symmetry object
   *
   */
  ~BifurcationSymmetry() {}

  /**
   * @brief Check if a segment pass the bifurcation symmetry restriction.
   *
   * @param segment The segment to be checked.
   * @return Returns true if the segment pass the bifurcation symmetry
   * restriction or false otherwise.
   */
  virtual bool pass(Segment segment);
};
#endif  //_CCOLAB_CCO_BIFURCATION_SYMMETRY_H
