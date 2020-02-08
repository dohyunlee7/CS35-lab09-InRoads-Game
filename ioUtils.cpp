/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include "ioUtils.h"
#include "adjacencyListUndirectedGraph.h"
#include "adts/graph.h"
#include "adts/stlBST.h"

using namespace std;

std::pair<Graph<string, bool, int>*,
          Dictionary<std::string, std::pair<int, int>>*>
readInroadsMap(string filename) {
    ifstream file(filename);
    string line;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    Dictionary<string, pair<int, int>>* dictionary =
        new STLBST<string, pair<int, int>>();
    Graph<string, bool, int>* graph =
        new AdjacencyListUndirectedGraph<string, bool, int>();
    try {
        getline(file, line);
        while (line != "end") {
            if (line == "vertex") {
                string vertex;
                getline(file, vertex);
                getline(file, line);
                int x = stoi(line);
                getline(file, line);
                int y = stoi(line);
                dictionary->insert(vertex, pair<int, int>(x, y));
                graph->insertVertex(vertex);
            } else if (line == "edge") {
                string location1;
                getline(file, location1);
                string location2;
                getline(file, location2);
                int weight;
                getline(file, line);
                weight = stoi(line);
                graph->insertEdge(location1, location2, false, weight);
            } else {
                throw std::runtime_error("Unexpected line in map file: " +
                                         line);
            }
            getline(file, line);
        }
    } catch (std::exception& e) {
        delete dictionary;
        delete graph;
        throw;
    }
    return pair<Graph<string, bool, int>*,
                Dictionary<std::string, std::pair<int, int>>*>(graph,
                                                               dictionary);
}
