/**
 * @file CubeFunction.h
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
#include <cmath>
#include <string>

#include "geometry/Geometry.h"
#include "interface/DomainFunction.h"

using std::cout;
using std::endl;

#ifndef _CCOLAB_DOMAIN_CUBEFUNCTION_H
#define _CCOLAB_DOMAIN_CUBEFUNCTION_H
class CubeFunction : public DomainFunction {
 private:
  /**
   * @brief The side length of the cube.
   *
   */
  double _length = 1.0;

  /**
   * @brief The Geometry object to do some geometric calculations.
   *
   */
  Geometry *_geometry;

 public:
  /**
   * @brief Construct a new Cube Function object.
   *
   * @param dimension The dimension of the points in the domain.
   * @param length The side length of the cube.
   */
  CubeFunction(int dimension, double length)
      : _length(length), DomainFunction(dimension) {
    _geometry = new Geometry(dimension);
  }

  /**
   * @brief Construct a new Cube Function object
   *
   * @param length The side length of the cube.
   */
  explicit CubeFunction(double length) : _length(length), DomainFunction() {
    _geometry = new Geometry(dimension());
  }

  /**
   * @brief Construct a new Cube Function object.
   *
   * @param dimension The dimension of the points in the domain.
   */
  explicit CubeFunction(int dimension) : DomainFunction(dimension) {
    _geometry = new Geometry(dimension);
  }

  /**
   * @brief Check if the segment with endpoints A and B is in the cube.
   *
   * @param pointA A given point in the cube.
   * @param pointB A given point in the cube.
   * @return Returns true if the segment with endpoints A and B is in the
   * cube. Returns false otherwise.
   */
  ~CubeFunction() {}
  virtual bool isIn(Point pointA, Point pointB);
};
#endif  //_CCOLAB_DOMAIN_CUBEFUNCTION_H
