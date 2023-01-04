#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];
  XRectangle recs[2];

 public:
  Xwindow(int width=520, int height=560);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue, Yellow, Purple, Pink, Orange, Brown}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);

  // Undraw a string 
  void undrawString(int x, int y, int width, int height);
  
  // Draw two rectangle frames
  void drawFrame();

  // Set up
  void setUp(int l1, int l2); // l1 is player1's level, l2 is player2's level

  void setHighest(bool check, int highest);
  void setScore(bool check, int score);
  void setLevel(bool check, int level);

  void clearNextBlock(bool player);
  void setNextBlock(bool check, std::string bType);

};

#endif

