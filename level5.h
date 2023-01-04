#ifndef _LEVEL5_H_
#define _LEVEL5_H_
#include "level.h"
using namespace std;

class Level5 : public Level {
  bool checkRandom;
  int randomIndex;
  string filename;
  vector<string> store;
public:
  Level5();
  string getBlock() override;
  int getLevel() override;
  void changeState(string file = "") override;
  ~Level5();
};

#endif
