#include "city.h"
#include <cmath>
double operator- (const city& c1, const city& c2) {
    return sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
}

bool city::get_type() {
    return this->type;
}