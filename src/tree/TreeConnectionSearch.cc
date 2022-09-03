/**
 * @file TreeConnectionSearch.cc
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
#include "TreeConnectionSearch.h"

#include <iostream>
#include <string>

#include "geometry/Geometry.h"
using std::cout;
using std::endl;

TreeConnectionSearch::TreeConnectionSearch(int numberOfConnections,
                                           int totalNumberOfSegments,
                                           int dimension) {
  _numberOfConnections = numberOfConnections;
  _currentNumberOfConnections = 0;
  _currentNumberOfSegments = 0;

  /**
   *  Allocate all vectors once. It speed up the code because later it wont
   *  need to create/destroy objects as the tree grows.
   * */
  _segmentDistance = new double[totalNumberOfSegments];
  _segmentID = new int[totalNumberOfSegments];
  _closestSegments = new int[_numberOfConnections];

  _geometry = new Geometry(dimension);
}

TreeConnectionSearch::TreeConnectionSearch(TreeModel *tree,
                                           int numberOfConnections) {
  _tree = tree;
  _numberOfConnections = numberOfConnections;
  _currentNumberOfConnections = 0;
  _currentNumberOfSegments = 0;

  /**
   *  Allocate all vectors once. It speed up the code because later it wont
   *  need to create/destroy objects as the tree grows.
   * */
  _segmentDistance = new double[_tree->totalNumberOfSegments()];
  _segmentID = new int[_tree->totalNumberOfSegments()];
  _closestSegments = new int[_numberOfConnections];

  _geometry = new Geometry(_tree->dimension());
}

TreeConnectionSearch::~TreeConnectionSearch() {
  // delete[] _segmentDistance;
  // delete[] _segmentID;
  // delete[] _closestSegments;
}

void TreeConnectionSearch::setTree(TreeModel *tree) { _tree = tree; }

TreeModel *TreeConnectionSearch::tree() { return _tree; }

int TreeConnectionSearch::currentNumberOfConnections() {
  return _currentNumberOfConnections;
}

int *TreeConnectionSearch::atPoint(Point point) {
  int i, j, k, oldSegmentID;
  double d, oldDistance;
  _currentNumberOfSegments = 0;

  /* Compute the distance of the point from each segment. */
  for (i = _tree->begin(); i < _tree->end(); i++) {
    d = _geometry->distanceFromSegment(point, _tree->proximalPoint(i),
                                       _tree->distalPoint(i));
    _segmentDistance[_currentNumberOfSegments] = d;
    _segmentID[_currentNumberOfSegments] = i;
    _currentNumberOfSegments++;
  }

  /* Sort the computed distances. */
  sort();

  /* Get the closest segments */
  _currentNumberOfConnections = _currentNumberOfSegments < _numberOfConnections
                                    ? _currentNumberOfSegments
                                    : _numberOfConnections;

  for (i = 0; i < _currentNumberOfConnections; i++) {
    _closestSegments[i] = _segmentID[i];
  }

  return _closestSegments;
}

void TreeConnectionSearch::sort() {
  /* Bubble sort */
  int i, oldSegmentID;
  bool swap;
  double oldDistance;

  do {
    swap = false;
    for (i = 0; i < _currentNumberOfSegments - 1; i++) {
      if (_segmentDistance[i] > _segmentDistance[i + 1]) {
        oldDistance = _segmentDistance[i];
        oldSegmentID = _segmentID[i];
        _segmentDistance[i] = _segmentDistance[i + 1];
        _segmentID[i] = _segmentID[i + 1];
        _segmentDistance[i + 1] = oldDistance;
        _segmentID[i + 1] = oldSegmentID;
        swap = true;
      }
    }
  } while (swap);
}
