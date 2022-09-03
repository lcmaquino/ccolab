/**
 * @file Progress.cc
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
#include "Progress.h"

Progress::Progress(int totalSteps) {
  int i;
  _totalSteps = totalSteps;
  _bar = "[";
  _length = _length - _prefix.size() - 8;

  for (i = 0; i < _length; i++) {
    _bar.append("-");
  }
  _bar.append("]");
}

Progress::Progress(int totalSteps, string prefix) {
  int i;
  _totalSteps = totalSteps;
  _prefix = prefix;
  _bar = "[";
  _length = _length - _prefix.size() - 8;

  for (i = 0; i < _length; i++) {
    _bar.append("-");
  }
  _bar.append("]");
}

Progress::Progress(int totalSteps, string prefix, char fill, int length,
                   string EOL) {
  int i;
  _totalSteps = totalSteps;
  _fill = fill;
  _prefix = prefix;
  _length = length - _prefix.size() - 8;
  _step = 1;
  _EOL = EOL;
  _printBar = true;
  _bar = "[";
  for (i = 0; i < _length; i++) {
    _bar.append("-");
  }

  _bar.append("]");
}

void Progress::print() {
  double percent;
  stringstream _per;
  if (_printBar) {
    percent = 100.0 * _step / _totalSteps;
    _per << fixed << setprecision(1) << percent;
    cout << "\r" << _prefix << " " << _bar << " " << _per.str() << "%";
    _printBar = false;
    if (_step == _totalSteps) {
      reset();
    }
  }
}

void Progress::next() {
  int i;
  _step++;
  int fill = (_bar.size() - 1) * _step / _totalSteps;
  for (i = 1; i < fill; i++) {
    _bar[i] = _fill;
  }

  _printBar = true;
}

void Progress::reset() {
  _step = 0;
  _printBar = true;
}
