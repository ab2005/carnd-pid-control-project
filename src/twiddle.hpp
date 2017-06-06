#pragma once
#include <valarray>

class Twiddle {
public:
    using array = std::valarray<double>;
    array params;
    array perturbation;
    
    Twiddle() {}
    ~Twiddle() {}
    
    void init(const array& params, const array& perturbation, const int cycle);
    bool update(double cte);
    double getTotalPerturbation();
    void reset();
    
private:
    void twiddleParams();
    int count_cycle;
    int count;
    double current_error;
    double best_error;
    int current_param;
    int _state;
};
