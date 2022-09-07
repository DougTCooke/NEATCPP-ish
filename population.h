#ifndef H_POPULATION
#define H_POPULATION
#include <vector>
#include "trainer.hpp"
#include "species.h"

namespace NeuralNetwork
{
    class Network;

    class Population
    {
    public:
        Population(Population* oldpop);
        ~Population();
        void clean();

        void evaluate(Trainer* trainer);
        static inline bool sortSpeciesHelper(Network* n1, Network* n2);
        void mutate();

        size_t numNetworks();

        std::vector<Species*> speciess;
        float highestFitness;
        Network* bestNetwork;
        void addNetwork(Network* net);
    private:
        float populationFitness;
    };
}

#endif