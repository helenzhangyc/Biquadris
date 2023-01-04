#ifndef _TBLOCK_H_
#define _TBLOCK_H_

#include <string>
#include <vector>
#include <iostream>
#include "block.h"
using namespace std;

class TBlock : public Block {
private:
  int count;
  int deLevel;
  string blockType = "T";
  vector<bool> coordFill{true, true, true, false, true, false};
  vector<vector<int>> coords{vector<int>{0, -3}, vector<int>{1, -3}, vector<int>{2, -3}, vector<int>{0, -4}, vector<int>{1, -4}, vector<int>{2, -4}};
  vector<vector<int>> coordsCpy = coords;

public:
  TBlock(int deLevel);
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
  ~TBlock() override;
};

#endif
