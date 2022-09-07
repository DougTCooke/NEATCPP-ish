#include "config.h"

namespace NeuralNetwork
{
    unsigned int Config::hmaxPopulation = 150;
    unsigned int Config::hinputNodes = 2;
    unsigned int Config::houtputNodes = 1;
    unsigned int Config::hmaxItterations = 400;
    float Config::hspeciesCuttof = 3;
    float Config::hexcessiveNodeMultiplyer = 1.0;
    float Config::hdisjointedNodeMultiplyer = 1.0;
    float Config::hweightDifferenceMultiplyer = 0.3;
    float Config::hprobabilityofmutatingnode = 0.02;
    float Config::hprobabilityofmutatingconnection = 0.05;

    Config::Config()
    {
    }

    unsigned int Config::maxPopulation()
    {
        return hmaxPopulation;
    }

    unsigned int Config::inputNodes()
    {
        return hinputNodes;
    }

    unsigned int Config::outputNodes()
    {
        return houtputNodes;
    }

    unsigned int Config::maxItterations()
    {
        return hmaxItterations;
    }

    float Config::speciesCuttof()
    {
        return hspeciesCuttof;
    }

    float Config::excessiveNodeMultiplyer()
    {
        return hexcessiveNodeMultiplyer;
    }

    float Config::disjointedNodeMultiplyer()
    {
        return hdisjointedNodeMultiplyer;
    }

    float Config::weightDifferenceMultiplyer()
    {
        return hweightDifferenceMultiplyer;
    }

    float Config::probabilityofmutatingnode()
    {
        return hprobabilityofmutatingnode;
    } 

    float Config::probabilityofmutatingconnection()
    {
        return hprobabilityofmutatingconnection;
    }
}