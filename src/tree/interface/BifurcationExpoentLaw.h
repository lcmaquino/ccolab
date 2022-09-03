/**
 * @file BifurcationExpoentLaw.h
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

#ifndef _CCOLAB_TREE_INTERFACE_BIFURCATIONEXPOENTLAW_H
#define _CCOLAB_TREE_INTERFACE_BIFURCATIONEXPOENTLAW_H
class BifurcationExpoentLaw {
 public:
  /**
   * @brief Construct a new Bifurcation Expoent Law object.
   * 
   */
  BifurcationExpoentLaw() {}

  /**
   * @brief Destroy the Bifurcation Expoent Law object.
   * 
   */
  ~BifurcationExpoentLaw() {}

  /**
   * @brief Evaluate the bifurcation expoent at the given segement
   * bifurcation level.
   * 
   * @param segmentLevel The segment bifurcation level.
   * @return The bifurcation expoent.
   */
  virtual double eval(int segmentLevel) = 0;
};
#endif //_CCOLAB_TREE_INTERFACE_BIFURCATIONEXPOENTLAW_H
