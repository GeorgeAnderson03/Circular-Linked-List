#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void Reverse();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;  // doesn't work?
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}
template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (head_ == nullptr) {
    head_ = tail_ = new Node<T>(data);
    tail_->next = head_;
    return;
  }
  if (node_order_ == Order::kASC) {
    Node<T>* temp = new Node<T>(data);
    if (data <= head_->data) {
      temp->next = head_;
      head_ = temp;
      tail_->next = head_;
      return;
    }
    if (data >= tail_->data) {
      tail_->next = temp;
      tail_ = temp;
      tail_->next = head_;
      return;
    }
    Node<T>* current = head_;
    while (current->next != head_) {
      if (current->next->data > data) {
        temp->next = current->next;
        current->next = temp;
        break;
      }
      current = current->next;
    }
  } else if (node_order_ == Order::kDESC) {
    Node<T>* temp = new Node<T>(data);
    if (data >= head_->data) {
      temp->next = head_;
      head_ = temp;
      tail_->next = head_;
      return;
    }
    if (data <= tail_->data) {
      tail_->next = temp;
      tail_ = temp;
      tail_->next = head_;
      return;
    }
    Node<T>* current = head_;
    while (current->next != head_) {
      if (current->next->data < data) {
        temp->next = current->next;
        current->next = temp;
        break;
      }
      current = current->next;
    }
  }
}
template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  node_order_ = source.node_order_;
  if (source.head_ == nullptr) {
    return;
  }

  // copy()
  Node<T>* current = source.head_;
  while (current->next != source.head_) {
    InsertInOrder(current->data);
    current = current->next;
  }
  InsertInOrder(current->data);
}
template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(
    const CircularLinkedList<T>& source) {
  if (this == &source) {
    return *this;
  }
  if (head_ != nullptr) {
    if (head_->next == head_) {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    } else {
      Node<T>* nextnode = head_;
      do {
        nextnode = nextnode->next;
        delete head_;
        head_ = nextnode;
        tail_->next = head_;
      } while (head_->next != head_);
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    }
  }
  // clear();
  // copy()
  // return *this;
  node_order_ = source.node_order_;
  if (!(source.head_ == nullptr)) {
    Node<T>* current = source.head_;
    while (current->next != source.head_) {
      InsertInOrder(current->data);
      current = current->next;
    }
    InsertInOrder(current->data);
  }
  return *this;
}
template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  if (head_ == nullptr) {
    return;
  }
  if (head_->next == head_) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    Node<T>* nextnode = head_;
    do {
      nextnode = nextnode->next;
      delete head_;
      head_ = nextnode;
      tail_->next = head_;
    } while (head_->next != head_);
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
  }
}
template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else {
    node_order_ = Order::kASC;
  }
  if (head_ == nullptr) {
    return;
  }
  Node<T>* previous = nullptr;
  Node<T>* current = head_;
  Node<T>* nextnode = nullptr;
  do {
    nextnode = current->next;
    current->next = previous;
    previous = current;
    current = nextnode;
  } while (current != head_);
  head_->next = tail_;
  head_ = previous;
  tail_ = current;
}

#endif