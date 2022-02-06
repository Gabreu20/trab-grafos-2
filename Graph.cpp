#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>
#include <iterator>
#include <limits>
#include <vector>
#include <algorithm> // sort
#include <string.h> // memset

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node)
{

    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->first_edge = nullptr;
    this->number_edges = 0;
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    while (next_node != nullptr)
    {

        next_node->removeAllEdges();
        Node *aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

// Getters
int Graph::getOrder()
{
    return this->order;
}
int Graph::getNumberEdges()
{

    return this->number_edges;
}
//Function that verifies if the graph is directed
bool Graph::getDirected()
{

    return this->directed;
}
//Function that verifies if the graph is weighted at the edges
bool Graph::getWeightedEdge()
{

    return this->weighted_edge;
}

//Function that verifies if the graph is weighted at the nodes
bool Graph::getWeightedNode()
{

    return this->weighted_node;
}

Node *Graph::getFirstNode()
{

    return this->first_node;
}

Node *Graph::getLastNode()
{

    return this->last_node;
}

Edge *Graph::getFirstEdge()
{
    return this->first_edge;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/
void Graph::imprimir()
{
    cout << endl;
    if (this->first_node!=nullptr)
    {
        Node *next_node = this->first_node;

        while (next_node != nullptr)
        {
            cout << "(";
            cout << next_node->getInDegree();
            cout << ") ";
            cout << next_node->getId();
            cout << " (";
            cout << next_node->getOutDegree();
            cout << ")";
            Edge *next_edge = next_node->getFirstEdge();

            while(next_edge != nullptr)
            {
                cout << " -> " << next_edge->getTargetId();
                next_edge = next_edge->getNextEdge();
            }
            cout << endl;

            next_node = next_node->getNextNode();
        }
    }
}

void Graph::setFirstEdge(Edge *e)
{
    this->first_edge = e;
}

void Graph::addNode(Node *Id)//adiciona a um grafo a copia de um no, com todoas as suas arestas incluidas
{

    //a copia � declarada
    Node *novoNo = new Node(Id->getId());

    //copia recebe os atributos copiados
    novoNo->last_edge=Id->last_edge;
    novoNo->first_edge=Id->first_edge;
    novoNo->in_degree=Id->in_degree;
    novoNo->out_degree=Id->out_degree;
    novoNo->weight=Id->weight;
    novoNo->next_node=nullptr;

    //adicionada ao grafo
    if (this->first_node==nullptr)
    {
        this->first_node= novoNo;
        this->last_node= novoNo;
    }
    else
    {

        Node *aux=last_node;
        aux->setNextNode(novoNo);
        last_node=novoNo;
    }
}


void Graph::insertNode(int id)
{
    if (this->first_node==nullptr)
    {
        Node *p = new Node(id);
        this->first_node= p;
        this->last_node=p;
    }
    else
    {
        Node *aux=this->last_node;
        Node *p = new Node(id);
        aux->setNextNode(p);
        this->last_node=p;
    }
}

void Graph::insertEdge(int id, int target_id, float weight, int id_edge)
{
    if(directed == 0)
    {
        if (this->first_node!=nullptr)
        {
            int achado=0;   // variavel que verifica se o indice ja foi achado

            Node *next_node = this->first_node;
            while (next_node != nullptr && achado==0 )
            {
                if(next_node->getId()==id)
                {
                    Node *aux = getNode(target_id);
                    aux->insertEdge(target_id,id,weight,id_edge);
                    //addciona edge
                    this->number_edges++;
                    next_node->insertEdge(id,target_id,weight, id_edge);
                    next_node->incrementOutDegree();
                    Node* target = getNode(target_id);
                    target->incrementInDegree();
                    achado=1;
                }
                next_node = next_node->getNextNode();
            }
        }
    }
    else if(directed == 1)
    {
        if (this->first_node!=nullptr)
        {
            int achado=0;   // variavel que verifica se o indice ja foi achado

            Node *next_node = this->first_node;
            while (next_node != nullptr && achado==0 )
            {
                if(next_node->getId()==id)
                {
                    //addciona edge
                    this->number_edges++;
                    next_node->insertEdge(id,target_id,weight, id_edge);
                    next_node->incrementOutDegree();
                    Node* target = getNode(target_id);
                    target->incrementInDegree();
                    achado=1;
                }
                next_node = next_node->getNextNode();
            }
        }
    }
}

void Graph::removeNode(int id)
{
    if (this->first_node!=nullptr)
    {

        Node *aux1;
        Node *aux2;
        Node *next_node = this->first_node;
        while (next_node != nullptr)
        {
            if(next_node->getId()==id)
            {
                if(next_node==this->first_node)
                {
                    aux2=next_node->getNextNode();
                    first_node=aux2;
                    delete next_node;
                }
                else if (next_node==this->last_node)
                {
                    last_node=aux1;
                    delete next_node;
                }
                else
                {
                    aux2=next_node->getNextNode();
                    aux1->setNextNode(aux2);
                    delete next_node;
                }

            }
            aux1=next_node;
            next_node = next_node->getNextNode();
        }
    }
}

bool Graph::searchNode(int id)
{
    if (this->first_node!=nullptr)
    {
        int achado=0;   // variavel que verifica se o indice ja foi achado
        Node *next_node = this->first_node;
        while (next_node != nullptr)
        {
            if(next_node->getId()==id)
                return 1;
            next_node = next_node->getNextNode();
        }
    }
    return 0;
}

Node *Graph::getNode(int id)
{
    if (this->first_node!=nullptr)
    {
        int achado=0;   // variavel que verifica se o indice ja foi achado
        Node *next_node = this->first_node;
        while (next_node != nullptr)
        {
            if(next_node->getId()==id)
                return next_node;
            next_node = next_node->getNextNode();
        }
    }
    return nullptr;
}
Edge *Graph::getEdge(int Source, int target)
{
    Node *n = this->getFirstNode();
    while(n != nullptr)
    {
        Edge *e = n->getFirstEdge();
        while(e != nullptr)
        {
            if(e->getSource() == Source && e->getTargetId() == target)
                return e;
            e = e->getNextEdge();
        }
        n = n->next_node;
    }
    return nullptr;
}


string Graph::Saida()
{
    string GraphTxt;
    if(directed==0)
    {
        GraphTxt=GraphTxt+"strict graph {"+'\n';


        Node *next_node=first_node;
        while(next_node!=nullptr)
        {
            Edge *next_edge=next_node->getFirstEdge();
            while(next_edge!=nullptr)
            {
                GraphTxt=GraphTxt + to_string(next_node->getId()) + "--" + to_string(next_edge->getTargetId()) + ";" +'\n';
                next_edge=next_edge->getNextEdge();
            }
            next_node=next_node->getNextNode();
        }

        GraphTxt=GraphTxt+'}';

        return GraphTxt;
    }

    if(directed==1)
    {
        GraphTxt=GraphTxt+"Digraph saida {"+'\n';


        Node *next_node=first_node;
        while(next_node!=nullptr)
        {
            Edge *next_edge=next_node->getFirstEdge();
            while(next_edge!=nullptr)
            {
                GraphTxt=GraphTxt + to_string(next_node->getId()) + "->" + to_string(next_edge->getTargetId()) + ";" +'\n';
                next_edge=next_edge->getNextEdge();
            }
            next_node=next_node->getNextNode();
        }

        GraphTxt=GraphTxt+'}';

         return  GraphTxt;
    }
    return 0;
}
