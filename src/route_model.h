#ifndef ROUTE_MODEL_H
#define ROUTE_MODEL_H

#include <limits> //for type safe calcualation and checks
#include <cmath>
#include <unordered_map>
#include "model.h"
#include <iostream>

//extends the model class with additional functionalities specific to route finding(pathfinding algos)
class RouteModel : public Model {

  public:
    class Node : public Model::Node {
      public:
        Node * parent = nullptr; //pointer to parent node in route search tree
        float h_value = std::numeric_limits<float>::max(); //set heuristic value to maximum
        float g_value = 0.0; //cost from start node to this node
        bool visited = false;
        std::vector<Node *> neighbors; //list of pointers to neighbouring nodes

        void FindNeighbors(); //populate neighbours vector with adjacent nodes //defined in route_model.cpp
        float distance(Node other) const {	//calcualtes eucledian distance to another node
            return std::sqrt(std::pow((x - other.x), 2) + std::pow((y - other.y), 2));
        }
		
		//default constructor
        Node(){}
        Node(int idx, RouteModel * search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}

      private:
        int index; //index of node
        Node * FindNeighbor(std::vector<int> node_indices);
        RouteModel * parent_model = nullptr;  
    };

    RouteModel(const std::vector<std::byte> &xml); //constructor to take a vector of byte(XML) to initialize model 
    Node &FindClosestNode(float x, float y); 	//find nearest node and to give coordinates and return reference to it
    auto &SNodes() { return m_Nodes; }			//returns reference to m_Nodes allowing access to nodes stored in model
    std::vector<Node> path;
    
  private:
    void CreateNodeToRoadHashmap();
    std::unordered_map<int, std::vector<const Model::Road *>> node_to_road;
    std::vector<Node> m_Nodes; //represents routing graph

};

#endif
