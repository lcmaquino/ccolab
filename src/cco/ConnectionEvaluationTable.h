/**
 * @file ConnectionEvaluationTable.h
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

#include "Connection.h"
#include "ValidAngle.h"
#include "ValidSegment.h"
#include "WithoutIntersection.h"
#include "interface/GeometricRestriction.h"
#include "tree/interface/TreeModel.h"

#ifndef _CCOLAB_CCO_CONNECTIONEVALUATIONTABLE_H
#define _CCOLAB_CCO_CONNECTIONEVALUATIONTABLE_H
class ConnectionEvaluationTable {
 private:
  /**
   * @brief The tree to add new connections.
   * 
   */
  TreeModel *_tree;

  /**
   * @brief The vector of Connection objects.
   * 
   */
  Connection *_connections;

  /**
   * @brief The vector of integers representing the reasonable connections.
   * 
   */
  int *_reasonableConnections;

  /**
   * @brief The total number of connections.
   * 
   */
  int _numberOfConnections;

  /**
   * @brief The current number of connections.
   * 
   */
  int _currentNumberOfConnections = 0;

  /**
   * @brief The current number of reasonable connections.
   * 
   */
  int _currentNumberOfReasonableConnections = 0;

  /**
   * @brief The geometric restriction to check on connections. Segments 
   * on connection should not intersect other tree segment.
   * 
   */
  WithoutIntersection *withoutIntersection;

  /**
   * @brief Copy a Connection objetc from source to destination.
   * 
   * @param source The source Connection object.
   * @param destination The destination Connection object.
   */
  void copy(Connection source, Connection *destination);

 public:
  /**
   * @brief Construct a new Connection Evaluation Table object
   * 
   * @param tree The tree to add new connections.
   * @param numberOfConnections The number of connections.
   */
  ConnectionEvaluationTable(TreeModel *tree, int numberOfConnections);

  /**
   * @brief Destroy the Connection Evaluation Table object
   * 
   */
  ~ConnectionEvaluationTable();

  /**
   * @brief Set the Tree object.
   * 
   * @param tree The tree.
   */
  void setTree(TreeModel *tree);

  /**
   * @brief Get the tree.
   * 
   * @return TreeModel* The tree.
   */
  TreeModel *tree();

  /**
   * @brief Remove the invalid connections (ie, the connections not passing the
   * geometric restrcions.
   * 
   */
  void reduce();

  /**
   * @brief Add a new connection.
   * 
   * @param connection The new connection.
   */
  void add(Connection connection);

  /**
   * @brief Get the reasonable connection with minimum target function value.
   * 
   * @return The connection with minimum target function value
   */
  Connection optimalReasonableConnection();

  /**
   * @brief Reset to 0 the current number of connections.
   * 
   */
  void reset();

  /**
   * @brief Get the vector of Connection objetcs.
   * 
   * @return The vector of Connection objetcs.
   */
  Connection *connections();

  /**
   * @brief Get the vector of integers representing the reasonable connections.
   * 
   * @return The vector of integers representing the reasonable connections. 
   */
  int *reasonableConnections();

  /**
   * @brief Get the current number of connections.
   * 
   * @return The current number of connections. 
   */
  int currentNumberOfConnections();

  /**
   * @brief Get the current number of reasonable connections.
   * 
   * @return The current number of reasonable connections.
   */
  int currentNumberOfReasonableConnection();
};
#endif //_CCOLAB_CCO_CONNECTIONEVALUATIONTABLE_H
