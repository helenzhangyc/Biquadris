#include <iostream>
#include <string>
#include "OBlock.h"
#include <vector>
using namespace std;

OBlock::OBlock(int deLevel) : deLevel{deLevel}, count{4} {}
OBlock::~OBlock() {
  coordFill.clear();
  coords.clear();
  coordsCpy.clear();
}

void OBlock::left() {
  int len = coordsCpy.size();
  for(int i = 0; i < len; ++i) {
    --coordsCpy[i][0];
  }
}

void OBlock::right() {
  int len = coordsCpy.size();
  for(int i = 0; i < len; ++i) {
    ++coordsCpy[i][0];
  }
}

void OBlock::down() {
  int len = coordsCpy.size();
  for(int i = 0; i < len; ++i) {
    --coordsCpy[i][1];
  }
}

int OBlock::getLevel() {
  return deLevel;
}

bool OBlock::modifyCount() {
  count--;
  if (count != 0) {
    return false;
  } else {
    return true;
  }
}


void OBlock::clockwise() {
  // find the bottom left
  int minX = 10;
  int minY = 0;
  // find the top right
  int maxX = 0;
  int maxY = -17;

  int len = coordsCpy.size();
  for (int i = 0; i < len; ++i) {
    int curX = coordsCpy[i][0];
    int curY = coordsCpy[i][1];
    if (curX <= minX && curY <= minY) {
      minX = curX;
      minY = curY;
    }
    if (curX >= maxX && curY >= maxY) {
      maxX = curX;
      maxY = curY;
    }   
  }

  // rotate
  for (int i = 0; i < len; ++i) {
    int curX = coordsCpy[i][0];
    int curY = coordsCpy[i][1];
    int newX = minX + minY - curY;
    int newY = curX + minY - minX;
    coordsCpy[i][0] = newX;
    coordsCpy[i][1] = newY;
  }

  // move right by (maxY - minY) cells
  for (int i = 0; i < (maxY - minY); ++i) {
    right();
  }
}


void OBlock::changeContent(bool check) {
  int len = coords.size();
  if (check == false) {
    // copy coords into coordsCpy
    for (int i = 0; i < len; ++i) {
      int tempX = coords[i][0];
      int tempY = coords[i][1];
      coordsCpy[i][0] = tempX;
      coordsCpy[i][1] = tempY;
    }
  } else {
    // copy coordsCpy into coords
    for (int i = 0; i < len; ++i) {
      int tempX = coordsCpy[i][0];
      int tempY = coordsCpy[i][1];
      coords[i][0] = tempX;
      coords[i][1] = tempY;
    }
  }
}

void OBlock::counterClockwise() {
  for (int i = 0; i < 3; ++i) {
    clockwise();
  }
}

string OBlock::getType() {
  return "O";
}

vector<bool>& OBlock::getCoordFill() { return coordFill; }
vector<vector<int>>& OBlock::getCoords() { return coords; }
vector<vector<int>>& OBlock::getCoordsCpy() { return coordsCpy; }

