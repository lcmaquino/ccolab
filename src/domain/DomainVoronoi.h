/**
 * @file DomainVoronoi.h
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
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "interface/DomainFunction.h"
#include "interface/DomainSubsets.h"
#include "tree/interface/TreeModel.h"
using std::ofstream;
using std::cout;
using std::endl;

#ifndef _CCOLAB_DOMAIN_DOMAINVORONOI_H
#define _CCOLAB_DOMAIN_DOMAINVORONOI_H
class DomainVoronoi : public DomainSubsets {
 private:
  /**
   * @brief The vector of trees.
   *
   */
  TreeModel **_trees;

  /**
   * @brief The Geometry object to do some geometric calculations.
   *
   */
  Geometry *_geometry;

  /**
   * @brief The vector of points.
   *
   */
  Point **_points;

  /**
   * @brief The vector of points ID.
   *
   */
  int *_pointTreeID;

  /**
   * @brief The total number of points.
   *
   */
  int _totalPoints;

  /**
   * @brief The current number of points.
   *
   */
  int _currentNumberOfPoints;

  /**
   * @brief The vector of target perfusion flow.
   *
   */
  double *_targetPerfusionFlow;

  /**
   * @brief The territory weigth.
   *
   */
  double _territoryWeigth;

  /**
   * @brief Extract the distal point of each segment of the trees.
   *
   */
  void extractReferencePoints();

  /**
   * @brief Calculate the distances between the given point and
   * the trees on the forest.
   * 
   * @param point The given point
   * @return vector of the distances between the given point and
   * the trees on the forest.
   */
  double *distanceFromTrees(Point point);

 public:
  /**
   * @brief Construct a new Domain Voronoi object.
   * 
   * @param domain The domain.
   * @param trees The vector of trees.
   * @param targetPerfusionFlow The vector of target perfusion flow.
   * @param numberOfTrees The number of trees.
   * @param territoryWeigth The territory weigth in (0, 1].
   */
  DomainVoronoi(Domain *domain, TreeModel **trees, double *targetPerfusionFlow,
                int numberOfTrees, double territoryWeigth);

  /**
   * @brief Destroy the Domain Voronoi object.
   * 
   */
  ~DomainVoronoi();

  /**
   * @brief Set the Trees object.
   * 
   * @param trees Vector of trees.
   */
  void setTrees(TreeModel **trees);

  /**
   * @brief Write the VTK DataFile with the points in domain and its
   * associated subset.
   * 
   * @param filename The filename.
   * @param unit The unit of the metric system. The value 1.0 means meters,
   * 100.0 means centimeters and 1000.0 means milimeters.
   */
  void diagram(string filename, double unit = 1.0);

  /**
   * @brief Write the comma-separated values (CSV) file for the 
   * subset territory. It uses one space as delimiter for columns.
   * 
   * Each row has the tree index (in first column "SUBSET") and
   * the tree territory value (in second column "TERRITORY"). The 
   * tree territory value is the percentage of points in domain associated
   * with the tree.
   * 
   * @param filename The filename.
   */
  void territory(string filename);

  /**
   * @brief Write the comma-separated values (CSV) file for the 
   * reference points. It uses one space as delimiter for columns.
   * 
   * Each row has the x, y, and z coordinate (respectively in columns "x",
   * "y", and "z") and the subset index (in column "SUBSET").
   * 
   * @param filename The filename.
   * @param unit The unit of the metric system. The value 1.0 means meters,
   * 100.0 means centimeters and 1000.0 means milimeters.
   */
  void referencePoints(string filename, double unit = 1.0); 

  /**
   * @brief Set the territory weigth.
   * 
   * @param territoryWeigth The territory weigth.
   */
  void setTerritoryWeigth(double territoryWeigth);

  /**
   * @brief Get the territory weigth.
   * 
   * @return The territory weigth.
   */
  double territoryWeigth();

  /**
   * @brief Get the subset index associated with a given point.
   * 
   * @param point The given point.
   * @return The subset index.
   */
  virtual int inSubset(Point point);
};
#endif  //_CCOLAB_DOMAIN_DOMAINVORONOI_H
