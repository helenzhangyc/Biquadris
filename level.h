#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <random>

using namespace std;

class Level {
public:
  virtual string getBlock() = 0;
  virtual int getLevel() = 0;
  virtual ~Level() = 0;
  virtual void changeState(string file = "") = 0;
};

#endif
