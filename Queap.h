// Dominykas Pavlavičius 1k 2.1gr
// Queap implementation
// This file contains the declaration of the Queap class and custom exception

#ifndef QUEAP_H
#define QUEAP_H

#include <memory>
#include <stdexcept>
#include <string>

namespace my_project {

// Exception class for handling duplicate values in the Queap
class DuplicateValueException : public std::runtime_error {
public:
    explicit DuplicateValueException(int value)
        : std::runtime_error("Duplicate value: " + std::to_string(value)) {}
};

class Queap {
public:
    Queap();                                  // Default constructor
    Queap(const Queap& other);                // Copy constructor for deep copy
    Queap& operator=(const Queap& other);     // Copy assignment operator
    ~Queap();                                 // Destructor

    void enqueue(int x);                      // Add value to the queue
    void dequeue();                           // Remove the front value from the queue
    int findMin() const;                      // Return the minimum value
    bool isEmpty() const;                     // Check if queue is empty
    int size() const;                         // Get the number of elements in queue
    void printQueap() const;                  // Print all values in the queue

    // Operator overloads for comparison and access
    bool operator==(const Queap& other) const;    // Check if two Queaps are equal
    bool operator!=(const Queap& other) const;    // Check if two Queaps are not equal
    bool operator<(const Queap& other) const;     // Comparison
    bool operator>(const Queap& other) const;
    bool operator<=(const Queap& other) const;
    bool operator>=(const Queap& other) const;
    int operator[](int index) const;              // Access element at index
    Queap& operator+=(const Queap& other);        // Add contents of another Queap
    Queap& operator-=(const Queap& other);        // Remove elements found in another Queap
    void operator!();                             // Clear the queue

private:
    struct QueapImpl;                             // Forward declaration of implementation
    std::unique_ptr<QueapImpl> impl;              // Pointer to internal implementation
};

} // namespace my_project

#endif
