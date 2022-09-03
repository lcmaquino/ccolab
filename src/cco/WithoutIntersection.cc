/**
 * @file WithoutIntersection.cc
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
#include "WithoutIntersection.h"

WithoutIntersection::WithoutIntersection(TreeModel *tree)
    : GeometricRestriction(tree) {
  _geometry = new Geometry(tree->dimension());
}

bool WithoutIntersection::pass(Segment segment) {
  /* Search for intersection. */
  int i, j;
  Segment checkSegments[3] = {
      segment,
      tree()->left(segment.ID()),
      tree()->right(segment.ID()),
  };

  for (i = tree()->begin(); i < tree()->end(); i++) {
    for (j = 0; j < 3; j++) {
      if (isRelative(*tree()->segment(i), checkSegments[j])) {
        continue;
      }

      if (_geometry->hasIntersection(
              tree()->proximalPoint(i), tree()->distalPoint(i),
              tree()->proximalPoint(checkSegments[j].ID()),
              tree()->distalPoint(checkSegments[j].ID()),
              tree()->radius(i) + tree()->radius(checkSegments[j].ID()))) {
        return false;
      }
    }
  }

  return true;
}

bool WithoutIntersection::isRelative(Segment segmentA,
                                     Segment segmentB) {
  return (segmentA.ID() == segmentB.ID() || segmentA.ID() == segmentB.left() ||
          segmentA.ID() == segmentB.right() || segmentA.ID() == segmentB.up() ||
          segmentB.ID() == segmentA.left() ||
          segmentB.ID() == segmentA.right() || segmentB.ID() == segmentA.up());
}
