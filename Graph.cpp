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
#include <string.h>  // memset

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
// Function that verifies if the graph is directed
bool Graph::getDirected()
{

    return this->directed;
}
// Function that verifies if the graph is weighted at the edges
bool Graph::getWeightedEdge()
{

    return this->weighted_edge;
}
// Function that verifies if the graph is weighted at the nodes
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
    if (this->first_node != nullptr)
    {
        Node *next_node = this->first_node;

        while (next_node != nullptr)
        {
            cout << "COR: " << next_node->color << "* ";
            cout << next_node->getId();
            cout << "-" << next_node->peso;
            Edge *next_edge = next_node->getFirstEdge();

            while (next_edge != nullptr)
            {
                cout << " -> " << next_edge->getTargetId();
                next_edge = next_edge->getNextEdge();
            }

            cout << endl;

            next_node = next_node->getNextNode();
        }
    }
}

void Graph::imprimirAdjacencia()
{
    cout << endl;
    if (this->first_node != nullptr)
    {
        Node *next_node = this->first_node;

        while (next_node != nullptr)
        {
            cout << "[";
            cout << next_node->getId();
            Edge *next_edge = next_node->getFirstEdge();

            while (next_edge != nullptr)
            {
                cout << "," << next_edge->getTargetId();
                next_edge = next_edge->getNextEdge();
            }
            cout << "]" << endl;

            next_node = next_node->getNextNode();
        }
    }
}

void Graph::setFirstEdge(Edge *e)
{
    this->first_edge = e;
}

void Graph::addNode(Node *Id) // adiciona a um grafo a copia de um no, com todoas as suas arestas incluidas
{

    // a copia � declarada
    Node *novoNo = new Node(Id->getId());

    // copia recebe os atributos copiados
    novoNo->last_edge = Id->last_edge;
    novoNo->first_edge = Id->first_edge;
    novoNo->in_degree = Id->in_degree;
    novoNo->out_degree = Id->out_degree;
    novoNo->weight = Id->weight;
    novoNo->next_node = nullptr;

    // adicionada ao grafo
    if (this->first_node == nullptr)
    {
        this->first_node = novoNo;
        this->last_node = novoNo;
    }
    else
    {

        Node *aux = last_node;
        aux->setNextNode(novoNo);
        last_node = novoNo;
    }
}

void Graph::insertNode(int id, int peso)
{
    if (this->first_node == nullptr)
    {
        Node *p = new Node(id);
        this->first_node = p;
        this->last_node = p;
        p->peso = peso;
    }
    else
    {
        Node *aux = this->last_node;
        Node *p = new Node(id);
        aux->setNextNode(p);
        this->last_node = p;
        p->peso = peso;
    }
}



void Graph::insertEdge(int id, int target_id, float weight, int id_edge)
{
    if (directed == 0)
    {
        if (this->first_node != nullptr)
        {
            int achado = 0; // variavel que verifica se o indice ja foi achado

            Node *next_node = this->first_node;
            while (next_node != nullptr && achado == 0)
            {
                if (next_node->getId() == id)
                {
                    Node *aux = getNode(target_id);
                    aux->insertEdge(target_id, id, weight, id_edge);
                    // addciona edge
                    this->number_edges++;
                    next_node->insertEdge(id, target_id, weight, id_edge);
                    next_node->incrementOutDegree();
                    Node *target = getNode(target_id);
                    target->incrementInDegree();
                    achado = 1;
                }
                next_node = next_node->getNextNode();
            }
        }
    }
    else if (directed == 1)
    {
        if (this->first_node != nullptr)
        {
            int achado = 0; // variavel que verifica se o indice ja foi achado

            Node *next_node = this->first_node;
            while (next_node != nullptr && achado == 0)
            {
                if (next_node->getId() == id)
                {
                    // addciona edge
                    this->number_edges++;
                    next_node->insertEdge(id, target_id, weight, id_edge);
                    next_node->incrementOutDegree();
                    Node *target = getNode(target_id);
                    target->incrementInDegree();
                    achado = 1;
                }
                next_node = next_node->getNextNode();
            }
        }
    }
}

void Graph::removeNode(int id)
{
    if (this->first_node != nullptr)
    {

        Node *aux1;
        Node *aux2;
        Node *next_node = this->first_node;
        while (next_node != nullptr)
        {
            if (next_node->getId() == id)
            {
                if (next_node == this->first_node)
                {
                    aux2 = next_node->getNextNode();
                    first_node = aux2;
                    delete next_node;
                }
                else if (next_node == this->last_node)
                {
                    last_node = aux1;
                    delete next_node;
                }
                else
                {
                    aux2 = next_node->getNextNode();
                    aux1->setNextNode(aux2);
                    delete next_node;
                }
            }
            aux1 = next_node;
            next_node = next_node->getNextNode();
        }
    }
}

bool Graph::searchNode(int id)
{
    if (this->first_node != nullptr)
    {
        int achado = 0; // variavel que verifica se o indice ja foi achado
        Node *next_node = this->first_node;
        while (next_node != nullptr)
        {
            if (next_node->getId() == id)
                return 1;
            next_node = next_node->getNextNode();
        }
    }
    return 0;
}

