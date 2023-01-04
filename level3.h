#ifndef _LEVEL3_H_
#define _LEVEL3_H_
#include "level.h"
using namespace std;

class Level3 : public Level {
  bool checkRandom;
  int randomIndex;
  string filename;
  vector<string> store;
public:
  Level3();
  string getBlock() override;
  int getLevel() override;
  void changeState(string file = "") override;
  ~Level3();
};

#endif
