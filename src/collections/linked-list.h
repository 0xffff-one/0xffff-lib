#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include <algorithm>

template <typename T>
class LinkedList {
 public:
  LinkedList() = default;
  void push(T data) {
    auto node = new Node(data);
    if (this->tail == nullptr) {
      this->tail = node;
      this->head = this->tail;
    } else {
      this->tail->next = node;
      this->tail = node;
    }
  }

  T& operator[](size_t idx) {
    auto walk = this->head;
    if (walk == nullptr) {
      throw "index out of range";
    }

    while (walk != nullptr && idx != 0) {
      walk = walk->next;
      idx--;
    }

    if (idx != 0) {
      throw "index out of range";
    }
    return walk->data;
  }

 private:
  struct Node {
    T data;
    Node* next = nullptr;
    Node* prev = nullptr;
    Node() = default;
    Node(T data) : data(data) {}
  };

  Node* head = nullptr;
  Node* tail = nullptr;
};
#endif /* ifndef _LINKED_LIST_ */
