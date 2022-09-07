#ifndef H_NEURALNETWORKNODEGENE
#define H_NEURALNETWORKNODEGENE
#include "activations.hpp"

namespace NeuralNetwork
{
    class NodeGene
	{
    public:
		NodeGene();
		NodeGene(unsigned int type, Activation::Func activationFunc);
		NodeGene(unsigned int id, unsigned int type, Activation::Func activationFunc);
        unsigned int getId();
		unsigned int getType();
		Activation::Func getActivationFunc();
		
		static void setNextId(unsigned int i);
		
    private:
		static unsigned int nextId;
		unsigned int id;
		unsigned int type; //0 input, 1 hidden 2 output 3 bias
		Activation::Func activationFunc;
	};
}

#endif