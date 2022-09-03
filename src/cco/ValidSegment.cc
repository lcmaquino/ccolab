/**
 * @file ValidSegment.cc
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
#include "ValidSegment.h"

ValidSegment::ValidSegment(TreeModel *tree) : GeometricRestriction(tree) { ; }

bool ValidSegment::pass(Segment segment) {
  /* The segment length sould be at least twice the radius. */
  double parentRadius = tree()->radius(segment.ID()),
         parentLength = tree()->length(segment.ID()),
         leftLength = tree()->length(segment.left()),
         rightLength = tree()->length(segment.right());
  return (parentLength >= 2 * parentRadius &&
          leftLength >= 2 * parentRadius * segment.bifurcationRatioLeft() &&
          rightLength >= 2 * parentRadius * segment.bifurcationRatioRight());
}
