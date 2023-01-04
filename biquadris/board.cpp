#include "board.h"
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

Board::Board(bool showWindow) : showWindow{showWindow}, w{nullptr} {
  if (showWindow) w = make_shared<Xwindow>();
  else w = nullptr;
  player1 = make_shared<Player>(w, showWindow, true);
  player2 = make_shared<Player>(w, showWindow, false);
}

Board::~Board() {

}

void Board::setUp(string filename1, string filename2, int level1, int level2) {
  if (level1 == 0) {
    player1Lvl = make_shared<Level0>(filename1);
    player2Lvl = make_shared<Level0>(filename2);
  } else if (level1 == 1) {
    player1Lvl = make_shared<Level1>();
    player2Lvl = make_shared<Level1>();
  } else if (level1 == 2) {
    player1Lvl = make_shared<Level2>();
    player2Lvl = make_shared<Level2>();
  } else if (level1 == 3) {
    player1Lvl = make_shared<Level3>();
    player2Lvl = make_shared<Level3>();
  } else {
    player1Lvl = make_shared<Level4>();
    player2Lvl = make_shared<Level4>();
  }

  if(showWindow) w -> setUp(level1, level2);
}

void Board::getCurBlock(bool check) {
  shared_ptr<Player> p = nullptr;
  shared_ptr<Level> l = nullptr;
  if (check == true) {
    l = player1Lvl;
    p = player1;
  } else {
    l = player2Lvl;
    p = player2;
  }
  string blockType = l->getBlock();
  int level = l->getLevel();
  if (blockType == "I") {
    p->currentBlock = make_shared<IBlock>(level);
  } else if (blockType == "J") {
    p->currentBlock = make_shared<JBlock>(level);
  } else if (blockType == "L") {
    p->currentBlock = make_shared<LBlock>(level);
  } else if (blockType == "O") {
    p->currentBlock = make_shared<OBlock>(level);
  } else if (blockType == "S") {
    p->currentBlock = make_shared<SBlock>(level);
  } else if (blockType == "Z") {
    p->currentBlock = make_shared<ZBlock>(level);
  } else {
    p->currentBlock = make_shared<TBlock>(level);
  }
}

void Board::getNextBlock(bool check) {
  shared_ptr<Player> p = nullptr;
  shared_ptr<Level> l = nullptr;
  if (check == true) {
    l = player1Lvl;
    p = player1;
  } else {
    l = player2Lvl;
    p = player2;
  }
  string blockType = l->getBlock();
  int level = l->getLevel();
  if (blockType == "I") {
    p->nextBlock = make_shared<IBlock>(level);
  } else if (blockType == "J") {
    p->nextBlock = make_shared<JBlock>(level);
  } else if (blockType == "L") {
    p->nextBlock = make_shared<LBlock>(level);
  } else if (blockType == "O") {
    p->nextBlock = make_shared<OBlock>(level);
  } else if (blockType == "S") {
    p->nextBlock = make_shared<SBlock>(level);
  } else if (blockType == "Z") {
    p->nextBlock = make_shared<ZBlock>(level);
  } else {
    p->nextBlock = make_shared<TBlock>(level);
  }
  if(showWindow) w -> setNextBlock(check, blockType);
}

void Board::setLevel(int n, bool b, string file) {
  if (n == 0) {
    if (b) {
      shared_ptr<Level> l = make_shared<Level0>(file);
      swap(player1Lvl, l);
    }
    else {
      shared_ptr<Level> l = make_shared<Level0>(file);
      swap(player2Lvl, l);
    }
  } else if (n == 1) {
    if (b) { 
      shared_ptr<Level> l = make_shared<Level1>();
      swap(player1Lvl, l);
    }
    else { 
      shared_ptr<Level> l = make_shared<Level1>();
      swap(player2Lvl, l);
    }
  } else if (n == 2) {
    if (b) {
      shared_ptr<Level> l = make_shared<Level2>();
      swap(player1Lvl, l);
    }
    else {
      shared_ptr<Level> l = make_shared<Level2>();
      swap(player2Lvl, l);
    }
  } else if (n == 3) {
    if (b) {
      shared_ptr<Level> l = make_shared<Level3>();
      swap(player1Lvl, l);
    }
    else {
      shared_ptr<Level> l = make_shared<Level3>();
      swap(player2Lvl, l);
    }
  } else 
    if (b) {
      shared_ptr<Level> l = make_shared<Level4>();
      swap(player1Lvl, l);
    }
    else {
      shared_ptr<Level> l = make_shared<Level4>();
      swap(player2Lvl, l);
    }

    if(showWindow) w -> setLevel(b, n);
} 


