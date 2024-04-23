#include "map.h"
#include <fstream>
#include <iostream>
map::map(std::string filename) {
    std::ifstream fin(filename);

    if (!fin.is_open()) {
        std::cout << "ERRIR: File isn't open\n";
        return;
    }
    int n;
    fin >> n;

    for (int i = 0; i < n; i++) {
        double x, y;
        bool type;
        fin >> x >> y >> type;
        cities.push_back(city(x, y, type));
    }

    fin.close();
}

double map::distance(int i, int j) {
   
    return cities[i] - cities[j];
}

int map::count_cities() {
    return cities.size();
}

bool map::type(int i) {
    return cities[i].get_type();
}