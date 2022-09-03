/**
 * @file Tree.cc
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
#include "Tree.h"

#include <cmath>
#include <iostream>
#include <string>

using std::cout;
using std::endl;

Tree::Tree(Point seed, int numberOfTerminals, int dimension)
    : TreeModel(seed, numberOfTerminals, dimension) {

  _geometry = new Geometry(dimension);

  setBifurcationExpoent(new ConstantBifurcationExpoent(3.0));

  /* 0.0036 (N/m^2)·s = 3.6 cP */
  setBloodViscosity(new ConstantBloodViscosity(0.0036));

  /**
   *  Allocate all segments once. It speed up the code because later it wont
   *  need to create/destroy objects as the tree grows.
   **/
  _segments = new Segment[TreeModel::totalNumberOfSegments()];
  _reducedHydrodynamicResistance =
      new double[TreeModel::totalNumberOfSegments()];
  _length = new double[TreeModel::totalNumberOfSegments()];
}

Tree::Tree(Point seed, int numberOfTerminals, int dimension,
           double perfusionVolume, double perfusionPressure,
           double terminalPressure, double perfusionFlow,
           BloodViscosity *bloodViscosity,
           BifurcationExpoentLaw *bifurcationExpoent)
    : TreeModel(seed, numberOfTerminals, dimension, perfusionVolume,
                perfusionPressure, terminalPressure, perfusionFlow,
                bloodViscosity, bifurcationExpoent) {

  _geometry = new Geometry(dimension);

  /**
   *  Allocate all segments once. It speed up the code because later it wont
   *  need to create/destroy objects as the tree grows.
   **/
  _segments = new Segment[TreeModel::totalNumberOfSegments()];
  _reducedHydrodynamicResistance =
      new double[TreeModel::totalNumberOfSegments()];
}

Tree::~Tree() {
  delete[] _reducedHydrodynamicResistance;
  delete[] _length;
  delete _geometry;
}

int Tree::currentNumberOfTerminals() { return _currentNumberOfTerminals; }

int Tree::begin() { return _rootID; }

int Tree::end() { return currentNumberOfSegments(); }

void Tree::setSeed(double *value) {
  Point seed(value, dimension());
  TreeModel::setSeed(seed);
}

Segment Tree::root() { return _segments[_rootID]; }

Segment Tree::parent(int segmentID) {
  int parentID;
  if (isRoot(segmentID)) {
    return _segments[segmentID];
  } else {
    parentID = _segments[segmentID].up();
    return _segments[parentID];
  }
}

Segment Tree::left(int segmentID) {
  int leftID = _segments[segmentID].left();
  return _segments[leftID];
}

Segment Tree::right(int segmentID) {
  int rightID = _segments[segmentID].right();
  return _segments[rightID];
}

void Tree::moveDistalPoint(int segmentID, Point point) {
  int _left, _right;
  double oldLength;
  _segments[segmentID].setPoint(point);
  _length[segmentID] = _geometry->distance(proximalPoint(segmentID), point);
  if (!isTerminal(segmentID)) {
    _left = _segments[segmentID].left();
    oldLength = _length[_left];
    _length[_left] = _geometry->distance(point, distalPoint(_left));
    _reducedHydrodynamicResistance[_left] =
        _reducedHydrodynamicResistance[_left] +
        _poiseuilleLawConstant * (bloodViscosity(_left) * _length[_left] -
                                  bloodViscosity(_left) * oldLength);

    _right = _segments[segmentID].right();
    oldLength = _length[_right];
    _length[_right] = _geometry->distance(point, distalPoint(_right));
    _reducedHydrodynamicResistance[_right] =
        _reducedHydrodynamicResistance[_right] +
        _poiseuilleLawConstant * (bloodViscosity(_right) * _length[_right] -
                                  bloodViscosity(_right) * oldLength);
  }

  update(_segments[segmentID]);
}

Segment *Tree::segment(int segmentID) { return &_segments[segmentID]; }

double Tree::length(int segmentID) {
  return (TreeModel::lengthUnit()) * _length[segmentID];
}

double Tree::radius(int segmentID) {
  int _parent;
  double radiusRatio = 1.0;
  double rootRadius =
      TreeModel::radiusUnit() *
      pow(reducedHydrodynamicResistance(_rootID) * _perfusionFlow /
              (_perfusionPressure - _terminalPressure),
          0.25);

  while (!isRoot(segmentID)) {
    _parent = _segments[segmentID].up();
    if (_segments[_parent].left() == segmentID) {
      radiusRatio *= _segments[_parent].bifurcationRatioLeft();
    } else {
      radiusRatio *= _segments[_parent].bifurcationRatioRight();
    }
    segmentID = _parent;
  }

  return radiusRatio * rootRadius;
}

double Tree::volume() {
  int i;
  double r, vol = 0.0;

  for (i = begin(); i < end(); i++) {
    r = radius(i);
    vol += (r * r) * length(i);
  }
  
  vol *= M_PI;
  
  return vol;
}

