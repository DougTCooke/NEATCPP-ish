#ifndef H_TRAINER
#define H_TRAINER

//trainer template
namespace NeuralNetwork 
{
    class Network;
    
    class Trainer
    {
    public:
        Trainer() {};
        virtual ~Trainer() {};

        virtual void newGeneration(size_t i) {};
        virtual float evaluate(Network* net) = 0;
    };
}

#endif