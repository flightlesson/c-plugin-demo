#include "Klass.hpp"

#include <iostream>

int Klass::doSomething(Stuff *stuff) {
  std::cout << "Klass did something, stuff is " << stuff->name << std::endl;
  return 13;
}
