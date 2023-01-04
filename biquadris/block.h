#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Block {
public:
  virtual string getType() = 0;
  virtual void left() = 0;
  virtual void right() = 0;
  virtual void down() = 0;
  virtual int getLevel() = 0;
  virtual bool modifyCount() = 0;
  virtual void clockwise() = 0;
  virtual void counterClockwise() = 0;
  virtual void changeContent(bool check) = 0;
  virtual ~Block() = 0;
  virtual vector<bool> &getCoordFill() = 0;
  virtual vector<vector<int>> &getCoords() = 0;
  virtual vector<vector<int>> &getCoordsCpy() = 0;
};

#endif
