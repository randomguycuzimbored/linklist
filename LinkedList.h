#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(const T& d) : data(d), next(nullptr), prev(nullptr) {}
    };

    /*==== Construction / Destruction ====*/

LinkedList() : head(nullptr), tail(nullptr), count(0) {
// nothing else to do
}

LinkedList<T>& operator=(const LinkedList<T>& rhs) {
    if (this == &rhs) {
        return *this;
    }

    Clear();

    const Node* cur = rhs.head;

    while (cur != nullptr) {
        AddTail(cur->data);
        cur = cur->next;
    }

    return *this;
}

LinkedList(const LinkedList<T>& other)
    : head(nullptr), tail(nullptr), count(0) {

    const Node* cur = other.head;

    while (cur != nullptr) {
        AddTail(cur->data);
        cur = cur->next;
    }
}

    ~LinkedList(){
	Clear();
    }


    /*==== Behaviors ====*/
void PrintForward() const {
    const Node* cur = head;

    while (cur != nullptr) {
        std::cout << cur->data << std::endl;
        cur = cur->next;
    }
}

void PrintReverse() const {
    const Node* cur = tail;

    while (cur != nullptr) {
        std::cout << cur->data << std::endl;
        cur = cur->prev;
    }
}


void PrintForwardRecursive(const Node* node) const {
    if (node == nullptr) {
        return;
    }

    std::cout << node->data << std::endl;
    PrintForwardRecursive(node->next);
}

void PrintReverseRecursive(const Node* node) const {
    if (node == nullptr) {
        return;
    }

    PrintReverseRecursive(node->next);
    std::cout << node->data << std::endl;
}


    /*==== Accessors ====*/
unsigned int NodeCount() const {
    return count;
}

const Node* Head() const {
    return head;
}

Node* Head() {
    return head;
}

const Node* Tail() const {
    return tail;
}

Node* Tail() {
    return tail;
}

Node* Find(const T& value) {
    Node* cur = head;

    while (cur != nullptr) {
        if (cur->data == value) {
            return cur;
        }

        cur = cur->next;
    }

    return nullptr;
}

const Node* Find(const T& value) const {
    const Node* cur = head;

    while (cur != nullptr) {
        if (cur->data == value) {
            return cur;
        }

        cur = cur->next;
    }

    return nullptr;
}

void FindAll(std::vector<Node*>& outData, const T& value) {
    Node* cur = head;

    while (cur != nullptr) {
        if (cur->data == value) {
            outData.push_back(cur);
        }

        cur = cur->next;
    }
}

Node* GetNode(unsigned int index) {
    if (index >= count) {
        throw std::out_of_range("index out of range");
    }

    Node* cur = head;

    for (unsigned int i = 0; i < index; i++) {
        cur = cur->next;
    }

    return cur;
}

const Node* GetNode(unsigned int index) const {
    if (index >= count) {
        throw std::out_of_range("index out of range");
    }

    const Node* cur = head;

    for (unsigned int i = 0; i < index; i++) {
        cur = cur->next;
    }

    return cur;
}


    /*==== Insertion ====*/

void AddHead(const T& data) {
    Node* n = new Node(data);

    // 1. New node points forward to the old head
    n->next = head;

    // 2. Handle the old head, or empty-list case
    if (head != nullptr) {
        head->prev = n;
    } else {
        tail = n;
    }

    // 3. Update head
    head = n;

    // 4. Increase node count
    count++;
}

void AddTail(const T& data) {
    Node* n = new Node(data);

    // 1. New node points backward to the old tail
    n->prev = tail;

    // 2. Handle the old tail, or empty-list case
    if (tail != nullptr) {
        tail->next = n;
    } else {
        head = n;
    }

    // 3. Update tail
    tail = n;

    // 4. Increase node count
    count++;
}


void AddNodesTail(const T* values, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        AddTail(values[i]);
    }
}

void AddNodesHead(const T* values, unsigned int n) {
    for (int i = static_cast<int>(n) - 1; i >= 0; i--) {
        AddHead(values[i]);
    }
}

void InsertAfter(Node* node, const T& data) {
    if (node == tail) {
        AddTail(data);
        return;
    }

    Node* n = new Node(data);

    n->prev = node;
    n->next = node->next;

    node->next->prev = n;
    node->next = n;

    count++;
}

void InsertBefore(Node* node, const T& data) {
    if (node == head) {
        AddHead(data);
        return;
    }

    Node* n = new Node(data);

    n->next = node;
    n->prev = node->prev;

    node->prev->next = n;
    node->prev = n;

    count++;
}

void InsertAt(const T& data, unsigned int index) {
    if (index > count) {
        throw std::out_of_range("index out of range");
    }

    if (index == 0) {
        AddHead(data);
    }
    else if (index == count) {
        AddTail(data);
    }
    else {
        InsertBefore(GetNode(index), data);
    }
}

    /*==== Removal ====*/


bool RemoveHead() {
    if (head == nullptr) {
        return false;
    }

    RemoveNode(head);
    return true;
}

bool RemoveTail() {
    if (tail == nullptr) {
        return false;
    }

    RemoveNode(tail);
    return true;
}

bool RemoveAt(unsigned int index) {
    if (index >= count) {
        return false;
    }

    RemoveNode(GetNode(index));
    return true;
}

unsigned int Remove(const T& value) {
    unsigned int removed = 0;
    Node* cur = head;

    while (cur != nullptr) {
        Node* next = cur->next;

        if (cur->data == value) {
            RemoveNode(cur);
            removed++;
        }

        cur = next;
    }

    return removed;
}






void Clear() {
    Node* cur = head;

    while (cur != nullptr) {
        Node* nxt = cur->next;
        delete cur;
        cur = nxt;
    }

    head = nullptr;
    tail = nullptr;
    count = 0;
}

    /*==== Operators ====*/

/*==== Operators ====*/

// Non-const indexing
T& operator[](unsigned int index) {
    return GetNode(index)->data;
}

// Const indexing
const T& operator[](unsigned int index) const {
    return GetNode(index)->data;
}

// Equality
bool operator==(const LinkedList<T>& rhs) const {
    if (count != rhs.count) {
        return false;
    }

    const Node* cur1 = head;
    const Node* cur2 = rhs.head;

    while (cur1 != nullptr) {
        if (cur1->data != cur2->data) {
            return false;
        }

        cur1 = cur1->next;
        cur2 = cur2->next;
    }

    return true;
}

    /*==== Debug helper (not in the spec) ====*/

    bool IsConsistent() const {
        // I1: empty means empty everywhere
        if (head == nullptr || tail == nullptr) {
            return head == nullptr && tail == nullptr && count == 0;
        }

        // I2: the ends point outward at nothing
        if (head->prev != nullptr || tail->next != nullptr) {
            return false;
        }

        unsigned int seen = 0;

        for (const Node* cur = head; cur != nullptr; cur = cur->next) {
            seen++;

            if (seen > count) return false; // too many nodes, or a cycle

            // I3: neighbors agree
            if (cur->next != nullptr && cur->next->prev != cur) {
                return false;
            }

            // the walk must finish exactly on tail
            if (cur->next == nullptr && cur != tail) {
                return false;
            }
        }

        return seen == count;
    }


private:

void RemoveNode(Node* x) {
    if (x->prev != nullptr) {
        x->prev->next = x->next;
    } else {
        head = x->next;
    }

    if (x->next != nullptr) {
        x->next->prev = x->prev;
    } else {
        tail = x->prev;
    }

    delete x;
    count--;
}

    Node* head;
    Node* tail;
    unsigned int count;
};
