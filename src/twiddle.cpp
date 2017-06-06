#include "twiddle.hpp"


void Twiddle::init(const array& params, const array& perturbation, const int cycle) {
    this->params = params;
    this->perturbation.resize(params.size());
    this->perturbation = perturbation;
    
    this->count_cycle = cycle;
    this->count = 0;
    this->current_error = 0;
    this->best_error = -1;
    this->current_param = 0;
    this->_state = 0;
}

void Twiddle::reset() {
    count = 0;
    current_error = 0;
    _state = 0;
}

bool Twiddle::update(double cte) {
    current_error += cte * cte;
    count ++;
    
    if (count % count_cycle == 0) {
        // Simulation cycle completed, get error and twiddle params
        twiddleParams();
        current_error = 0;
        printf("Twiddle best_error = %.3e total_perturbation = %5.2f "
               "  {Kp = %8.4e, Ki = %8.4e, Kd = %8.4e}"
               "   P[%d] [%8.4f, %8.4f, %8.4f]\n",
               best_error,
               getTotalPerturbation(),
               params[0], params[1], params[2],
               current_param,
               perturbation[0], perturbation[1], perturbation[2]);
        return true;
    }
    
    return false;
}

double Twiddle::getTotalPerturbation() {
    return std::abs(perturbation).sum();
}

void Twiddle::twiddleParams() {
    do switch (_state) {
        case 0:
            best_error = current_error;
            params[current_param] += perturbation[current_param];
            _state = 1;
            break;
        case 1:
            if (current_error < best_error) {
                best_error = current_error;
                perturbation[current_param] *= 1.05;
                // finished with this param
                current_param = (current_param + 1) % params.size();
                _state = 0;
            } else {
                params[current_param] -= 2 * perturbation[current_param];
                _state = 2;
            }
            break;
        case 2:
            if (current_error < best_error) {
                best_error = current_error;
                perturbation[current_param] *= 1.05;
            } else {
                params[current_param] += perturbation[current_param];
                perturbation[current_param] *= 0.95;
            }
            
            // this is the fianle param
            current_param = (current_param + 1) % params.size();
            _state = 0;
            break;
    } while (_state == 0);
}
