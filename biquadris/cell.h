#ifndef _CELL_H_
#define _CELL_H_
#include "block.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "SBlock.h"
#include "ZBlock.h"
#include "TBlock.h"
#include "window.h"
#include <memory>
using namespace std;

class Cell {
  private:
  int x;
  int y;
  shared_ptr<Xwindow> w;
  int width;
  int height;
  bool showWindow;
  bool player; //player1 if player is true

  public:
  shared_ptr<Block> storedBlock;
  bool blind;
  bool star;

  Cell(int xcor, int ycor, shared_ptr<Xwindow> w, bool showWindow, bool player);
  bool filled();
  void draw();
  void undraw();
  void clear();
  void update(shared_ptr<Cell> other);
  void setBlind();
  void unsetBlind();
};

#endif