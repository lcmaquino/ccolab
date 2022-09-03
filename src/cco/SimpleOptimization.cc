/**
 * @file SimpleOptimization.cc
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
 * @file SimpleOptimization.cpp
 * @author Luiz Cláudio Mesquita de Aquino (luiz.aquino@ufvjm.edu.br)
 * @brief
 * @version 1.0
 * @date 2022-05-18
 */
#include "SimpleOptimization.h"

SimpleOptimization::SimpleOptimization(Domain *domain, TreeModel *tree,
                                       TargetFunction *targetFunction,
                                       int intervalDivision)
    : GeometricOptimization(domain, tree, targetFunction) {
  int numberOfGeometricRestrictions = 2;
  _degreeOfSymmetry = 0.0;
  _geometry = new Geometry(domain->dimension());
  _intervalDivision = intervalDivision;
  _targetFunction = targetFunction;
  GeometricRestriction **_geometricRestrictions =
      new GeometricRestriction *[numberOfGeometricRestrictions];
  _geometricRestrictions[0] = new ValidSegment(tree);
  _geometricRestrictions[1] = new BifurcationSymmetry(tree, _degreeOfSymmetry);
  setGeometricRestrictions(_geometricRestrictions,
                           numberOfGeometricRestrictions);
}

SimpleOptimization::SimpleOptimization(Domain *domain, TreeModel *tree,
                                       TargetFunction *targetFunction,
                                       int intervalDivision,
                                       double degreeOfSymmetry)
    : GeometricOptimization(domain, tree, targetFunction) {
  int numberOfGeometricRestrictions = 2;
  _degreeOfSymmetry = degreeOfSymmetry;
  _geometry = new Geometry(domain->dimension());
  _intervalDivision = intervalDivision;
  _targetFunction = targetFunction;
  GeometricRestriction **_geometricRestrictions =
      new GeometricRestriction *[numberOfGeometricRestrictions];
  _geometricRestrictions[0] = new ValidSegment(tree);
  _geometricRestrictions[1] = new BifurcationSymmetry(tree, _degreeOfSymmetry);
  setGeometricRestrictions(_geometricRestrictions,
                           numberOfGeometricRestrictions);
}

Connection SimpleOptimization::bifurcation(Segment segment) {
  int i, j, newSegment = segment.right(), connectionSegment = segment.left(),
            numberOfPoints = _intervalDivision + 1, line, column;
  double a, b, step = 1.0 / _intervalDivision, offset = 0.3;
  double evaluatedTargetFunction, minimumEvaluatedTargetFunction = 1e15;
  bool hasMinimum = false;
  Connection *minimumConnection;
  Point segmentProximalPoint = tree()->proximalPoint(segment.ID());
  Point oldBifurcationPoint = segment.point();
  Point newSegmentDistalPoint = tree()->distalPoint(newSegment);
  Point connectionSegmentDistalPoint = tree()->distalPoint(connectionSegment);
  Point optimalBifurcationPoint, newBifurcationPoint, mapPointA, mapPointB,
      mapPointC;
  Point Xi = _geometry->add(
      segmentProximalPoint,
      _geometry->scalarProduct(offset,
                               _geometry->subtract(connectionSegmentDistalPoint,
                                                   segmentProximalPoint)));
  Point Xj = _geometry->add(
      segmentProximalPoint,
      _geometry->scalarProduct(1.0 - offset,
                               _geometry->subtract(connectionSegmentDistalPoint,
                                                   segmentProximalPoint)));
  Point Xnew = _geometry->add(
      newSegmentDistalPoint,
      _geometry->scalarProduct(
          offset,
          _geometry->subtract(oldBifurcationPoint, newSegmentDistalPoint)));

  for (line = numberOfPoints; line >= 1; line--) {
    for (column = 1; column <= line; column++) {
      /**
       *    Calculate the map for (a, b) to the new birufcation point.
       *
       *    map(a, b) = (1 - a - b)*Xi + a*Xnew + b*Xj
       *
       *    That function maps points on the triangle given by vertices
       *    Xi, Xj, and Xnew with the triangle given by vertices (0, 0),
       *    (1, 0), and (0, 1) in such a way that map(0, 0) = Xi,
       *    map(1, 0) = Xnew, and map(0, 1) = Xj.
       **/
      a = (column - 1) * step;
      b = (numberOfPoints - line) * step;
      mapPointA = _geometry->scalarProduct(1 - a - b, Xi);
      mapPointB = _geometry->scalarProduct(a, Xnew);
      mapPointC = _geometry->scalarProduct(b, Xj);
      newBifurcationPoint =
          _geometry->add(_geometry->add(mapPointA, mapPointB), mapPointC);

      /* Move the bifurcation to the new bifurcation point. */
      tree()->moveDistalPoint(segment.ID(), newBifurcationPoint);

      /* Check the geometric restrictions. */
      if (passRestrictions(segment)) {
        /* Evaluate the target function. */
        evaluatedTargetFunction = _targetFunction->eval();

        /* Store the connection with minimum target function value. */
        if (evaluatedTargetFunction < minimumEvaluatedTargetFunction) {
          minimumEvaluatedTargetFunction = evaluatedTargetFunction;
          optimalBifurcationPoint = newBifurcationPoint;
          hasMinimum = true;
        }
      }
    }
  }

  if (hasMinimum) {
    minimumConnection = new Connection(segment.ID(), optimalBifurcationPoint,
                                       tree()->right(segment.ID()),
                                       minimumEvaluatedTargetFunction);
  } else {
    minimumConnection = new Connection();
  }

  /* Move back the bifurcation to the old bifurcation point. */
  tree()->moveDistalPoint(segment.ID(), oldBifurcationPoint);

  return *minimumConnection;
}

void SimpleOptimization::setIntervalDivision(int value) {
  _intervalDivision = value;
}
