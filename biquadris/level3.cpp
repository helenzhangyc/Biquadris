#include "level3.h"
#include <iostream>
using namespace std;

Level3::Level3() : checkRandom(true), randomIndex(0) {

}

string Level3::getBlock() {
  if (checkRandom == false) {
    string blockName = store[randomIndex];
    randomIndex = randomIndex + 1;
    if (randomIndex == store.size()) {
      randomIndex = 0;
    }
    return blockName;
  } else {
    int tmp = rand() % 9 + 1;
    if (tmp == 1) {
      return "I";
    } else if (tmp == 2) {
      return "J";
    } else if (tmp == 3) {
      return "L";
    } else if (tmp == 4) {
      return "O";
    } else if (tmp == 5) {
      return "T";
    } else if (tmp == 6 || tmp == 8) {
      return "S";
    } else {
      return "Z";
    }
  }
}

Level3::~Level3() {
  store.clear();
}

int Level3::getLevel() {
  return 3;
}

void Level3::changeState(string file) {
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
