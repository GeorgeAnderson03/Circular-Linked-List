#include <iostream>

#include "circular-linked-list.hpp"

int main() {
  CircularLinkedList<int> temp;
  CircularLinkedList<int> temp2;
  temp.InsertInOrder(1);
  temp.InsertInOrder(2);
  temp.InsertInOrder(3);
  temp.InsertInOrder(4);
  temp2.InsertInOrder(4);
  std::cout << temp2 << "temp 2" << std::endl;
  std::cout << temp << std::endl;
  temp.Reverse();
  std::cout << temp << std::endl;
  temp.Reverse();
  std::cout << temp << std::endl;
  temp.Reverse();
  std::cout << temp << std::endl;
  CircularLinkedList<int> temp3 = temp;
  std::cout << temp3 << "temp3" << std::endl;
  temp2 = temp;
  std::cout << temp2 << std::endl;
}
