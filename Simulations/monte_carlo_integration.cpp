#include <iostream>
#include <random>
#include <cmath>

// just a simple demonstration of monte_carlo integration using the standard normal distribution
constexpr double g_pi{3.141592};

double uniform_x_i(const double a, const double b) {
    // sample instance from uniform distribution on [a,b]

    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<double> distr(a,b);
    return distr(generator);
}

double standard_normal(const double x) {
    // test function: standard normal density
    return ( 1 / std::sqrt(2 * g_pi) ) * std::exp(-0.5 * x * x);
}

double monte_carlo_integration(const double a, const double b, const double N, double (*func)(const double)) {
    // monte carlo integration -- sum all computed test function for all generated samples x_i from uniform
    // distribution over [a,b] and multiply by interval length; take sample mean of all these

    double y_i{};
    for (int i = 0; i < N; ++i)
        y_i += (b-a) * func(uniform_x_i(a,b));
    return y_i / N;
}


int main() {
    // driver code

    constexpr double a{-1.0};
    constexpr double b{1.0};
    constexpr int N{100000};
    
    std::cout << monte_carlo_integration(a,b,N,&standard_normal);

    return 0;
}

