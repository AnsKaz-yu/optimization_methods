#ifndef OPTIMIZATION_METHODS_DYNAMIC_ALGORITHM_H
#define OPTIMIZATION_METHODS_DYNAMIC_ALGORITHM_H
#include "map.h"

class dynamic_algorithm {
public:
    dynamic_algorithm(double t, int m0, int m1, map* M);
    double get_answer();
private:
    map* M; //карта для которой работает алгоритм
    double answer; //ответ для этой карты
    double t; //время от начала, за которое должны быть выполнены условия
    int m1; //за t не менее m1 городов группы 1
    int m0; //за t не менее m0 городов группы 0
    bool the_answer_is_calculated;
    void calculation();
};


#endif //OPTIMIZATION_METHODS_DYNAMIC_ALGORITHM_H
