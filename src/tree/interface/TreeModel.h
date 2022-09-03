/**
 * @file TreeModel.h
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
#include <string>

#include "BifurcationExpoentLaw.h"
#include "BloodViscosity.h"
#include "Segment.h"
using std::cout;
using std::endl;

#ifndef _CCOLAB_TREE_INTERFACE_TREEMODEL_H
#define _CCOLAB_TREE_INTERFACE_TREEMODEL_H
class TreeModel {
 private:
  /**
   * @brief Seed of the tree.
   * 
   */
  Point _seed;

  /**
   * @brief Vector of segments on the tree.
   * 
   */
  Segment *_segments;

  /**
   * @brief The number of terminal segments.
   * 
   */
  int _numberOfTerminals = 0;

  /**
   * @brief The total number of segments.
   * 
   */
  int _totalNumberOfSegments = 0;

  /**
   * @brief The current number of segments.
   * 
   */
  int _currentNumberOfSegments = 0;

  /**
   * @brief The dimension of the points on the tree.
   * 
   */
  int _dimension = 3;

  /**
   * @brief The unit of the metric system used to represent the radius.
   * The value 1.0 means meters, 100.0 means centimeters and 1000.0
   * means milimeters.
   * 
   */
  double _radiusUnit = 1.0;

  /**
   * @brief The unit of the metric system used to represent the length.
   * The value 1.0 means meters, 100.0 means centimeters and 1000.0
   * means milimeters.
   * 
   */
  double _lengthUnit = 1.0;

  /**
   * @brief The blood viscosity for the segments.
   * 
   */
  BloodViscosity *_bloodViscosity;

  /**
   * @brief The bifurcation expoent for the segment.
   * 
   */
  BifurcationExpoentLaw *_bifurcationExpoent;

 public:
  /**
   * @brief The index of root segment.
   * 
   */
  const int _rootID = 0;

  /**
   * @brief The perfusion volume. Defaults to 0.0001 m^3 (ie, 100 cm^3).
   * 
   */
  double _perfusionVolume = 0.0001;

  /**
   * @brief The perfusion pressure. Defaults to 13332.236535 N/m^2
   * (ie, 100 mm Hg).
   * 
   */
  double _perfusionPressure = 13332.236535;

  /**
   * @brief The terminal pressure. Defaults to 7999.341921 N/m^2
   * (ie, 60 mm Hg).
   * 
   */
  double _terminalPressure = 7999.341921;

  /**
   * @brief The perfusion flow. Defaults to 0.00000833 m^3/s (ie, 500 ml/min).
   * 
   */
  double _perfusionFlow = 0.00000833;

  /**
   * @brief The constant factor on the poiseuille law expression.
   * 
   */
  const double _poiseuilleLawConstant = 8.0 / M_PI;

  /**
   * @brief The terminal end index.
   * 
   */
  const int _TERMINALEND = -1;

  /**
   * @brief Construct a new Tree Model object.
   * 
   */
  TreeModel(){}

  /**
   * @brief Construct a new Tree Model object.
   * 
   * @param bloodViscosity The blood viscosity for the segments.
   * @param bifurcationExpoent The bifurcartion expoent for the segments.
   */
  TreeModel(BloodViscosity *bloodViscosity,
            BifurcationExpoentLaw *bifurcationExpoent) {
    _bloodViscosity = bloodViscosity;
    _bifurcationExpoent = bifurcationExpoent;
  }

  /**
   * @brief Construct a new Tree Model object.
   * 
   * @param seed The seed of the tree.
   * @param numberOfTerminals The number of terminal segments.
   * @param dimension The dimension of the points on the tree.
   */
  TreeModel(Point seed, int numberOfTerminals, int dimension)
      : _seed(seed),
        _numberOfTerminals(numberOfTerminals),
        _dimension(dimension) {
    _currentNumberOfSegments = 0;
    _totalNumberOfSegments = 2 * numberOfTerminals - 1;

    if (dimension == 2) {
      /* 0.0025 m^2 = 25 cm^2*/
      _perfusionVolume = 0.0025;
    }
  }

  /**
   * @brief Construct a new Tree Model object
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
  TreeModel(Point seed, int numberOfTerminals, int dimension,
            double perfusionVolume, double perfusionPressure,
            double terminalPressure, double perfusionFlow,
            BloodViscosity *bloodViscosity,
            BifurcationExpoentLaw *bifurcationExpoent)
      : _seed(seed),
        _numberOfTerminals(numberOfTerminals),
        _dimension(dimension),
        _perfusionVolume(perfusionVolume),
        _perfusionPressure(perfusionPressure),
        _terminalPressure(terminalPressure),
        _perfusionFlow(perfusionFlow),
        _bloodViscosity(bloodViscosity),
        _bifurcationExpoent(bifurcationExpoent) {
    _currentNumberOfSegments = 0;
    _totalNumberOfSegments = 2 * numberOfTerminals - 1;

    if (dimension == 2) {
      /* 0.0025 m^2 = 25 cm^2*/
      _perfusionVolume = 0.0025;
    }
  }

  /**
   * @brief Destroy the Tree Model object.
   * 
   */
  ~TreeModel() {
    delete[] _segments;
  }

  /**
   * @brief Get the segment root index.
   * 
   * @return The segment root index.
   */
  virtual int rootID() { return _rootID; }

  /**
   * @brief Get the seed of the tree.
   * 
   * @return The seed of the tree.
   */
  virtual Point seed() { return _seed; }

  /**
   * @brief Get the vector of segments of the tree.
   * 
   * @return The vector of segments of the tree.
   */
  virtual Segment *segments() { return _segments; }

  /**
   * @brief Get the number of terminal segments.
   * 
   * @return The number of terminal segments.
   */
  virtual int numberOfTerminals() { return _numberOfTerminals; }

  /**
   * @brief Get the current number of terminal segments.
   * 
   * @return The current number of terminal segments.
   */
  virtual int currentNumberOfTerminals() = 0;

  /**
   * @brief Get the current number of segments.
   * 
   * @return The current number of segments.
   */
  virtual int currentNumberOfSegments() { return _currentNumberOfSegments; }

  /**
   * @brief Ge the total number of segments.
   * 
   * @return The total number segments.
   */
  virtual int totalNumberOfSegments() { return _totalNumberOfSegments; }

  /**
   * @brief Get the index of the first segment on the tree.
   * 
   * @return The index of the first segment on the tree.
   */
  virtual int begin() = 0;

  /**
   * @brief Get the index of the last segment on the tree.
   * 
   * @return The index of the last segment on the tree.
   */
  virtual int end() = 0;

  /**
   * @brief Get the dimension of the points on the tree.
   * 
   * @return The dimension of the points on the tree. 
   */
  virtual int dimension() { return _dimension; }

  /**
   * @brief Get the unit of the metric system used to represent the radius.
   * 
   * @return The unit of the metric system used to represent the radius.
   */
  virtual double radiusUnit() { return _radiusUnit; }

  /**
   * @brief Get the unit of the metric system used to represent the length.
   * 
   * @return The unit of the metric system used to represent the length.
   */
  virtual double lengthUnit() { return _lengthUnit; }

  /**
   * @brief Get the perfusion volume.
   * 
   * @return The perfusion volume.
   */
  virtual double perfusionVolume() { return _perfusionVolume; }

  /**
   * @brief Get the perfusion pressure.
   * 
   * @return The perfusion pressure.
   */
  virtual double perfusionPressure() { return _perfusionPressure; }

  /**
   * @brief Get the terminal perfusion pressure.
   * 
   * @return The terminal perfusion pressure.
   */
  virtual double terminalPressure() { return _terminalPressure; }

  /**
   * @brief Get the perfusion flow.
   * 
   * @return The perfusion flow.
   */
  virtual double perfusionFlow() { return _perfusionFlow; }

  /**
   * @brief Get the blood viscosity passing through the given segment.
   * 
   * @param segmentID The index of the segment.
   * @return The blood viscosity passing through the given segment.
   */
  virtual double bloodViscosity(int segmentID) {
    return _bloodViscosity->eval(segmentID);
  }

  /**
   * @brief Get the blood viscosity passing through the given segment.
   * 
   * @param segmentLevel The bifurcation level for the segment.
   * @return The bifurcation expoent for the segment radius.
   */
  virtual double bifurcationExpoent(int segmentLevel) {
    return _bifurcationExpoent->eval(segmentLevel);
  }

  /**
   * @brief Set the seed of the tree.
   * 
   * @param point The seed of the tree. 
   */
  virtual void setSeed(Point point) { _seed = point; }

  /**
   * @brief Set the number of terminal segments.
   * 
   * @param value The number of terminal segments
   */
  virtual void setNumberOfTerminals(int value) { _numberOfTerminals = value; }

  /**
   * @brief Set the current number of segments.
   * 
   * @param value The current number of segments.
   */
  virtual void setCurrentNumberOfSegments(int value) {
    _currentNumberOfSegments = value;
  }

  /**
   * @brief Set the dimension of the points on the tree.
   * 
   * @param value The dimension of the points on the tree.
   */
  virtual void setDimension(int value) { _dimension = value; }

  /**
   * @brief Set the unit of the metric system used to represent the radius.
   * 
   * @param value The unit of the metric system used to represent the radius. 
   * The value 1.0 means meters, 100.0 means centimeters and 1000.0 means
   * milimeters.
   */
  virtual void setRadiusUnit(double value) { _radiusUnit = value; }

  /**
   * @brief Set the unit of the metric system used to represent the length.
   * 
   * @param value The unit of the metric system used to represent the length.
   * The value 1.0 means meters, 100.0 means centimeters and 1000.0 means
   * milimeters.
   * 
   */
  virtual void setLengthUnit(double value) { _lengthUnit = value; }

  /**
   * @brief Set the perfusion volume.
   * 
   * @param value The perfusion volume.
   * 
   */
  virtual void setPerfusionVolume(double value) { _perfusionVolume = value; }

  /**
   * @brief Set the perfusion pressure.
   * 
   * @param value The perfusion pressure.
   * 
   */
  virtual void setPerfusionPressure(double value) {
    _perfusionPressure = value;
  }

  /**
   * @brief Set the terminal pressure.
   * 
   * @param value The terminal pressure.
   * 
   */
  virtual void setTerminalPressure(double value) { _terminalPressure = value; }

  /**
   * @brief Set the perfusion flow.
   * 
   * @param value The perfusion flow.
   * 
   */
  virtual void setPerfusionFlow(double value) { _perfusionFlow = value; }

  /**
   * @brief Set the blood viscosity for the segments.
   * 
   * @param bloodViscosity The blod viscosity for the segments.
   */
  virtual void setBloodViscosity(BloodViscosity *bloodViscosity) {
    _bloodViscosity = bloodViscosity;
  }

  /**
   * @brief Set the bifurcation expoent for the segment radius.
   * 
   * @param bifurcationExpoentLaw The bifurcation expoent for the segment radius.
   */
  virtual void setBifurcationExpoent(
      BifurcationExpoentLaw *bifurcationExpoentLaw) {
    _bifurcationExpoent = bifurcationExpoentLaw;
  }

  /**
   * @brief Get the root segment.
   * 
   * @return The root segment.
   */
  virtual Segment root() = 0;

  /**
   * @brief Get the parent (ie, ascendent) segment.
   * 
   * @param segmentID The index of the segment.
   * 
   */
  virtual Segment parent(int segmentID) = 0;

  /**
   * @brief Get the left segment (ie, left descendent segment).
   * 
   * @param segmentID The index of the segment.
   * 
   */
  virtual Segment left(int segmentID) = 0;

  /**
   * @brief Get the right segment (ie, right descendent segment).
   * 
   * @param segmentID The index of the segment.
   * 
   */
  virtual Segment right(int segmentID) = 0;

  /**
   * @brief Get the segment.
   * 
   * @param segmentID The index of the segment.
   * 
   */
  virtual Segment *segment(int segmentID) = 0;

  /**
   * @brief Move the distal point of the segment.
   * 
   * @param segmentID The index of the segment.
   * @param point The new distal point.
   * 
   */
  virtual void moveDistalPoint(int segmentID, Point point) = 0;

  /**
   * @brief Get the length of the segment.
   * 
   * @param segmentID The index of the segment. 
   * @return The length of the segment.
   */
  virtual double length(int segmentID) = 0;

  /**
   * @brief Get the radius of the segment.
   * 
   * @param segmentID The index of the segment. 
   * @return The radius of the segment.
   */
  virtual double radius(int segmentID) = 0;

  /**
   * @brief Get the tree volume.
   * 
   * @return The tree volume.
   */
  virtual double volume() = 0;

  /**
   * @brief Get the reduced hydrodynamic resistance of the tree begining at
   * the given segment. 
   * 
   * @param segmentID The index of the segment.
   * @return the reduced hydrodynamic resistance of the tree begining at
   * the given segment.
   */
  virtual double reducedHydrodynamicResistance(int segmentID) = 0;

  /**
   * @brief Get the bifurcation level of the segment.
   * 
   * @param segmentID The index of the segment.
   * @return The bifurcation level of the segment. 
   */
  virtual int level(int segmentID) = 0;

  /**
   * @brief Get the Strahler order of the segment.
   * 
   * @param segmentID The index of the segment.
   * @return The Strahler order of the segment. 
   */
  virtual int strahlerOrder(int segmentID) = 0;

  /**
   * @brief Grow the root segment.
   * 
   * @param root The root segment.
   * @return The root segment.
   */
  virtual Segment growRoot(Segment root) = 0;

  /**
   * @brief Copy the variables from the source segment to the destination
   * segment.
   * 
   * @param source The source segment.
   * @param destination The destination segment.
   */
  virtual void copy(Segment source, Segment destination) = 0;

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
                                   Segment child) = 0;

  /**
   * @brief Remove the segment from the tree.
   * 
   * @param segment The segment to be removed.
   * @return The parent segment of the removed segment. 
   */
  virtual Segment remove(Segment segment) = 0;

  /**
   * @brief Recalculate the radii bifurcations ratio and the flow from the 
   * given segment up to the root segment.
   * 
   * @param segment The given segment.
   */
  virtual void update(Segment segment) = 0;

  /**
   * @brief Check if a segment is the root segment.
   * 
   * @param segmentID The segment to be checked.
   * @return Returns true if the segment is the root segment. Returns false
   * otherwise.
   * 
   */
  virtual bool isRoot(int segmentID) = 0;

  /**
   * @brief Check if a segment is a terminal segment.
   * 
   * @param segmentID The segment to be checked.
   * @return Returns true if the segment is a terminal segment. Returns false
   * otherwise.
   * 
   */
  virtual bool isTerminal(int segmentID) = 0;

  /**
   * @brief Get the proximal point of the given segment.
   * 
   * @param segmentID The index of the segment.
   * @return The proximal point of the given segment.
   */
  virtual Point proximalPoint(int segmentID) = 0;

  /**
   * @brief Get the distal point of the given segment.
   * 
   * @param segmentID The index of the segment.
   * @return The distal point of the given segment.
   */
  virtual Point distalPoint(int segmentID) = 0;

  /**
   * @brief Get the flow passing through the root segment.
   * 
   * @return The flow passing through the root segment.
   */
  virtual double flow() = 0;

  /**
   * @brief Print the seed and the segments of the tree for debugging.
   * 
   */
  virtual void print() = 0;
};
#endif //_CCOLAB_TREE_INTERFACE_TREEMODEL_H