double Tree::reducedHydrodynamicResistance(int segmentID) {
  return _reducedHydrodynamicResistance[segmentID];
}

int Tree::level(int segmentID) {
  int _level = 0;
  while (!isRoot(segmentID)) {
    _level++;
    segmentID = _segments[segmentID].up();
  }

  return _level;
}

int Tree::strahlerOrder(int segmentID) {
  int leftSO, rightSO;

  if (isTerminal(segmentID)) {
    return 1;
  } else {
    leftSO = strahlerOrder(left(segmentID).ID());
    rightSO = strahlerOrder(right(segmentID).ID());
    if (leftSO == rightSO) {
      return leftSO + 1;
    } else {
      return leftSO > rightSO ? leftSO : rightSO;
    }
  }
}

Segment Tree::growRoot(Segment root) {
  double rootLength = _geometry->distance(seed(), root.point());
  double segmentReducedHydrodynamicResistance =
      _poiseuilleLawConstant * bloodViscosity(_rootID) * rootLength;

  _segments[_rootID].setID(_rootID);
  copy(root, _segments[_rootID]);
  _reducedHydrodynamicResistance[_rootID] =
      segmentReducedHydrodynamicResistance;
  _length[_rootID] = rootLength;
  setCurrentNumberOfSegments(1);
  _currentNumberOfTerminals = 1;

  return _segments[_rootID];
}

void Tree::copy(Segment source, Segment destination) {
  _segments[destination.ID()].setDimension(dimension());
  _segments[destination.ID()].setPoint(source.point());
  _segments[destination.ID()].setFlow(source.flow());
  _segments[destination.ID()].setBifurcationRatioLeft(
      source.bifurcationRatioLeft());
  _segments[destination.ID()].setBifurcationRatioRight(
      source.bifurcationRatioRight());
  _segments[destination.ID()].setLeft(source.left());
  _segments[destination.ID()].setRight(source.right());

  if (source.left() != _TERMINALEND) {
    _segments[source.left()].setUp(destination.ID());
  }

  if (source.right() != _TERMINALEND) {
    _segments[source.right()].setUp(destination.ID());
  }
}

Segment Tree::growSegment(Point bifurcationPoint, Segment parent,
                               Segment child) {
  double segmentReducedHydrodynamicResistance;
  Segment connection(dimension()), bifurcation(dimension()),
      newSegment(dimension());

  /* Create the connection segment as a copy of the parent. */
  _segments[currentNumberOfSegments()].setDimension(dimension());
  _segments[currentNumberOfSegments()].setID(currentNumberOfSegments());
  _segments[currentNumberOfSegments()].setPoint(parent.point());
  _segments[currentNumberOfSegments()].setFlow(parent.flow());
  _segments[currentNumberOfSegments()].setBifurcationRatioLeft(
      parent.bifurcationRatioLeft());
  _segments[currentNumberOfSegments()].setBifurcationRatioRight(
      parent.bifurcationRatioRight());
  _segments[currentNumberOfSegments()].setLeft(parent.left());
  _segments[currentNumberOfSegments()].setRight(parent.right());
  if (parent.left() != _TERMINALEND) {
    _segments[parent.left()].setUp(currentNumberOfSegments());
  }

  if (parent.right() != _TERMINALEND) {
    _segments[parent.right()].setUp(currentNumberOfSegments());
  }

  _segments[currentNumberOfSegments()].setUp(parent.ID());
  _length[currentNumberOfSegments()] =
      _geometry->distance(bifurcationPoint, parent.point());
  _reducedHydrodynamicResistance[currentNumberOfSegments()] =
      _reducedHydrodynamicResistance[parent.ID()] +
      _poiseuilleLawConstant *
          (bloodViscosity(currentNumberOfSegments()) *
               _length[currentNumberOfSegments()] -
           bloodViscosity(parent.ID()) * length(parent.ID()));
  setCurrentNumberOfSegments(currentNumberOfSegments() + 1);

  /* Add the new segment. */
  _segments[currentNumberOfSegments()].setDimension(dimension());
  _segments[currentNumberOfSegments()].setID(currentNumberOfSegments());
  _segments[currentNumberOfSegments()].setPoint(child.point());
  _segments[currentNumberOfSegments()].setFlow(child.flow());
  _segments[currentNumberOfSegments()].setUp(parent.ID());
  _length[currentNumberOfSegments()] =
      _geometry->distance(bifurcationPoint, child.point());
  _reducedHydrodynamicResistance[currentNumberOfSegments()] =
      _poiseuilleLawConstant * bloodViscosity(currentNumberOfSegments()) *
      _length[currentNumberOfSegments()];
  setCurrentNumberOfSegments(currentNumberOfSegments() + 1);

  /* Update the bifurcation segment. */
  _segments[parent.ID()].setPoint(bifurcationPoint);
  _segments[parent.ID()].setLeft(currentNumberOfSegments() - 2);
  _segments[parent.ID()].setRight(currentNumberOfSegments() - 1);
  _length[parent.ID()] =
      _geometry->distance(proximalPoint(parent.ID()), distalPoint(parent.ID()));

  /* Recalculate the radii bifurcations ratio and the flow. */
  update(_segments[parent.ID()]);

  _currentNumberOfTerminals++;

  return _segments[parent.ID()];
}

