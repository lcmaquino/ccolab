/*
 * @file forest-invasion.cc
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

#include "../src/forest/ForestCcoInvasion.h"
#include "../src/domain/CircleFunction.h"
#include "../src/domain/DomainFile.h"
#include "../src/tree/Tree.h"
#include "../src/tree/TreeFile.h"

using namespace std;

int main(int argc, char *argv[]) {
  /* Declare the variables: */
  int numberOfTrees = 2,
    numberOfConnections = 20,
    maximumNumberOfAttempts = 10,
    numberOfTerminals = 250;

  double targetPerfusionFlow[] = {0.667, 0.333}, 
    invasionCoefficient = 0.75,
    radiusExpoent = 2.0,
    lengthExpoent = 1.0,
    radius = 0.0287941;

  Domain *domain;
  DomainFile *domainFile;
  TreeModel **trees;
  TreeFile *treeFile;
  ForestCcoInvasion *forestCcoInvasion;

  /* Instantiate the DomainFile and TreeModel: */
  domainFile = new DomainFile(
      "../data/sphere/default-sphere.vtk",
      new CircleFunction(radius)
  );

  trees = new TreeModel *[2];
  trees[0] = new Tree(
    domainFile->seed(0),
    numberOfTerminals,
    domainFile->dimension()
  );
  trees[1] = new Tree(
    domainFile->seed(1),
    numberOfTerminals,
    domainFile->dimension()
  );

  /* Set the perfusion volume and the terminal pressure: */
  /* The total perfusion flow is 0.00000833 m^3/s = 500 ml/min */
  trees[0]->setPerfusionFlow(targetPerfusionFlow[0] * 8.33e-6);
  trees[1]->setPerfusionFlow(targetPerfusionFlow[1] * 8.33e-6);

  /* 9599.21 N/m^2 = 72 mm Hg*/
  trees[0]->setTerminalPressure(9.59921e3);
  trees[1]->setTerminalPressure(9.59921e3);


  /* Instantiate the ForestCcoInvasion object: */
  forestCcoInvasion = new ForestCcoInvasion(
    domainFile,
    trees,
    numberOfTrees,
    numberOfTerminals,
    invasionCoefficient,
    targetPerfusionFlow,
    radiusExpoent,
    lengthExpoent
  );

  /* Grow the tree: */
  forestCcoInvasion->grow();

  /* Save the tree file: */
  treeFile = new TreeFile(forestCcoInvasion->tree(0));

  /* 
    Set the segment length unit as centimeter and
    the radius unit as millimeter.
  */
  treeFile->tree()->setLengthUnit(100.0);
  treeFile->tree()->setRadiusUnit(1000.0);

  treeFile->save("forest-invasion-tree1.vtk");

  treeFile = new TreeFile(forestCcoInvasion->tree(1));

  /* 
    Set the segment length unit as centimeter and
    the radius unit as millimeter.
  */
  treeFile->tree()->setLengthUnit(100.0);
  treeFile->tree()->setRadiusUnit(1000.0);

  treeFile->save("forest-invasion-tree2.vtk");

  return 0;
}