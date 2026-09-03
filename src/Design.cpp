#include "Design.h"
#include <iostream>
#include "Implementation.h"
std::string Design::state() const { return "Design"; }
void Design::updateState() { std::cout << "Transitioning from Design to Implementation.\n"; }
