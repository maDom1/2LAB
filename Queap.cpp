#include "Queap.h"
#include <deque>
#include <set>
#include <iostream>
#include <memory>
#include <algorithm>
#include <stdexcept>

using namespace std;

namespace my_project {

struct Queap::QueapImpl {
    static const int MAX_SIZE = 25;

    deque<int> queue;
    multiset<int> minSet;

    void enqueue(int x) {
        if (queue.size() >= MAX_SIZE) {
            throw overflow_error("Queap is full. Maximum size is 25.");
        }
        if (minSet.count(x) > 0) {
            throw DuplicateValueException(x);
        }
        queue.push_back(x);
        minSet.insert(x);
    }

    void dequeue() {
        if (queue.empty()) {
            throw underflow_error("Queue is empty. Cannot dequeue.");
        }
        int front = queue.front();
        queue.pop_front();
        minSet.erase(minSet.find(front));
    }

    int findMin() const {
        if (minSet.empty()) {
            throw underflow_error("Queue is empty. Cannot find minimum.");
        }
        return *minSet.begin();
    }

    bool isEmpty() const {
        return queue.empty();
    }

    int size() const {
        return (int)queue.size();
    }

    void printQueap() const {
        cout << "Queap contents: ";
        for (int val : queue) {
            cout << val << " ";
        }
        cout << endl;
    }

    bool isEqualTo(const QueapImpl& other) const {
        return queue == other.queue;
    }

    int getAtIndex(int index) const {
        if (index < 0 || index >= (int)queue.size()) {
            throw out_of_range("Index out of range in Queap");
        }
        return queue[index];
    }

    void addFrom(const QueapImpl& other) {
        for (int val : other.queue) {
            if (queue.size() >= MAX_SIZE) break;
            if (minSet.count(val) == 0) {
                queue.push_back(val);
                minSet.insert(val);
            }
        }
    }

    void removeFrom(const QueapImpl& other) {
        for (int val : other.queue) {
            auto it = find(queue.begin(), queue.end(), val);
            if (it != queue.end()) {
                queue.erase(it);
                minSet.erase(minSet.find(val));
            }
        }
    }

    void clear() {
        queue.clear();
        minSet.clear();
    }
};

Queap::Queap() : impl(make_unique<QueapImpl>()) {}

Queap::Queap(const Queap& other) : impl(make_unique<QueapImpl>(*other.impl)) {}

Queap::~Queap() = default;

void Queap::enqueue(int x) {
    impl->enqueue(x);
}

void Queap::dequeue() {
    impl->dequeue();
}

int Queap::findMin() const {
    return impl->findMin();
}

bool Queap::isEmpty() const {
    return impl->isEmpty();
}

int Queap::size() const {
    return impl->size();
}

void Queap::printQueap() const {
    impl->printQueap();
}

Queap& Queap::operator=(const Queap& other) {
    if (this != &other) {
        impl = make_unique<QueapImpl>(*other.impl);
    }
    return *this;
}

bool Queap::operator==(const Queap& other) const {
    return impl->isEqualTo(*other.impl);
}

bool Queap::operator!=(const Queap& other) const {
    return !(*this == other);
}

bool Queap::operator<(const Queap& other) const {
    return impl->queue < other.impl->queue;
}

bool Queap::operator>(const Queap& other) const {
    return impl->queue > other.impl->queue;
}

bool Queap::operator<=(const Queap& other) const {
    return !(*this > other);
}

bool Queap::operator>=(const Queap& other) const {
    return !(*this < other);
}

int Queap::operator[](int index) const {
    return impl->getAtIndex(index);
}

Queap& Queap::operator+=(const Queap& other) {
    impl->addFrom(*other.impl);
    return *this;
}

Queap& Queap::operator-=(const Queap& other) {
    impl->removeFrom(*other.impl);
    return *this;
}

void Queap::operator!() {
    impl->clear();
}

}