void Board::init() {
  getCurBlock(true);
  getCurBlock(false);
  getNextBlock(true);
}

bool Board::checkFilled(shared_ptr<Player> p) {
	bool valid = true;
  vector<vector<int>>& coordinates = p->currentBlock->getCoordsCpy();
  vector<bool>& coordinatesFill = p->currentBlock->getCoordFill();
	for(int i = 0; i < coordinates.size(); ++i) {
		if (coordinatesFill[i]) { 
			vector<int> coord = coordinates[i];
			int x = coord[0];
			int y = abs(coord[1]);
			if (0 <= x && x< 11 && 0 <= y && y < 18) {
				if ((p->gameBoard)[y][x]->filled() && p->gameBoard[y][x]->storedBlock != p->currentBlock) {
          valid = false;
          break;
        }
			} else {
        valid = false;
        break;
      }
		}
	}
  if (valid == true) {
    vector<vector<int>>& lastcoordinate = p->currentBlock->getCoords();
    for (int i = 0; i < lastcoordinate.size(); ++i) {
      if (coordinatesFill[i]) {
			vector<int> coord = lastcoordinate[i];
			int x = coord[0];
			int y = abs(coord[1]);
      p->gameBoard[y][x]->clear(); //undraw cell 
      }
    }
    p->currentBlock->changeContent(true);
    for (int i = 0; i < coordinates.size(); ++i) {
      if (coordinatesFill[i]) { 
			vector<int> coord = coordinates[i];
			int x = coord[0];
			int y = abs(coord[1]);
      p->gameBoard[y][x]->storedBlock = p->currentBlock;
      p->gameBoard[y][x]->draw(); //draw cell 
      }
    }
  } else {
    p->currentBlock->changeContent(false);
  }
	return valid;
}

bool Board::validCW(bool check) {
  shared_ptr<Player> p = nullptr;
  if (check == true) {
    p = player1;
  } else {
    p = player2;
  }
	p->currentBlock->clockwise();
	return checkFilled(p);
}

bool Board::validCCW(bool check) {
  shared_ptr<Player> p = nullptr;
  if (check == true) {
    p = player1;
  } else {
    p = player2;
  }
	p->currentBlock->counterClockwise();
	return checkFilled(p);
}

bool Board::validLeft(bool check) {
  shared_ptr<Player> p = nullptr;
  if (check == true) {
    p = player1;
  } else {
    p = player2;
  }
	p->currentBlock->left();
	return checkFilled(p);
}

bool Board::validRight(bool check) {
  shared_ptr<Player> p = nullptr;
  if (check == true) {
    p = player1;
  } else {
    p = player2;
  }
	p->currentBlock->right();
	return checkFilled(p);
}

bool Board::validDown(bool check) {
  shared_ptr<Player> p = nullptr;
  if (check == true) {
    p = player1;
  } else {
    p = player2;
  }
	p->currentBlock->down();
	return checkFilled(p);
}

bool Board::drop(bool check) {
  while (validDown(check) != false) {
    continue;
  }
  shared_ptr<Player> p = nullptr;
  if (check == true) {
    p = player1;
  } else {
    p = player2;
  }
  vector<vector<int>>& coords = p->currentBlock->getCoords();
  // check if all the coords are in the red part
  for (auto n : coords) {
    if (n[1] > -3) {
      return false;
    }
  }
  p->blockNum++;
  return true;
}


