#include "level1.h"
using namespace std;

Level1::Level1() {}
Level1::~Level1() {

}

int Level1::getLevel() {
  return 1;
}

string Level1::getBlock() {
  int tmp = rand() % 12 + 1;
  if (tmp == 1 || tmp == 12) {
    return "I";
  } else if (tmp == 2 || tmp == 11) {
    return "J";
  } else if (tmp == 3 || tmp == 10) {
    return "L";
  } else if (tmp == 4 || tmp == 9) {
    return "O";
  } else if (tmp == 5 || tmp == 8) {
    return "T";
  } else if (tmp == 7) {
    return "S";
  } else {
    return "Z";
  }
}

void Level1::changeState(string file) {}
