#ifndef H_CONFIG
#define H_CONFIG
#include <string>

//This was going to be read from a file, static variables where a quick fix 
namespace NeuralNetwork
{
    class Config
    {
    public:
        Config();
        static unsigned int maxPopulation();
        static unsigned int inputNodes();
        static unsigned int outputNodes();
        static unsigned int maxItterations();
        static float speciesCuttof();
        static float excessiveNodeMultiplyer();
        static float disjointedNodeMultiplyer();
        static float weightDifferenceMultiplyer();
        static float probabilityofmutatingnode();
        static float probabilityofmutatingconnection();
    private:
        static unsigned int hmaxPopulation;
        static unsigned int hinputNodes;
        static unsigned int houtputNodes;
        static unsigned int hmaxItterations;
        static float hspeciesCuttof;
        static float hexcessiveNodeMultiplyer;
        static float hdisjointedNodeMultiplyer;
        static float hweightDifferenceMultiplyer;
        static float hprobabilityofmutatingnode;
        static float hprobabilityofmutatingconnection;
    };
}

#endif