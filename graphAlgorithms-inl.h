/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>
#include "adts/dictionary.h"
#include "adts/stlMinPriorityQueue.h"
#include "adts/stack.h"
#include "adts/stlStack.h"
#include "adts/list.h"
#include "adts/stlList.h"
#include "adts/stlHashTable.h"
#include "adts/stlQueue.h"
#include "adts/graph.h"

template <typename V, typename E, typename W>
bool reachableDFS(V src, V dest, Graph<V, E, W>* g) {
    //throw runtime_error("Not yet implemented: reachableDFS");
    STLStack<V> theStack;
    Dictionary<V,bool>* taken = new STLHashTable<V,bool>();
    theStack.push(src);
    taken->insert(src, true);
    while(!theStack.isEmpty()){
      V loc = theStack.pop();
      if(loc == dest){
        delete taken;
        return true;
      }
      vector<V> theNeighbors = g->getNeighbors(loc);
      for(int i = 0; i < theNeighbors.size(); i ++){
        if(!taken->contains(theNeighbors[i])){
          theStack.push(theNeighbors[i]);
          taken->insert(theNeighbors[i], true);
        }
      }

    }
    delete taken;
    return false;
}

template <typename V, typename E, typename W>
vector<V> shortestLengthPathBFS(V src, V dest, Graph<V, E, W>* g) {
    STLHashTable<V, V>* hasher = new STLHashTable<V,V>();
    Queue<V>* theQueue = new STLQueue<V>();
    hasher->insert(src, src);
    theQueue->enqueue(src);

    while(!theQueue->isEmpty()){
      V newVal = theQueue->dequeue();
      if(newVal == dest){
        V pos = newVal;
        STLList<V> thePath;
        thePath.insertFirst(newVal);
        while(newVal != src){
          newVal = hasher->get(newVal);
          thePath.insertFirst(newVal);
        }
        vector<V> vecOrdPath;
        for(int i = 0; i < thePath.getSize(); i ++){
          vecOrdPath.push_back(thePath.get(i));
        }
        //clean up memory
        delete hasher;
        delete theQueue;
        return vecOrdPath;
        }
        vector<V> theNeighbors = g->getNeighbors(newVal);
        for(int i = 0; i < theNeighbors.size(); i ++){
          if(hasher->contains(theNeighbors[i]) == false){
            theQueue->enqueue(theNeighbors[i]);
            hasher->insert(theNeighbors[i], newVal);
          }
        }
      }
      delete hasher;
      delete theQueue;
      throw runtime_error("A path was not discovered");

}


template <typename V, typename E, typename W>
Dictionary<V, W>* singleSourceShortestPath(V src, Graph<V, E, W>* g) {
    Dictionary<V, W>* totalWeight = new STLHashTable<V, W>();
    PriorityQueue<int, V>* theQueue = new STLMinPriorityQueue<int, V>();
    totalWeight->insert(src, 0);
    theQueue->insert(0, src);

    while(!theQueue->isEmpty()){
      V newVal = theQueue->remove();
      vector<Edge<V, E, W>> theEdges = g->getOutgoingEdges(newVal);

      for(int i = 0; i < theEdges.size(); i ++){
        Edge<V, E, W> edge1 = theEdges[i];
        int newWeight = edge1.getWeight() + totalWeight->get(newVal);
        V theNeighbors = theEdges[i].getDestination();

        if(!totalWeight->contains(theNeighbors)){
          theQueue->insert(newWeight, theNeighbors);
          totalWeight->insert(theNeighbors, newWeight);
        }

        else if(totalWeight->get(theNeighbors) > newWeight){
          theQueue->insert(newWeight, theNeighbors);
          totalWeight->update(theNeighbors, newWeight);
        }
      }
    }
    //delete totalWeight;
    delete theQueue;
    return totalWeight;
}
