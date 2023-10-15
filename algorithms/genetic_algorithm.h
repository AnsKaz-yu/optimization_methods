#ifndef OPTIMIZATION_METHODS_GENETIC_ALGORITHM_H
#define OPTIMIZATION_METHODS_GENETIC_ALGORITHM_H
#include "../data storage/map.h"
#include <vector>
struct _population{
    std::vector<int> individual;
    bool complications_are_performed;
    double answer;
    friend bool operator< ( const _population& a, const _population& b){
        if (a.complications_are_performed == b.complications_are_performed){
            return a.answer < b.answer;
        }

        if (a.complications_are_performed) return true;
        else return false;
    }
};

class genetic_algorithm {
public:
    genetic_algorithm(double t, int m0, int m1, map* M, double answer, double accuracy);
    std::vector<double> get_report(); //отчёт о точности решения в зависимости от количества итераций
private:
    double answer; //ответ для этой карты
    double t; //время от начала, за которое должны быть выполнены условия
    int m1; //за t не менее m1 городов группы 1
    int m0; //за t не менее m0 городов группы 0
    bool the_answer_is_calculated;
    map* M; //карта для которой работает алгоритм
    void calculate(); //сами вычисления
    std::vector<double> report; //отчет о точности от итераций
    double accuracy; //заданная точность

    void create_starting_population(std::vector<_population>& population);
    void krossingover(std::vector<_population>& population);
    void mutations(std::vector<_population>& population);
    void selection(std::vector<_population>& population);
};


#endif //OPTIMIZATION_METHODS_GENETIC_ALGORITHM_H
