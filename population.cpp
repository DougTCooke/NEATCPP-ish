#include <algorithm>
#include <cmath>
#include <iostream>
#include "population.h"
#include "network.h"
#include "util.h"
#include "config.h"

namespace NeuralNetwork
{
    Population::Population(Population* oldpop)
    {
        bestNetwork = nullptr;
        if (oldpop)
        {
            speciess = oldpop->speciess;
        }
        else
        {
            Species* s = new Species();
            for (size_t i = 0; i < Config::maxPopulation(); i++)
            {
                s->addNetwork(new Network(Config::inputNodes(), Config::outputNodes(), Activation::neatDocumentedsigmoid, Activation::step));
            }
            speciess.push_back(s);
        }
    }

    Population::~Population()
    {
    }

    void Population::clean()
    {
        for (Species* s : speciess)
        {
            delete s;
        }
        speciess.resize(0);
    }

    void Population::evaluate(Trainer* trainer)
    {
        populationFitness = 0;
        highestFitness = 0;
        for (Species* species : speciess)
        {
            populationFitness += species->evaluate(trainer);
            if (species->front()->getFitness() > highestFitness)
            {
                highestFitness = species->front()->getFitness();
                bestNetwork = species->front();
            }
        }
    }

    void Population::mutate()
    {
        std::vector<Network*> outcast;
        for (Species* species : speciess)
        {
            size_t newSize = populationFitness == 0 ? species->size() : floor(species->getFitness() / populationFitness * Config::maxPopulation());
            std::vector<Network*> temp = species->mutate(newSize);
            outcast.insert(outcast.end(), temp.begin(), temp.end());
        }
        for(Network* n : outcast)
        {
            addNetwork(n);
        }
        
        std::vector<Species*>::iterator s = speciess.begin();
        while (s != speciess.end())
        {
            if (!(*s)->isValid())
            {
                delete (*s);
                s = speciess.erase(s);
            }
            else
            {
                s++;
            }
        }
    }

    size_t Population::numNetworks()
    {
        size_t size;
        for (auto s : speciess)
        {
            size += s->size();
        }
        return size;
    }

    void Population::addNetwork(Network* net)
    {
        for (Species* species : speciess)
        {
            if (Network::similarity(net, species->front()) < Config::speciesCuttof())
            {
                species->addNetwork(net);
                return;
            }
        }
        Species* s = new Species(net);
        speciess.push_back(s);
    }
}