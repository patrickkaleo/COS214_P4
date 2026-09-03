#include "Deployed.h"
#include <iostream>
std::string Deployed::state() const { return "Deployed"; }
void Deployed::updateState() { std::cout << "Task is already Deployed.\n"; }
