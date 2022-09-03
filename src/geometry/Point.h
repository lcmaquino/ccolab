/**
 * @file Point.h
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
#ifndef _CCOLAB_GEOMETRY_POINT_H
#define _CCOLAB_GEOMETRY_POINT_H
class Point {
 private:
  /**
   * @brief The point dimesion.
   * 
   */
  int _dimension;

  /**
   * @brief The x coordinate.
   * 
   */
  double _x = 0.0;

  /**
   * @brief The y coordinate.
   * 
   */
  double _y = 0.0;

  /**
   * @brief The z coordinate.
   * 
   */
  double _z = 0.0;

 public:
  /**
   * @brief Construct a new Point object.
   * 
   */
  Point();

  /**
   * @brief Construct a new Point object.
   * 
   * @param dimension The point dimension.
   */
  explicit Point(int dimension);

  /**
   * @brief Construct a new Point object.
   * 
   * @param point Vector of the point coordinates.
   * @param dimension The point dimension.
   */
  Point(double *point, int dimension);

  /**
   * @brief Destroy the Point object.
   * 
   */
  ~Point() {}

  /**
   * @brief Get the x coordinate.
   * 
   * @return The x coordinate. 
   */
  double x();

  /**
   * @brief Get the y coordinate.
   * 
   * @return The y coordinate. 
   */
  double y();

  /**
   * @brief Get the z coordinate.
   * 
   * @return The z coordinate. 
   */
  double z();

  /**
   * @brief Get the point dimension.
   * 
   * @return The point dimension.
   */
  int dimension();

  /**
   * @brief Set the x coordinate.
   * 
   * @param value The x coordinate.
   */
  void setX(double value);

  /**
   * @brief Set the y coordinate.
   * 
   * @param value The y coordinate.
   */
  void setY(double value);

  /**
   * @brief Set the z coordinate.
   * 
   * @param value The z coordinate.
   */
  void setZ(double value);

  /**
   * @brief Set the point coordinates.
   * 
   * @param The vector of point coordinates.
   */
  void set(double *point);

  /**
   * @brief Set the point dimension.
   * 
   * @param value The point dimension.
   */
  void setDimension(int value);
  
  /**
   * @brief Print the point coordinates for debugging.
   * 
   */
  void print();
};
#endif //_CCOLAB_GEOMETRY_POINT_H
