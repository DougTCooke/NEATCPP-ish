#ifndef H_SPECIES
#define H_SPECIES
#include <vector>
#include "trainer.hpp"

namespace NeuralNetwork
{
    class Network;

    class Species
    {
    public:
        Species();
        Species(Network* network);
        ~Species();

        //returns species fitness value
        float evaluate(Trainer* t);

        //returns list of unfitting networks
        std::vector<Network*> mutate(size_t newSize);

        //returns false when no longer relevant
        bool isValid();

        //return number of networks
        size_t size();

        //returns species fitness
        float getFitness();

        void addNetwork(Network* network);
        void printToConsoleAllNetworks();

        //maybe change to turning copy of network
        std::vector<Network*>::const_iterator begin();
        std::vector<Network*>::const_iterator end();
        Network* front();
        Network* back();
        
    private:
        inline static bool sortNetworks(Network* n1, Network* n2);
        
        std::vector<Network*> networks;
        
        float fitness;
        float highestFitness;
        unsigned int highestFitnessGeneration;
        unsigned int generations;
    };
}

#endif