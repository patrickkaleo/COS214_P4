#include "Implementation.h"
#include <iostream>
#include "UnderReview.h"
std::string Implementation::state() const { return "Implementation"; }
void Implementation::updateState() { std::cout << "Transitioning from Implementation to UnderReview.\n"; }
