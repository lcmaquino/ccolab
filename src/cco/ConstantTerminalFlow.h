/**
 * @file ConstantTerminalFlow.h
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
#include "interface/TerminalFlowFunction.h"

#ifndef _CCOLAB_CCO_CONSTANTTERMINALFLOW_H
#define _CCOLAB_CCO_CONSTANTTERMINALFLOW_H
class ConstantTerminalFlow : public TerminalFlowFunction {
 private:
  /**
   * @brief The target function value.
   * 
   */
  double _targetFunction;

 public:
  /**
   * @brief Construct a new Constant Terminal Flow object.
   * 
   */
  ConstantTerminalFlow();

  /**
   * @brief Construct a new Constant Terminal Flow object.
   * 
   * @param tree The tree.
   */
  explicit ConstantTerminalFlow(TreeModel *tree);

  /**
   * @brief Destroy the Constant Terminal Flow object.
   * 
   */
  ~ConstantTerminalFlow() {}

  /**
   * @brief Evaluate the flow for a terminal segment.
   * 
   * @param segment The terminal segment to evaluate the flow.
   * @return The value of the flow passing through the terminal segment.
   */
  virtual double eval(Segment segment);
};
#endif //_CCOLAB_CCO_CONSTANTTERMINALFLOW_H
