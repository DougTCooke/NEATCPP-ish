#include <iostream>
#include <bits/stdc++.h>
#include "species.h"
#include "network.h"
#include "config.h"
#include "util.h"

namespace NeuralNetwork
{
    Species::Species()
    {
        networks = {};
        fitness = 0;
        generations = 0;
        highestFitness = 0;
        highestFitnessGeneration = 0;
    }

    Species::Species(Network* network) : Species()
    {
        networks.push_back(network);
    }

    Species::~Species()
    {
        for (Network* n : networks)
        {
            delete n;
        }
    }

    float Species::evaluate(Trainer* trainer)
    {
        fitness = 0;
        float f;
        for (Network* net : networks)
        {
            f = trainer->evaluate(net);
            net->setFitness(f);
            fitness += f;
            if (f > highestFitness)
            {
                highestFitness = f;
                highestFitnessGeneration = generations;
            }
        }
        std::sort(networks.begin(), networks.end(), sortNetworks);
        fitness /= networks.size();
        return fitness;
    }

    std::vector<Network*> Species::mutate(size_t newSize)
    {
        generations++;

        size_t prevSize = networks.size();
        size_t removeTo = floor(0.75 * newSize);
        removeTo = removeTo < 1 ? 1 : removeTo;

        if (removeTo < prevSize)
        {
            for (size_t i = removeTo; i < networks.size(); i++)
            {
                delete networks[i];
                networks[i] = nullptr;
            }
        }
        
        networks.resize(newSize, nullptr);
        int lastNetwork = removeTo < prevSize ? removeTo : prevSize;
        for (size_t i = 1; i < networks.size(); i++)
        {
            if (networks[i])
            {
                networks[i]->mutate();
            }
            else
            {
                if (prevSize == 1)
                {
                    networks[i] = new Network(*networks[0]);
                    networks[i]->mutate();
                }
                else
                {
                    networks[i] = Network::cross(networks[0], networks[Util::uniformUnsignedInt(lastNetwork - 1)]);
                }
            }
        }

        std::vector<Network*> returnNetworks;
        std::vector<Network*> goodNetworks;

        for (Network* n : networks)
        {
            if (Network::similarity(networks[0], n) > Config::speciesCuttof())
            {
                returnNetworks.push_back(n);
            }
            else
            {
                goodNetworks.push_back(n);
            }
        }
        networks = goodNetworks;
        return returnNetworks;
    }

    bool Species::isValid()
    {
        return ( networks.size() > 2 || generations == 0 ) && (generations - highestFitnessGeneration) < 50;
    }

    size_t Species::size()
    {
        return networks.size();
    }

    float Species::getFitness()
    {
        return fitness;
    }

    void Species::addNetwork(Network* network)
    {
        networks.push_back(network);
    }

    void Species::printToConsoleAllNetworks()
    {
        for (Network* n : networks)
        {
            n->printToConsole();
            std::cout << '\n';
        }
    }

    std::vector<Network*>::const_iterator Species::begin()
    {
        return networks.begin();
    }

    std::vector<Network*>::const_iterator Species::end()
    {
        return networks.end();
    }

    Network* Species::front()
    {
        return networks.front();
    }

    Network* Species::back()
    {
        return networks.back();
    }

    inline bool Species::sortNetworks(Network* n1, Network* n2)
    {
        return (n1->getFitness() > n2->getFitness());
    }
};