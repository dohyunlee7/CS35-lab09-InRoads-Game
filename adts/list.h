#pragma once
/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

/**
 * A List is an abstract (a.k.a. pure virtual) class specifying the interface
 * for a list of an arbitrary data type.
 */
template <typename T> class List {
  public:
    virtual ~List(){/* do nothing */};

    /**
     * Determines the size of the list.
     * @return The number of elements in the list.
     */
    virtual int getSize() = 0;

    /**
     * Determines whether the list is empty.
     * @return true if the list is empty; false if it is not.
     */
    virtual bool isEmpty() = 0;

    /**
     * Retrieves the first element of the list.
     * @return The element at index 0 of this list.
     * @throws runtime_error If the list is empty.
     */
    virtual T getFirst() = 0;

    /**
     * Retrieves the last element of the list.
     * @return The element at the last index of this list.
     * @throws runtime_error If the list is empty.
     */
    virtual T getLast() = 0;

    /**
     * Retrieves the element from the list at index i.
     * @param i The index for the element to retrieve.
     * @return The element at that index.
     * @throws runtime_error If there is no index i in this list.
     */
    virtual T get(int i) = 0;

    /**
     * Inserts a value at the beginning of this list.
     * @param value The value to insert.
     */
    virtual void insertFirst(T value) = 0;

    /**
     * Inserts the value at the end of this list.
     * @param value The value to insert.
     */
    virtual void insertLast(T value) = 0;

    /**
     * Removes the first element from this list.
     * @return The element that was removed.
     * @throws runtime_error If the list was empty.
     */
    virtual T removeFirst() = 0;

    /**
     * Removes the last element from this list.
     * @return The element that was removed.
     * @throws runtime_error If the list was empty.
     */
    virtual T removeLast() = 0;

    // You can safely ignore the following code.  This eliminates some default
    // class routines, preventing you from using them accidentally.
    // Specifically, we are disabling the use of the copy constructor and the
    // copy assignment operator.  You can read more here:
    //   http://www.cplusplus.com/articles/y8hv0pDG/
  public:
    List() {
    }

  private:
    List(const List& other) = delete;
    List& operator=(const List& other) = delete;
};
