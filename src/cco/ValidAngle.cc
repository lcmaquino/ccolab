/**
 * @file ValidAngle.cc
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
#include "ValidAngle.h"

ValidAngle::ValidAngle(TreeModel *tree, double minumumAngle,
                       double maximumAngle)
    : GeometricRestriction(tree) {
  _minumumAngle = minumumAngle;
  _maximumAngle = maximumAngle;
  _geometry = new Geometry(tree->dimension());
}

bool ValidAngle::pass(Segment segment) {
  double segmentAngle;
  Point leftSegmentVector, rightSegmentVector;
  bool passTheRestriciton = false;

  /* Compute the current angle defined by the segment descendents. */
  leftSegmentVector =
      _geometry->subtract(tree()->left(segment.ID()).point(), segment.point());
  rightSegmentVector =
      _geometry->subtract(tree()->right(segment.ID()).point(), segment.point());
  segmentAngle = _geometry->angle(leftSegmentVector, rightSegmentVector);

  /* Check if the angle is between minimum and maximum angles. */
  if (_minumumAngle < segmentAngle && segmentAngle < _maximumAngle) {
    passTheRestriciton = true;
  }

  return passTheRestriciton;
}

