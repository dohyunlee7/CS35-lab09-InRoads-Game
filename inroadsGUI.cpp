/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include <stdexcept>

#include "inroadsGUI.h"

using namespace std;

InroadsGUI::InroadsGUI(Dictionary<string, pair<int, int>>* vertexPositions,
                       string mapPath, bool debug) {
    this->guiArgs = new const char*[4 + (debug ? 1 : 0)];
    int argIdx = 0;
    this->guiArgs[argIdx++] = "java";
    this->guiArgs[argIdx++] = "-jar";
    this->guiArgs[argIdx++] = "InroadsGUI.jar";
    if (debug) {
        this->guiArgs[argIdx++] = "-D";
    }
    this->guiArgs[argIdx++] = NULL;

    this->subprocess = new Subprocess(this->guiArgs, true);
    this->reader = new InroadsDataReader(this->subprocess->stdout, debug);
    this->writer = new InroadsDataWriter(this->subprocess->stdin, debug);

    this->writer->writeVertexPositions(vertexPositions);
    this->writer->writeMapPath(mapPath);
}

InroadsGUI::~InroadsGUI() {
    stopGUI();
    delete[] this->guiArgs;
}

void InroadsGUI::updateInroadsMap(Graph<string, bool, int>* graph) {
    if (this->subprocess != NULL) {
        this->writer->writeInroadsGraph(graph);
    } else {
        throw runtime_error(
            "The GUI is no longer functioning; cannot update map.");
    }
}

void InroadsGUI::updateScoreText(string scoreText) {
    if (this->subprocess != NULL) {
        this->writer->writeScoreText(scoreText);
    } else {
        throw runtime_error(
            "The GUI is no longer functioning; cannot update score text.");
    }
}

void InroadsGUI::updateTurnText(string turnText) {
    if (this->subprocess != NULL) {
        this->writer->writeTurnText(turnText);
    } else {
        throw runtime_error(
            "The GUI is no longer functioning; cannot update turn text.");
    }
}

void InroadsGUI::updateMessage(string message) {
    if (this->subprocess != NULL) {
        this->writer->writeGameMessage(message);
    } else {
        throw runtime_error(
            "The GUI is no longer functioning; cannot update message.");
    }
}

pair<string, string> InroadsGUI::getNextMove() {
    if (this->subprocess != NULL) {
        vector<string> message = this->reader->readMessage();
        if (message.size() > 0 && message[0] == "close") {
            stopGUI();
            return pair<string, string>("", "");
        } else if (message.size() > 0 && message[0] == "error") {
            stopGUI();
            throw runtime_error("GUI error: " + message.at(1));
        } else if (message.size() > 0 && message[0] == "edge") {
            return pair<string, string>(message.at(1), message.at(2));
        } else {
            throw runtime_error("Unrecognized message from GUI");
        }
    } else {
        throw runtime_error("Attempted to get next move from GUI which is "
                            "no longer functioning.");
    }
}

void InroadsGUI::stopGUI() {
    if (this->subprocess != NULL) {
        this->subprocess->kill();
        delete this->subprocess;
        delete this->reader;
        delete this->writer;
        this->subprocess = NULL;
    }
}
