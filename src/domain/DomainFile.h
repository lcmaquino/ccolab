/**
 * @file DomainFile.h
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

#include "TautologyFunction.h"
#include "interface/Domain.h"
#include "interface/DomainFunction.h"

using std::string;
using std::invalid_argument;
using std::ofstream;
using std::ifstream;
using std::stringstream;
using std::istringstream;
using std::cout;
using std::endl;

#ifndef _CCOLAB_DOMAIN_DOMAINFILE_H
#define _CCOLAB_DOMAIN_DOMAINFILE_H
class DomainFile : public Domain {
 private:
  /**
   * @brief The domain seeds.
   *
   */
  double *_seeds;

  /**
   * @brief The domain points.
   *
   */
  double *_points;

  /**
   * @brief The index of the current point visited in domain.
   *
   */
  int _currentPoint = 0;

  /**
   * @brief Total number of points in the domain.
   *
   */
  int _totalNumberOfPoints = 0;

  /**
   * @brief Total number of seeds in the domain.
   *
   */
  int _numberOfSeeds = 0;

  /**
   * @brief Version of the VTK domain file.
   *
   */
  float _version;

  /**
   * @brief Title of the VTK domain file.
   *
   */
  string _title;

  /**
   * @brief Data type index of the VTK domain file.
   *
   */
  int _dataType;

  /**
   * @brief Data type keyword of the VTK domain file.
   *
   */
  string const _dataTypeKeyword[2] = {"ASCII", "BINARY"};

  /**
   * @brief Dataset type keyword of the VTK domain file.
   *
   */
  string const _datasetTypeKeyword = "FIELD";

  /**
   * @brief Get the coordinate (x, y or z) of the point with index pointID.
   *
   * @param pointID The point index.
   * @param coordinate The point coordinate (0 for x, 1 for y and 2 for z).
   * @return The coordinate value.
   */
  double pointCoordinate(int pointID, int coordinate);

  /**
   * @brief Get the coordinate (x, y or z) of the seed with index pointID.
   *
   * @param pointID The seed index.
   * @param coordinate The seed coordinate (0 for x, 1 for y and 2 for z).
   * @return The coordinate value.
   */
  double seedCoordinate(int seedID, int coordinate);

  /**
   * @brief The domain function.
   *
   */
  DomainFunction *_domainFunction;

 public:
  /**
   * @brief Construct a new Domain File object.
   * 
   * @param filename The filename.
   */
  DomainFile(string filename);
  
  /**
   * @brief Construct a new Domain File object.
   * 
   * @param filename The filename.
   * @param domainFunction The domain function.
   */
  DomainFile(string filename, DomainFunction *domainFunction);

  /**
   * @brief Construct a new Domain File object.
   * 
   * @param filename The file name.
   * @param totalNumberOfPoints The total number of points.
   * @param domainFunction The domain function.
   */
  DomainFile(string filename, int totalNumberOfPoints,
             DomainFunction *domainFunction);

  /**
   * @brief Destroy the Domain File object.
   * 
   */
  virtual ~DomainFile();

  /**
   * @brief Get a point in the domain.
   * 
   * @return A point in the domain.
   */
  virtual Point point();

  /**
   * @brief Get a seed in the domain.
   * 
   * @param seedID The seed index.
   * @return A seed in the domain.
   */
  virtual Point seed(int seedID);

  /**
   * @brief Check if the segment with endpoints A and B is in domain.
   * 
   * @param pointA A given point in domain.
   * @param pointB A given point in domain.
   * @return Returns true if the segment with endpoints A and B is in domain.
   * Returns false otherwise.
   */
  virtual bool isIn(Point pointA, Point pointB);

  /**
   * @brief Get the total number of points in domain.
   * 
   * @return The total number of points. 
   */
  virtual int totalNumberOfPoints();

  /**
   * @brief Get the number of seeds.
   * 
   * @return The number of seeds.
   */
  virtual int numberOfSeeds();

  /**
   * @brief Check if the domain has available point to be visited.
   * 
   * @return Returns true if the domain has available point to be visited.
   * Returns false otherwise.
   */
  virtual bool hasAvailablePoint();

  /**
   * @brief Reset the domain in a way that its points could be visited again.
   * 
   */
  virtual void reset();

  /**
   * @brief Set the domain function.
   * 
   */
  void setDomainFunction(DomainFunction *domainFunction);

  /**
   * @brief Get the domain function.
   * 
   * @return The domain function.
   */
  DomainFunction *domainFunction();

  /**
   * @brief Open the domain VTK file.
   * 
   * @param filename The filename.
   * @return Returns true if the file could be opened and has the correct VTK
   * format. Returs false otherwise.
   */
  bool open(string filename);

  /**
   * @brief Print the DomainFile object variables for debugging.
   * 
   */
  void print();
};
#endif  //_CCOLAB_DOMAIN_DOMAINFILE_H
