#include <iostream>
#include <string>
#include "LBlock.h"
#include <vector>
using namespace std;

LBlock::LBlock(int deLevel) : deLevel{deLevel}, count{4} {}
LBlock::~LBlock() {
  coordFill.clear();
  coords.clear();
  coordsCpy.clear();
}

void LBlock::left() {
  int len = coordsCpy.size();
  for(int i = 0; i < len; ++i) {
    --coordsCpy[i][0];
  }
}

void LBlock::right() {
  int len = coordsCpy.size();
  for(int i = 0; i < len; ++i) {
    ++coordsCpy[i][0];
  }
}

void LBlock::down() {
  int len = coordsCpy.size();
  for(int i = 0; i < len; ++i) {
    --coordsCpy[i][1];
  }
}

int LBlock::getLevel() {
  return deLevel;
}

bool LBlock::modifyCount() {
  count--;
  if (count != 0) {
    return false;
  } else {
    return true;
  }
}


void LBlock::clockwise() {
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


void LBlock::changeContent(bool check) {
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

void LBlock::counterClockwise() {
  for (int i = 0; i < 3; ++i) {
    clockwise();
  }
}

string LBlock::getType() {
  return "L";
}


vector<bool>& LBlock::getCoordFill() { return coordFill; }
vector<vector<int>>& LBlock::getCoords() { return coords; }
vector<vector<int>>& LBlock::getCoordsCpy() { return coordsCpy; }
