#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <vector>
#include <memory>
#include "cell.h"
#include "block.h"
using namespace std;

class Xwindow;
class Player {
  public:
  int highestScore;
  int score;
  vector<vector<shared_ptr<Cell>>> gameBoard;
  shared_ptr<Block> currentBlock;
  shared_ptr<Block> nextBlock;
  shared_ptr<Block> currentBlockCpy;
  shared_ptr<Block> nextBlockCpy;
  bool blind;
  bool heavy;
  bool force;
  int blockNum;
  bool blockClear;
  int dropcount;
  bool starTerminate;

  Player(shared_ptr<Xwindow> w, bool showWindow, bool player); //player1 if player is true
  int setStar();
};

#endif