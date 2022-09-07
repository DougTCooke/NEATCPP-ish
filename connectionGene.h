#ifndef H_NEURALNETWORKCONNECTIONGENE
#define H_NEURALNETWORKCONNECTIONGENE
#include <vector>

namespace NeuralNetwork
{
    class ConnectionGene
    {
    public:
        ConnectionGene(unsigned int in, unsigned int out);
        ~ConnectionGene();

        unsigned int getInId();
        unsigned int getOutId();
        double getWeight();
        bool getEnabled();
        unsigned int getInnov();

        void setWeight(double value);
        void offsetWeight(double value);
        void setEnabled(bool v);

        static unsigned int findInnov(unsigned int in, unsigned int out);
        static void findNodesInbetween(unsigned int in, unsigned int out, std::vector<unsigned int>& returnArray);

    private:
        unsigned int inId;
		unsigned int outId;
		double weight;
		bool enabled;
		unsigned int innov;

        static std::vector<std::pair<unsigned int, unsigned int>> globalGenes;
    };
}


#endif