// return true if special actions are triggered, false otherwise
bool Board::checkGrid(bool check) {
  shared_ptr<Player> player = nullptr;
  shared_ptr<Level> lvl = nullptr;
  if (check == true) {
    player = player1;
    lvl = player1Lvl;
  } else {
    player = player2;
    lvl = player2Lvl;
  }
  int cancelLine = 0;
  int increaseScore = 0;
  // find max and min coord
  vector<vector<int>> coords = player->currentBlock->getCoords();
  int minX = 10;
  int minY = 0;
  int maxX = 0;
  int maxY = -17;
  int len = coords.size();
  for (int i = 0; i < len; ++i) {
    int curX = coords[i][0];
    int curY = coords[i][1];
    if (curX <= minX && curY <= minY) {
      minX = curX;
      minY = curY;
    }
    if (curX >= maxX && curY >= maxY) {
      maxX = curX;
      maxY = curY;
    }
  }
  int stop = 0 - maxY;
  for (int i = abs(minY); i >= stop; --i) {
    bool needCancel = true;
    for (int j = 0; j <= 10; ++j) {     
      if (player->gameBoard[i][j]->filled() == false) {
        needCancel = false;
        break;
      }
    }
    if (needCancel == true) {
      cancelLine++;
      for (int j = 0; j <= 10; ++j) {
        if (player->gameBoard[i][j]->storedBlock != nullptr) { 
          bool cancelTheBlock = player->gameBoard[i][j]->storedBlock->modifyCount();
          if (cancelTheBlock == true) {
            increaseScore += (player->gameBoard[i][j]->storedBlock->getLevel() + 1) * (player->gameBoard[i][j]->storedBlock->getLevel() + 1);
          }
        }
      }
      // move down each row
      for (int y = i - 1; y >= 0; --y) {
        for (int x = 0; x <= 10; ++x) {
          player->gameBoard[y+1][x]->update(player->gameBoard[y][x]);
          cout << "LINE 335" << endl;

        }
        if (y == 0) {
          for (int x = 0; x <= 10; ++x) {
            player->gameBoard[y][x]->clear(); 
            cout << "LINE 340" << endl;
          }
        }
      } 
      i = i + 1;
    }
  }
  // calculate the increscore caused by cancelling lines
  int curLevel = lvl->getLevel();
  if (cancelLine != 0) {
    increaseScore += (curLevel + cancelLine) * (curLevel + cancelLine);
  }
  player->score += increaseScore;
  if (player->score > player->highestScore) {
    player->highestScore = player->score;
  }
  if (lvl->getLevel() == 4) {
    if (cancelLine > 0) {
      player->blockClear = true;
    }
    if (player->blockNum % 5 == 0) {
      if (player->blockClear == false) {
        int starpos = player->setStar();
        if (starpos >= 0) {
        bool needCancel = true;
        for (int j = 0; j <= 10; ++j) {     
          if (player->gameBoard[starpos][j]->filled() == false) {
            needCancel = false;
            break;
          }
        }
        if (needCancel == true) {
          player->score += (curLevel + 1) * (curLevel + 1);
          for (int j = 0; j <= 10; ++j) {
            if (player->gameBoard[starpos][j]->storedBlock != nullptr) { 
              bool cancelTheBlock = player->gameBoard[starpos][j]->storedBlock->modifyCount();
              if (cancelTheBlock == true) {
                player->score += (player->gameBoard[starpos][j]->storedBlock->getLevel() + 1) * (player->gameBoard[starpos][j]->storedBlock->getLevel() + 1);
              }
            }
          }
      if (player->score > player->highestScore) {
        player->highestScore = player->score;
      }
          for (int y = starpos - 1; y >= 0; --y) {
            for (int x = 0; x <= 10; ++x) {
              player->gameBoard[y+1][x]->update(player->gameBoard[y][x]);
              cout << "LINE 385" << endl; 
            }
            if (y == 0) {
              for (int x = 0; x <= 10; ++x) {
                player->gameBoard[y][x]->clear();
                cout << "LINE 390" << endl;
              }
            }
          } 
        }
      }
    }
      player->blockClear = false;
    }
  }
  
  if (showWindow) {
    w -> setScore(check, player->score);
    w -> setHighest(check, player->score);
  }

  if (cancelLine >= 2) {
    return true;
  } else {
  return false;
  }
}



bool Board::isHeavy(bool check) {
  if (check) {
    return player1->heavy;
  } else {
    return player2->heavy;
  }
}


