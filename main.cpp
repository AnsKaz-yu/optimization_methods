#include <iostream>
#include "map.h"
#include "dynamic_algorithm.h"
#include "genetic_algorithm.h"


int main() {
    setlocale(LC_ALL, "Russian");
    map* M = new map("map.txt");
    std::cout << "����� ������� ���������" << std::endl;
    int n = M->count_cities();
    std::cout << "������� �� �����: " << n << std::endl;
    int k0 = 0, k1 = 0;
    for (int i = 0; i < n; i++) {
        if (M->type(i)) k1++;
        else k0++;
    }

    std::cout << "�� ��� " << k0 << " 1-���� (����������� >= m1 �� t �������)" << std::endl;
    std::cout << "� " << k1 << " 2-���� (����������� <= m2 �� t �������)" << std::endl;

    std::cout << "��� ����������� ������� ������, ������� ����������:" << std::endl << "t = ";
    double t;
    int m0, m1;
    std::cin >> t;
    std::cout << "m1 = ";
    std::cin >> m0;
    std::cout << "m2 = ";
    std::cin >> m1;

    std::cout << "���������� ������� �������" << std::endl << std::endl;

    std::cout << "������ ������������� ���������..." << std::endl;
    dynamic_algorithm D(t, m0, m1, M);
    double D_answer = D.get_answer();

    if (D_answer == INT_MAX) {
        std::cout << "������� �����������";
        return 0;
    }

    std::cout << "����������� �������, ���������� ������������ ����������: " << D_answer << std::endl;

    std::cout << "������ ������������� ���������..." << std::endl;
    genetic_algorithm G(t, m0, m1, M, D_answer, 0.1);
    std::vector<double> G_answer = G.get_report();
    std::cout << "����������� �������, ���������� ������������ ����������: " << G_answer.back() << std::endl;
    std::cout << "����� � ���������� ������������� ���������: \n";
    for (auto u : G_answer) {
        std::cout << std::abs(D_answer - u) << ' ';
    }

    return 0;
}
