#include "util.h"

namespace NeuralNetwork
{
    std::random_device Util::rd;
    std::mt19937 Util::generator(rd());
    std::normal_distribution<double> Util::normalDis(0, 0.1);
    std::uniform_real_distribution<double> Util::uniformDis(-1, 1);
    std::uniform_real_distribution<double> Util::uniformDis01(0, 1);

    double Util::normRandom()
    {
        return normalDis(generator);
    }

    double Util::normalRandomCapped()
    {
        double res = normRandom();
        return res > 1 ? res < -1 ? res : -1 : 1;
    }

    double Util::uniformRandom()
    {
        return uniformDis(generator);
    }

    double Util::uniform01()
    {
        return uniformDis01(generator);
    }

    //inclusive
    unsigned int Util::uniformUnsignedInt(unsigned int max)
    {
        return std::uniform_int_distribution<>(0, max)(generator);
    }
}
