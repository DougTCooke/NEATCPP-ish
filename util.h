#ifndef H_NEURALNETWORKUTIL
#define H_NEURALNETWORKUTIL
#include <random>

namespace NeuralNetwork
{
    class Util
    {
    public:
        //normal distribution
        static double normRandom();
        
        //normal distribution capped between -1 and 1
        static double normalRandomCapped();
        
        //uniform distribution between -1 and 1
        static double uniformRandom();
        
        //uniform disribution between 0 - 1 inclusive
        static double uniform01();

        //inclusive uniform
        static unsigned int uniformUnsignedInt(unsigned int max);

    private:
        static std::random_device rd;
        static std::mt19937 generator;
        static std::normal_distribution<double> normalDis;
        static std::uniform_real_distribution<double> uniformDis;
        static std::uniform_real_distribution<double> uniformDis01;
    };
}

#endif