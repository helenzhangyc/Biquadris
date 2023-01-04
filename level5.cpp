#include "level5.h"
using namespace std;

Level5::Level5() : randomIndex(0), checkRandom(true) {}

string Level5::getBlock() {
  if (checkRandom == false) {
    string blockName = store[randomIndex];
    randomIndex = randomIndex + 1;
    if (randomIndex == store.size()) {
      randomIndex = 0;
    }
    return blockName;
  } else {
    int tmp = rand() % 5 + 1;
    if (tmp == 1) {
      return "J";
    } else if (tmp == 2) {
      return "L";
    } else if (tmp == 3) {
      return "T";
    } else if (tmp == 4) {
      return "S";
    } else {
      return "Z";
    }
  }
}

Level5::~Level5() {
  store.clear();
}

int Level5::getLevel() {
  return 5;
}

void Level5::changeState(string file) {
  if (checkRandom == true) {
    checkRandom = false;
    store.clear();
    filename = file;
    ifstream infile{ filename };
    string blockName;
    while ( true ) {
        infile >> blockName;
        if ( infile.fail() ) break;
        store.emplace_back(blockName);
    }
    randomIndex = 0;
  } else {
    checkRandom = true;
  }
}
