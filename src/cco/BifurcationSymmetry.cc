/**
 * @file BifurcationSymmetry.cc
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
#include "BifurcationSymmetry.h"

BifurcationSymmetry::BifurcationSymmetry(TreeModel *tree,
                                         double degreeOfSymmetry)
    : GeometricRestriction(tree) {
  _degreeOfSymmetry = degreeOfSymmetry;
}

bool BifurcationSymmetry::pass(Segment segment) {
  double degreeOfSymmetry, leftRadius = tree()->radius(segment.left()),
                           rightRadius = tree()->radius(segment.right());

  degreeOfSymmetry = leftRadius <= rightRadius ? leftRadius / rightRadius
                                               : rightRadius / leftRadius;

  /* Check if the degree of symmetry is more than _degreeOfSymmetry */
  return (degreeOfSymmetry >= _degreeOfSymmetry);
}
