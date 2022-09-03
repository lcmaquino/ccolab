/**
 * @file CubeFunction.cc
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
#include "CubeFunction.h"

bool CubeFunction::isIn(Point pointA, Point pointB) {
  return (0.0 <= pointA.x() && pointA.x() <= _length) &&
         (0.0 <= pointA.y() && pointA.y() <= _length) &&
         (0.0 <= pointA.z() && pointA.z() <= _length) &&
         (0.0 <= pointB.x() && pointB.x() <= _length) &&
         (0.0 <= pointB.y() && pointB.y() <= _length) &&
         (0.0 <= pointB.z() && pointB.z() <= _length);
}