Node *Graph::getNode(int id)
{
    if (this->first_node != nullptr)
    {
        int achado = 0; // variavel que verifica se o indice ja foi achado
        Node *next_node = this->first_node;
        while (next_node != nullptr)
        {
            if (next_node->getId() == id)
                return next_node;
            next_node = next_node->getNextNode();
        }
    }
    return nullptr;
}
Edge *Graph::getEdge(int Source, int target)
{
    Node *n = this->getFirstNode();
    while (n != nullptr)
    {
        Edge *e = n->getFirstEdge();
        while (e != nullptr)
        {
            if (e->getSource() == Source && e->getTargetId() == target)
                return e;
            e = e->getNextEdge();
        }
        n = n->next_node;
    }
    return nullptr;
}
void Graph::removeDoVetor(int vetor[],int id)
{
    for(int i=0;i<quantidade;i++)
    {
        if(vetor[i]==id){
            i++;
            while(i<quantidade){
                vetor[i-1]=vetor[i];
                i++;
            }
            break;
        }
    }
    quantidade--;
}
void Graph::drawGraph()
{
    Node *nextNode=this->getFirstNode();
    while(nextNode!=nullptr){
        if(nextNode->color==0)
            drawGraph(nextNode);
        nextNode=nextNode->getNextNode();
    }
}


// gap calculus
void Graph::drawGraph(Node *n)
{
    quantidade=0;
    // colore o primeiro node
    this->activeColor++;
    n->color = activeColor;

    // Inicia a lista de adjacencia
    cout << "lista inicial: ";
    AttCandList(n);
    for(int i=0;i<quantidade;i++){
        cout << candidatos[i] << " ";
    }
    cout << endl;

    if(quantidade==0){

        Edge *aux=n->getFirstEdge();
        Node *aux2=getNode(aux->getTargetId());
        n->color=aux2->color;
        return;
    }


    // inicializa o maior e o menor como o primeiro node
    int menor = n->peso;
    int maior = n->peso;

    //================ loop ================
    int choosenNode = 0;
    int indexEscolhido = 0;

    int primeiroGap=1;
    int valorPrimeiroGap=0;

    bool achou = false;
    int p=0;

    int gapTarget=1000;
    int aux;
    int aux2=500;
    while (p!=1)
    {
        aux2=500;


        for (int i = 0; i < quantidade; i++)
        {
            int pesoDoCandidato=getNode(candidatos[i])->peso;

            if(pesoDoCandidato<maior && pesoDoCandidato > menor)
            {
                choosenNode=i;
                break;
            }
            else if(pesoDoCandidato >= maior)
            {

                aux=pesoDoCandidato - menor;
                if(aux2>aux)
                {
                    choosenNode=i;
                    aux2=aux;
                }

            }
            else if (pesoDoCandidato < menor)
            {
                aux= maior - pesoDoCandidato;
                if(aux2>aux){
                    choosenNode=i;
                    aux2=aux;
                }

            }
        }

        if(primeiroGap==1){
            valorPrimeiroGap=aux2;
            primeiroGap=0;
        }

        if(valorPrimeiroGap+valorPrimeiroGap < aux2 && primeiroGap==0){ //futura metrica
            cout << valorPrimeiroGap <<"<" <<aux2;
            break;
        }
        gapTarget=maior-menor;
        getNode(candidatos[choosenNode])->color=activeColor;
        AttCandList(getNode(candidatos[choosenNode]));

        cout << candidatos[choosenNode] <<" - ";

        removeDoVetor(candidatos,candidatos[choosenNode]);



        for(int i=0;i<quantidade;i++){
            cout << candidatos[i] << " ";
        }

        cout << endl;
        cin >> p;
        cout << "tamanho lista candidatos: " << quantidade << "   ";
        if(quantidade==0)
            break;
    }

    cout << "tamanho lista candidatos: " << quantidade << endl;
    if(quantidade>0){
        cout << "->>" <<getNode(candidatos[0])->getId() << endl;
        drawGraph(getNode(candidatos[0]));
    }
}



string Graph::Saida()
{
    string GraphTxt;
    if (directed == 0)
    {
        GraphTxt = GraphTxt + "strict graph {" + '\n';

        Node *next_node = first_node;
        while (next_node != nullptr)
        {
            Edge *next_edge = next_node->getFirstEdge();
            while (next_edge != nullptr)
            {
                GraphTxt = GraphTxt + to_string(next_node->getId()) + "--" + to_string(next_edge->getTargetId()) + ";" + '\n';
                next_edge = next_edge->getNextEdge();
            }
            next_node = next_node->getNextNode();
        }

        GraphTxt = GraphTxt + '}';

        return GraphTxt;
    }

    if (directed == 1)
    {
        GraphTxt = GraphTxt + "Digraph saida {" + '\n';

        Node *next_node = first_node;
        while (next_node != nullptr)
        {
            Edge *next_edge = next_node->getFirstEdge();
            while (next_edge != nullptr)
            {
                GraphTxt = GraphTxt + to_string(next_node->getId()) + "->" + to_string(next_edge->getTargetId()) + ";" + '\n';
                next_edge = next_edge->getNextEdge();
            }
            next_node = next_node->getNextNode();
        }

        GraphTxt = GraphTxt + '}';

        return GraphTxt;
    }
    return 0;
}