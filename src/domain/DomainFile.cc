/**
 * @file DomainFile.cc
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
#include "DomainFile.h"

DomainFile::DomainFile(string filename) : Domain() {
  _domainFunction = new TautologyFunction();
  open(filename);
}

DomainFile::DomainFile(string filename, DomainFunction *domainFunction)
    : Domain() {
  _domainFunction = domainFunction;
  open(filename);
}

DomainFile::DomainFile(string filename, int totalNumberOfPoints,
                       DomainFunction *domainFunction)
    : Domain() {
  _totalNumberOfPoints = totalNumberOfPoints;
  _domainFunction = domainFunction;
  open(filename);
}

DomainFile::~DomainFile() { 
  delete[] _points; 
  delete[] _seeds;
}

double DomainFile::pointCoordinate(int pointID, int coordinate) {
  return _points[pointID * dimension() + coordinate];
}

double DomainFile::seedCoordinate(int seedID, int coordinate) {
  return _seeds[seedID * dimension() + coordinate];
}

Point DomainFile::seed(int seedID) {
  Point *pt;
  pt = new Point(dimension());

  if (seedID >= 0 && seedID < _numberOfSeeds) {
    pt->setX(seedCoordinate(seedID, 0));
    pt->setY(seedCoordinate(seedID, 1));
    if (dimension() == 3) {
      pt->setZ(seedCoordinate(seedID, 2));
    }

    return *pt;
  } else {
    throw invalid_argument("Oops! Invalid seed ID.");
  }
}

Point DomainFile::point() {
  int i = 0;
  Point *pt;
  pt = new Point(dimension());

  if (hasAvailablePoint()) {
    pt->setX(pointCoordinate(_currentPoint, 0));
    pt->setY(pointCoordinate(_currentPoint, 1));
    if (dimension() == 3) {
      pt->setZ(pointCoordinate(_currentPoint, 2));
    }
    _currentPoint++;
    return *pt;
  } else {
    throw invalid_argument("Oops! No more points on domain file.");
  }
}

bool DomainFile::isIn(Point pointA, Point pointB) {
  return _domainFunction->isIn(pointA, pointB);
}

int DomainFile::totalNumberOfPoints() { return _totalNumberOfPoints; }

bool DomainFile::hasAvailablePoint() {
  return (_currentPoint < _totalNumberOfPoints);
}

void DomainFile::reset() { _currentPoint = 0; }

void DomainFile::setDomainFunction(DomainFunction *domainFunction) {
  _domainFunction = domainFunction;
}

DomainFunction *DomainFile::domainFunction() { return _domainFunction; }

bool DomainFile::open(string filename) {
  int i, j, pos, value, totalNumberOfPoints;
  double doubleValue;
  bool invalidFile = false, found;
  ifstream file;
  string line, keyword, errorMessage;
  file.open(filename);
  if (file.is_open()) {
    /* Read the vtk file version */
    getline(file, line);
    pos = line.find("# vtk DataFile Version ");
    if (pos == 0) {
      pos = line.find_first_of("0123456789");
      if (pos != string::npos) {
        stringstream(line.substr(pos)) >> _version;
      } else {
        errorMessage = "Invalid first line.";
        invalidFile = true;
      }
    } else {
      invalidFile = true;
    }

    /* Read the file title */
    if (!invalidFile) {
      getline(file, _title);
      invalidFile = (_title.length() > 256);
      if (invalidFile) {
        errorMessage = "The title must have less than 256 characters.";
      }
    }

    /* Read the data type */
    if (!invalidFile) {
      found = false;
      getline(file, line);
      for (i = 0; i < 2; i++) {
        if (line.compare(_dataTypeKeyword[i]) == 0) {
          _dataType = i;
          found = true;
          break;
        }
      }

      invalidFile = !found;
      if (invalidFile) {
        errorMessage = "Invalid data type. It must be ASCII or BINARY.";
      }
    }

    /* Read the dataset type */
    if (!invalidFile) {
      getline(file, line);
      pos = line.find(_datasetTypeKeyword);
      if (pos == 0) {
        pos = line.find_first_of("0123456789");
        if (pos != string::npos) {
          stringstream(line.substr(pos)) >> value;
          /* The vtk field file must have 4 arrays. */
          invalidFile = (value != 4);
        } else {
          invalidFile = true;
        }
      } else {
        invalidFile = true;
      }

      if (invalidFile) {
        errorMessage = "Invalid dataset type.";
      }
    }

    /* Read the dimension */
    if (!invalidFile) {
      keyword = "dimension";
      getline(file, line);
      pos = line.find(keyword);
      if (pos == 0) {
        getline(file, line);
        stringstream(line.substr(0)) >> value;
        if (value == 2 || value == 3) {
          setDimension(value);

          /* Skip one line */
          getline(file, line);
        } else {
          invalidFile = true;
        }
      } else {
        invalidFile = true;
      }

      if (invalidFile) {
        errorMessage = "Invalid dimension.";
      }
    }

    /* Read the area or volume */
    if (!invalidFile) {
      keyword = (dimension() == 2) ? "area" : "volume";
      getline(file, line);
      pos = line.find(keyword);
      if (pos == 0) {
        getline(file, line);
        stringstream(line.substr(0)) >> doubleValue;
        if (doubleValue >= 0.0) {
          setVolume(doubleValue);

          /* Skip one line */
          getline(file, line);
        } else {
          invalidFile = true;
        }
      } else {
        invalidFile = true;
      }

      if (invalidFile) {
        errorMessage = "Invalid " + keyword + ".";
      }
    }

    /* Read the seeds */
    if (!invalidFile) {
      keyword = "seeds";
      getline(file, line);
      pos = line.find(keyword);
      if (pos == 0) {
        stringstream(line.substr(keyword.length() + 3)) >> _numberOfSeeds;
        if (_numberOfSeeds > 0) {
          _seeds = new double[_numberOfSeeds * dimension()];
          for (i = 0; i < _numberOfSeeds; i++) {
            getline(file, line);
            istringstream iss(line);
            for (j = 0; j < dimension(); j++) {
              iss >> doubleValue;
              _seeds[i * dimension() + j] = doubleValue;
            }
          }

          /* Skip one line */
          getline(file, line);
        } else {
          invalidFile = true;
        }
      } else {
        invalidFile = true;
      }

      if (invalidFile) {
        errorMessage = "Invalid seeds.";
      }
    }

    /* Read the points */
    if (!invalidFile) {
      keyword = "points";
      getline(file, line);
      pos = line.find(keyword);
      if (pos == 0) {
        stringstream(line.substr(keyword.length() + 3)) >> totalNumberOfPoints;
        if (_totalNumberOfPoints == 0) {
          _totalNumberOfPoints = totalNumberOfPoints;
        } else {
          if (_totalNumberOfPoints > totalNumberOfPoints) {
            _totalNumberOfPoints = totalNumberOfPoints;
          }
        }

        if (_totalNumberOfPoints > 0) {
          _points = new double[_totalNumberOfPoints * dimension()];
          for (i = 0; i < _totalNumberOfPoints; i++) {
            getline(file, line);
            istringstream iss(line);
            for (j = 0; j < dimension(); j++) {
              iss >> doubleValue;
              _points[i * dimension() + j] = doubleValue;
            }
          }
        } else {
          invalidFile = true;
        }
      } else {
        invalidFile = true;
      }

      if (invalidFile) {
        errorMessage = "Invalid points.";
      }
    }
  } else {
    invalidFile = true;
    errorMessage = "The file is not opening.";
  }

  file.close();

  if (invalidFile) {
    cout << "Oops! " << filename << " invalid domain file." << endl;
    cout << "Error: " << errorMessage << endl;
  }

  return invalidFile;
}

int DomainFile::numberOfSeeds() { return _numberOfSeeds; }

void DomainFile::print() {
  int i, j;
  cout << "VTK file version: " << _version << endl;
  cout << "VTK file title: " << _title << endl;
  cout << "_dimension: " << dimension() << endl;
  cout << "seeds: " << endl;
  for (i = 0; i < _numberOfSeeds; i++) {
    cout << i << ": (" << seedCoordinate(i, 0) << ", " << seedCoordinate(i, 1);
    if (dimension() == 3) {
      cout << ", " << seedCoordinate(i, 2);
    }
    cout << ")" << endl;
  }

  cout << "total of seeds: " << _numberOfSeeds << endl;
  cout << "points: " << endl;
  for (i = 0; i < _totalNumberOfPoints; i++) {
    cout << i << ": (" << pointCoordinate(i, 0) << ", "
         << pointCoordinate(i, 1);
    if (dimension() == 3) {
      cout << ", " << pointCoordinate(i, 2);
    }
    cout << ")" << endl;
  }

  cout << "total of points: " << _totalNumberOfPoints << endl;
}
