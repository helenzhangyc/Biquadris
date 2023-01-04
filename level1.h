#ifndef _LEVEL1_H_
#define _LEVEL1_H_
#include "level.h"
using namespace std;

class Level1 : public Level {

public:
  Level1();
  string getBlock() override;
  int getLevel() override;
  ~Level1();
  void changeState(string file = "") override;
};

#endif
