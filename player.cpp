#include "player.h"
using namespace std;

Player::Player(shared_ptr<Xwindow> w, bool showWindow, bool player) : 
highestScore{0}, score{0}, currentBlock{nullptr}, nextBlock{nullptr}, currentBlockCpy{nullptr}, nextBlockCpy{nullptr}, blind{false}, heavy{false}, force{false}, blockNum{0}, blockClear{false}, dropcount{0}, starTerminate{false} {
  for(int r = 0; r < 18; ++r) {
    vector<shared_ptr<Cell>> v;
    for (int c = 0; c < 11; ++c) {
      shared_ptr<Cell> cell = make_shared<Cell>(c, r, w, showWindow, player);
      v.push_back(cell);
    }
    gameBoard.push_back(v);
  }
}

int Player::setStar() {
  int starpos = 17;
  bool checkset = true;
  if (gameBoard[0][5]->filled() == true) {
    checkset = false;
  }
  for (int i = 0; i <= 17; ++i) {
    if (gameBoard[i][5]->filled() == false) {
      starpos = i;
      continue;
    } else {
      break;
    }
  }
  if (checkset) {
    gameBoard[starpos][5]->star = true;
    gameBoard[starpos][5]->draw();
  } else {
    starpos = -999;
    starTerminate = true;
  }
  return starpos;
}

