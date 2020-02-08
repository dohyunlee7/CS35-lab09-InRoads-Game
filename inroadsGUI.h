/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#pragma once

#include <string>

#include "adts/graph.h"

#include "gui/inroadsDataReader.h"
#include "gui/inroadsDataWriter.h"
#include "gui/subprocess.h"

class InroadsGUI {
  public:
    /**
     * Creates a new Inroads GUI.  This produces a GUI window for the user to
     * interact with.
     * @param vertexPositions The positions of the vertices in the upcoming
     *                        graph.
     * @param mapPath The path of the map file being drawn.
     * @param debug true to put the GUI into debug mode.
     */
    InroadsGUI(Dictionary<std::string, pair<int, int>>* vertexPositions,
               std::string mapPath, bool debug = false);

    /**
     * Destroys the Inroads GUI.  This action closes the window if it is still
     * open.
     */
    ~InroadsGUI();

    /**
     * Updates the graph being displayed by the GUI.  This method copies the
     * contents of the provided graph into the display.  It must be called when
     * the map should be updated even if the same graph pointer is used.  The
     * labels on each edge of the graph determine whether that road has been
     * improved: true means it has while false mean it hasn't.
     * @param graph The graph that should be used to update the GUI.  The caller
     *              retains ownership of the graph.
     */
    void updateInroadsMap(Graph<std::string, bool, int>* graph);

    /**
     * Updates the message displayed in the GUI window.
     * @param message The new message to display.
     */
    void updateMessage(std::string message);

    /**
     * Updates the score text displayed in the GUI window.
     * @param score text The score text to display.
     */
    void updateScoreText(std::string scoreText);

    /**
     * Updates the turn text displayed in the GUI window.
     * @param turn The turn text to display.
     */
    void updateTurnText(std::string turnText);

    /**
     * Retrieves the next move from the GUI.  This method will wait until the
     * user provides some input and then produce a return value that describes
     * that input.  The result is always a pair of strings.  The possible
     * outcomes are:
     *   1. The player has selected an edge, in which case the two strings are
     *      the names of the vertices that this edge connects.
     *   2. The player has closed the window (meaning that the program should
     *      now stop and no further moves will be made), in which case the two
     *      strings are both empty ("").
     * If anything goes wrong during this process (e.g. getting a move from a
     * GUI that has been closed), an exception is thrown.
     * @return The next move in the GUI as described above.
     */
    std::pair<std::string, std::string> getNextMove();

  private:
    const char** guiArgs;

    Subprocess* subprocess;
    InroadsDataReader* reader;
    InroadsDataWriter* writer;

    void stopGUI();
};
