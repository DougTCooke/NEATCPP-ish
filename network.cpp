#include <bits/stdc++.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "network.h"
#include "util.h"
#include "config.h"

namespace NeuralNetwork
{
	Network::Network()
	{
		fitness = 0;
		connectionGenes = {};
		nodeGenes = {};
	}
	
	Network::Network(int inputSize, int outputSize, Activation::Func hiddenLayerActivation, Activation::Func outputActivation) : Network()
	{
		hiddenLayerActivationFunc = hiddenLayerActivation;
		for (size_t i = 0; i < inputSize; i++)
		{
			nodeGenes.push_back(NodeGene(i, 0, nullptr));
		}
		nodeGenes.push_back(NodeGene(inputSize, 3, nullptr));
		for (size_t i = 0; i < outputSize; i++)
		{
			nodeGenes.push_back(NodeGene(i + inputSize + 1, 2, outputActivation));
		}
		addInitialConnections();
	}

	Network::~Network()
	{

	}

	std::vector<double> Network::calculate(std::vector<double>& inputs)
	{
		std::vector<double> result;
		calculatedNodes.clear();
		for (unsigned int i = 0; i < inputs.size(); i++)
		{
			calculatedNodes.insert(std::make_pair(i, inputs[i]));
		}
		
		for (size_t i = 0; i < nodeGenes.size(); i++)
		{
			if (nodeGenes[i].getType() == 2)
			{
				result.push_back(calculateNode(nodeGenes[i].getId()));
			}
		}
		return result;
	}

	void Network::mutate()
	{
		if (connectionGenes.size() == 0)
		{
			addConnection();
			return;
		}
		
		double chance = Util::uniform01();
		if (chance < Config::probabilityofmutatingnode())
		{
			addNode();
		}
		else if (chance < Config::probabilityofmutatingnode() + Config::probabilityofmutatingconnection())
		{
			addConnection();
		}
		else
		{
			mutateWeights();
		}
	}

	void Network::printToConsole()
	{
		printf("Number : Type  -Node Genes %lu\n", nodeGenes.size());
		for (NodeGene& node : nodeGenes)
		{
			printf("%6u : %4u\n", node.getId(), node.getType());
		}
		printf("\nFrom : To : Weight : Enabled : innov  -Connection Genes %lu\n", connectionGenes.size());
		for (ConnectionGene& con : connectionGenes)
		{
			printf("%4u : %2u : %.4f : %7u : %5u\n", con.getInId(), con.getOutId(), con.getWeight(), con.getEnabled(), con.getInnov());
		}
	}

	void Network::setFitness(float f)
	{
		fitness = f;
	}

	float Network::getFitness()
	{
		return fitness;
	}

	//net1 is the fiter network
	Network* Network::cross(Network* net1, Network* net2)
	{
		Network* out = new Network();
		
		out->hiddenLayerActivationFunc = net1->hiddenLayerActivationFunc;
		//match connectionGenes
		unsigned int innov = 0;
		unsigned int pos1 = -1;
		unsigned int pos2 = -1;
		unsigned int highestinnov = 0;
		for (ConnectionGene& c : net1->connectionGenes)
		{
			highestinnov = c.getInnov() > highestinnov ? c.getInnov() : highestinnov;
		}
		
		while (innov <= highestinnov)
		{
			pos1 = -1;
			pos2 = -1;
			for (unsigned int i = 0; i < net1->connectionGenes.size(); i++)
			{
				if (net1->connectionGenes[i].getInnov() == innov)
				{
					pos1 = i;
					break;
				}
			}
			for (unsigned int i = 0; i < net2->connectionGenes.size(); i++)
			{
				if (net2->connectionGenes[i].getInnov() == innov)
				{
					pos2 = i;
					break;
				}
			}
			//chose random
			if (pos1 != -1 && pos2 != -1)
			{
				ConnectionGene g = Util::uniformUnsignedInt(1) == 1 ? net1->connectionGenes[pos1] : net2->connectionGenes[pos2];
				out->connectionGenes.push_back(g);
			}
			else if (pos1 != -1)
			{
				out->connectionGenes.push_back(net1->connectionGenes[pos1]);
			}
			innov++;
		}
		//the crossed network follows the same structure as the fittest
		out->nodeGenes = net1->nodeGenes;
		return out;
	}

