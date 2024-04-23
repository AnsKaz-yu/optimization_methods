#ifndef OPTIMIZATION_METHODS_MAP_H
#define OPTIMIZATION_METHODS_MAP_H
#include <vector>
#include <string>
#include "city.h"

class map {
public:
    map(std::string filename);
    double distance(int i, int j);
    int count_cities(void);
    bool type(int i);
private:
    std::vector<city> cities;
};


#endif //OPTIMIZATION_METHODS_MAP_H
