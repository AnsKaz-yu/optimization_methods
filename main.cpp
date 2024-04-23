#include <iostream>
#include "map.h"
#include "dynamic_algorithm.h"
#include "genetic_algorithm.h"


int main() {
    setlocale(LC_ALL, "Russian");
    map* M = new map("map.txt");
    std::cout << "Карта успешно загружена" << std::endl;
    int n = M->count_cities();
    std::cout << "Городов на карте: " << n << std::endl;
    int k0 = 0, k1 = 0;
    for (int i = 0; i < n; i++) {
        if (M->type(i)) k1++;
        else k0++;
    }

    std::cout << "Из них " << k0 << " 1-типа (ограничение >= m1 за t времени)" << std::endl;
    std::cout << "И " << k1 << " 2-типа (ограничение <= m2 за t времени)" << std::endl;

    std::cout << "Для дальнейшего решения задачи, введите усложнения:" << std::endl << "t = ";
    double t;
    int m0, m1;
    std::cin >> t;
    std::cout << "m1 = ";
    std::cin >> m0;
    std::cout << "m2 = ";
    std::cin >> m1;

    std::cout << "Усложнения успешно введены" << std::endl << std::endl;

    std::cout << "Запуск динамического алгоритма..." << std::endl;
    dynamic_algorithm D(t, m0, m1, M);
    double D_answer = D.get_answer();

    if (D_answer == INT_MAX) {
        std::cout << "Условия невыполнимы";
        return 0;
    }

    std::cout << "Оптимальное решение, полученное динамическим алгоритмом: " << D_answer << std::endl;

    std::cout << "Запуск генетического алгоритма..." << std::endl;
    genetic_algorithm G(t, m0, m1, M, D_answer, 0.1);
    std::vector<double> G_answer = G.get_report();
    std::cout << "Оптимальное решение, полученное генетическим алгоритмом: " << G_answer.back() << std::endl;
    std::cout << "Отчёт о сходимости генетического алгоритма: \n";
    for (auto u : G_answer) {
        std::cout << std::abs(D_answer - u) << ' ';
    }

    return 0;
}
