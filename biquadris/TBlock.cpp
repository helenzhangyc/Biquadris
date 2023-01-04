#include <iostream>
#include <string>
#include "TBlock.h"
#include <vector>
using namespace std;

TBlock::TBlock(int deLevel) : deLevel{deLevel}, count{4} {}
TBlock::~TBlock() {
  coordFill.clear();
  coords.clear();
  coordsCpy.clear();
}

void TBlock::left() {
  int len = coordsCpy.size();
  for(int i = 0; i < len; ++i) {
    --coordsCpy[i][0];
  }
}

void TBlock::right() {
  int len = coordsCpy.size();
  for(int i = 0; i < len; ++i) {
    ++coordsCpy[i][0];
  }
}

void TBlock::down() {
  int len = coordsCpy.size();
  for(int i = 0; i < len; ++i) {
    --coordsCpy[i][1];
  }
}

int TBlock::getLevel() {
  return deLevel;
}

bool TBlock::modifyCount() {
  count--;
  if (count != 0) {
    return false;
  } else {
    return true;
  }
}


void TBlock::clockwise() {
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


void TBlock::changeContent(bool check) {
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

void TBlock::counterClockwise() {
  for (int i = 0; i < 3; ++i) {
    clockwise();
  }
}

string TBlock::getType() {
  return "T";
}


vector<bool>& TBlock::getCoordFill() { return coordFill; }
vector<vector<int>>& TBlock::getCoords() { return coords; }
vector<vector<int>>& TBlock::getCoordsCpy() { return coordsCpy; }
