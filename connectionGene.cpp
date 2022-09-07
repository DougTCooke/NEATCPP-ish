#include "connectionGene.h"
#include <iostream>

using namespace NeuralNetwork;

std::vector<std::pair<unsigned int, unsigned int>> ConnectionGene::globalGenes;

ConnectionGene::ConnectionGene(unsigned int in, unsigned int out)
{   
    innov = findInnov(in, out);
    if (innov == -1)
    {
        innov = globalGenes.size();
        globalGenes.push_back(std::make_pair<>(in, out));
    }
    outId = out;
    inId = in;
    weight = 1;
    enabled = true;
}

ConnectionGene::~ConnectionGene()
{}

unsigned int ConnectionGene::getInId()
{
    return inId;
}

unsigned int ConnectionGene::getOutId()
{
    return outId;
}

double ConnectionGene::getWeight()
{
    return weight;
}

bool ConnectionGene::getEnabled()
{
    return enabled;
}

unsigned int ConnectionGene::getInnov()
{
    return innov;
}

void ConnectionGene::setWeight(double w)
{
    weight = w;
    weight = weight > 1 ? 1 : weight;
    weight = weight < -1 ? -1 : weight;
}

void ConnectionGene::offsetWeight(double w)
{
    weight += w;
    weight = weight > 1 ? 1 : weight;
    weight = weight < -1 ? -1 : weight;
}

void ConnectionGene::setEnabled(bool v)
{
    enabled = v;
}

unsigned int ConnectionGene::findInnov(unsigned int in, unsigned int out)
{
    for (unsigned int i = 0; i < globalGenes.size(); i++)
    {
        if (globalGenes[i].first == in && globalGenes[i].second == out) return i; 
    }
    return -1;
}

void ConnectionGene::findNodesInbetween(unsigned int in, unsigned int out, std::vector<unsigned int>& returnArray)
{
    std::vector<unsigned int> outOf;
    for (auto& pair : globalGenes)
    {
        if (pair.first == in)
        {
            outOf.push_back(pair.second);
        }
    }
    for (auto& pair : globalGenes)
    {
        if (pair.second == out)
        {
            for (unsigned int i = 0; i < outOf.size(); i++)
            {
                if (outOf[i] == pair.first)
                {
                    returnArray.push_back(pair.first);
                }
            }
        }
    }
}