Segment Tree::remove(Segment segment) {
  int parentID = segment.up(), connectionID = _segments[segment.up()].left(),
      terminalID = _segments[segment.up()].right();

  /* Update the bifurcation segment. */
  _segments[parentID].setPoint(_segments[connectionID].point());
  _segments[parentID].setLeft(_segments[connectionID].left());
  _segments[parentID].setRight(_segments[connectionID].right());
  if (!isTerminal(connectionID)) {
    _segments[_segments[connectionID].left()].setUp(parentID);
    _segments[_segments[connectionID].right()].setUp(parentID);
  } else {
    _segments[parentID].setFlow(_segments[connectionID].flow());
  }

  _length[parentID] =
      _geometry->distance(proximalPoint(parentID), distalPoint(parentID));

  /* Remove the given terminal segment. */
  setCurrentNumberOfSegments(currentNumberOfSegments() - 1);

  /* Remove the connection segment. */
  setCurrentNumberOfSegments(currentNumberOfSegments() - 1);

  /* Recalculate the radii bifurcations ratio and the flow. */
  update(_segments[parentID]);

  _currentNumberOfTerminals--;

  return _segments[parentID];
}

void Tree::update(Segment segment) {
  int segmentID = segment.ID(), connectionID, _newID;
  double connectionFlow, newFlow, flowRatio, leftReducedHydrodynamicResistance,
      rightReducedHydrodynamicResistance, reducedHydrodynamicResistanceRatio,
      radiusRatio, Rtemp, radiusRatioPowerBifurcationExpoent, leftRadiusRatio,
      rightRadiusRatio;

  /* Recalculate the radii bifurcations ratio and the flow from the segment up
   * to the root. */
  do {
    if (isTerminal(segmentID)) {
      _reducedHydrodynamicResistance[segmentID] = _poiseuilleLawConstant *
                                                  bloodViscosity(segmentID) *
                                                  length(segmentID);
      _segments[segmentID].setBifurcationRatioLeft(1.0);
      _segments[segmentID].setBifurcationRatioRight(1.0);
    } else {
      connectionID = _segments[segmentID].left();
      _newID = _segments[segmentID].right();

      connectionFlow = _segments[connectionID].flow();
      newFlow = _segments[_newID].flow();
      _segments[segmentID].setFlow(connectionFlow + newFlow);
      flowRatio = connectionFlow / newFlow;

      leftReducedHydrodynamicResistance =
          reducedHydrodynamicResistance(connectionID);
      rightReducedHydrodynamicResistance =
          reducedHydrodynamicResistance(_newID);
      reducedHydrodynamicResistanceRatio = leftReducedHydrodynamicResistance /
                                           rightReducedHydrodynamicResistance;

      radiusRatio = pow(flowRatio * reducedHydrodynamicResistanceRatio, 0.25);
      radiusRatioPowerBifurcationExpoent =
          pow(radiusRatio, bifurcationExpoent(segmentID));
      leftRadiusRatio = pow(1.0 + 1.0 / radiusRatioPowerBifurcationExpoent,
                            -1.0 / bifurcationExpoent(segmentID));
      rightRadiusRatio = pow(1.0 + radiusRatioPowerBifurcationExpoent,
                             -1.0 / bifurcationExpoent(segmentID));

      _segments[segmentID].setBifurcationRatioLeft(leftRadiusRatio);
      _segments[segmentID].setBifurcationRatioRight(rightRadiusRatio);

      Rtemp = pow(leftRadiusRatio, 4.0) / leftReducedHydrodynamicResistance +
              pow(rightRadiusRatio, 4.0) / rightReducedHydrodynamicResistance;
      _reducedHydrodynamicResistance[segmentID] =
          _poiseuilleLawConstant * bloodViscosity(segmentID) *
              length(segmentID) +
          1.0 / Rtemp;
    }

    segmentID = _segments[segmentID].up();
  } while (segmentID != _TERMINALEND);
}

bool Tree::isRoot(int segmentID) { return segmentID == _rootID; }

bool Tree::isTerminal(int segmentID) {
  return (_segments[segmentID].left() == _TERMINALEND &&
          _segments[segmentID].right() == _TERMINALEND);
}

Point Tree::proximalPoint(int segmentID) {
  int parentID;
  if (isRoot(segmentID)) {
    return seed();
  } else {
    parentID = _segments[segmentID].up();
    return _segments[parentID].point();
  }
}

Point Tree::distalPoint(int segmentID) { return _segments[segmentID].point(); }

double Tree::flow() { return _segments[_rootID].flow(); }

void Tree::print() {
  int i;

  cout << "Seed:" << endl;
  seed().print();

  for (i = 0; i < currentNumberOfSegments(); i++) {
    _segments[i].print(reducedHydrodynamicResistance(i), length(i), radius(i));
  }

  cout << "---" << endl;
}
