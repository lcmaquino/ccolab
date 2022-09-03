/**
 * @file Tree.h
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
#include "ConstantBifurcationExpoent.h"
#include "ConstantBloodViscosity.h"
#include "geometry/Geometry.h"
#include "interface/TreeModel.h"

#ifndef _CCOLAB_TREE_TREE_H
#define _CCOLAB_TREE_TREE_H
class Tree : public TreeModel {
 private:
  /**
   * @brief Vector of segments on the tree.
   *
   */
  Segment *_segments;

  /**
   * @brief Vector of the reduced hydrodynamic resistance.
   *
   */
  double *_reducedHydrodynamicResistance;

  /**
   * @brief Vector of the segments length.
   *
   */
  double *_length;

  /**
   * @brief Geometry object to do some geometric calculations.
   *
   */
  Geometry *_geometry;

  /**
   * @brief The current number of terminal segments.
   *
   */
  int _currentNumberOfTerminals = 0;

 public:
  /**
   * @brief Construct a new Tree object.
   *
   * @param seed The seed of the tree.
   * @param numberOfTerminals The number of terminal segments.
   * @param dimension The dimension of the points on the tree.
   */
  Tree(Point seed, int numberOfTerminals, int dimension);

  /**
   * @brief Construct a new Tree object
   *
   * @param seed The seed of the tree.
   * @param numberOfTerminals The number of terminal segments.
   * @param dimension The dimension of the points on the tree.
   * @param perfusionVolume The perfusion volume.
   * @param perfusionPressure The perfusion pressure.
   * @param terminalPressure The terminal pressure.
   * @param perfusionFlow The perfusion flow.
   * @param bloodViscosity The blood viscosity for the segments.
   * @param bifurcationExpoent The bifurcartion expoent for the segments.
   */
  Tree(Point seed, int numberOfTerminals, int dimension, double perfusionVolume,
       double perfusionPressure, double terminalPressure, double perfusionFlow,
       BloodViscosity *bloodViscosity,
       BifurcationExpoentLaw *bifurcationExpoent);

  /**
   * @brief Destroy the Tree object.
   *
   */
  ~Tree();

  /**
   * @brief Get the current number of terminal segments.
   *
   * @return The current number of terminal segments.
   */
  virtual int currentNumberOfTerminals();

  /**
   * @brief Get the index of the first segment on the tree.
   *
   * @return The index of the first segment on the tree.
   */
  virtual int begin();

  /**
   * @brief Get the index of the last segment on the tree.
   *
   * @return The index of the last segment on the tree.
   */
  virtual int end();

  /**
   * @brief Get the root segment.
   *
   * @return The root segment.
   */
  virtual Segment root();

  /**
   * @brief Get the parent (ie, ascendent) segment.
   *
   * @param segmentID The index of the segment.
   *
   */
  virtual Segment parent(int segmentID);

  /**
   * @brief Get the left segment (ie, left descendent segment).
   *
   * @param segmentID The index of the segment.
   *
   */
  virtual Segment left(int segmentID);

  /**
   * @brief Get the right segment (ie, right descendent segment).
   *
   * @param segmentID The index of the segment.
   *
   */
  virtual Segment right(int segmentID);

  /**
   * @brief Get the segment.
   *
   * @param segmentID The index of the segment.
   *
   */
  virtual Segment *segment(int segmentID);

  /**
   * @brief Move the distal point of the segment.
   *
   * @param segmentID The index of the segment.
   * @param point The new distal point.
   *
   */
  virtual void moveDistalPoint(int segmentID, Point point);

  /**
   * @brief Get the length of the segment.
   *
   * @param segmentID The index of the segment.
   * @return The length of the segment.
   */
  virtual double length(int segmentID);

  /**
   * @brief Get the radius of the segment.
   *
   * @param segmentID The index of the segment.
   * @return The radius of the segment.
   */
  virtual double radius(int segmentID);

  /**
   * @brief Get the tree volume.
   *
   * @return The tree volume.
   */
  virtual double volume();

  /**
   * @brief Get the reduced hydrodynamic resistance of the tree begining at
   * the given segment.
   *
   * @param segmentID The index of the segment.
   * @return the reduced hydrodynamic resistance of the tree begining at
   * the given segment.
   */
  virtual double reducedHydrodynamicResistance(int segmentID);

  /**
   * @brief Get the bifurcation level of the segment.
   *
   * @param segmentID The index of the segment.
   * @return The bifurcation level of the segment.
   */
  virtual int level(int segmentID);

  /**
   * @brief Get the Strahler order of the segment.
   *
   * @param segmentID The index of the segment.
   * @return The Strahler order of the segment.
   */
  virtual int strahlerOrder(int segmentID);

  /**
   * @brief Grow the root segment.
   *
   * @param root The root segment.
   * @return The root segment.
   */
  virtual Segment growRoot(Segment root);

  /**
   * @brief Copy the variables from the source segment to the destination
   * segment.
   *
   * @param source The source segment.
   * @param destination The destination segment.
   */
  virtual void copy(Segment source, Segment destination);

  /**
   * @brief Grow the new segment.
   *
   * @param bifurcationPoint The new distal point of the parent segment.
   * @param parent The parent segment.
   * @param child The child segment (it's a new segment to connect on the
   * tree).
   * @return The updated parent segment.
   */
  virtual Segment growSegment(Point bifurcationPoint, Segment parent,
                                   Segment child);

  /**
   * @brief Remove the segment from the tree.
   *
   * @param segment The segment to be removed.
   * @return The parent segment of the removed segment.
   */
  virtual Segment remove(Segment segment);

  /**
   * @brief Recalculate the radii bifurcations ratio and the flow from the
   * given segment up to the root segment.
   *
   * @param segment The given segment.
   */
  virtual void update(Segment segment);

  /**
   * @brief Check if a segment is the root segment.
   *
   * @param segmentID The segment to be checked.
   * @return Returns true if the segment is the root segment. Returns false
   * otherwise.
   *
   */
  virtual bool isRoot(int segmentID);

  /**
   * @brief Check if a segment is a terminal segment.
   *
   * @param segmentID The segment to be checked.
   * @return Returns true if the segment is a terminal segment. Returns false
   * otherwise.
   *
   */
  virtual bool isTerminal(int segmentID);

  /**
   * @brief Get the proximal point of the given segment.
   *
   * @param segmentID The index of the segment.
   * @return The proximal point of the given segment.
   */
  virtual Point proximalPoint(int segmentID);

  /**
   * @brief Get the distal point of the given segment.
   *
   * @param segmentID The index of the segment.
   * @return The distal point of the given segment.
   */
  virtual Point distalPoint(int segmentID);

  /**
   * @brief Get the flow passing through the root segment.
   *
   * @return The flow passing through the root segment.
   */
  virtual double flow();

  /**
   * @brief Print the seed and the segments of the tree for debugging.
   *
   */
  virtual void print();
  void setSeed(double *value);
};
#endif
