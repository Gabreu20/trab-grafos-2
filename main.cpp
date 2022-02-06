#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Graph.h"
#include "Node.h"
#include <limits>
using namespace std;

Graph* leitura(ifstream& input_file, int directed, int weightedEdge, int weightedNode)
{

    //Vari�veis para auxiliar na cria��o dos n�s no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;

    //Pegando a ordem do grafo
    input_file >> order;

    //Criando objeto grafo
    Graph* graph = new Graph(order, directed, weightedEdge, weightedNode);

    //Leitura de arquivo

    int edge_id = 1;
    if(!graph->getWeightedEdge() && !graph->getWeightedNode())
    {
        for(int i=0; i<order; i++)
        {
            graph->insertNode(i);
        }
        while(input_file >> idNodeSource >> idNodeTarget)
        {
            graph->insertEdge(idNodeSource, idNodeTarget, 1, edge_id);
            edge_id++;
        }

    }
    else if(graph->getWeightedEdge() && !graph->getWeightedNode() )
    {

        float edgeWeight;
        for(int i=0; i<order; i++)
        {
            graph->insertNode(i);
        }

        while(input_file >> idNodeSource >> idNodeTarget >> edgeWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight, edge_id);
            edge_id++;
        }

    }
    else if(graph->getWeightedNode() && !graph->getWeightedEdge())
    {

        for(int i=0; i<order; i++)
        {
            graph->insertNode(i);
        }
        float nodeSourceWeight, nodeTargetWeight;

        while(input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, 1, edge_id);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
            edge_id++;
        }

    }
    else if(graph->getWeightedNode() && graph->getWeightedEdge())
    {
        for(int i=0; i<order; i++)
        {
            graph->insertNode(i);
        }
        float nodeSourceWeight, nodeTargetWeight, edgeWeight;

        while(input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight)
        {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight, edge_id);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);
            edge_id++;
        }

    }

    graph->setFirstEdge(graph->getFirstNode()->getFirstEdge());

    return graph;
}

int menu()
{

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

int selecionar(int selecao, Graph* graph, string output)
{
    ofstream output_file;
    output_file.open(output, ios::out | ios::trunc);
    switch (selecao)
    {
    //sai do programa
    case 0:
    {
        output_file.close();
        return 0;
    }
    case 9:
    {
        graph->imprimir();
        break;
    }
    default:
    {
        cout << " Error!!! invalid option!!" << endl;
    }

    }
    return 0;
}

int mainMenu(string output_file, Graph* graph)
{

    int selecao = 1;

    while(selecao != 0)
    {

        selecao = menu();

        selecionar(selecao, graph, output_file);
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    //int argc, char const *argv[]
    //int argc=6;
    //char *argv[]= {"Bom","grafo_10.txt","output.txt","1","1","0"};

    //Verifica��o se todos os par�metros do programa foram entrados
    if (argc != 6)
    {

        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
        return 1;

    }

    string program_name(argv[0]);
    string input_file_name(argv[1]);

    string instance;
    if(input_file_name.find("v") <= input_file_name.size())
    {
        string instance = input_file_name.substr(input_file_name.find("v"));
        cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
    }

    //Abrindo arquivo de entrada
    ifstream input_file;

    input_file.open(argv[1], ios::in);

    Graph* graph;

    if(input_file.is_open())
    {

        graph = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

    }
    else
        cout << "Unable to open " << argv[1];

    mainMenu(argv[2], graph);



    //Fechando arquivo de entrada
    input_file.close();

    return 0;
}
