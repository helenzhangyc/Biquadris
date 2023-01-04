#ifndef _SBLOCK_H_
#define _SBLOCK_H_

#include <string>
#include <vector>
#include <iostream>
#include "block.h"
using namespace std;

class SBlock : public Block {
private:
  int count;
  int deLevel;
  string blockType = "S";
  vector<bool> coordFill{false, true, true, true, true, false};
  vector<vector<int>> coords{vector<int>{0, -3}, vector<int>{1, -3}, vector<int>{2, -3}, vector<int>{0, -4}, vector<int>{1, -4}, vector<int>{2, -4}};
  vector<vector<int>> coordsCpy = coords;
  
public:
  SBlock(int deLevel);
  void left() override;
  void right() override;
  void down() override;
  int getLevel() override;
  bool modifyCount() override;
  void clockwise() override;
  void changeContent(bool check) override;
  void counterClockwise() override;
  string getType() override;
  vector<bool> &getCoordFill() override;
  vector<vector<int>> &getCoords() override;
  vector<vector<int>> &getCoordsCpy() override;
  ~SBlock() override;
};

#endif
