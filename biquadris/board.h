#ifndef _BOARD_H_
#define _BOARD_H_
#include "player.h"
#include "block.h"
#include "cell.h"
#include "window.h"
#include "level.h"
#include <memory>
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "LBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "ZBlock.h"
#include "TBlock.h"
#include "IBlock.h"
#include "OBlock.h"

using namespace std;

class Board {
private:
  shared_ptr<Player> player1;
  shared_ptr<Player> player2;
  shared_ptr<Level> player1Lvl;
  shared_ptr<Level> player2Lvl;
  shared_ptr<Xwindow> w;
  bool showWindow;
public:
  Board(bool showWindow); //如果false， 不show window， 如果true， window board一起show
  ~Board();
  void setUp(string filename1, string filename2, int level1, int level2);
  void setLevel(int n, bool b, string file);
  void init(); //give players blocks
  void getCurBlock(bool check);
  void getNextBlock(bool p);
  void show(bool showWindow);
  void putBlock(); // put two current block onto the gameBoard (the gameBoard is empty)
  bool putCurBlock(bool p); // put the currentBlock of both players onto the gameBoard
  // If has place to put, put it on and return true, return false otherwise

  bool checkFilled(shared_ptr<Player> p);
  bool validCW(bool check);
  bool validCCW(bool check);   
  bool validLeft(bool check);
  bool validRight(bool check);
	bool validDown(bool check);
  bool drop(bool check);
  bool checkGrid(bool check);
  bool isHeavy(bool check);
  void restart();
  bool changeBlock(string bType, bool player); 
  string win();
  void changeToHeavy(bool check);
  void changeToBlind(bool check); 
  void updatePlayer(bool check); // updatePlayer(等会儿谁写完了吱我一下)
  void changeRandom (bool check, string filename);
  void modifyDrop(bool check, int count);
  int getDroptime(bool check);
  void removeBlind(bool check);//check true 那么remove player1的heavy false check==false p2 heavy turn false
  void hint(bool check);
  bool checkFilledHint(shared_ptr<Player> p, vector<vector<int>> coordinates);
  bool operate(shared_ptr<Player> p, vector<vector<int>> coordinates, int &leftcount, int &rightcount, int &downdeep); 
  void leftHint(vector<vector<int>>& coords); 
  void rightHint(vector<vector<int>>& coords); 
  void downHint(vector<vector<int>>& coords); 
  bool dropHint(shared_ptr<Player> p,vector<vector<int>> &coords);
  int minY(vector<vector<int>> coords);
  int getLevel(bool check);
  string finalWin();
  bool StarTerminate(bool check);
};

#endif
