#include "genetic_algorithm.h"
#include <iostream>
#include <set>
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

void genetic_algorithm::print_population(std::vector<_population> p) {
    std::cout << std::endl;
    for (auto _p : p) {
        for (auto i : _p.individual) {
            std::cout << i + 1 << ' ';
        }
        std::cout << std::endl;
        std::cout << _p.answer << ' ' << bool(_p.complications_are_performed) << std::endl;
    }
    std::cout << std::endl;
}


void genetic_algorithm::calculate() {
    the_answer_is_calculated = true;
    
    std::vector<_population> population;
    srand(time(0));

    create_starting_population(population); //создание стартовой популяции
    do{
        print_population(population);
        krossingover(population);
        mutations(population);
        selection(population);
        //report.push_back(population[0].answer - accuracy); //заносим данные в отчетность
    }while (abs(population[0].answer - answer) > accuracy || !population[0].complications_are_performed);
}

double genetic_algorithm::calc_answer(std::vector<int> indiv) {
    double answer = 0;
    int prev_city = indiv[0];
    for (auto city : indiv) {
        answer += this->M->distance(city, prev_city);
        prev_city = city;
    }
    return answer;
}

bool genetic_algorithm::calc_complications(std::vector<int> indiv) {
    double time = 0;
    int k0 = 0;
    int k1 = 0;
    int prev_city = indiv[0];
    for (auto city : indiv) {
       
        time += this->M->distance(city, prev_city);
        
        if (time > t && k0 < m0) return false;

        if (this->M->type(city)) k1++;
        else k0++;

        if (time <= t && k1 > m1) return false;
    }
    return true;
}

void genetic_algorithm::create_starting_population(std::vector<_population> &population) {
    
    int n = M->count_cities();
    //генерируем половину схем абсолютно случайным образом

    for (int i = 0; i < POPULATION_SIZE; i++) {
        _population new_population;
        
        for (int j = 0; j < n; j++) {
            new_population.individual.push_back(j);
        }
        new_population.mix(0, n);
        new_population.complications_are_performed = calc_complications(new_population.individual);
        new_population.answer = calc_answer(new_population.individual);

        population.push_back(new_population);
    }
}



_population genetic_algorithm::calc_kross(_population p1, _population p2, int k) {
    _population p;
    std::multiset<int> control;
    for (int i = 0; i < k; i++) { //берем первые k городов из p1
        p.individual.push_back(p1.individual[i]);
        control.insert(p1.individual[i]);
    }

    for (int i = k; i < p2.individual.size(); i++) { //добираем из p2
        p.individual.push_back(p2.individual[i]);
        control.insert(p2.individual[i]);
    }

    //находим забытые (те, что не упоминались ни разу)
    std::vector<int> lost;
    for (int i = 0; i < p1.individual.size(); i++) {
        if (control.count(p1.individual[i]) == 0) {
            lost.push_back(p1.individual[i]);
        }
    }

    //отсеиваем те, что попались несколько раз и добавляем те, которые не попались ни разу
    for (int i = 0; i < p.individual.size(); i++) {
        if (control.count(p.individual[i]) > 1) {
            control.erase(p.individual[i]);
            p.individual[i] = lost.back();
            lost.pop_back();
        }
    }

    p.complications_are_performed = calc_complications(p.individual);
    p.answer = calc_answer(p.individual);

    return p;
}

void genetic_algorithm::krossingover(std::vector<_population> &population) {
    std::vector<_population> new_population;
    for (auto p1 : population) {
        for (auto p2 : population) {
            int k = rand() % this->M->count_cities(); //находим случайную границу скрещивания
            _population new_p1, new_p2;
            new_p1 = calc_kross(p1, p2, k);
            new_p2 = calc_kross(p2, p1, k);
            new_population.push_back(new_p1);
            new_population.push_back(new_p2);
        }
    }
    std::swap(population, new_population);
}

void genetic_algorithm::selection(std::vector<_population> &population) {
    //сортировка и унифицирование
    std::set<_population> uni;
    for (auto u : population) {
        uni.insert(u);
    }
    population.clear();

    for (auto u : uni) {
        population.push_back(u);
    }

    //удаление лишних
    while (population.size() > POPULATION_SIZE) {
        population.pop_back();
    }

    //добавление новых, если осталось слишком мало
    std::vector<_population> n_population;
    create_starting_population(n_population);
    while (population.size() < POPULATION_SIZE) {
        population.push_back(n_population.back());
        n_population.pop_back();
    }

    //запись в отчёт
    if (population[0].complications_are_performed) {
        report.push_back(abs(population[0].answer));
    }
    else {
        if (!report.empty()) report.push_back(report.back());
    }
    //std::cout << report.back() << std::endl;
}

void genetic_algorithm::mutations(std::vector<_population> &population) {

    for (auto& p : population) {
        //меняем местами рандомные два города
        int i = rand() % this->M->count_cities();
        int j = rand() % this->M->count_cities();
        std::swap(p.individual[i], p.individual[j]);
        p.complications_are_performed = calc_complications(p.individual);
        p.answer = calc_answer(p.individual);

    }
}
