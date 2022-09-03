/**
 * @file Progress.h
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
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>

using std::string;
using std::stringstream;
using std::fixed;
using std::setprecision;
using std::cout;
using std::endl;

#ifndef _CCOLAB_PROGRESS_PROGRESS_H
#define _CCOLAB_PROGRESS_PROGRESS_H
class Progress {
 private:
  /**
   * @brief Total number of spaces.
   * 
   */
  int _totalSteps;

  /**
   * @brief The current step.
   * 
   */
  int _step = 0;

  /**
   * @brief The number of characters on each line.
   * 
   */
  int _length = 80;

  /**
   * @brief The character used to fill blank space.
   * 
   */
  char _fill = '#';

  /**
   * @brief The line prefix.
   * 
   */
  string _prefix = "Progress";

  /**
   * @brief The line suffix.
   * 
   */
  string _suffix = "";

  /**
   * @brief The character on the end of line.
   * 
   */
  string _EOL = "\r";

  /**
   * @brief The string representing the line.
   * 
   */
  string _bar;

  /**
   * @brief Flag if the bar should be printed.
   * 
   */
  bool _printBar = true;

 public:

  /**
   * @brief Construct a new Progress object
   * 
   * @param totalSteps The total number of steps.
   */
  explicit Progress(int totalSteps);

  /**
   * @brief Construct a new Progress object.
   * 
   * @param totalSteps The total number of steps.
   * @param prefix The line prefix.
   */
  Progress(int totalSteps, string prefix);

  /**
   * @brief Construct a new Progress object.
   * 
   * @param totalSteps The total number of steps.
   * @param prefix The line prefix.
   * @param fill The character to fill blank space.
   * @param length The number of characters on each line.
   * @param EOL The character on the end of line.
   */
  Progress(int totalSteps, string prefix, char fill, int length,
           string EOL = "\r");

  /**
   * @brief Destroy the Progress object.
   * 
   */
  ~Progress() { cout << "\n"; }

  /**
   * @brief Print the progrees line.
   * 
   */
  void print();

  /**
   * @brief Add one step on the progess line.
   * 
   */
  void next();

  /**
   * @brief Reset the progess line.
   * 
   */
  void reset();
};
#endif  //_CCOLAB_PROGRESS_PROGRESS_H