void Board::removeBlind(bool check) {
  if (check == true) {
    player1->blind = false;
    for (int r = 5; r <= 14; ++r) {
      for (int c = 2; c <= 8; ++c) {
        player1 -> gameBoard[r][c] -> unsetBlind();
      }
    }
  } else {
    player2->blind = false;
    for (int r = 5; r <= 14; ++r) {
      for (int c = 2; c <= 8; ++c) {
        player2 -> gameBoard[r][c] -> unsetBlind();
      }
    }
  }
}

void printFirstLine(string blockType) {
  if (blockType == "I") {
    cout << "IIII       ";
  } else if (blockType == "J") {
    cout << "J          ";
  } else if (blockType == "L") {
    cout << "  L        ";
  } else if (blockType == "O") {
    cout << "OO         ";
  } else if (blockType == "S") {
    cout << " SS        ";
  } else if (blockType == "Z") {
    cout << "ZZ         ";
  } else if (blockType == "T") {
    cout << "TTT        ";
  }
}

void printSecondLine(string blockType) {
  if (blockType == "I") {
    cout << "           ";
  } else if (blockType == "J") {
    cout << "JJJ        ";
  } else if (blockType == "L") {
    cout << "LLL        ";
  } else if (blockType == "O") {
    cout << "OO         ";
  } else if (blockType == "S") {
    cout << "SS         ";
  } else if (blockType == "Z") {
    cout << " ZZ        ";
  } else if (blockType == "T") {
    cout << " T         ";
  }
}

void Board::show(bool showWindow) {
  bool p1blind = false;
  bool p2blind = false;
  if (player1->blind == true) {
    p1blind = true;
  }
  if (player2->blind == true) {
    p2blind = true;
  }
    cout << "Level:    " << player1Lvl->getLevel() << "      " << "Level:    " << player2Lvl->getLevel() << endl;
    cout << "Score:";
    cout << setw(5);
    cout << player1->score;
    cout << "      ";
    cout << "Score:";
    cout << setw(5);
    cout << player2->score << endl;
    cout << "-----------      -----------" << endl;
    
    for (int row = 0; row < 18; row++) {
      vector<shared_ptr<Cell>> p1CurRow = player1->gameBoard[row];
      vector<shared_ptr<Cell>> p2CurRow = player2->gameBoard[row];
      int len = p1CurRow.size();
      for (int col = 0; col < len; ++col) {
        if (p1blind == true && row >= 5 && row <= 14 && col >= 2 && col <= 8) {
          cout << "?";
        } else {
          if (p1CurRow[col]->storedBlock != nullptr) {
            cout << p1CurRow[col]->storedBlock->getType();
          } else if (p1CurRow[col]->star == true) {
            cout << "*";
          } else {
            cout << " ";
          }
        }
      }
      cout << "      ";
      for (int col = 0; col < len; ++col) {
        if (p2blind == true && row >= 5 && row <= 14 && col >= 2 && col <= 8) {
          cout << "?";
        } else {
          if (p2CurRow[col]->storedBlock != nullptr) {
            cout << p2CurRow[col]->storedBlock->getType();
          } else if (p2CurRow[col]->star == true) {
            cout << "*";
          } else {
            cout << " ";
          }
        }
      }
      cout << "" << endl;
    }
    
    cout << "-----------      -----------" << endl;
    cout << "Next:            Next:" << endl;
   
    shared_ptr<Block> p1NextBlock = player1->nextBlock;
    shared_ptr<Block> p2NextBlock = player2->nextBlock;
    
    if (p1NextBlock == nullptr) {
      cout << "           ";
    } else {
      printFirstLine(p1NextBlock->getType());
    }
    cout << "      ";
    if (p2NextBlock == nullptr) {
      cout << "           ";
    } else {
      printFirstLine(p2NextBlock->getType());
    }
    cout << endl;

    if (p1NextBlock == nullptr) {
      cout << "           ";
    } else {
      printSecondLine(p1NextBlock->getType());
    }
    cout << "      ";
    if (p2NextBlock == nullptr) {
      cout << "           ";
    } else {
      printSecondLine(p2NextBlock->getType());
    }
    cout << endl;
}


