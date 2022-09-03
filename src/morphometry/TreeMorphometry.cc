/**
 * @file TreeMorphometry.cc
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
#include "TreeMorphometry.h"

void TreeMorphometry::analytics() {
  int i, totalNumberOfSegments = _tree->totalNumberOfSegments();
  _length = new double[totalNumberOfSegments];
  _radius = new double[totalNumberOfSegments];
  _level = new int[totalNumberOfSegments];
  _strahlerOrder = new int[totalNumberOfSegments];

  for (i = _tree->begin(); i < _tree->end(); i++) {
    _length[i] = _tree->length(i);
    _radius[i] = _tree->radius(i);
    _level[i] = _tree->level(i);
    _strahlerOrder[i] = _tree->strahlerOrder(i);
  }
}

void TreeMorphometry::save(string filename, string delimiter) {
  int i;
  ofstream treefile;
  treefile.open(filename);
  analytics();
  if (treefile.is_open()) {
    treefile << "LENGTH" << delimiter << "RADIUS" << delimiter << "LEVEL"
             << delimiter << "STRAHLER_ORDER" << endl;
    for (i = _tree->begin(); i < _tree->end(); i++) {
      treefile << _length[i] << delimiter << _radius[i] << delimiter
               << _level[i] << delimiter << _strahlerOrder[i] << endl;
    }
    treefile.close();
  } else {
    cout << "Unable to open: \"" << filename << "\"." << endl;
  }
}
