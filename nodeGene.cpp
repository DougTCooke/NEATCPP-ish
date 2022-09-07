#include "nodeGene.h"

using namespace NeuralNetwork;

unsigned int NodeGene::nextId = 0;

NodeGene::NodeGene()
{
	id = -1;
	type = -1;
	activationFunc = Activation::linear;
}

NodeGene::NodeGene(unsigned int t, Activation::Func f)
{
	id = nextId++;
    type = t;
	activationFunc = f;
}

NodeGene::NodeGene(unsigned int i, unsigned int t, Activation::Func f)
{
	id = i;
	type = t;
	activationFunc = f;
}

unsigned int NodeGene::getId()
{
	return id;
}

unsigned int NodeGene::getType()
{
	return type;
}

Activation::Func NodeGene::getActivationFunc()
{
	return activationFunc;
}

void NodeGene::setNextId(unsigned int i)
{
	nextId = i;
}