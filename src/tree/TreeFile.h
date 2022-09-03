/**
 * @author Luiz Cláudio Mesquita de Aquino (luiz.aquino@ufvjm.edu.br)
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
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "interface/TreeModel.h"

using std::string, std::invalid_argument, std::ofstream, std::ifstream,
    std::stringstream, std::istringstream, std::cout, std::endl,
    std::numeric_limits;

#ifndef _CCOLAB_TREE_TREEFILE_H
#define _CCOLAB_TREE_TREEFILE_H
class TreeFile {
 private:
  TreeModel *_tree;

 public:
  explicit TreeFile(TreeModel *tree);
  TreeModel *tree();
  void setTree(TreeModel *tree);
  void save(string filename);
};
#endif  //_CCOLAB_TREE_TREEFILE_H
