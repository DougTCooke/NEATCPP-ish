#ifndef H_NEURALNETWORKACTIVATION
#define H_NEURALNETWORKACTIVATION
#include <cmath>

namespace NeuralNetwork::Activation
{
    typedef double(*Func)(double x);

    inline double linear(double x) 
    {
        return x;
    }

    inline double step(double x)
    {
        return x > 0 ? 1 : 0;
    }

    inline double sigmoid(double x)
    {
        return 1 / (1 + exp(-x));
    }

    inline double neatDocumentedsigmoid(double x)
    {
        return 1 / (1 + exp(-4.9*x));
    }

    inline double tanh(double x)
    {
        return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
    }

    inline double reLU(double x)
    {
        return x > 0 ? x : 0;
    }

    inline double leakyReLU(double x)
    {
        return x > 0 ? x : 0.1*x;
    }

    inline double swish(double x)
    {
        return x / (1 + exp(-x));
    }
}

#endif