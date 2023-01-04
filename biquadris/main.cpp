#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h> 
#include <memory>
#include <string>
#include "board.h"

using namespace std;

int main(int argc, char * argv[]) {
  cin.exceptions(ios::eofbit);
  bool showWindow = true;
  bool haveSeed = false;
  int seed = 0;
  string scriptfile1 = "sequence1.txt"; //level1 player1's filename
  string scriptfile2 = "sequence2.txt"; //level1 player2's filename
  int levelHolder = 0; //store starting level1 leve2
  int level1 = 0;
  int level2 = 0;

  for (int i = 1; i < argc; ++i) {
    if (string(argv[i]).compare("-text") == 0) {
      showWindow = false;
    } else if (string(argv[i]).compare("-seed") == 0) { 
      haveSeed = true;
      seed = stoi(argv[i + 1]);
      i = i + 1;
    } else if (string(argv[i]).compare("-scriptfile1") == 0) {
      scriptfile1 = argv[i + 1];
      i = i + 1;
    } else if (string(argv[i]).compare("-scriptfile2") == 0) {
      scriptfile2 = argv[i + 1];
      i = i + 1;
    } else if (string(argv[i]).compare("-startlevel") == 0) {
      level1 = stoi(argv[i + 1]);
      level2 = stoi(argv[i + 1]);
      levelHolder = stoi(argv[i + 1]);
      i = i + 1;
    }
  }

  if (haveSeed == true) {
    srand(seed);
  } //####command line argument extraction done####

  bool player = true; // true=player1's turn, false=player2's turn
  bool readSequence = false; //true=read from sequence
  int turn = 0; //inc by 1 after a player'turn finishes
  string cmd = ""; //
  int commandIndex = 1; //multiplier prefix ex.: 3left
  int commandPos = -1; //the last index position of a command where its an int
  vector<string> inputcommand; //vector of commands from file 
  int inputIndex = 0;
  string inputfileName = "";
  bool tmpplayer;
  auto g = make_unique<Board>(showWindow);
  bool gameOver = false;
  bool p1hint = true;
  bool p2hint = true;
  bool forceDrop = false;

  g->setUp(scriptfile1, scriptfile2, level1, level2);
  g->init();
  g->putBlock();
  g->show(showWindow);

  while (true) {
    try{
      forceDrop = false;
      if (turn % 2 == 1) {
        player = false;
      } else {
        player = true;
      }

      commandIndex = 1;

      if (g->getDroptime(player) > 0) { //auto drop
        cmd = "drop";
        commandIndex = 1;
      } else {
        
        if (readSequence == true) { //end of file
          if (inputIndex == inputcommand.size()) {
            cout << "Your file doesn't have any command to be executed. Please mannually input any commands." << endl;
            readSequence = false;
          }
        } 

        if (readSequence == true) { //read from sequence 
          cmd = inputcommand[inputIndex];
          inputIndex = inputIndex + 1;
        } else { //read from user input 
          cin >> cmd;
        }

        //get the last index position in cmd where it's an int 
        for (int i = 0; i < cmd.size(); ++i) {
          if (cmd[i] >= 48 && cmd[i] <= 57 ) {
            commandPos = i;
          } else {
            break;
          }
        }

        //convert multiplier prefix from string to int 
        if (commandPos > 0) {
          commandIndex = stoi(cmd.substr(0, commandPos + 1));
        } else if (commandPos == 0) {
          commandIndex = cmd[0] - 48;
        }

      //extract command  
      cmd = cmd.substr(commandPos + 1, cmd.size());
      commandPos = -1;
      }

      if (cmd == "lef" || cmd == "left") {
        if (commandIndex == 0) {
          cout << "Trivial left command" << endl;
          continue;
        }

        for (int i = 0; i < commandIndex; ++i) {
          bool check = g->validLeft(player);
          if (check == false) {
            break;
          }
        }

        int downtime = 0;
        if (g->getLevel(player) == 3 || g->getLevel(player) == 4) {
          downtime = downtime + 1;
        }
        if (g->isHeavy(player) == true) {
          downtime = downtime + 2;
        }

        for (int i = 0; i < downtime; ++i) {
          bool check = g->validDown(player);
          if (check == false) {
            if (g->isHeavy(player) == true) {
              forceDrop = true;
            }
            break;
          }
        }
        g->show(showWindow);

      } else if (cmd == "ri" || cmd == "rig" || cmd == "righ" || cmd == "right") {
        if (commandIndex == 0) {
          cout << "Trivial right command" << endl;
          continue;
        }

        for (int i = 0; i < commandIndex; ++i) {
          bool check = g->validRight(player);
          if (check == false) {
            break;
          }
        }

        int downtime = 0;
        if (g->getLevel(player) == 3 || g->getLevel(player) == 4) {
          downtime = downtime + 1;
        }
        if (g->isHeavy(player) == true) {
          downtime = downtime + 2;
        }

        for (int i = 0; i < downtime; ++i) {
          bool check = g->validDown(player);
          if (check == false) {
            if (g->isHeavy(player) == true) {
              forceDrop = true;
            }
            break;
          }
        }
        g->show(showWindow);

      } else if (cmd == "do" || cmd == "dow" || cmd == "down") {
        if (commandIndex == 0) {
          cout << "Trivial down command" << endl;
          continue;
        }

        int downtime = commandIndex;
        if (g->getLevel(player) == 3 || g->getLevel(player) == 4) {
          downtime = downtime + 1;
        }
        
        for (int i = 0; i < downtime; ++i) {
          bool check = g->validDown(player);
          if (check == false) {
            break;
          }
        }
        g->show(showWindow);

      } else if (cmd == "levelu" || cmd == "levelup") {

        int levelIncrease = 0;
        string filename = "";

        if (player == true) {
          level1 = level1 + commandIndex;
          if (level1 > 4) {
            level1 = 4;
          }
          levelIncrease = level1;
          filename = scriptfile1;
        } else {
          level2 = level2 + commandIndex;
          if (level2 > 4) {
            level2 = 4;
          }
          levelIncrease = level2;
          filename = scriptfile2;
        }
        g->setLevel(levelIncrease, player, filename); 
        g->show(showWindow);

      } else if (cmd == "leveld" || cmd == "leveldo" || cmd == "leveldow" || cmd == "leveldown") {

        int levelDecrease = 0;
        string filename = "";

        if (player == true) {
          level1 = level1 - commandIndex;
          if (level1 < 0) {
            level1 = 0;
          }
          levelDecrease = level1;
          filename = scriptfile1;
        } else {
          level2 = level2 - commandIndex;
          if (level2 < 0) {
            level2 = 0;
          }
          levelDecrease = level2;
          filename = scriptfile2;
        }
        g->setLevel(levelDecrease, player, filename); 
        g->show(showWindow);

      } else if (cmd == "I" || cmd == "J" || cmd == "L" || cmd == "S" || cmd == "Z" || cmd == "T" || cmd == "O" ) {

        bool validChange = g->changeBlock(cmd, player);

        if (validChange == false) {
          cout << "No space for the " << cmd << "-block. Keep the current Block that you have" << endl;
        } 
        g->show(showWindow);

      } else if (cmd == "re" || cmd == "res" || cmd == "rest" || cmd == "resta" || cmd == "restar" || cmd == "restart") {

          level1 = levelHolder;
          level2 = levelHolder;

          g->restart();
          g->setUp(scriptfile1, scriptfile2, level1, level2);
          g->init();
          g->putBlock();

          turn = 0;
          gameOver = false;
          p1hint = true;
          p2hint = true;

          g->show(showWindow);

      } else if (cmd == "ra" || cmd == "ran" || cmd == "rand" || cmd == "rando" || cmd == "random") {
        if (player) {
          if (level1 == 3 || level1 == 4) {
            g->changeRandom(player, "apple");
          } else {
            if (level2 == 3 || level2 == 4) {
              g->changeRandom(player, "apple");
            }
          }
        }
        g->show(showWindow);

      } else if (cmd == "n" || cmd == "no" || cmd == "nor" || cmd == "nora" || cmd == "noran" || cmd == "norand" || cmd == "norando" || cmd == "norandom") {
        if (readSequence == true) {
          if (inputIndex == inputcommand.size()) {
            cout << "Your file doesn't have any command to be executed. Please mannually input any commands." << endl;
            readSequence = false;
          }
        } 

        if (readSequence == true) {
          cmd = inputcommand[inputIndex];
          inputIndex = inputIndex + 1;        
        } else {
          cin >> cmd;
        }

        if (player) {
          if (level1 == 3 || level1 == 4) {
            g->changeRandom(player, cmd);
          }
        } else {
          if (level2 == 3 || level2 == 4) {
            g->changeRandom(player, cmd);
          }
        }
        g->show(showWindow);

      } else if (cmd == "cl" || cmd == "clo" || cmd == "cloc" || cmd == "clock" || cmd == "clockw" || cmd == "clockwi" || cmd == "clockwis" || cmd == "clockwise") {
        if (commandIndex == 0) {
          cout << "Trivial clockwise command" << endl;
          continue;
        }

        for (int i = 0; i < commandIndex; ++i) {
          bool check = g->validCW(player);
          if (check == false) {
            break;
          }
        }

        int downtime = 0;
        if (g->getLevel(player) == 3 || g->getLevel(player) == 4) {
          downtime = downtime + 1;
        }

        for (int i = 0; i < downtime; ++i) {
          bool check = g->validDown(player);
          if (check == false) {
            break;
          }
        }
        g->show(showWindow);

      } else if (cmd == "co" || cmd == "cou" || cmd == "coun" || cmd == "count" || cmd == "counte" || cmd == "counter" || cmd == "counterc" || cmd == "countercl" || cmd == "counterclo" || cmd == "countercloc" || cmd == "counterclock" || cmd == "counterclockw" || cmd == "counterclockwi" || cmd == "counterclockwis" || cmd == "counterclockwise") {
        if (commandIndex == 0) {
          cout << "Trivial counterclockwise command" << endl;
          continue;
        }

        for (int i = 0; i < commandIndex; ++i) {
          bool check = g->validCCW(player);
          if (check == false) {
            break;
          }
        }

        int downtime = 0;
        if (g->getLevel(player) == 3 || g->getLevel(player) == 4) {
          downtime = downtime + 1;
        }

        for (int i = 0; i < downtime; ++i) {
          bool check = g->validDown(player);
          if (check == false) {
            break;
          }
        }
        g->show(showWindow);

      } else if (cmd == "s" || cmd == "se" || cmd == "seq" || cmd == "sequ" || cmd == "seque" || cmd == "sequen" || cmd == "sequenc" || cmd == "sequence") {
        string tmp = "";

        if (readSequence == true) {
          if (inputIndex == inputcommand.size()) {
            cout << "Your file doesn't have any command to be executed. Please mannually input any commands." << endl;
            readSequence = false;
          }
        } 

        if (readSequence == true) {
          tmp = inputcommand[inputIndex];
        } else {
          cin >> tmp;
          readSequence = true;
        }

        //clear command vector and read in new commands from file
        inputcommand.clear();
        inputcommand.shrink_to_fit();
        inputIndex = 0;

        ifstream inputfile{tmp};
        string commands;
        while ((inputfile >> commands)) {
          inputcommand.emplace_back(commands);
        }      
        g->show(showWindow); 

      } else if (cmd == "h" || cmd == "hi" || cmd == "hin" || cmd == "hint") {
        if (player && p1hint) {
          g->show(showWindow);
          g->hint(player);
          p1hint = false;
        } else if (player == false && p2hint) {
          g->show(showWindow);
          g->hint(player);
          p2hint = false;
        } else {
          cout << "You have consumed the change to use hint before." << endl;
        }
      } 

      if (cmd == "dr" || cmd == "dro" || cmd == "drop" || forceDrop == true) {
        if (forceDrop == true) {
          commandIndex = 1;
        }

        if (commandIndex > 0) {
          if (commandIndex > 1) {
            g->modifyDrop(player, commandIndex - 1);
          }

          bool validDrop = g->drop(player);
          if (validDrop == false) {
            gameOver = true;

          } else {
            bool callSpecial = g->checkGrid(player);
            if (callSpecial == true) {
              g->show(showWindow);
              cout << "You now active the Special action. Available actions are:" << endl;
              cout << "blind  heavy  force" << endl;
              cout << "Please select one on your opponent by typing the action's name all in lowercase: " << endl;

              if (readSequence == true) {
                if (inputIndex == inputcommand.size()) {
                  cout << "Your file doesn't have any command. Please mannually input any commands." << endl;
                  readSequence = false;
                }
              } 

              if (readSequence == true) {
                cmd = inputcommand[inputIndex];
                inputIndex = inputIndex + 1;
              } else {
                while (true) {
                cin >> cmd;
                if (cmd == "blind" || cmd == "heavy" || cmd == "force") {
                  break;
                } else {
                  cout << "Input is invalid, please input again." << endl;
                }
                }
              }

              if (cmd == "blind") {
                g->changeToBlind(player);
              } else if (cmd == "heavy") {
                g->changeToHeavy(player);
              } else if (cmd == "force") {
                cout << "Please select the block that you want your opponent's current block be: " << endl;
                cout << "L I O S Z T J" << endl;

              if (readSequence == true) {
                if (inputIndex == inputcommand.size()) {
                  cout << "Your file doesn't have any command. Please mannually input any commands." << endl;
                  readSequence = false;
                }
              }

                if (readSequence == true) {
                  cmd = inputcommand[inputIndex];
                  inputIndex = inputIndex + 1;
                } else {
                  while (true) {
                    cin >> cmd;
                    if (cmd == "I" || cmd == "J" || cmd == "L" || cmd == "S" || cmd == "Z" || cmd == "T" || cmd == "O" ) {
                  break;
                } else {
                  cout << "Input is invalid, please input again." << endl;
                }
                }
                }

                if (player == true) {
                  tmpplayer = false;
                } else {
                  tmpplayer = true;
                }

                bool validforce = g->changeBlock(cmd, tmpplayer);
                if (validforce == false) {
                  gameOver = true;
                }
              }
            }
            if (g->StarTerminate(player) == true) {
              gameOver = true;
            }
            if (gameOver == false) {
              bool validSwap = g->putCurBlock(player);

              //new block cannot be placed in its initial position => lose
              if (validSwap == false) {
                gameOver = true;
              }

              if (gameOver == false) {
                turn = turn + 1;

                int remainingDrop = g->getDroptime(player);
                if (remainingDrop > 0 && commandIndex == 1) {
                  g->modifyDrop(player, remainingDrop - 1);
                }
                
                g->removeBlind(player);
                p1hint = true;
                p2hint = true;
                g->show(showWindow);
              }
            }
          }
        } else {
          cout << "Trivial drop command." << endl;
          g->show(showWindow);
        }
      } 

      if (gameOver == true) {

        cout << "No space for you to drop the block or place the next block or place a star. Game Over." << endl;

        string winner = g->win();

        if (winner == "Tie") {
          cout << "Tie" << endl;
        } else {
          cout << "This round's winner is " << winner << endl;
        }

        cout << "Do you want to restart another round?(Y/N) ";

        if (readSequence == true) {
          if (inputIndex == inputcommand.size()) {
            cout << "Your file doesn't have any command to executed. Please mannually input any commands." << endl;
            readSequence = false;
          }
        } 

        if (readSequence == true) {
          cmd = inputcommand[inputIndex];
          inputIndex = inputIndex + 1;
        } else {
          while (true) {
            cin >> cmd;
            if (cmd == "N" || cmd == "Y") {
              break;
            } else {
              cout << "Invalid input. Please input again." << endl;
            }
          }
        }

        if (cmd == "N") {
          break;
        } else {
          level1 = levelHolder;
          level2 = levelHolder;
          g->restart();
          g->setUp(scriptfile1, scriptfile2, level1, level2);
          g->init();
          g->putBlock();
          turn = 0;
          p1hint = true;
          p2hint = true;
          gameOver = false; 
          g->show(showWindow);
        }
      }
    } catch (exception &) { break; }
  }
  string finalwinner = g->finalWin();
  if (finalwinner == "Tie") {
    cout << "Both of players' highestscores are same. Tie" << endl;
  } else {
    cout << "This highest score winner is: " << finalwinner << endl;
  }
}
