/**
 * @file TargetVolume.cc
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
#include "TargetVolume.h"

#include <cmath>
#include <iostream>
#include <string>

using std::cout;
using std::endl;

TargetVolume::TargetVolume(TreeModel *tree, double radiusExpoent,
                           double lengthExpoent)
    : TargetFunction(tree) {
  _radiusExpoent = radiusExpoent;
  _lengthExpoent = lengthExpoent;
}

double TargetVolume::eval() {
  int i;
  double volume = 0.0;
  for (i = tree()->begin(); i < tree()->end(); i++) {
    /*
        The classic Target Function is proportional to the real
        tree volume when _radiusExpoent = 2 and _lengthExpoent = 1.
    */
    volume += pow(tree()->radius(i), _radiusExpoent) *
              pow(tree()->length(i), _lengthExpoent);
  }

  return volume;
}
