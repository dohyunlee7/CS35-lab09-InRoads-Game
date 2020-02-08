/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#pragma once

#include <stdexcept>
#include <string>

class GuiFailure : public std::runtime_error {
  public:
    explicit GuiFailure(const char* message) : std::runtime_error(message) {
    }
    explicit GuiFailure(std::string& message) : std::runtime_error(message) {
    }
    virtual ~GuiFailure() throw() {
    }
};
