/**
 * @file DomainSubsets.h
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

#include "Domain.h"
#include "DomainFile.h"
#include "geometry/Geometry.h"
#include "progress/Progress.h"

using std::string, std::cout, std::endl;

#ifndef _CCOLAB_DOMAIN_INTERFACE_DOMAINSUBSETS_H
#define _CCOLAB_DOMAIN_INTERFACE_DOMAINSUBSETS_H
class DomainSubsets {
 private:
  /**
   * @brief The domain.
   * 
   */
  Domain *_domain;

  /**
   * @brief The number of subsets in the domain.
   * 
   */
  int _numberOfSubsets;

 public:
  /**
   * @brief Construct a new Domain Subsets object.
   * 
   * @param domain The domain.
   * @param numberOfSubsets The number of subsets in the domain.
   */
  DomainSubsets(Domain *domain, int numberOfSubsets)
      : _domain(domain), _numberOfSubsets(numberOfSubsets){}

  /**
   * @brief Destroy the Domain Subsets object.
   * 
   */
  ~DomainSubsets(){}

  /**
   * @brief Get the domain.
   * 
   * @return The domain. 
   */
  Domain *domain() { return _domain; }

  /**
   * @brief Set the domain.
   * 
   * @param domain The domain.
   */
  void setDomain(Domain *domain) { _domain = domain; }

  /**
   * @brief Get the number of subsets in the domain.
   * 
   * @return The number of subsets. 
   */
  int numberOfSubsets() { return _numberOfSubsets; }

  /**
   * @brief Set the number of subsets in the domain.
   * 
   * @param value The number of subsets.
   */
  void setNumberOfSubsets(int value) { _numberOfSubsets = value; }

  /**
   * @brief Get the subset where a given point is.
   * 
   * @param point The given point.
   * @return The subset where the given point is.
   */
  virtual int inSubset(Point point) = 0;
};
#endif //_CCOLAB_DOMAIN_INTERFACE_DOMAINSUBSETS_H