void Board::restart() {
  player1->score = 0;
  for (auto n : player1->gameBoard) {
    for (auto n2 : n) {
      n2->clear();
    }
  }
  shared_ptr<Block> tmp1 = nullptr;
  swap(tmp1, player1->currentBlock);
  shared_ptr<Block> tmp2 = nullptr;
  swap(tmp2, player1->nextBlock);
  shared_ptr<Block> tmp3 = nullptr;
  swap(tmp3, player1->currentBlockCpy);
  shared_ptr<Block> tmp4 = nullptr;
  swap(tmp4, player1->nextBlockCpy);
  player1->blind = false;
  player1->heavy = false;
  player1->force = false;
  player1->blockNum = 0;
  player1->blockClear = false;
  player1->dropcount = 0;
  player1->starTerminate = false;

  player2->score = 0;
  for (auto n : player2->gameBoard) {
    for (auto n2 : n) {
      n2->clear();
    }
  }
  
  shared_ptr<Block> tmp5 = nullptr;
  swap(tmp5, player2->currentBlock);
  shared_ptr<Block> tmp6 = nullptr;
  swap(tmp6, player2->nextBlock);
  shared_ptr<Block> tmp7 = nullptr;
  swap(tmp7, player2->currentBlockCpy);
  shared_ptr<Block> tmp8 = nullptr;
  swap(tmp8, player2->nextBlockCpy);
  player2->blind = false;
  player2->heavy = false;
  player2->force = false;
  player2->blockNum = 0;
  player2->blockClear = false;
  player2->dropcount = 0;
  player2->starTerminate = false;
}


bool Board::changeBlock(string bType, bool player) {
  shared_ptr<Player> p = nullptr;
  shared_ptr<Level> l = nullptr;
  if (player == true) {
    p = player1;
    l = player1Lvl;
  } else {
    p = player2;
    l = player2Lvl;
  }
  shared_ptr<Block> cur = p->currentBlock;
  
  // find max and min coord for old block 
  vector<vector<int>>& coordsCur = cur->getCoords();
  int minX = 10;
  int minY = 0;
  int maxX = 0;
  int maxY = -17;
  int len = coordsCur.size();
  for (int i = 0; i < len; ++i) {
    int curX = coordsCur[i][0];
    int curY = coordsCur[i][1];
    if (curX <= minX && curY <= minY) {
      minX = curX;
      minY = curY;
    }
    if (curX >= maxX && curY >= maxY) {
      maxX = curX;
      maxY = curY;
    }
  }
  
  //create new block 
  shared_ptr<Block> newBlock = nullptr;
  int level = l->getLevel();
  if (bType == "I") {
    newBlock = make_shared<IBlock>(level);
  } else if (bType == "J") {
    newBlock = make_shared<JBlock>(level);
  } else if (bType == "L") {
    newBlock = make_shared<LBlock>(level);
  } else if (bType == "O") {
    newBlock = make_shared<OBlock>(level);
  } else if (bType == "S") {
    newBlock = make_shared<SBlock>(level);
  } else if (bType == "Z") {
    newBlock = make_shared<ZBlock>(level);
  } else {
    newBlock = make_shared<TBlock>(level);
  }

  // find max and min coord for new block 
  vector<bool>& coordinatesFillNew = newBlock->getCoordFill();
  vector<vector<int>>& coordsNew = newBlock->getCoords();
  int minXnew = 10;
  int minYnew = 0;
  int maxXnew = 0;
  int maxYnew = -17;
  int lenNew = coordsNew.size();
  for (int i = 0; i < lenNew; ++i) {
    int curX = coordsNew[i][0];
    int curY = coordsNew[i][1];
    if (curX <= minXnew && curY <= minYnew) {
      minXnew = curX;
      minYnew = curY;
    }
    if (curX >= maxXnew && curY >= maxYnew) {
      maxXnew = curX;
      maxYnew = curY;
    }
  }
  
  //move new block such that its bottom left is at where that of old block is 
  //and check if any of the new Block's cell has been occupied 
  int moveX = minX - minXnew;
  int moveY = minY - minYnew;
  bool valid = true;
  for (int i = 0; i < lenNew; ++i) {
    coordsNew[i][0] += moveX;
    coordsNew[i][1] += moveY;

    if (coordinatesFillNew[i]) {
      int x = coordsNew[i][0];
      int y = abs(coordsNew[i][1]);

      if (0 <= x && x< 11 && 0 <= y && y < 18) {
        //filled means occupied by blocks other than the one to be replaced
        if ((p->gameBoard)[y][x]->filled() && (p->gameBoard)[y][x]->storedBlock != cur) {
          valid = false;
          break;
        }
      } else {
        valid = false;
        break;
      }
    }
  }
  //update new block's coordsCpy to coords
  if (valid == true) {
    newBlock -> changeContent(true);

    //clear old block from gameBoard
    vector<bool>& coordinatesFill = cur->getCoordFill();
    for (int i = 0; i < len; ++i) {
      if (coordinatesFill[i]) {
        int x = coordsCur[i][0];
        int y = abs(coordsCur[i][1]);
        shared_ptr<Block> tmp = nullptr;
        p->gameBoard[y][x]->clear(); //undraw cell
      }
    }

    //add new block to gameBoard
    for (int i = 0; i < lenNew; ++i) {
      if (coordinatesFillNew[i]) {
        int x = coordsNew[i][0];
        int y = abs(coordsNew[i][1]);
        p->gameBoard[y][x]->storedBlock = newBlock;
        p->gameBoard[y][x]->draw(); //draw cell
      }
    }
    
    swap(p->currentBlock, newBlock);
  }
  return valid;
}


