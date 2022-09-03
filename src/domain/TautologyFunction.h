/**
 * @file TautologyFunction.h
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
#include <string>

#include "interface/DomainFunction.h"

using std::cout;
using std::endl;

#ifndef _CCOLAB_DOMAIN_TAUTOLOGYFUNCTION_H
#define _CCOLAB_DOMAIN_TAUTOLOGYFUNCTION_H
class TautologyFunction : public DomainFunction {
 public:
  /**
   * @brief Construct a new Tautology Function object.
   * 
   */
  TautologyFunction() : DomainFunction() {}

  /**
   * @brief Construct a new Tautology Function object.
   * 
   * @param dimension The dimension of the points in domain.
   */
  explicit TautologyFunction(int dimension) : DomainFunction(dimension) {}

  /**
   * @brief Destroy the Tautology Function object.
   * 
   */
  ~TautologyFunction() {}

  /**
   * @brief Check if the segment with endpoints A and B is in domain.
   * 
   * @param pointA A given point in domain.
   * @param pointB A given point in domain.
   * @return Always returns true because the given domain is being
   * considerated as convex.
   */
  virtual bool isIn(Point pointA, Point pointB) { return true; }
};
#endif  //_CCOLAB_DOMAIN_TAUTOLOGYFUNCTION_H
