#include "PersonnelDecorator.h"
std::string PersonnelDecorator::decoration() const {
    return "[Personnel: " + deco + "] -> " + item->getDescription();
}
