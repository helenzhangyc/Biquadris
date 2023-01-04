#include "level2.h"
using namespace std;


Level2::Level2() {

}

Level2::~Level2() {

}

int Level2::getLevel() {
  return 2;
}

string Level2::getBlock() {
  int tmp = rand() % 7 + 1;
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
  } else if (tmp == 7) {
    return "S";
  } else {
    return "Z";
  }
}

void Level2::changeState(string file) {}
