#include "level0.h"
using namespace std;

Level0::Level0(string name) : filename(name), index(0) {
  ifstream infile{ filename };
  string blockName;
    while ( true ) {
        infile >> blockName;
        if ( infile.fail() ) break;
        store.emplace_back(blockName);
    }
}


int Level0::getLevel() {
  return 0;
}


string Level0::getBlock() {
  string tmp = store[index];
  index = index + 1;
  if (index == store.size()) {
    index = 0;
  }
  return tmp;
}

Level0::~Level0() {
  store.clear();
}

void Level0::changeState(string file) {};
