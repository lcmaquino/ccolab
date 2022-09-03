/**
 * @file Geometry.cc
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
#include <cmath>
#include <iostream>
using std::string, std::cout, std::endl;

#include "Geometry.h"

Geometry::Geometry(int dimension) { _dimension = dimension; }

Point Geometry::add(Point pointA, Point pointB) {
  Point C(_dimension);
  C.setX(pointA.x() + pointB.x());
  C.setY(pointA.y() + pointB.y());
  if (_dimension == 3) {
    C.setZ(pointA.z() + pointB.z());
  }

  return C;
}

Point Geometry::subtract(Point pointA, Point pointB) {
  Point C(_dimension);
  C.setX(pointA.x() - pointB.x());
  C.setY(pointA.y() - pointB.y());
  if (_dimension == 3) {
    C.setZ(pointA.z() - pointB.z());
  }

  return C;
}

double Geometry::distance(Point pointA, Point pointB) {
  double squaredDistance =
      (pointA.x() - pointB.x()) * (pointA.x() - pointB.x()) +
      (pointA.y() - pointB.y()) * (pointA.y() - pointB.y());
  if (_dimension == 3) {
    squaredDistance += (pointA.z() - pointB.z()) * (pointA.z() - pointB.z());
  }
  return sqrt(squaredDistance);
}

double Geometry::dot(Point pointA, Point pointB) {
  double _dot = pointA.x() * pointB.x() + pointA.y() * pointB.y();
  if (_dimension == 3) {
    _dot += pointA.z() * pointB.z();
  }

  return _dot;
}

Point Geometry::scalarProduct(double scalar, Point v) {
  Point C(_dimension);
  C.setX(scalar * v.x());
  C.setY(scalar * v.y());
  if (_dimension == 3) {
    C.setZ(scalar * v.z());
  }

  return C;
}

Point Geometry::unitVector(Point pointA, Point pointB) {
  Point AB(_dimension);
  double _norm = distance(pointA, pointB);
  AB.setX((pointB.x() - pointA.x()) / _norm);
  AB.setY((pointB.y() - pointA.y()) / _norm);
  if (_dimension == 3) {
    AB.setZ((pointB.z() - pointA.z()) / _norm);
  }

  return AB;
}

double Geometry::norm(Point v) { return sqrt(dot(v, v)); }

Point Geometry::crossProduct(Point u, Point v) {
  /*
      w = crossProduct(u, v)

          |  i  j   k  |
      w = | ux  uy  uz |
          | vx  vy  vz |
  */

  Point w(3);
  double uz, vz;

  uz = u.dimension() == 2 ? 0.0 : u.z();
  vz = v.dimension() == 2 ? 0.0 : v.z();
  w.setX(uz * v.y() - u.y() * vz);
  w.setY(u.x() * vz - uz * v.x());
  w.setZ(u.y() * v.x() - u.x() * v.y());

  return w;
}

Point Geometry::middle(Point pointA, Point pointB) {
  return scalarProduct(0.5, add(pointA, pointB));
}

double Geometry::angle(Point u, Point v) {
  /* If u or v is the null vector, then the angle between u and v is equal to 0.
   */
  return (norm(u) < _TOLERANCE || norm(v) < _TOLERANCE)
             ? 0.0
             : acos(dot(u, v) / (norm(u) * norm(v)));
}

double Geometry::distanceFromSegment(Point point, Point proximalPoint,
                                     Point distalPoint) {
  return _dimension == 2
             ? distanceFromSegment2D(point, proximalPoint, distalPoint)
             : distanceFromSegment3D(point, proximalPoint, distalPoint);
}

double Geometry::distanceFromSegment2D(Point point, Point proximalPoint,
                                       Point distalPoint) {
  /**
      Here we use the "critical distance".
      @todo: explain the "critical distance".
  */
  Point AB(2), AP(2);
  double innerProduct, d, dA, dB;

  /** vector AB given by:
   * A: proximalPoint;
   * B: distalPoint;
   */
  AB = subtract(distalPoint, proximalPoint);

  /** vector AP given by:
   * A: proximalPoint;
   * P: point;
   */
  AP = subtract(point, proximalPoint);

  /* Inner product: AP·AB/AB·AB */
  innerProduct = dot(AP, AB) / dot(AB, AB);

  if (0.0 <= innerProduct && innerProduct <= 1.0) {
    /**
     *  Given the line s with direction v = (p, q) and point A = (x0, y0),
     *  the equation of that line is:
     *
     *  q(x - x0) - p(y - y0) = 0
     *
     *  The distance of a point P = (x1, y1) from the line s is:
     *
     *  d = |q(x1 - x0) - p(y1 - y0)|/sqrt(p^2 + q^2)
     *
     *  Note:
     *  (1) the value of innerProduct means that the orthogonal projection of
     *     the point onto the segment is in that segment.
     */
    d = fabs(AB.y() * AP.x() - AB.x() * AP.y()) / (norm(AB));
  } else {
    dA = distance(point, proximalPoint);
    dB = distance(point, distalPoint);
    d = fmin(dA, dB);
  }

  return d;
}

