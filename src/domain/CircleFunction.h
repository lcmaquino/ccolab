/**
 * @file CircleFunction.h
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

#ifndef _CCOLAB_DOMAIN_CIRCLEFUNCTION_H
#define _CCOLAB_DOMAIN_CIRCLEFUNCTION_H
class CircleFunction : public DomainFunction {
 private:
  /**
   * @brief The circle (or sphere) radius.
   * 
   */
  double _radius = 1.0;

  /**
   * @brief The Geometry Object to do some geometric calculations.
   * 
   */
  Geometry *_geometry;

 public:
  /**
   * @brief Construct a new Circle Function object.
   * 
   * @param dimension The dimension of the points in the domain.
   * @param radius The radius of the circle (or sphere).
   */
  CircleFunction(int dimension, double radius)
      : _radius(radius), DomainFunction(dimension) {
    _geometry = new Geometry(dimension);
  }

  /**
   * @brief Construct a new Circle Function object.
   * 
   * @param radius The radius of the circle (or sphere).
   */
  explicit CircleFunction(double radius) : _radius(radius), DomainFunction() {
    _geometry = new Geometry(dimension());
  }

  /**
   * @brief Construct a new Circle Function object
   * 
   * @param dimension The dimension of the points in the domain.
   */
  explicit CircleFunction(int dimension) : DomainFunction(dimension) {
    _geometry = new Geometry(dimension);
  }

  /**
   * @brief Destroy the Circle Function object.
   * 
   */
  ~CircleFunction() {}

  /**
   * @brief Check if the segment with endpoints A and B is in the circle
   * (or sphere).
   * 
   * @param pointA A given point in the circule (or sphere).
   * @param pointB A given point in the circule (or sphere).
   * @return Returns true if the segment with endpoints A and B is in the
   * circle (or sphere). Returns false otherwise.
   */
  virtual bool isIn(Point pointA, Point pointB);
};
#endif //_CCOLAB_DOMAIN_CIRCLEFUNCTION_H
