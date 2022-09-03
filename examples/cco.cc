/*
 * @file cco.cc
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

/*
 * @author Luiz Cláudio Mesquita de Aquino (luiz.aquino@ufvjm.edu.br)
 * @brief
 * @version 1.0
 * @date 2020-10-10
 */
#include <cmath>
#include <iostream>
#include <string>

#include "../src/cco/ConstrainedConstructiveOptimization.h"
#include "../src/domain/CircleFunction.h"
#include "../src/domain/DomainFile.h"
#include "../src/tree/Tree.h"
#include "../src/tree/TreeFile.h"

using namespace std;

int main(int argc, char *argv[]) {
  /* Declare the variables: */
  int numberOfConnections = 20,
    maximumNumberOfAttempts = 10,
    numberOfTerminals = 250;

  double radiusExpoent = 2.0,
    lengthExpoent = 1.0,
    radius = 0.0287941;

  Domain *domainFile;
  TreeModel *tree;
  TreeFile *treeFile;

  /* Instantiate the DomainFile and TreeModel: */
  domainFile = new DomainFile(
      "../data/sphere/default-sphere.vtk",
      new CircleFunction(radius)
  );

  tree = new Tree(
      domainFile->seed(0),
      numberOfTerminals,
      domainFile->dimension()
  );

  /* Set the perfusion volume and the terminal pressure: */
  tree->setPerfusionVolume(domainFile->volume());

  /* 9599.21 N/m^2 = 72 mm Hg */
  tree->setTerminalPressure(9.59921e3);


  /* Instantiate the ConstrainedConstructiveOptimization object: */
  ConstrainedConstructiveOptimization cco(
      domainFile,
      tree,
      numberOfTerminals,
      radiusExpoent,
      lengthExpoent,
      numberOfConnections,
      maximumNumberOfAttempts
  );

  /* Grow the tree: */
  cco.grow();

  /* Save the tree file: */
  treeFile = new TreeFile(cco.tree());

  /* 
    Set the segment length unit as centimeter and
    the radius unit as millimeter.
  */
  treeFile->tree()->setLengthUnit(100.0);
  treeFile->tree()->setRadiusUnit(1000.0);

  treeFile->save("cco-tree.vtk");

  return 0;
}