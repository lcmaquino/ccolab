/**
 * @file ForestConnectionSearch.cc
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
#include "ForestConnectionSearch.h"

ForestConnectionSearch::ForestConnectionSearch(int numberOfConnections,
                                               TreeModel **trees,
                                               int numberOfTrees, bool *active,
                                               int totalNumberOfSegments,
                                               int dimension) {
  _trees = trees;
  _active = active;
  _numberOfConnections = numberOfConnections;
  _numberOfTrees = numberOfTrees;
  _currentNumberOfConnections = 0;
  _currentNumberOfSegments = 0;

  /**
   *  Allocate all vectors once. It speed up the code because later it wont
   *  need to create/destroy objects as the tree grows.
   * */
  _segmentDistance = new double[totalNumberOfSegments];
  _segmentID = new int[totalNumberOfSegments];
  _treeID = new int[totalNumberOfSegments];
  _closestSegments = new int[2 * _numberOfConnections];

  _geometry = new Geometry(dimension);
}

ForestConnectionSearch::~ForestConnectionSearch() {
  delete[] _segmentDistance;
  delete[] _segmentID;
  delete[] _treeID;
  delete[] _closestSegments;
}

void ForestConnectionSearch::setTrees(TreeModel **trees) { _trees = trees; }

TreeModel **ForestConnectionSearch::trees() { return _trees; }

int ForestConnectionSearch::currentNumberOfConnections() {
  return _currentNumberOfConnections;
}

int *ForestConnectionSearch::atPoint(Point point) {
  int t, i, j, k, oldSegmentID;
  double d, oldDistance;
  _currentNumberOfSegments = 0;

  /* Compute the distance of the point from each segment. */
  for (t = 0; t < _numberOfTrees; t++) {
    if (!_active[t]) {
      continue;
    }

    for (i = _trees[t]->begin(); i < _trees[t]->end(); i++) {
      d = _geometry->distanceFromSegment(point, _trees[t]->proximalPoint(i),
                                         _trees[t]->distalPoint(i));
      _segmentDistance[_currentNumberOfSegments] = d;
      _segmentID[_currentNumberOfSegments] = i;
      _treeID[_currentNumberOfSegments] = t;
      _currentNumberOfSegments++;
    }
  }

  /* Sort the computed distances. */
  sort();

  /* Get the closest segments */
  _currentNumberOfConnections = _currentNumberOfSegments < _numberOfConnections
                                    ? _currentNumberOfSegments
                                    : _numberOfConnections;

  for (i = 0; i < _currentNumberOfConnections; i++) {
    j = 2 * i;
    _closestSegments[j] = _treeID[i];
    _closestSegments[j + 1] = _segmentID[i];
  }

  return _closestSegments;
}

int *ForestConnectionSearch::atPoint(Point point, int treeID) {
  int t, i, j, k, oldSegmentID;
  double d, oldDistance;
  _currentNumberOfSegments = 0;

  /* Compute the distance of the point from the given tree. */
  for (i = _trees[treeID]->begin(); i < _trees[treeID]->end(); i++) {
    d = _geometry->distanceFromSegment(point, _trees[treeID]->proximalPoint(i),
                                       _trees[treeID]->distalPoint(i));
    _segmentDistance[_currentNumberOfSegments] = d;
    _segmentID[_currentNumberOfSegments] = i;
    _treeID[_currentNumberOfSegments] = treeID;
    _currentNumberOfSegments++;
  }

  /* Sort the computed distances. */
  sort();

  /* Get the closest segments */
  _currentNumberOfConnections = _currentNumberOfSegments < _numberOfConnections
                                    ? _currentNumberOfSegments
                                    : _numberOfConnections;

  for (i = 0; i < _currentNumberOfConnections; i++) {
    j = 2 * i;
    _closestSegments[j] = treeID;
    _closestSegments[j + 1] = _segmentID[i];
  }

  return _closestSegments;
}

void ForestConnectionSearch::sort() {
  /* Bubble sort */
  int i, oldSegmentID, oldTreeID;
  bool swap;
  double oldDistance;

  do {
    swap = false;
    for (i = 0; i < _currentNumberOfSegments - 1; i++) {
      if (_segmentDistance[i] > _segmentDistance[i + 1]) {
        oldDistance = _segmentDistance[i];
        oldSegmentID = _segmentID[i];
        oldTreeID = _treeID[i];

        _segmentDistance[i] = _segmentDistance[i + 1];
        _segmentID[i] = _segmentID[i + 1];
        _treeID[i] = _treeID[i + 1];

        _segmentDistance[i + 1] = oldDistance;
        _segmentID[i + 1] = oldSegmentID;
        _treeID[i + 1] = oldTreeID;

        swap = true;
      }
    }
  } while (swap);
}