	float Network::similarity(Network* net1, Network* net2)
	{
		//check for cheats
		if (net1->connectionGenes.size() == 0)
		{
			if (net2->connectionGenes.size() == 0)
			{
				return 0;
			}
			else
			{
				return net2->connectionGenes.size() * Config::excessiveNodeMultiplyer();
			}
		}	
		else
		{
			if (net2->connectionGenes.size() == 0)
			{
				return Config::excessiveNodeMultiplyer() * net1->connectionGenes.size();
			}
		}
		
		unsigned int excessiveGenes = 0;
		unsigned int disjointedGenes = 0;
		double weightDif = 0;
		unsigned int weightDifNum = 0;

		//excessive genes
		Network* smaller;
		Network* larger;

		unsigned int net1LargestInnov = 0;
		unsigned int net2LargestInnov = 0;
		for (ConnectionGene& g : net1->connectionGenes)
		{
			net1LargestInnov = g.getInnov() > net1LargestInnov ? g.getInnov() : net1LargestInnov;
		}
		for (ConnectionGene& g : net2->connectionGenes)
		{
			net2LargestInnov = g.getInnov() > net2LargestInnov ? g.getInnov() : net2LargestInnov;
		}
		
		unsigned int smallestnetlargestinnov;

		if (net1LargestInnov > net2LargestInnov)
		{
			//net1 is larger
			larger = net1;
			smaller = net2;
			smallestnetlargestinnov = net2LargestInnov;
		}
		else
		{
			//net2 is larger
			larger = net2;
			smaller = net1;
			smallestnetlargestinnov = net1LargestInnov;
		}

		for (ConnectionGene& gene : larger->connectionGenes)
		{
			if (gene.getInnov() > smallestnetlargestinnov)
			{
				excessiveGenes++;
			}
		}
		
		//for all smaller inovation numbers search both networks
		for (size_t i = 0; i < smallestnetlargestinnov + 1; i++)
		{
			bool n1found = false;
			bool n2found = false;
			unsigned int n1;
			unsigned int n2;
			for (n1 = 0; n1 < net1->connectionGenes.size(); n1++)
			{
				if (net1->connectionGenes[n1].getInnov() == i)
				{
					n1found = true;
					break;
				}
			}
			for (n2 = 0; n2 < net2->connectionGenes.size(); n2++)
			{
				if (net2->connectionGenes[n2].getInnov() == i)
				{
					n2found = true;
					break;
				}
			}
			if (n1found != n2found)
			{
				disjointedGenes++;
			}
			if (n1found && n2found)
			{
				weightDif += abs(net1->connectionGenes[n1].getWeight() - net2->connectionGenes[n2].getWeight());
				weightDifNum++;
			}
		}

		unsigned int maxGenes = std::max(net1->connectionGenes.size(), net2->connectionGenes.size());
		maxGenes = maxGenes < 20 ? 1 : maxGenes;

		return (Config::excessiveNodeMultiplyer() * excessiveGenes / maxGenes) + (Config::disjointedNodeMultiplyer() * disjointedGenes / maxGenes) + (Config::weightDifferenceMultiplyer() * weightDif / weightDifNum	);
	}

	void Network::addInitialConnections()
	{
		for (NodeGene& go : nodeGenes)
		{
			if (go.getType() == 2)
			{
				for (NodeGene& gi : nodeGenes)
				{
					if (gi.getType() == 0 || gi.getType() == 3)
					{
						connectionGenes.push_back(ConnectionGene(gi.getId(), go.getId()));
					}
				}
			}
		}
		
	}

	double Network::calculateNode(unsigned int id)
	{
		unsigned int nodeIndex = 0;
		for (size_t i = 0; i < nodeGenes.size(); i++)
		{
			if (nodeGenes[i].getId() == id)
			{
				nodeIndex = i;
				break;
			}
		}
		
		if (nodeGenes[nodeIndex].getType() == 3)
		{
			return 1;
		}
		auto exists = calculatedNodes.find(id);
		if (exists != calculatedNodes.end())
		{
			return exists->second;
		}
		double value = 0;
		for (size_t i = 0; i < connectionGenes.size(); i++)
		{
			if (connectionGenes[i].getOutId() == id && connectionGenes[i].getEnabled())
			{
				value += calculateNode(connectionGenes[i].getInId()) * connectionGenes[i].getWeight();
			}
		}
		
		value = (nodeGenes[nodeIndex].getActivationFunc())(value);
		calculatedNodes.insert(std::make_pair(id, value));
		return value;
	}

	void Network::mutateWeights()
	{
		if (connectionGenes.size() == 0)
		{
			return;
		}

		for (ConnectionGene& gene: connectionGenes)
		{
			double chance = Util::uniform01();
			if (chance < 0.80) //offset weight
			{
				gene.offsetWeight(Util::normRandom());	
			}
			else //completely change weight
			{
				gene.setWeight(Util::uniformRandom());
			}
		}
	}

