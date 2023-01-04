#ifndef _LEVEL0_H_
#define _LEVEL0_H_
#include "level.h"

using namespace std;

class Level0 : public Level {
  int index;
  string filename;
  vector<string> store;
public:
  Level0(string name);
  string getBlock() override;
  int getLevel() override;
  ~Level0();
  void changeState(string file = "") override;
};

#endif
