/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#pragma once
//#include "graphAlgorithms-inl.h"
#include "adts/graph.h"
#include <string>
using std::string;
using std::pair;
/**
 * An instance of this class represents a single game of Inroads.  An object of
 * type InroadsGame does not represent the user interface, but does represent
 * the idea of a game of Inroads, including the state of the board and all of
 * the information pertaining to the player.  It also includes the logic for
 * making moves in the game and enforces the game's rules.
 */
class InroadsGame {
  public:
    // TODO: write your InroadsGame constructor and method declarations here
    InroadsGame(Graph<string, bool, int>* graph);
    ~InroadsGame();
    int getTurnNum();
    int getScore();
    void nextMove(pair<string, string> myMove);
    int hospitalScore();
    int libraryScore();
    int storeScore();
    int totalScoreRound();
  private:
    // TODO: write your InroadsGame fields here
    int score;
    int turn;
    string message;
    bool visited;
    Graph<string, bool, int>* graph;
};
