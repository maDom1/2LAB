#include "Queap.h"
#include <stdexcept>
#include <iostream>
#include <memory>

using namespace std;

namespace my_project {

class MyDeque {
    struct Node {
        int value;
        Node* prev;
        Node* next;
        Node(int v) : value(v), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int sz;

public:
    MyDeque() : head(nullptr), tail(nullptr), sz(0) {}
    ~MyDeque() { clear(); }

    void push_back(int x) {
        Node* n = new Node(x);
        if (!head) {
            head = tail = n;
        } else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
        sz++;
    }

    void pop_front() {
        if (!head) throw underflow_error("Deque is empty");
        Node* h = head;
        head = head->next;
        if (head) head->prev = nullptr; else tail = nullptr;
        delete h;
        sz--;
    }

    int front() const {
        if (!head) throw underflow_error("Deque is empty");
        return head->value;
    }

    int size() const {
        return sz;
    }

    bool empty() const {
        return (sz == 0);
    }

    bool removeOne(int x) {
        Node* cur = head;
        while (cur) {
            if (cur->value == x) {
                Node* p = cur->prev;
                Node* nx = cur->next;
                if (p) p->next = nx; else head = nx;
                if (nx) nx->prev = p; else tail = p;
                delete cur;
                sz--;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    void clear() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        sz = 0;
    }

    bool equals(const MyDeque& other) const {
        if (sz != other.sz) return false;
        Node* a = head;
        Node* b = other.head;
        while (a && b) {
            if (a->value != b->value) return false;
            a = a->next;
            b = b->next;
        }
        return true;
    }

    bool lessThan(const MyDeque& other) const {
        Node* a = head;
        Node* b = other.head;
        while (a && b) {
            if (a->value < b->value) return true;
            if (a->value > b->value) return false;
            a = a->next;
            b = b->next;
        }
        return (sz < other.sz);
    }

    int at(int index) const {
        if (index < 0 || index >= sz) {
            throw out_of_range("Index out of range in Deque");
        }
        Node* cur = head;
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }
        return cur->value;
    }

    void copyFrom(const MyDeque& other) {
        clear();
        Node* cur = other.head;
        while (cur) {
            push_back(cur->value);
            cur = cur->next;
        }
    }

    void printAll() const {
        Node* cur = head;
        while (cur) {
            cout << cur->value << " ";
            cur = cur->next;
        }
    }
};

class MyMultiSet {
    struct Node {
        int value;
        Node* prev;
        Node* next;
        Node(int v) : value(v), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int sz;

public:
    MyMultiSet() : head(nullptr), tail(nullptr), sz(0) {}
    ~MyMultiSet() { clear(); }

    void insert(int x) {
        Node* n = new Node(x);
        if (!head) {
            head = tail = n;
            sz++;
            return;
        }
        Node* cur = head;
        while (cur && cur->value <= x) {
            cur = cur->next;
        }
        if (!cur) {
            tail->next = n;
            n->prev = tail;
            tail = n;
        } else {
            Node* p = cur->prev;
            n->next = cur;
            cur->prev = n;
            n->prev = p;
            if (p) p->next = n; else head = n;
        }
        sz++;
    }

    int count(int x) const {
        int c = 0;
        Node* cur = head;
        while (cur) {
            if (cur->value == x) c++;
            cur = cur->next;
        }
        return c;
    }

    void eraseOne(int x) {
        Node* cur = head;
        while (cur) {
            if (cur->value == x) {
                Node* p = cur->prev;
                Node* nx = cur->next;
                if (p) p->next = nx; else head = nx;
                if (nx) nx->prev = p; else tail = p;
                delete cur;
                sz--;
                return;
            }
            cur = cur->next;
        }
    }

    bool empty() const {
        return (sz == 0);
    }

    void clear() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        sz = 0;
    }

    int getMin() const {
        if (!head) throw underflow_error("No elements in container");
        return head->value;
    }

    void copyFrom(const MyMultiSet& other) {
        clear();
        Node* cur = other.head;
        while (cur) {
            insert(cur->value);
            cur = cur->next;
        }
    }
};

struct Queap::QueapImpl {
private:
    friend class Queap;
    static const int MAX_SIZE = 25;
    MyDeque queue;
    MyMultiSet minSet;
};

Queap::Queap() : impl(std::make_unique<QueapImpl>()) {}

Queap::Queap(const Queap& other) : impl(std::make_unique<QueapImpl>()) {
    impl->queue.copyFrom(other.impl->queue);
    impl->minSet.copyFrom(other.impl->minSet);
}

Queap& Queap::operator=(const Queap& other) {
    if (this != &other) {
        impl->queue.copyFrom(other.impl->queue);
        impl->minSet.copyFrom(other.impl->minSet);
    }
    return *this;
}

Queap::~Queap() = default;

void Queap::enqueue(int x) {
    if (impl->queue.size() >= QueapImpl::MAX_SIZE) {
        throw overflow_error("Queap is full. Maximum size is 25.");
    }
    if (impl->minSet.count(x) > 0) {
        throw DuplicateValueException(x);
    }
    impl->queue.push_back(x);
    impl->minSet.insert(x);
}

void Queap::dequeue() {
    if (impl->queue.empty()) {
        throw underflow_error("Queue is empty. Cannot dequeue.");
    }
    int frontVal = impl->queue.front();
    impl->queue.pop_front();
    impl->minSet.eraseOne(frontVal);
}

int Queap::findMin() const {
    if (impl->minSet.empty()) {
        throw underflow_error("Queue is empty. Cannot find minimum.");
    }
    return impl->minSet.getMin();
}

bool Queap::isEmpty() const {
    return impl->queue.empty();
}

int Queap::size() const {
    return impl->queue.size();
}

void Queap::printQueap() const {
    impl->queue.printAll();
}

bool Queap::operator==(const Queap& other) const {
    return impl->queue.equals(other.impl->queue);
}

bool Queap::operator!=(const Queap& other) const {
    return !(*this == other);
}

bool Queap::operator<(const Queap& other) const {
    return impl->queue.lessThan(other.impl->queue);
}

bool Queap::operator>(const Queap& other) const {
    return other.impl->queue.lessThan(impl->queue);
}

bool Queap::operator<=(const Queap& other) const {
    return !(*this > other);
}

bool Queap::operator>=(const Queap& other) const {
    return !(*this < other);
}

int Queap::operator[](int index) const {
    return impl->queue.at(index);
}

Queap& Queap::operator+=(const Queap& other) {
    for (int i = 0; i < other.impl->queue.size(); i++) {
        if (impl->queue.size() >= QueapImpl::MAX_SIZE) break;
        int val = other.impl->queue.at(i);
        if (impl->minSet.count(val) == 0) {
            impl->queue.push_back(val);
            impl->minSet.insert(val);
        }
    }
    return *this;
}

Queap& Queap::operator-=(const Queap& other) {
    for (int i = 0; i < other.impl->queue.size(); i++) {
        int val = other.impl->queue.at(i);
        if (impl->queue.removeOne(val)) {
            impl->minSet.eraseOne(val);
        }
    }
    return *this;
}

void Queap::operator!() {
    impl->queue.clear();
    impl->minSet.clear();
}

}
