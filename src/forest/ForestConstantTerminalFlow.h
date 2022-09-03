/**
 * @file ForestConstantTerminalFlow.h
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
#include "cco/interface/TerminalFlowFunction.h"

#ifndef _CCOLAB_FOREST_FORESTCONSTANTTERMINALFLOWOPTIMIZATION_H
#define _CCOLAB_FOREST_FORESTCONSTANTTERMINALFLOWOPTIMIZATION_H
class ForestConstantTerminalFlow : public TerminalFlowFunction {
 private:
  /**
   * @brief The vector of trees.
   * 
   */
  TreeModel **_trees;

  /**
   * @brief The number of trees.
   * 
   */
  int _numberOfTrees;

  /**
   * @brief The number of terminals.
   * 
   */
  int _numberOfTerminals;

  /**
   * @brief The perfusion flow.
   * 
   */
  double _perfusionFlow;

 public:
  /**
   * @brief Construct a new Forest Constant Terminal Flow object.
   * 
   */
  ForestConstantTerminalFlow();

  /**
   * @brief Construct a new Forest Constant Terminal Flow object.
   * 
   * @param trees The vector of trees.
   * @param numberOfTrees The number of trees.
   * @param numberOfTerminals The number of terminals.
   */
  ForestConstantTerminalFlow(TreeModel **trees, int numberOfTrees,
                             int numberOfTerminals);

  /**
   * @brief Destroy the Forest Constant Terminal Flow object
   * 
   */
  ~ForestConstantTerminalFlow() {}

  /**
   * @brief Evaluate the flow passing through the terminal segment.
   * 
   * @param segment The terminal segment.
   * @return The value of the flow. 
   */
  virtual double eval(Segment segment);
};
#endif //_CCOLAB_FOREST_FORESTCONSTANTTERMINALFLOWOPTIMIZATION_H
