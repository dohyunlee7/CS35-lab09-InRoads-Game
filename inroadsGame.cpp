/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <string>

#include "inroadsGame.h"
#include "adts/edge.h"
#include "graphAlgorithms.h"
#include "adts/graph.h"
#include "adjacencyListUndirectedGraph.h"

using std::pair;
using std::string;

// using namespace std;

InroadsGame::InroadsGame(Graph<string, bool, int>* graph) {
  this->graph = graph;
  this->score = 0;
  this->turn = 1;
}

InroadsGame::~InroadsGame(){

}


int InroadsGame::getTurnNum(){
  return this->turn;
}

int InroadsGame::getScore(){
  return this->score;
}

void InroadsGame::nextMove(pair<string, string> myMove){
  //add the edge
  //update the boolean to visited or true
  Edge<string,bool,int> theEdge = this->graph->getEdge(myMove.first, myMove.second);
  int theWeight = theEdge.getWeight();

  this->graph->removeEdge(myMove.first, myMove.second);
  this->graph->insertEdge(myMove.first, myMove.second, true, theWeight);
  this->turn += 1;
}

int InroadsGame::hospitalScore(){
  //vector<string> locations = g->getVertices()
  //int total = 0
  //for each string x in locations
    //if str[0] == 'R'
      //use dijkstras to compute minimum weight path from x to everything else (returns map of shortest distance to everything else)
      //int minWeight = 0
      //bool path to medical found = false
      //for each string y in locations
      //if y[0] == 'm'
        //compare dijkstras path from x to y against minweight

  //if pathtomedicalfound

  //total t = 420/minweight
  Graph<string, bool, int>* hosGraph = new AdjacencyListUndirectedGraph<string, bool, int>();
  vector<string> vertices = this->graph->getVertices();
  for(int i = 0; i < vertices.size(); i++){
    hosGraph->insertVertex(vertices[i]);
  }
  vector<Edge<string, bool, int>> edges = this->graph->getEdges();
  for(int i = 0; i < edges.size(); i ++){
    if(edges[i].getLabel() == true){
      hosGraph->insertEdge(edges[i].getSource(), edges[i].getDestination(), true, edges[i].getWeight());
    }
  }
  int hosScore = 0;
  for (int i = 0; i < vertices.size(); i++) {
    if (vertices[i][0] == 'R') {
      int minWeight = 1000;
      bool pathToHos = false;
      Dictionary<string, int>* minWeightPath = singleSourceShortestPath(vertices[i], hosGraph);
      for (int j = 0; j < vertices.size(); j++) {
        if (vertices[j][0] == 'M') {
          if (minWeightPath->contains(vertices[j])) {
            if (minWeightPath->get(vertices[j]) < minWeight) {
              minWeight = minWeightPath->get(vertices[j]);
              pathToHos = true;
            }
          }
        }
      }
      if (pathToHos == true) {
        hosScore += 420 / minWeight;
      }
      delete minWeightPath;
    }
  }
  delete hosGraph;
  return hosScore;
}

int InroadsGame::storeScore(){
  Graph<string, bool, int>* storeGraph = new AdjacencyListUndirectedGraph<string, bool, int>();
  vector<string> vertices = this->graph->getVertices();
  for(int i = 0; i < vertices.size(); i++){
    storeGraph->insertVertex(vertices[i]);
  }
  //this->graph->insertVertex(vertices);
  vector<Edge<string, bool, int>> edges = this->graph->getEdges();
  for(int i = 0; i < edges.size(); i++){
    if(edges[i].getLabel() == true){
      storeGraph->insertEdge(edges[i].getSource(), edges[i].getDestination(), true, edges[i].getWeight());
    }
  }
  int storeScore = 0;
  for(int i = 0; i < vertices.size(); i++){
    if(vertices[i][0] == 'R'){
      for(int j = 0; j < vertices.size(); j++){
        if(vertices[j][0] == 'S') {
          try{
            vector<string> numVert = shortestLengthPathBFS(vertices[i], vertices[j], storeGraph);
            if(numVert.size() <= 3){
              storeScore += 10;
            }
          } catch(runtime_error e){
          }
        }
      }
    }
  }
  delete storeGraph;
  return storeScore;
}

int InroadsGame::libraryScore(){
  //run the algorithm on the copy
  Graph<string, bool, int>* libGraph = new AdjacencyListUndirectedGraph<string, bool, int>();
  vector<string> vertices = this->graph->getVertices();
  for(int i = 0; i < vertices.size(); i++){
    libGraph->insertVertex(vertices[i]);
  }
  //this->graph->insertVertex(vertices);
  vector<Edge<string, bool, int>> edges = this->graph->getEdges();
  for(int i = 0; i < edges.size(); i ++){
    if(edges[i].getLabel() == true){
      libGraph->insertEdge(edges[i].getSource(), edges[i].getDestination(), true, edges[i].getWeight());
    }
  }
  int libScore = 0;
  for(int i = 0; i < vertices.size(); i ++){
    if(vertices[i][0] == 'R'){
      std::string tempS = "L";
      bool result = reachableDFS(vertices[i], tempS, libGraph);
      if(result == true){
          libScore += 15;
        }
      }
    }

  delete libGraph;
  return libScore;
}

int InroadsGame::totalScoreRound(){
  int lScore = libraryScore();
  int sScore = storeScore();
  int hScore = hospitalScore();
  this->score = lScore + sScore + hScore;
  return this->score; //hScore + sScore + lScore;
}
