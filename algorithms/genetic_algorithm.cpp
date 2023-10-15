#include "genetic_algorithm.h"
genetic_algorithm::genetic_algorithm(double t, int m0, int m1, map* M, double answer, double accuracy){
    this->t = t;
    this->m0 = m0;
    this->m1 = m1;
    this->M = M;
    this-> answer = answer;
    this->accuracy = accuracy;
    report.clear();
    the_answer_is_calculated = false;
}


std::vector<double> genetic_algorithm::get_report() {
    if (!the_answer_is_calculated){
        calculate();
    }
    return report;
}



void genetic_algorithm::calculate() {
    the_answer_is_calculated = true;
    int n = M->count_cities();
    std::vector<_population> population;

    create_starting_population(population); //создание стартовой популяции
    do{
        krossingover(population);
        mutations(population);
        selection(population);
        report.push_back(population[0].answer - accuracy); //заносим данные в отчетность
    }while (population[0].answer - accuracy > answer);
}

void genetic_algorithm::create_starting_population(std::vector<_population> &population) {

}

void genetic_algorithm::krossingover(std::vector<_population> &population) {

}

void genetic_algorithm::selection(std::vector<_population> &population) {

}

void genetic_algorithm::mutations(std::vector<_population> &population) {

}
