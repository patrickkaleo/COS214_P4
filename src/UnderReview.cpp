#include "UnderReview.h"
#include <iostream>
#include "Deployed.h"
std::string UnderReview::state() const { return "UnderReview"; }
void UnderReview::updateState() { std::cout << "Transitioning from UnderReview to Deployed.\n"; }