string Board::win() {
  if (player1->score > player2->score) {
    return "Player1";
  } else if (player1->score < player2->score) {
    return "Player2";
  } else {
    return "Tie";
  }
}


void Board::changeToHeavy(bool check) {
  if (check == true) {
    player2->heavy = true;
  } else {
    player1->heavy = true;
  }
}


void Board::changeToBlind(bool check) {
  if (check == true) {
    player2->blind = true;
    for (int r = 5; r <= 14; ++r) {
      for (int c = 2; c <= 8; ++c) {
        player2 -> gameBoard[r][c] -> setBlind();
      }
    }
  } else {
    player1->blind = true;
    for (int r = 5; r <= 14; ++r) {
      for (int c = 2; c <= 8; ++c) {
        player1 -> gameBoard[r][c] -> setBlind();
      }
    }
  }
}


void Board::putBlock() {
  shared_ptr<Block> p1CurBlock = player1->currentBlock;
  vector<bool>& cF1 = p1CurBlock->getCoordFill();
  vector<vector<int>>& cC1 = p1CurBlock->getCoords();
  int len = cC1.size();
  for (int i = 0; i < len; ++i) {
    if (cF1[i] == true) {
      int x = cC1[i][0];
      int y = 0-cC1[i][1];
      player1->gameBoard[y][x]->storedBlock = p1CurBlock;
      player1->gameBoard[y][x]->draw();
    }
  }
  shared_ptr<Block> p2CurBlock = player2->currentBlock;
  vector<bool>& cF2 = p2CurBlock->getCoordFill();
  vector<vector<int>>& cC2 = p2CurBlock->getCoords();
  int len2 = cC2.size();
  for (int i = 0; i < len2; ++i) {
    if (cF2[i] == true) {
      player2->gameBoard[0 - cC2[i][1]][cC2[i][0]]->storedBlock = p2CurBlock;
      player2->gameBoard[0 - cC2[i][1]][cC2[i][0]]->draw();
    }
  }
}


