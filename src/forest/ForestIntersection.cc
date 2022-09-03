/**
 * @file ForestIntersection.cc
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
#include "ForestIntersection.h"

ForestIntersection::ForestIntersection(int numberOfTress, TreeModel **trees)
    : GeometricRestriction() {
  _numberOfTrees = numberOfTress;
  _trees = trees;
  _geometry = new Geometry(trees[0]->dimension());
}

void ForestIntersection::setTreeID(int value) { _treeID = value; }

bool ForestIntersection::pass(Segment segment) {
  /* Search for intersection. */
  int t, i, j;
  Segment checkSegments[3] = {
      segment,
      _trees[_treeID]->left(segment.ID()),
      _trees[_treeID]->right(segment.ID()),
  };

  for (t = 0; t < _numberOfTrees; t++) {
    if (t != _treeID) {
      setTree(_trees[t]);
      for (i = tree()->begin(); i < tree()->end(); i++) {
        for (j = 0; j < 3; j++) {
          if (_geometry->hasIntersection(
                  tree()->proximalPoint(i), tree()->distalPoint(i),
                  _trees[_treeID]->proximalPoint(checkSegments[j].ID()),
                  _trees[_treeID]->distalPoint(checkSegments[j].ID()),
                  tree()->radius(i) +
                      _trees[_treeID]->radius(checkSegments[j].ID()))) {
            return false;
          }
        }
      }
    }
  }

  return true;
}
