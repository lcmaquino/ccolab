/**
 * @file CompetingOptimizedArterialTrees.h
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
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

#include "domain/DomainVoronoi.h"
#include "interface/Forest.h"

using std::cout;
using std::endl;

#ifndef _CCOLAB_FOREST_COMPETINGOPTMIZEDARTERIALTREES_H
#define _CCOLAB_FOREST_COMPETINGOPTMIZEDARTERIALTREES_H
class CompetingOptimizedArterialTrees : public Forest {
 private:
  /**
   * @brief The DomainVoronoi object to subdivide the domain.
   * 
   */
  DomainVoronoi *_domainVoronoi;

  /**
   * @brief The percentage of the target flow to be attained at the first
   * stage.
   * 
   */
  double _firstStage;

 public:
  /**
   * @brief Construct a new Competing Optimized Arterial Trees object.
   * 
   * @param domain The domain.
   * @param trees The vector of trees.
   * @param numberOfTrees The number of trees.
   * @param numberOfTerminals The number of terminals.
   * @param firstStage The percentage of the target flow to be attained at
   * the first stage.
   * @param targetPerfusionFlow The vector of target perfusion flows.
   * @param radiusExpoent The expoent for the segment radius on target
   * function expression. 
   * @param lengthExpoent The expoent for the segment length on target
   * function expression.
   */
  CompetingOptimizedArterialTrees(Domain *domain, TreeModel **trees,
                                  int numberOfTrees, int numberOfTerminals,
                                  double firstStage,
                                  double *targetPerfusionFlow,
                                  double radiusExpoent, double lengthExpoent);

  /**
   * @brief Destroy the Competing Optimized Arterial Trees object.
   * 
   */
  ~CompetingOptimizedArterialTrees() {}

  /**
   * @brief Get the DomainVoronoi object used to subdivide the domain.
   * 
   * @return The DomainVoronoi obect.
   */
  DomainVoronoi *domainVoronoi() { return _domainVoronoi; }

  /**
   * @brief Grow the root segment for each tree on the forest.
   * 
   */
  virtual void growRoot();

  /**
   * @brief Grow the segments for each tree on the forest.
   * 
   */
  virtual void grow();
};
#endif //_CCOLAB_FOREST_COMPETINGOPTMIZEDARTERIALTREES_H
