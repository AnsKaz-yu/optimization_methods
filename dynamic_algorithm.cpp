#include "dynamic_algorithm.h"
#include <vector>
#include <iostream>

dynamic_algorithm::dynamic_algorithm(double t, int m0, int m1, map* M) {
    this->t = t;
    this->m0 = m0;
    this->m1 = m1;
    this->M = M;
    this->the_answer_is_calculated = false;
    this->answer = INT_MAX;
}

double dynamic_algorithm::get_answer() {
    if (!the_answer_is_calculated)
        calculation();
    return answer;

}

struct bitstep {
    double time = INT_MAX;
    int k_m0 = 0, k_m1 = 0;
};

void dynamic_algorithm::calculation() {
    the_answer_is_calculated = true;
    int n = M->count_cities();
    std::vector<std::vector<bitstep> > dp((1 << n), std::vector<bitstep>(n, { INT_MAX, 0, 0 }));

    
    for (int i = 0; i < n; i++) {
        dp[(1<<i)][i] = { 0, (M->type(i) == 0), (M->type(i) == 1) }; //???
    }
    

    //dp[1][0] = { 0, (M->type(0) == 0), (M->type(0) == 1)};
    

    for (int mask = 2; mask < (1 << n); mask++)
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) { //если маска содержит i
                int _ = (1 << i);
                int mask_without_i = mask ^ (1 << i);

                for (int j = 0; j < n; j++) {
                    if (j != i && ((mask >> j) & 1)) {  //Если j != i и маска содержит j
                        if (dp[mask][i].time > dp[mask_without_i][j].time + M->distance(j, i)) {
                            bitstep new_el;
                            new_el.time = dp[mask_without_i][j].time + M->distance(j, i);
                            
                            if (new_el.time > t && dp[mask_without_i][j].k_m0 < m0) {
                                continue;
                            }
                      
                            new_el.k_m0 = dp[mask_without_i][j].k_m0 + (M->type(i) == 0);
                            new_el.k_m1 = dp[mask_without_i][j].k_m1 + (M->type(i) == 1);

                            if (new_el.time <= t && new_el.k_m1 > m1) {
                                continue;
                            }

                            //new_el.conditions = true;

                            
                            dp[mask][i] = new_el;

                            //std::cout << "\n\ndistance:\n";
                            //std::cout << i + 1 << ' ' << j + 1 << std::endl;
                            //std::cout << M->distance(j, i) << "\n\n";
                            //std::cout << mask << ' ' << mask_without_i << std::endl;
                        }
                    }
                }
            }
        }
    //std::cout << "\nAnswers:\n";
    for (int j = 0; j < n; j++) {
        answer = std::min(dp[(1 << n) - 1][j].time, answer);
        
    }
    //std::cout << "\n";
}