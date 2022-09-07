#include <iostream>
#include <fstream>
#include "population.h"
#include "trainer.hpp"
#include "network.h"
#include "util.h"
#include "nodeGene.h"
#include "config.h"

struct pair
{
    int awnser;
    std::vector<double> inputs;
};

std::vector<pair> pairs = {
    {0, {0, 0}},
    {1, {1, 0}},
    {1, {0, 1}},
    {0, {1, 1}}
};

class XORTrainer : public NeuralNetwork::Trainer
{
public:
    float evaluate(NeuralNetwork::Network* net)
    {
        float fitness = 0;
        for (pair& p : pairs)
        {
            if ((int)net->calculate(p.inputs)[0] == p.awnser)
            {
                fitness += 1;
            }
        }
        return fitness;
    }
};

int main(int argc, char const *argv[])
{
    NeuralNetwork::Config c;
    NeuralNetwork::NodeGene::setNextId(4); //offset hidden nodes by fixed
    XORTrainer t;

    //setup population
    NeuralNetwork::Population* pop = new NeuralNetwork::Population(nullptr);
    NeuralNetwork::Population* oldPop = nullptr;
    
    //training loop
    for (size_t i = 0; i < NeuralNetwork::Config::maxItterations(); i++)
    {
        std::cout << "========== gen " << i << " ==========" << std::endl;

        //evaluate all the networks
        pop->evaluate(&t);

        //print some stats about the best and last network
        std::cout << "Highest fitness: " << pop->highestFitness << "\n";
        pop->bestNetwork->printToConsole();
        std::cout << "Last network fitness: " << pop->speciess.back()->getFitness() << "\n";
        pop->speciess.back()->back()->printToConsole();

        //print some stats about each species
        std::cout << "Species (" << pop->speciess.size() << "):\n";
        for (NeuralNetwork::Species* s : pop->speciess)
        {
            std::cout << "Size: " << s->size() << " fitness: " << s->getFitness() << '\n';
        }

        //check if a solution has been found
        if ((int)pop->highestFitness == 4)
        {
            std::cout << "Found network\n";
            pop->bestNetwork->printToConsole();
            break;
        }
        
        //mutate the population
        pop->mutate();
        
        //check if the population died
        if (pop->numNetworks() == 0)
        {
            std::cout << "Failed on generation " << (i + 1) << std::endl;
            break;
        }
        //create next population
        oldPop = pop;
        pop = new NeuralNetwork::Population(pop);
        delete oldPop;
    }

    pop->clean();
    delete pop;
    return 0;
}
