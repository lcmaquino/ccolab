/**
 * @file DomainFunction.h
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
#include <iostream>

#include "geometry/Point.h"
using std::string, std::cout, std::endl;

#ifndef _CCOLAB_DOMAIN_INTERFACE_DOMAINFUNCTION_H
#define _CCOLAB_DOMAIN_INTERFACE_DOMAINFUNCTION_H
class DomainFunction {
 private:
  /**
   * @brief The dimension of the points in the domain.
   * 
   */
  int _dimension = 3;

 public:
  /**
   * @brief Construct a new Domain Function object.
   * 
   */
  DomainFunction() {}

  /**
   * @brief Construct a new Domain Function object.
   * 
   * @param dimension The dimension of the points in the domain.
   */
  DomainFunction(int dimension) : _dimension(dimension) {}

  /**
   * @brief Destroy the Domain Function object.
   * 
   */
  ~DomainFunction() {}

  /**
   * @brief Get the dimension of the points in the domain.
   * 
   * @return The dimension of the points in the domain. 
   */
  virtual int dimension() { return _dimension; }

 /**
  * @brief Set the dimension of the points in the domain.
  * 
  * @param value The dimension.
  */
  virtual void setDimension(int value) { _dimension = value; }

  /**
   * @brief Check if the segment with endpoints A and B is in domain.
   * 
   * @param pointA A given point in domain.
   * @param pointB A given point in domain.
   * @return Returns true if the segment with endpoints A and B is in domain.
   * Returns false otherwise.
   */
  virtual bool isIn(Point pointA, Point pointB) = 0;
};
#endif  //_CCOLAB_DOMAIN_INTERFACE_DOMAINFUNCTION_H