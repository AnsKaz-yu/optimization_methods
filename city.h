#ifndef OPTIMIZATION_METHODS_CITY_H
#define OPTIMIZATION_METHODS_CITY_H


class city {
public:
    city(double x, double y, bool type) {
        this->x = x;
        this->y = y;
        this->type = type;
    }

    bool get_type();

    friend double operator- (const city& c1, const city& c2);
private:
    double x, y;
    bool type;
};


#endif //OPTIMIZATION_METHODS_CITY_H
