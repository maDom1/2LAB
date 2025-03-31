// Dominykas Pavlavičius 1k 2.1gr
// Queap implementation
// This file contains the declaration of the Queap class

#ifndef QUEAP_H
#define QUEAP_H

#include <memory>
#include <stdexcept>
#include <string>

namespace my_project {

class DuplicateValueException : public std::runtime_error {
public:
    explicit DuplicateValueException(int value)
        : std::runtime_error("Duplicate value: " + std::to_string(value)) {}
};

class Queap {
public:
    Queap();
    Queap(const Queap& other);                    // Copy constructor
    Queap& operator=(const Queap& other);         // Copy assignment
    ~Queap();

    void enqueue(int x);
    void dequeue();
    int findMin() const;
    bool isEmpty() const;
    int size() const;
    void printQueap() const;

    // Operator overloads
    bool operator==(const Queap& other) const;
    bool operator!=(const Queap& other) const;
    bool operator<(const Queap& other) const;
    bool operator>(const Queap& other) const;
    bool operator<=(const Queap& other) const;
    bool operator>=(const Queap& other) const;
    int operator[](int index) const;
    Queap& operator+=(const Queap& other);
    Queap& operator-=(const Queap& other);
    void operator!();

private:
    struct QueapImpl;
    std::unique_ptr<QueapImpl> impl;
};

} // namespace my_project

#endif // QUEAP_H