bool Board::putCurBlock(bool p) {
  if (showWindow) w -> clearNextBlock(p); //clear old next block

  if (p == true) {
    swap(player1->currentBlock, player1->nextBlock);
    shared_ptr<Block> temp = nullptr;
    swap(player1->nextBlock, temp);
    shared_ptr<Block> p1CurBlock = player1->currentBlock;
    vector<bool>& cF1 = p1CurBlock->getCoordFill();
    vector<vector<int>>& cC1 = p1CurBlock->getCoords();
    int len = cC1.size();
    for (int i = 0; i < len; ++i) {
      if (cF1[i] == true) {
        if (player1->gameBoard[0 - cC1[i][1]][cC1[i][0]]->storedBlock != nullptr) {
          return false;
        }
      }
    }
    for (int i = 0; i < len; ++i) {
      if (cF1[i] == true) {
        player1->gameBoard[0 - cC1[i][1]][cC1[i][0]]->storedBlock = p1CurBlock;
        player1->gameBoard[0 - cC1[i][1]][cC1[i][0]]->draw(); //draw cell
      }
    }
    bool parameter = false;
    getNextBlock(parameter);
    return true;
  } else {
    swap(player2->currentBlock, player2->nextBlock);
    shared_ptr<Block> temp = nullptr;
    swap(player2->nextBlock, temp);
    shared_ptr<Block> p2CurBlock = player2->currentBlock;
    vector<bool>& cF2 = p2CurBlock->getCoordFill();
    vector<vector<int>>& cC2 = p2CurBlock->getCoords();
    int len = cC2.size();
    for (int i = 0; i < len; ++i) {
      if (cF2[i] == true) {
        if (player2->gameBoard[0 - cC2[i][1]][cC2[i][0]]->storedBlock != nullptr) {
          return false;
        }
      }
    }
    for (int i = 0; i < len; ++i) {
      if (cF2[i] == true) {
        player2->gameBoard[0 - cC2[i][1]][cC2[i][0]]->storedBlock = p2CurBlock;
        player2->gameBoard[0 - cC2[i][1]][cC2[i][0]]->draw();
      }
    }
    bool parameter = true;
    getNextBlock(parameter);
    return true;
  }
}


void Board::changeRandom (bool check, string filename) {
  shared_ptr<Level> l = nullptr;
  shared_ptr<Player> p = nullptr;
  if (check == true) {
    l = player1Lvl;
    p = player1;
  } else {
    l = player2Lvl;
    p = player2;
  }
  if (l->getLevel() == 3 || l->getLevel() == 4) {
    l -> changeState(filename);
  } 
  if (filename != "apple") {
    shared_ptr<Block> b = nullptr;
    swap(b, p->nextBlock);
    getNextBlock(check);
  }
}


void Board::modifyDrop(bool check, int count) {
  if (check == true) {
    player1->dropcount = count;
  } else {
    player2->dropcount = count;
  }
}


int Board::getDroptime(bool check) {
  if (check == true) {
    return player1->dropcount;
  } else {
    return player2->dropcount;
  }
}


void Board::hint(bool player) {
  vector<vector<int>> co1;
  vector<vector<int>> co2;
  vector<vector<int>> co3;
  vector<vector<int>> co4;
  shared_ptr<Player> tmp;
  if (player == true) {
    tmp = player1;
  } else {
    tmp = player2;
  }
  co1 = tmp->currentBlock->getCoordsCpy();
  tmp->currentBlock->clockwise();
  co2 = tmp->currentBlock->getCoordsCpy();
  tmp->currentBlock->clockwise();
  co3 = tmp->currentBlock->getCoordsCpy();
  tmp->currentBlock->clockwise();
  co4 = tmp->currentBlock->getCoordsCpy();
  tmp->currentBlock->changeContent(false);
  
  bool change2 = checkFilledHint(tmp, co2); //cw
  bool change3 = checkFilledHint(tmp, co3); //cw cw
  bool change4 = checkFilledHint(tmp, co4); //ccw
  int leftcount = 0;
  int rightcount = 0;
  int downdeep = 0;
  int cwcount = 0; 
  bool check = operate(tmp, co1, leftcount, rightcount, downdeep);
  if (change2 == true) {
    check = operate(tmp, co2, leftcount, rightcount, downdeep);
    if (check == true) {
      cwcount = 1;
    }
  } 
  if (change3 == true) {
    check = operate(tmp, co3, leftcount, rightcount, downdeep);
    if (check == true) {
      cwcount = 2;
    }
  }
  if (change4 == true) {
    check = operate(tmp, co4, leftcount, rightcount, downdeep);
    if (check == true) {
      cwcount = 3;
    }
  }
  if (cwcount > 0) {
    cout << "clockwise " << cwcount << " time(s) ";
  }
  if (leftcount > 0) {
    cout << "move left " << leftcount << " time(s) ";
  }
  if (rightcount > 0) {
    cout << "move right " << rightcount << " time(s) ";  
  }
  cout << "Drop." << endl;
}

