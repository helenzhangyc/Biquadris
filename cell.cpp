#include "cell.h"
#include <utility>
using namespace std;


Cell::Cell(int xcor, int ycor, shared_ptr<Xwindow> w, bool showWindow, bool player) : 
storedBlock{nullptr}, x{xcor+1}, y{ycor+5}, w{w}, star(false), 
blind{false}, width{20}, height{20}, showWindow{showWindow}, player{player} {}

bool Cell::filled() {
  if (storedBlock == nullptr && star == false) {
    return false;
  } else {
    return true;
  }
}

void Cell::clear() {
  shared_ptr<Block> temp = nullptr;
  swap(temp, storedBlock);
  star = false;
  blind = false;
  undraw();
}

void Cell::update(shared_ptr<Cell> other) {
  swap(storedBlock, other->storedBlock);
  swap(blind, other->blind);
  swap(star, other->star);
  draw();
  other -> draw();
}

void Cell::draw() {
  if (showWindow) {
    int xcor = x * width;
    int ycor = y * height;
    if (!player) xcor += 13 * width;
    int col;
    if (blind) col = Xwindow::Black;
    else if (star) col = Xwindow::Brown;
    else if (storedBlock == nullptr) col = Xwindow::White;
    else {
      string bType = storedBlock -> getType();
      if (bType == "I") {
        col = Xwindow::Red;
      } else if (bType == "J") {
        col = Xwindow::Orange;
      } else if (bType == "L") {
        col = Xwindow::Yellow;
      } else if (bType == "T") {
        col = Xwindow::Purple;
      } else if (bType == "S") {
        col = Xwindow::Green;
      } else if (bType == "Z") {
        col = Xwindow::Pink;
      } else { //O
        col = Xwindow::Blue;
      }
    }
    w -> fillRectangle(xcor, ycor, width, height, col);
  } else return;
}

void Cell::undraw() {
  if (showWindow) {
    int xcor = x * width;
    int ycor = y * height;
    if (!player) xcor += 13 * width;
    w->fillRectangle(xcor, ycor, width, height, Xwindow::White);
  } else return;
}

void Cell::setBlind() {
  blind = true;
  if (showWindow) {
    int xcor = x * width;
    int ycor = y * height;
    if (!player) xcor += 13 * width;
    w->fillRectangle(xcor, ycor, width, height, Xwindow::Black);
  }
}

void Cell::unsetBlind() {
  if (blind) {
    blind = false;
    if (showWindow) draw();
  } else return;
}

