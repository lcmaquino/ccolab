## Description
The CCOLab is a set of codes for constructing arterial trees.

It's available the following algorithms:
- Constrained Constructive Optimization (CCO) (Karch, 1999);
- CCO Forest Invasion (Aquino, 2022);
- Competing Optimized Arterial Trees (COAT) (Aquino, 2022).

### References

R Karch, F Neumann, M Neumann, and W Schreiner. A three-dimensional model for
arterial tree representation, generated by constrained constructive 
optimization. Computers in Biology and Medicine, 29(1):19–38, 1999.

L C M de Aquino. Desenvolvimento de algoritmos para construção 
automática de florestas de árvores arteriais. PhD tese, Pós-graduação 
em Modelagem Computacional – UFJF, Juiz de Fora, 2022.

## Install

### Clone the repository

Open your local terminal and run:
```
git clone https://github.com/lcmaquino/ccolab
```

It'll create the `ccolab` folder on your current working directory.

### Download the repository

[Download](https://github.com/lcmaquino/ccolab/archive/main.zip) the repository 
for your local files and extract it.

## Usage

### CCO

This example cover the case for constructing a tree in the perfusion 
domain as a sphere of 0.0287941 (meters) radius.

The tree will have 250 terminal segments. See the 
[`src/tree/interface/TreeModel.h`](src/tree/interface/TreeModel.h) to know all 
the tree parameters.

Include the headers:
```
#include "src/cco/ConstrainedConstructiveOptimization.h"
#include "src/domain/CircleFunction.h"
#include "src/domain/DomainFile.h"
#include "src/tree/Tree.h"
#include "src/tree/TreeFile.h"
```

Declare the variables:
```
int numberOfConnections = 20,
  maximumNumberOfAttempts = 10,
  numberOfTerminals = 250;

double radiusExpoent = 2.0,
  lengthExpoent = 1.0,
  radius = 0.0287941;

Domain *domainFile;
TreeModel *tree;
TreeFile *treeFile;
```

Instantiate the DomainFile and TreeModel:
```
domainFile = new DomainFile(
    "data/sphere/default-sphere.vtk",
    new CircleFunction(radius)
);

tree = new Tree(
    domainFile->seed(0),
    numberOfTerminals,
    domainFile->dimension()
);
```

Set the perfusion volume and the terminal pressure:
```
tree->setPerfusionVolume(domainFile->volume());

/* 9599.21 N/m^2 = 72 mm Hg */
tree->setTerminalPressure(9.59921e3);
```

Instantiate the ConstrainedConstructiveOptimization object:
```
ConstrainedConstructiveOptimization cco(
    domainFile,
    tree,
    numberOfTerminals,
    radiusExpoent,
    lengthExpoent,
    numberOfConnections,
    maximumNumberOfAttempts
);
```

Grow the tree:
```
cco.grow();
```

Save the tree file:
```
treeFile = new TreeFile(cco.tree());

/* 
  Set the segment length unit as centimeter and
  the radius unit as millimeter.
*/
treeFile->tree()->setLengthUnit(100.0);
treeFile->tree()->setRadiusUnit(1000.0);

treeFile->save("cco-tree.vtk");
```

### CCO Forest Invasion

This example cover the case for constructing a forest of two trees in the 
perfusion domain as a sphere of 0.0287941 (meters) radius.

The forest will have 250 terminal segments. The tree 1 will 
have 66.7% of the target flow and the tree 2 will have 
33.3%. The invasion coefficient is 0.75. See the 
[`src/tree/interface/TreeModel.h`](src/tree/interface/TreeModel.h) and 
[`src/forest/interface/Forest.h`](src/forest/interface/Forest.h)
to know all the tree and forest parameters.

Include the headers:
```
#include "src/forest/ForestCcoInvasion.h"
#include "src/domain/CircleFunction.h"
#include "src/domain/DomainFile.h"
#include "src/tree/Tree.h"
#include "src/tree/TreeFile.h"
```

Declare the variables:
```
int numberOfTrees = 2,
  numberOfConnections = 20,
  maximumNumberOfAttempts = 10,
  numberOfTerminals = 250;

double *targetPerfusionFlow[] = {0.667, 0.333}, 
  invasionCoefficient = 0.75,
  radiusExpoent = 2.0,
  lengthExpoent = 1.0,
  radius = 0.0287941;

Domain *domain;
DomainFile *domainFile;
TreeModel **trees;
TreeFile *treeFile;
ForestCcoInvasion *forestCcoInvasion;
```

Instantiate the DomainFile and TreeModel:
```
domainFile = new DomainFile(
    "data/sphere/default-sphere.vtk",
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
```

Set the target perfusion volume and the terminal pressure:
```
/* The total perfusion flow is 0.00000833 m^3/s = 500 ml/min */
trees[0]->setPerfusionFlow(targetPerfusionFlow[0] * 8.33e-6);
trees[1]->setPerfusionFlow(targetPerfusionFlow[1] * 8.33e-6);

/* 9599.21 N/m^2 = 72 mm Hg*/
trees[0]->setTerminalPressure(9.59921e3);
trees[1]->setTerminalPressure(9.59921e3);
```

Instantiate the ForestCcoInvasion object:
```
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
```

Grow the forest:
```
forestCcoInvasion->grow();
```

Save the trees files:
```
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
```

### COAT

This example cover the case for constructing a forest of two trees in the perfusion domain as a sphere of 0.0287941 (meters) radius.

The forest will have 250 terminal segments. The tree 1 will 
have 66.7% of the target flow and the tree 2 will have 
33.3%. The first stage coefficient is 0.2. See the 
[`src/tree/interface/TreeModel.h`](src/tree/interface/TreeModel.h) and 
[`src/forest/interface/Forest.h`](src/forest/interface/Forest.h)
to know all the tree and forest parameters.

Include the headers:
```
#include "src/forest/CompetingOptimizedArterialTrees.h"
#include "src/domain/CircleFunction.h"
#include "src/domain/DomainFile.h"
#include "src/tree/Tree.h"
#include "src/tree/TreeFile.h"
```

Declare the variables:
```
int numberOfTrees = 2,
  numberOfConnections = 20,
  maximumNumberOfAttempts = 10,
  numberOfTerminals = 250;

double *targetPerfusionFlow[] = {0.667, 0.333}, 
  stageCoefficient = 0.2,
  radiusExpoent = 2.0,
  lengthExpoent = 1.0,
  radius = 0.0287941;

Domain *domain;
DomainFile *domainFile;
TreeModel **trees;
TreeFile *treeFile;
CompetingOptimizedArterialTrees *coat;
```

Instantiate the DomainFile and TreeModel:
```
domainFile = new DomainFile(
    "data/sphere/default-sphere.vtk",
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
```

Set the target perfusion volume and the terminal pressure:
```
/* The total perfusion flow is 0.00000833 m^3/s = 500 ml/min */
trees[0]->setPerfusionFlow(targetPerfusionFlow[0] * 8.33e-6);
trees[1]->setPerfusionFlow(targetPerfusionFlow[1] * 8.33e-6);

/* 9599.21 N/m^2 = 72 mm Hg*/
trees[0]->setTerminalPressure(9.59921e3);
trees[1]->setTerminalPressure(9.59921e3);
```

Instantiate the CompetingOptimizedArterialTrees object:
```
coat = new CompetingOptimizedArterialTrees(
  domainFile,
  trees,
  numberOfTrees,
  numberOfTerminals,
  stageCoefficient,
  targetPerfusionFlow,
  radiusExpoent,
  lengthExpoent
);
```

Grow the forest:
```
coat->grow();
```

Save the trees files:
```
treeFile = new TreeFile(coat->tree(0));

/* 
  Set the segment length unit as centimeter and
  the radius unit as millimeter.
*/
treeFile->tree()->setLengthUnit(100.0);
treeFile->tree()->setRadiusUnit(1000.0);

treeFile->save("coat-tree1.vtk");

treeFile = new TreeFile(coat->tree(1));

/* 
  Set the segment length unit as centimeter and
  the radius unit as millimeter.
*/
treeFile->tree()->setLengthUnit(100.0);
treeFile->tree()->setRadiusUnit(1000.0);

treeFile->save("coat-tree2.vtk");
```

### Tree visualization

Use [ParaView](https://www.paraview.org/) to visualize the 
tree file. Follow the steps:

1. Click on the menu "File > Open…";
2. Choose the tree vtk file;
3. On Pipeline Browser window click on the opened file;
4. Click on the menu "Filters > Search…" and type "Cell Data to Point Data". Press enter to select;
5. Click on the menu "Filters > Search…" and type "Tube". Press enter to select;
6. On Pipeline Browser window click on the created Tube filter;
7. On Properties window for the Tube filter choose 0.01 as "Radius" and "By Scalar" as "Vary Radius";

## Working examples

To compile working examples open your local terminal and run:
```
cd examples
make
```

It will create the binaries `cco`, `forest-invasion`, and `coat`. Run 
those binaries on your local terminal:
```
./cco
./forest-invasion
./coat
```

Those binaries will create the files:
- `cco-tree.vtk`;
- `forest-invasion-tree1.vtk`;
- `forest-invasion-tree2.vtk`;
- `coat-tree1.vtk`;
- `coat-tree2.vtk`;

## License

CCOLab is open-sourced software licensed under the [GPL v3.0 or later](https://github.com/lcmaquino/ccolab/blob/main/LICENSE).
