/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include "inroadsDataWriter.h"

using namespace std;

InroadsDataWriter::InroadsDataWriter(ostream& output, bool debug)
    : DataWriter(output, debug) {
}

void InroadsDataWriter::writePoint(std::pair<int, int> point) {
    writePair<int, int>(point, [&](int x) -> void { return writeInt(x); },
                        [&](int x) -> void { return writeInt(x); });
}

void InroadsDataWriter::writeGameMessage(std::string gameMessage) {
    writeCharToStream('M');
    writeString("gameMessage");
    writeString(gameMessage);
    writeCharToStream('$');
    flushStream();
}

void InroadsDataWriter::writeInroadsGraph(Graph<string, bool, int>* graph) {
    writeCharToStream('M');
    writeString("graph");
    writeGraph<string, bool, int>(graph,
                                  [&](string vertex) { writeString(vertex); },
                                  [&](bool improved) { writeBool(improved); },
                                  [&](int weight) { writeInt(weight); });
    writeCharToStream('$');
    flushStream();
}

void InroadsDataWriter::writeMapPath(string mapPath) {
    writeCharToStream('M');
    writeString("mapPath");
    writeString(mapPath);
    writeCharToStream('$');
    flushStream();
}

void InroadsDataWriter::writeScoreText(string scoreText) {
    writeCharToStream('M');
    writeString("scoreText");
    writeString(scoreText);
    writeCharToStream('$');
    flushStream();
}

void InroadsDataWriter::writeTurnText(string turnText) {
    writeCharToStream('M');
    writeString("turnText");
    writeString(turnText);
    writeCharToStream('$');
    flushStream();
}

void InroadsDataWriter::writeVertexPositions(
    Dictionary<string, pair<int, int>>* positions) {
    writeCharToStream('M');
    writeString("vertexPositions");
    writeDictionary<string, pair<int, int>>(
        positions, [&](string key) { writeString(key); },
        [&](pair<int, int> value) {
            writePair<int, int>(value, [&](int n) { writeInt(n); },
                                [&](int n) { writeInt(n); });
        });
    writeCharToStream('$');
    flushStream();
}
