/**
 * @file Domain.h
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
#include "geometry/Point.h"

#ifndef _CCOLAB_DOMAIN_INTERFACE_DOMAIN_H
#define _CCOLAB_DOMAIN_INTERFACE_DOMAIN_H
class Domain {
 private:
  /**
   * @brief The dimension of the points in the domain.
   *
   */
  int _dimension = 3;

  /**
   * @brief The domain volume (in m^3).
   *
   */
  double _volume = 0.0;

 public:
  /**
   * @brief Construct a new Domain object.
   *
   */
  Domain() {}

  /**
   * @brief Construct a new Domain object.
   *
   * @param dimension The dimension of the points in the domain.
   */
  Domain(int dimension) : _dimension(dimension) {}

  /**
   * @brief Destroy the Domain object
   *
   */
  ~Domain() {}

  /**
   * @brief Get a point in the domain.
   *
   * @return A point in the domain.
   */
  virtual Point point() = 0;

  /**
   * @brief Get a seed in the domain.
   *
   * @param seedID seed index.
   * @return A seed in the domain.
   */
  virtual Point seed(int seedID) = 0;

  /**
   * @brief Check if the segment with endpoints A and B is in domain.
   *
   * @param pointA A given point in domain.
   * @param pointB A given point in domain.
   * @return Returns true if the segment with endpoints A and B is in domain.
   * Returns false otherwise.
   */
  virtual bool isIn(Point pointA, Point pointB) = 0;

  /**
   * @brief Get the total number of points in domain.
   *
   * @return The total number of points.
   */
  virtual int totalNumberOfPoints() = 0;

  /**
   * @brief Get the number of seeds.
   *
   * @return The number of seeds.
   */
  virtual int numberOfSeeds() = 0;

  /**
   * @brief Get the dimension of the points in domain.
   *
   * @return The dimension of the points in domain.
   */
  virtual int dimension() { return _dimension; }

  /**
   * @brief Get the domain volume (in m^3).
   *
   * @return The domain volume (in m^3).
   */
  virtual double volume() { return _volume; }

  /**
   * @brief Set the domain volume (in m^3).
   *
   * @param volume The domain volume (in m^3).
   */
  virtual void setVolume(double volume) { _volume = volume; }

  /**
   * @brief Set the dimension of the points in domain.
   *
   * @param The dimension of the points in domain.
   */
  virtual void setDimension(int dimension) { _dimension = dimension; }

  /**
   * @brief Check if the domain has available point to be visited.
   *
   * @return Returns true if the domain has available point to be visited.
   * Returns false otherwise.
   */
  virtual bool hasAvailablePoint() = 0;

  /**
   * @brief Reset the domain in a way that its points could be visited again.
   *
   */
  virtual void reset() = 0;
};
#endif  //_CCOLAB_DOMAIN_INTERFACE_DOMAIN_H