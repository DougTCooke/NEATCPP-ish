#ifndef H_NEURALNETWORK
#define H_NEURALNETWORK
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include "activations.hpp"
#include "nodeGene.h"
#include "connectionGene.h"

namespace NeuralNetwork
{
	class Network
	{
	public:
		Network();
		Network(int inputSize, int outputSize, Activation::Func hiddenLayerActivation, Activation::Func outputActivation);
		~Network();

		std::vector<double> calculate(std::vector<double> &inputs);
		void mutate();
		void printToConsole();

		void setFitness(float f);
		float getFitness();

		static Network* cross(Network* net1, Network* net2);
		static float similarity(Network* net1, Network* net2);

		void mutateWeights();
		bool addConnection();
		void addNode();
	private:
		//properties
		Activation::Func hiddenLayerActivationFunc;
		std::vector<NodeGene> nodeGenes;
		std::vector<ConnectionGene> connectionGenes;
		float fitness;

		//helpers
		void addInitialConnections();
		std::unordered_map<unsigned int, double> calculatedNodes;
		double calculateNode(unsigned int id);
		bool pathContains(unsigned int curId, unsigned int searchId);
	};
}

#endif