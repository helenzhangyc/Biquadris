#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[11][11]={"white", "black", "red", "green", "blue", "yellow", "purple", "pink", "orange", "brown"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 10; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);
  
  // set up frames
  recs[0] = XRectangle{19, 99, 222, 362};
  recs[1] = XRectangle{279, 99, 222, 362};

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg) {
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

void Xwindow::undrawString(int x, int y, int width, int height) {
  fillRectangle(x, y-20, width, height, Xwindow::White);
}

void Xwindow::drawFrame() {
  XDrawRectangles(d, w, DefaultGC(d, s), recs, 2);
}

void Xwindow::setUp(int l1, int l2) {
  drawFrame();

  //player1
  drawString(20, 40, "Highest:");
  drawString(130, 40, "0");
  drawString(20, 60, "Score:");
  drawString(130, 60, "0");
  drawString(20, 80, "Level:");
  drawString(130, 80, to_string(l1));
  drawString(20, 480, "Next:");

  //player2
  drawString(280, 40, "Highest:");
  drawString(390, 40, "0");
  drawString(280, 60, "Score:");
  drawString(390, 60, "0");
  drawString(280, 80, "Level:");
  drawString(390, 80, to_string(l2));
  drawString(280, 480, "Next:");
}

void Xwindow::setHighest(bool check, int highest) {
  if (check) {
    undrawString(130, 40, 20, 20);
    drawString(130, 40, to_string(highest));
  } else {
    undrawString(390, 40, 20, 20);
    drawString(390, 40, to_string(highest));
  }
}

void Xwindow::setScore(bool check, int score) {
  if (check) {
    undrawString(130, 60, 20, 20);
    drawString(130, 60, to_string(score));
  } else {
    undrawString(390, 60, 20, 20);
    drawString(390, 60, to_string(score));
  }
}

void Xwindow::setLevel(bool check, int level) {
  if (check) {
    undrawString(130, 80, 20, 20);
    drawString(130, 80, to_string(level));
  } else {
    undrawString(390, 80, 20, 20);
    drawString(390, 80, to_string(level));
  }
}

void Xwindow::clearNextBlock(bool player) {
  if (player) {
    for (int x = 20; x <= 80; ) {
      fillRectangle(x, 500, 20, 20, Xwindow::White);
      fillRectangle(x, 520, 20, 20, Xwindow::White);
      x += 20;
    } 
  } else {
    for (int x = 280; x <= 340; ) {
      fillRectangle(x, 500, 20, 20, Xwindow::White);
      fillRectangle(x, 520, 20, 20, Xwindow::White);
      x += 20;
    } 
  }
}

void Xwindow::setNextBlock(bool player, string bType) {
  int xcor20 = 20;
  int xcor40 = 40;
  int xcor60 = 60;
  int xcor80 = 80;
  if (!player) { 
    xcor20 += 260;
    xcor40 += 260;
    xcor60 += 260;
    xcor80 += 260;
  }
  if (bType == "I") {
    fillRectangle(xcor20, 520, 20, 20, Xwindow::Red);
    fillRectangle(xcor40, 520, 20, 20, Xwindow::Red);
    fillRectangle(xcor60, 520, 20, 20, Xwindow::Red);
    fillRectangle(xcor80, 520, 20, 20, Xwindow::Red);
  } else if (bType == "J") {
    fillRectangle(xcor20, 500, 20, 20, Xwindow::Orange);
    fillRectangle(xcor20, 520, 20, 20, Xwindow::Orange);
    fillRectangle(xcor40, 520, 20, 20, Xwindow::Orange);
    fillRectangle(xcor60, 520, 20, 20, Xwindow::Orange);
  } else if  (bType == "L") {
    fillRectangle(xcor20, 520, 20, 20, Xwindow::Yellow);
    fillRectangle(xcor40, 520, 20, 20, Xwindow::Yellow);
    fillRectangle(xcor60, 520, 20, 20, Xwindow::Yellow);
    fillRectangle(xcor60, 500, 20, 20, Xwindow::Yellow);
  } else if (bType == "T") {
    fillRectangle(xcor20, 500, 20, 20, Xwindow::Purple);
    fillRectangle(xcor40, 500, 20, 20, Xwindow::Purple);
    fillRectangle(xcor60, 500, 20, 20, Xwindow::Purple);
    fillRectangle(xcor40, 520, 20, 20, Xwindow::Purple);
  } else if (bType == "S") {
    fillRectangle(xcor20, 520, 20, 20, Xwindow::Green);
    fillRectangle(xcor40, 520, 20, 20, Xwindow::Green);
    fillRectangle(xcor40, 500, 20, 20, Xwindow::Green);
    fillRectangle(xcor60, 500, 20, 20, Xwindow::Green);
  } else if (bType == "Z") {
    fillRectangle(xcor20, 500, 20, 20, Xwindow::Pink);
    fillRectangle(xcor40, 500, 20, 20, Xwindow::Pink);
    fillRectangle(xcor40, 520, 20, 20, Xwindow::Pink);
    fillRectangle(xcor60, 520, 20, 20, Xwindow::Pink);
  } else { //O
    fillRectangle(xcor20, 500, 20, 20, Xwindow::Blue);
    fillRectangle(xcor40, 500, 20, 20, Xwindow::Blue);
    fillRectangle(xcor20, 520, 20, 20, Xwindow::Blue);
    fillRectangle(xcor40, 520, 20, 20, Xwindow::Blue);
  }
}




