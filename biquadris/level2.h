#ifndef _LEVEL2_H_
#define _LEVEL2_H_
#include "level.h"
using namespace std;

class Level2 : public Level {
public:
  Level2();
  string getBlock() override;
  int getLevel() override;
  ~Level2();
  void changeState(string file = "") override;
};

#endif
