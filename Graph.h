/**************************************************************************************************
 * Implementation of the TAD Graph
**************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include "Edge.h"
#include <fstream>
#include <stack>
#include <list>

using namespace std;

class Graph{

    //Atributes
    private:
        int order;
        int number_edges;
        bool directed;
        bool weighted_edge;
        bool weighted_node;
        Node* first_node;
        Node* last_node;
        Edge* first_edge;
        int activeColor = 0;

        int candidatos[100];
        int adjAux = 0;

    public:
        //Constructor
        Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
        //Destructor
        ~Graph();
        //Getters
        int getOrder();
        int getNumberEdges();
        bool getDirected();
        bool getWeightedEdge();
        bool getWeightedNode();
        Node* getFirstNode();
        Node* getLastNode();
        Edge* getFirstEdge();

        //Other methods
        void insertNode(int id, int peso);//insere um v�rtice
        void insertEdge(int id, int target_id, float weight, int id_edge);//insere uma aresta
        void removeNode(int id);//remove um v�rtice
        bool searchNode(int id);//procura um v�rtice
        Node* getNode(int id);//retorna um v�rtice(id)
        Edge* getEdge(int Source, int target);//retorna uma aresta(id)
        void setFirstEdge(Edge *e);//define o primeiro Edge
        bool contemVetor(int vetor[],int tamanho,int valor);    // confere se um id esta num vetor

        //gap calculus
        void drawGraph(Node *n);
        void AttCandList(Node *n);


        void imprimir();//imprime um grafo
        void imprimirAdjacencia();
        string Saida();

    private:
        void addNode(Node *Id);
        //Auxiliar methods

};

#endif // GRAPH_H_INCLUDED
