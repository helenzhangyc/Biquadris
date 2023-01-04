#ifndef _LEVEL4_H_
#define _LEVEL4_H_
#include "level.h"
using namespace std;

class Level4 : public Level {
  bool checkRandom;
  int randomIndex;
  string filename;
  vector<string> store;
public:
  Level4();
  string getBlock() override;
  int getLevel() override;
  void changeState(string file = "") override;
  ~Level4();
};

#endif