bool Board::operate(shared_ptr<Player> p, vector<vector<int>> coordinates, int &leftcount, int &rightcount, int &downdeep) {
  bool changed = false;
  vector<vector<int>> original = coordinates;
  bool check = dropHint(p, coordinates);
  if (check == true) {
    int minimaly = minY(coordinates);
    if (downdeep > minimaly) {
      downdeep = minimaly;
      changed = true;
    } 
  }
  coordinates = original;
  int leftcounter = 0;
  while (true) {
    leftHint(coordinates);
    if (checkFilledHint(p, coordinates) == false) {
      break;
    }
    vector<vector<int>> tmp = coordinates;
    check = dropHint(p, coordinates);
    leftcounter = leftcounter + 1;
    if (check == true) {
      int minimaly = minY(coordinates);
      if (downdeep > minimaly) {
      downdeep = minimaly;
      changed = true;
      rightcount = 0;
      leftcount = leftcounter;
      } 
    }
    coordinates = tmp;
  }
  coordinates = original;
  int rightcounter = 0;
  while (true) {
    rightHint(coordinates);
    if (checkFilledHint(p, coordinates) == false) {
      break;
    }
    vector<vector<int>> tmp = coordinates;
    check = dropHint(p, coordinates);
    rightcounter = rightcounter + 1;
    if (check == true) {
      int minimaly = minY(coordinates);
      if (downdeep > minimaly) {
      downdeep = minimaly;
      changed = true;
      rightcount = rightcounter;
      leftcount = 0;
      } 
    }
    coordinates = tmp;
  }
  return changed;
}

int Board::minY(vector<vector<int>> coords) {
  int res = 0;
  for (int i = 0; i < coords.size(); ++i) {
    if (coords[i][1] < res) res = coords[i][1];
  }
  return res;
}

bool Board::checkFilledHint(shared_ptr<Player> p, vector<vector<int>> coordinates) {
  bool valid = true;
  vector<bool>& coordinatesFill = p->currentBlock->getCoordFill();
  for(int i = 0; i < coordinates.size(); ++i) {
		if (coordinatesFill[i]) { 
			vector<int> coord = coordinates[i];
			int x = coord[0];
			int y = abs(coord[1]);
			if (0 <= x && x< 11 && 0 <= y && y < 18) {
				if ((p->gameBoard)[y][x]->filled() && p->gameBoard[y][x]->storedBlock != p->currentBlock) {
          valid = false;
          break;
        }
			} else {
        valid = false;
        break;
      }
		}
	}
  return valid;
}


void Board::leftHint(vector<vector<int>>& coords) {
  for (int i = 0; i < coords.size(); ++i) {
    --coords[i][0];
  }
}

void Board::rightHint(vector<vector<int>>& coords) {
  for (int i = 0; i < coords.size(); ++i) {
    ++coords[i][0];
  }
}
void Board::downHint(vector<vector<int>>& coords) {
  for (int i = 0; i < coords.size(); ++i) {
    --coords[i][1];
  }
}

bool Board::dropHint(shared_ptr<Player> p,vector<vector<int>> &coords) {
  while (true) {
    downHint(coords);
    if (checkFilledHint(p, coords) == false) {
      break;
    }
  }
  for (int i = 0; i < coords.size(); ++i) {
    ++coords[i][1];
  }
  for (auto n : coords) {
    if (n[1] > -3) {
      return false;
    }
  }
  return true;
}

int Board::getLevel(bool check) {
  if (check == true) {
    return player1->currentBlock->getLevel();
  } else {    
    return player2->currentBlock->getLevel();
  }
}


string Board::finalWin() {
  int score1 = player1->highestScore;
  int score2 = player2->highestScore;
  if (score1 == score2) {
    return "Tie";
  } else if (score1 > score2) {
    return "Player1";
  } else {
    return "Player2";
  }
}

bool Board::StarTerminate(bool check) {
  if (check == true) {
    return player1->starTerminate;
  } else {
    return player2->starTerminate;
  }
}