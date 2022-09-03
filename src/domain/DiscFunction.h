/**
 * @file DiscFunction.h
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
#include <iostream>
#include <string>

#include "geometry/Geometry.h"
#include "interface/DomainFunction.h"
using std::cout;
using std::endl;

#ifndef _CCOLAB_DOMAIN_DISCFUNCTION_H
#define _CCOLAB_DOMAIN_DISCFUNCTION_H
class DiscFunction : public DomainFunction {
 private:
  /**
   * @brief The disc inner radius.
   * 
   */
  double _innerRadius = 0.5;
  
  /**
   * @brief The disc out radius.
   * 
   */
  double _outRadius = 1.0;

  /**
   * @brief The Geomtry object to do some geometric calculations.
   * 
   */
  Geometry *_geometry;

 public:
  /**
   * @brief Construct a new Disc Function object
   * 
   * @param dimension The dimension of the points in the domain.
   * @param innerRadius The disc inner radius.
   * @param outRadius The disc out radius.
   */
  DiscFunction(int dimension, double innerRadius, double outRadius)
      : _innerRadius(innerRadius), _outRadius(outRadius), DomainFunction(dimension) {
    _geometry = new Geometry(dimension);
  }

  /**
   * @brief Construct a new Disc Function object.
   * 
   * @param innerRadius The disc inner radius.
   * @param outRadius The disc out radius.
   */
  DiscFunction(double innerRadius, double outRadius)
      : _innerRadius(innerRadius), _outRadius(outRadius), DomainFunction() {
    _geometry = new Geometry(dimension());
  }

  /**
   * @brief Construct a new Disc Function object.
   * 
   * @param dimension The dimension of the points in the domain.
   */
  explicit DiscFunction(int dimension) : DomainFunction(dimension) {
    _geometry = new Geometry(dimension);
  }

  /**
   * @brief Destroy the Disc Function object.
   * 
   */
  ~DiscFunction() {}

  /**
   * @brief Check if the segment with endpoints A and B is in the disc.
   *
   * @param pointA A given point in the disc.
   * @param pointB A given point in the disc.
   * @return Returns true if the segment with endpoints A and B is in the
   * disc. Returns false otherwise.
   */
  virtual bool isIn(Point pointA, Point pointB);
};
#endif //_CCOLAB_DOMAIN_DISCFUNCTION_H
