/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <istream>
#include <string>
#include <utility>

#include "formatError.h"
#include "inroadsDataReader.h"

using namespace std;

InroadsDataReader::InroadsDataReader(std::istream& input, bool debug)
    : DataReader(input, debug) {
}

pair<string, string> InroadsDataReader::readEdge() {
    return readPair<string, string>([&]() { return this->readString(); },
                                    [&]() { return this->readString(); });
}

vector<string> InroadsDataReader::readMessage() {
    requireCharFromStream('M', "Expected message");
    string messageType = readString();
    vector<string> message = {messageType};
    if (messageType == "edge") {
        pair<string, string> edge = readEdge();
        message.push_back(edge.first);
        message.push_back(edge.second);
    } else if (messageType == "error") {
        message.push_back(readString());
    } else if (messageType == "close") {
        // There's nothing else to read.
    }
    requireCharFromStream('$', "Expected message terminator");
    return message;
}
