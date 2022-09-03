/**
 * @file Connection.h
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

#include "tree/Segment.h"

#ifndef _CCOLAB_CCO_CONNECTION_H
#define _CCOLAB_CCO_CONNECTION_H
class Connection {
 private:
  int _bifurcationSegmentID = -1;
  Point _bifurcationPoint;
  Segment _newSegment;
  double _targetFunctionValue;

 public:
  /**
   * @brief Construct a new Connection object
   * 
   */
  Connection() {}

  /**
   * @brief Construct a new Connection object
   * 
   * @param segmentID ID for the segment where the new segment is connected.
   * @param bifurcationPoint Point on the segment with segmentID where the
   * new segment is connected.
   * @param newSegment The new segment connected to the segment with
   * segmentID.
   * @param targetFunctionValue The value of the target function evaluated for
   * the tree.
   */
  Connection(int segmentID, Point bifurcationPoint, Segment newSegment,
             double targetFunctionValue);

  /**
   * @brief Destroy the Connection object
   * 
   */
  ~Connection() {}

  /**
   * @brief Get the bifurcation segement ID.
   * 
   * @return The segment ID.
   */
  int bifurcationSegmentID();

  /**
   * @brief Get the bifurcation point.
   * 
   * @return The bifurcation point. 
   */
  Point bifurcationPoint();

  /**
   * @brief Get the new segment.
   * 
   * @return The new segment. 
   */
  Segment newSegment();

  /**
   * @brief Get the target function value.
   * 
   * @return The target function value. 
   */
  double targetFunctionValue();

  /**
   * @brief Set the bifurcation segment ID.
   * 
   * @param The segment ID.
   */
  void setBifurcationSegmentID(int segmentID);

  /**
   * @brief Set the bifurcation point.
   * 
   * @param The bifurcation point. 
   */
  void setBifurcationPoint(Point point);

  /**
   * @brief Set the new segment.
   * 
   * @param The new segment.
   */
  void setNewSegment(Segment segment);

  /**
   * @brief Set the target function value.
   * 
   * @param The target function value. 
   */
  void setTargetFunctionValue(double value);

  /**
   * @brief Check if a new segment was connected.
   * 
   * @return Returns true if a new segment was connected.
   * Returns false otherwise.
   */
  bool empty();

  /**
   * @brief Print the Connection object variables for debugging.
   * 
   */
  void print();
};
#endif //_CCOLAB_CCO_CONNECTION_H
