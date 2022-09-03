/**
 * @file ClassicDistanceCriterion.cc
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
#include "ClassicDistanceCriterion.h"

ClassicDistanceCriterion::ClassicDistanceCriterion() : DistanceCriterion() { ; }

ClassicDistanceCriterion::ClassicDistanceCriterion(TreeModel *tree)
    : DistanceCriterion(tree) {
  _geometry = new Geometry(tree->dimension());

  /* Minimum distance criterion */
  _minimumCriterionDistance =
      pow(tree->perfusionVolume(), 1.0 / tree->dimension());
}

bool ClassicDistanceCriterion::eval(Point point) {
  int i;
  double d;

  for (i = tree()->begin(); i < tree()->end(); i++) {
    d = _geometry->distanceFromSegment(point, tree()->proximalPoint(i),
                                       tree()->distalPoint(i));
    if (d < _minimumCriterionDistance) {
      return false;
    }
  }

  return true;
}

double ClassicDistanceCriterion::relax(double factor) {
  _minimumCriterionDistance *= factor;

  return _minimumCriterionDistance;
}

double ClassicDistanceCriterion::minimumDistanceCriterion() {
  return _minimumCriterionDistance;
}

double ClassicDistanceCriterion::update(int currentNumberOfTerminals) {
  _minimumCriterionDistance =
      pow(tree()->perfusionVolume() / currentNumberOfTerminals,
          1.0 / tree()->dimension());

  return _minimumCriterionDistance;
}
