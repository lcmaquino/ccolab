/**
 * @file GeometricOptimization.h
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
 *  CCO Lab is distributed in the hope that it will be useful,
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
 * @brief Define the geometric optimization interface.
 * @version 1.0
 * @date 2022-05-18
 *
 */

#include <string>

#include "Connection.h"
#include "GeometricRestriction.h"
#include "TargetFunction.h"
#include "domain/interface/Domain.h"
#include "tree/interface/TreeModel.h"

using std::cout;
using std::endl;

#ifndef _CCOLAB_CCO_INTERFACE_GEOMETRIC_OPTIMIZATION_H
#define _CCOLAB_CCO_INTERFACE_GEOMETRIC_OPTIMIZATION_H
class GeometricOptimization {
 private:
  /**
   * @brief The target function.
   *
   */
  TargetFunction *_targetFunction;

  /**
   * @brief The geometric restrcitions.
   *
   */
  GeometricRestriction **_geometricRestrictions;

  /**
   * @brief The number of geometric restricitons.
   *
   */
  int _numberOfGeometricRestrictions = 0;

  /**
   * @brief The domain.
   *
   */
  Domain *_domain;

  /**
   * @brief The tree.
   *
   */
  TreeModel *_tree;

 public:
  /**
   * @brief Construct a new Geometric Optimization object
   *
   * @param domain The domain to grow the tree.
   * @param tree The tree.
   * @param targetFunction The target function.
   */
  GeometricOptimization(Domain *domain, TreeModel *tree,
                        TargetFunction *targetFunction)
      : _domain(domain), _tree(tree), _targetFunction(targetFunction) {
    _domain = domain;
    _tree = tree;
  }

  /**
   * @brief Destroy the Geometric Optimization object
   *
   */
  ~GeometricOptimization() {}

  /**
   * @brief Set the Tree object.
   *
   * @param tree The tree.
   */
  virtual void setTree(TreeModel *tree) { _tree = tree; }

  /**
   * @brief Get the Tree object.
   *
   * @return TreeModel*
   */
  virtual TreeModel *tree() { return _tree; }

  /**
   * @brief Set the Domain object.
   *
   * @param domain The domain.
   */
  virtual void setDomain(Domain *domain) { _domain = domain; }

  /**
   * @brief Get the Domain object.
   *
   * @return Domain*
   */
  virtual Domain *domain() { return _domain; }

  /**
   * @brief Set the Geometric Restrictions object.
   *
   * @param geometricRestrictions The geometric restrictions.
   * @param numberOfGeometricRestrictions The number of geometric restrictions.
   */
  virtual void setGeometricRestrictions(
      GeometricRestriction **geometricRestrictions,
      int numberOfGeometricRestrictions) {
    _geometricRestrictions = geometricRestrictions;
    _numberOfGeometricRestrictions = numberOfGeometricRestrictions;
  }

  /**
   * @brief Check if the segment pass the geometric restrictions.
   *
   * @param segment The segment to check.
   * @return Returns true if the segment pass the geometric restricitons.
   * returns false otherwise.
   */
  virtual bool passRestrictions(Segment segment) {
    int i;
    bool pass = true;
    Segment rightSegment = _tree->right(segment.ID()),
                 leftSegment = _tree->left(segment.ID());
    if (_domain->isIn(_tree->proximalPoint(segment.ID()),
                      _tree->distalPoint(segment.ID())) &&
        _domain->isIn(_tree->proximalPoint(rightSegment.ID()),
                      _tree->distalPoint(rightSegment.ID())) &&
        _domain->isIn(_tree->proximalPoint(leftSegment.ID()),
                      _tree->distalPoint(leftSegment.ID()))) {
      for (i = 0; i < _numberOfGeometricRestrictions; i++) {
        if (!_geometricRestrictions[i]->pass(segment)) {
          pass = false;
          break;
        }
      }
    } else {
      pass = false;
    }

    return pass;
  }

  /**
   * @brief Find the bifurcation connection that minimize the target funcion.
   *
   * @param segment
   * @return Connection
   */
  virtual Connection bifurcation(Segment segment) = 0;
};
#endif  //_CCOLAB_CCO_INTERFACE_GEOMETRIC_OPTIMIZATION_H