	bool Network::addConnection()
	{
		//make list of ending nodes
		std::vector<unsigned int> endingNodes;
		for (size_t i = 0; i < nodeGenes.size(); i++)
		{
			if (nodeGenes[i].getType() != 0 && nodeGenes[i].getType() != 3)
			{
				endingNodes.push_back(nodeGenes[i].getId());
			}
		}
		
		//chose random possible ending
		while (endingNodes.size() > 0)
		{
			unsigned int endingId = endingNodes[Util::uniformUnsignedInt(endingNodes.size() - 1)];
			//create list of possible nodes and slowly reduce for failures
			std::vector<unsigned int> startingNodes;
			for (size_t i = 0; i < nodeGenes.size(); i++)
			{
				if (nodeGenes[i].getType() != 2 && nodeGenes[i].getId() != endingId)
				{
					startingNodes.push_back(nodeGenes[i].getId());
				}
			}
			//chose random input
			while (startingNodes.size() > 0)
			{
				unsigned int startingId = startingNodes[Util::uniformUnsignedInt(startingNodes.size() - 1)];
				bool good = true;

				//check if already exists
				for (ConnectionGene& conn : connectionGenes)
				{
					if (conn.getInId() == startingId && conn.getOutId() == endingId && conn.getEnabled() == true)
					{
						good = false;
					}
				}
				//check if node loops back 
				if (pathContains(endingId, startingId))
				{
					good = false;
				}
				
				//all is good
				if (good)
				{
					//check if needs to be enabled
					for (ConnectionGene& conn : connectionGenes)
					{
						if (conn.getInId() == startingId && conn.getOutId() == endingId)
						{
							conn.setEnabled(true);
							return true;
						}
					}
					//else add new
					connectionGenes.push_back(ConnectionGene(startingId, endingId));
					return true;
				}
				
				//bad connection
				startingNodes.erase(std::find(startingNodes.begin(), startingNodes.end(), startingId));
			}
			endingNodes.erase(std::find(endingNodes.begin(), endingNodes.end(), endingId));
		}
		return false;
	}

	bool Network::pathContains(unsigned int curId, unsigned int searchId)
	{
		for (ConnectionGene& conn : connectionGenes)
		{
			if (conn.getInId() == curId)
			{
				//is on path
				if (conn.getOutId() == searchId)
				{
					return true;
				}
				//ignore if its an output else search all its paths
				if (pathContains(conn.getOutId(), searchId))
				{
					return true;
				}
			}
			
		}
		return false;
	}

	void Network::addNode()
	{
		if (connectionGenes.size() == 0)
		{
			return;
		}
		
		NodeGene nodeToAdd;
		//get random enabled connection to add node between
		std::vector<unsigned int> connectionIds = {};
		unsigned int connId;
		for (unsigned int i = 0; i < connectionGenes.size(); i++)
		{
			if (connectionGenes[i].getEnabled() == true)
			{
				connectionIds.push_back(i);
			}
		}
		if (connectionIds.size() == 0)
		{
			return;
		}
		
		connId = connectionIds[Util::uniformUnsignedInt(connectionIds.size() - 1)];
		unsigned int startingNode = connectionGenes[connId].getInId();
		unsigned int endingNode = connectionGenes[connId].getOutId();
		//check global connections list for connection between starting and ending with middle node.
		std::vector<unsigned int> nodesBetween;
		ConnectionGene::findNodesInbetween(startingNode, endingNode, nodesBetween);
		
		for (size_t b = 0; b < nodesBetween.size(); b++)
		{
			bool found = false;
			for (size_t ng = 0; ng < nodeGenes.size(); ng++)
			{
				if (nodeGenes[ng].getId() == nodesBetween[b])
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				//add node with index of b to current network
				nodeToAdd = NodeGene(nodesBetween[b], 1, hiddenLayerActivationFunc);
			}
		}
		//if no match found then create node with new id
		if (nodeToAdd.getId() == -1)
		{
			nodeToAdd = NodeGene(1, hiddenLayerActivationFunc);
		}
		//disable old connection
		connectionGenes[connId].setEnabled(false);
		//add new connections
		ConnectionGene firstg = ConnectionGene(startingNode, nodeToAdd.getId());
		ConnectionGene secondg = ConnectionGene(nodeToAdd.getId(), endingNode);
		secondg.setWeight(connectionGenes[connId].getWeight());

		//push back items
		nodeGenes.push_back(nodeToAdd);
		connectionGenes.push_back(firstg);
		connectionGenes.push_back(secondg);
	}
}