double Geometry::distanceFromSegment3D(Point point, Point proximalPoint,
                                       Point distalPoint) {
  /**
      Here we use the "critical distance".
      @todo: explain the "critical distance".
  */
  Point AB(3), AP(3);
  double innerProduct, d, dA, dB;

  /** vector AB given by:
   * A: proximalPoint;
   * B: distalPoint;
   */
  AB = subtract(distalPoint, proximalPoint);

  /** vector AP given by:
   * A: proximalPoint;
   * P: point;
   */
  AP = subtract(point, proximalPoint);

  /* Inner product: (AP·AB)/(AB·AB) */
  innerProduct = dot(AP, AB) / dot(AB, AB);

  if (0.0 <= innerProduct && innerProduct <= 1.0) {
    /**
     *  Given the line s with direction AB = (p, q, r) and point A = (x0, y0,
     * z0), the distance of a point P = (x1, y1, z1) from the line s is:
     *
     *  d = norm(crossProduct(AP, AB))/norm(AB)
     *
     *  Note:
     *  (1) the value of innerProduct means that the orthogonal projection of
     *     the point onto the segment is in that segment.
     */

    d = norm(crossProduct(AP, AB)) / (norm(AB));
  } else {
    dA = distance(point, proximalPoint);
    dB = distance(point, distalPoint);
    d = fmin(dA, dB);
  }

  return d;
}

bool Geometry::hasIntersection(Point pointA, Point pointB, Point pointC,
                               Point pointD, double tolerance) {
  return _dimension == 2
             ? hasIntersection2D(pointA, pointB, pointC, pointD, tolerance)
             : hasIntersection3D(pointA, pointB, pointC, pointD, tolerance);
}

bool Geometry::hasIntersection2D(Point pointA, Point pointB, Point pointC,
                                 Point pointD, double tolerance) {
  /**
   *
   *   We need to solve the equation in parameters r and s:
   *
   *   A + r(B - A) = C + s(D - C)
   *
   *   rAB - sCD = AC
   *
   *   [ AB.x()  -CD.x() ][ r ]  =  [AC.x()]
   *   [ AB.y()  -CD.y() ][ s ]  =  [AC.y()]
   *
   */
  Point AB(2), CD(2), AC(2);
  double det, r, detR, s, detS, dist1, dist2;

  AB = subtract(pointB, pointA);
  CD = subtract(pointD, pointC);
  AC = subtract(pointC, pointA);

  det = AB.x() * (-CD.y()) - (-CD.x()) * (AB.y());

  if (fabs(det) < _TOLERANCE * _TOLERANCE) {
    return false;
  }

  /* Applying Cramer's rule to find r and s. */
  detR = (AC.x() * (-CD.y()) - (-CD.x()) * (AC.y()));
  detS = (AB.x() * (AC.y()) - (AC.x()) * (AB.y()));
  r = detR / det;
  s = detS / det;

  dist1 = tolerance / norm(AB);
  dist2 = tolerance / norm(CD);

  return ((0.0 < r && r < 1.0 + dist1) && (0.0 < s && s < 1.0 + dist2));
}

bool Geometry::hasIntersection3D(Point pointA, Point pointB, Point pointC,
                                 Point pointD, double tolerance) {
  /**
   *   Let PQ be the shortest segment between AB and CD.
   *
   *   Note that P is in AB, Q is in CD and PQ is perpendicular to AB and CD.
   *   It follows that:
   *
   *   P = A + r*(B - A)
   *   Q = C + s*(D - C)
   *   <PQ, AB> = 0
   *   <PQ, CD> = 0
   *
   *   We need to solve the system of equations:
   *
   *   <AC + s*CD - r*AB, AB> = 0
   *   <AC + s*CD - r*AB, CD> = 0
   *
   *   That is:
   *
   *   <AB, AB>*r - <CD, AB>*s = <AC, AB>
   *   <AB, CD>*r - <CD, CD>*s = <AC, CD>
   *
   *   The matrix form of the system:
   *
   *   [ <AB, AB>  - <CD, AB> ][ r ]  =  [<AC, AB>]
   *   [ <AB, CD>  - <CD, CD> ][ s ]  =  [<AC, CD>]
   *
   */
  Point AB(3), AC(3), CD(3), P(3), Q(3), PQ(3);
  double squaredNormAB, squaredNormCD, squaredNormPQ, dotABCD, dotACCD, dotACAB,
      det, r, s;

  AB = subtract(pointB, pointA);
  CD = subtract(pointD, pointC);
  squaredNormAB = dot(AB, AB);
  squaredNormCD = dot(CD, CD);
  dotABCD = dot(AB, CD);
  det = dotABCD * dotABCD - squaredNormAB * squaredNormCD;

  if (fabs(det) < _TOLERANCE) {
    return false;
  }

  AC = subtract(pointC, pointA);
  dotACAB = dot(AC, AB);
  dotACCD = dot(AC, CD);
  r = (dotABCD * dotACCD - dotACAB * squaredNormCD) / det;
  s = (dotACCD * squaredNormAB - dotACAB * dotABCD) / det;
  P = add(pointA, scalarProduct(r, AB));
  Q = add(pointC, scalarProduct(s, CD));
  PQ = subtract(Q, P);
  squaredNormPQ = dot(PQ, PQ);

  return (0.0 < r && r < 1.0 && 0.0 < s && s < 1.0 &&
          squaredNormPQ < tolerance * tolerance);
}
