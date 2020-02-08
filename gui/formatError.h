/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#pragma once

#include "guiFailure.h"

class FormatError : public GuiFailure {
  public:
    explicit FormatError(const char* message) : GuiFailure(message) {
    }
    explicit FormatError(std::string& message) : GuiFailure(message) {
    }
    virtual ~FormatError() throw() {
    }
};
