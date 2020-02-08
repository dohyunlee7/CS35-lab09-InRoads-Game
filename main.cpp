/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include "inroadsGame.h"

#include "inroadsGUI.h"
#include "ioUtils.h"

using namespace std;

int main(int argc, char** argv) {
    // Check command line arguments and give up if necessary.
    if (argc != 2) {
        cerr << "Expected one argument: name of map file." << endl;
        return 1;
    }

    // Initialize randomizer.  This should happen before any random numbers are
    // selected.
    srand(time(nullptr));

    // Get command-line argument.
    string mapFilename = string(argv[1]);

    // Read the Inroads map file.
    pair<Graph<string, bool, int>*, Dictionary<string, pair<int, int>>*>
        mapFileContents;
    try {
        mapFileContents = readInroadsMap(mapFilename);
    } catch (exception e) {
        cout << "Could not read Inroads map file " << mapFilename << ": "
             << e.what() << endl;
    }
    // The map file contained the graph representing the map.  It also contained
    // the vertex positions (so we know where each vertex goes on the map).
    Graph<string, bool, int>* graph = mapFileContents.first;
    Dictionary<string, pair<int, int>>* vertexPositions =
        mapFileContents.second;

    // Create the GUI object here.  This is statically allocated, so the GUI
    // will disappear the moment your program leaves the main function.
    // The GUI object should only be used by main, and not by any other function
    // or object; do NOT change the type of this variable.
    InroadsGUI gui(vertexPositions, mapFilename);

    // Tell the GUI about the graph we have.
    gui.updateInroadsMap(graph);
    gui.updateScoreText("Score: 0");
    gui.updateTurnText("Turn: 1");

    // TODO: Write code that runs the game.  You'll want to write most of your
    // game logic into the RailwayGame class and then use an object of that type
    // here to control the game and relay what it says to the GUI.  This
    // assignment is more open-ended than the previous assignments.

    // TODO: Delete the following code.  It's just here at the start of the
    // assignment to make sure that you can see what the GUI looks like.  If we
    // didn't do something here (like wait for the user to press enter on the
    // console), then the main function would stop and the GUI would instantly
    // vanish.
//pair<string, string> myMove = gui.getNextMove();
    //create a inroadsgame object
    InroadsGame theGame(graph);
    int num = 0;
    int gameTotal = 0;
    //while the games still running
      //update the map, score, turn, and message
    while(num < 20){
      pair<string, string> myMove = gui.getNextMove();
      if(graph->getEdge(myMove.first, myMove.second).getLabel()){
        continue;
      }
      theGame.nextMove(myMove);
      int currentScore = theGame.totalScoreRound();
      //outsource to inroadsGame
      string score = to_string(currentScore);
      string turn = to_string(theGame.getTurnNum());
      gui.updateInroadsMap(graph);
      gui.updateScoreText("Score: " + score);
      gui.updateTurnText("Turn:" + turn);
      //get the gui message box to reset the scores per turn
      int lScore = 0;
      int sScore = 0;
      int hScore = 0;
      lScore = theGame.libraryScore();
      sScore = theGame.storeScore();
      hScore = theGame.hospitalScore();
      string libScore = to_string(lScore);
      string storeScore = to_string(sScore);
      string hospScore = to_string(hScore);
      gameTotal += lScore + sScore + hScore;
      string total = to_string(gameTotal);
      //return total score of the turn, not for the entire game
      gui.updateMessage("Total points this turn: " + to_string(lScore + sScore +
      hScore) + ".\n\t "
      "+" + libScore + " from the library.\n\t "
      "+" + storeScore + " from stores.\n\t  "
      "+" + hospScore + " from medical access. "
      );
      gui.updateScoreText("Score: " + total);
      num += 1;
    }
    gui.updateTurnText("Game Over");
    string deleteThisVariable;
    getline(cin, deleteThisVariable);
    // Finally, clean up and exit successfully.
    delete graph;
    delete vertexPositions;
    return 0;
}
