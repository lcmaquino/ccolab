/**
 * @file SimpleOptimization.h
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

#include "BifurcationSymmetry.h"
#include "TargetVolume.h"
#include "ValidSegment.h"
#include "geometry/Geometry.h"
#include "interface/GeometricOptimization.h"
using std::cout;
using std::endl;

#ifndef _CCOLAB_CCO_SIMPLEOPTIMIZATION_H
#define _CCOLAB_CCO_SIMPLEOPTIMIZATION_H
class SimpleOptimization : public GeometricOptimization {
 private:
  /**
   * @brief The target function to be evaluated.
   * 
   */
  TargetFunction *_targetFunction;

  /**
   * @brief Geometry object to do some geometric calculations.
   * 
   */
  Geometry *_geometry;

  /**
   * @brief The number of subdivisions of the interval where to evaluate the
   * target function.
   * 
   */
  int _intervalDivision = 5;

  /**
   * @brief The dregree of symmetry on some bifurcation is the ratio between
   * the minimum and maximum radius of the descendent segments.
   * 
   */
  double _degreeOfSymmetry = 0.0;

 public:
  /**
   * @brief Construct a new Simple Optimization object.
   * 
   * @param domain The domain where the tree grows.
   * @param tree The tree.
   * @param targetFunction The target function to be evaluated. 
   * @param intervalDivision The number of interval subdivisions for evaluate.
   */
  SimpleOptimization(Domain *domain, TreeModel *tree,
                     TargetFunction *targetFunction, int intervalDivision);

  /**
   * @brief Construct a new Simple Optimization object.
   * 
   * @param domain The domain where the tree grows.
   * @param tree The tree.
   * @param targetFunction The target function to be evaluated. 
   * @param intervalDivision The number of interval subdivisions for evaluate.
   * @param degreeOfSymmetry The minimum degree of symmetry allowed on 
   * bifurcations.
   */
  SimpleOptimization(Domain *domain, TreeModel *tree,
                     TargetFunction *targetFunction, int intervalDivision,
                     double degreeOfSymmetry);
  /**
   * @brief Destroy the Simple Optimization object.
   * 
   */
  ~SimpleOptimization() {}

  /**
   * @brief Get the connection for the given segment.
   * 
   * @param segment The new segment connected to the tree.
   * @return Connection The information about the connection for the given
   * segment.
   */
  virtual Connection bifurcation(Segment segment);

  /**
   * @brief Set the number of interval subdivisions.
   * 
   * @param value The number of interval subdivisions.
   */
  void setIntervalDivision(int value);
};
#endif  //_CCOLAB_CCO_SIMPLEOPTIMIZATION_H
