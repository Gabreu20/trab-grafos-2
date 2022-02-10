#include <iostream>
#include <fstream>
#include <string.h>
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
#include <sstream>
#include <ctime>
#include <chrono>
using namespace std::chrono;
using namespace std;

string inputTooutput;

void parOrdenado(string aresta, int *x, int *y)
{
    int i = 1;
    char aux1[8];
    char aux2[8];

    aux1[0] = aresta[i];
    while (true)
    {
        if (aresta[i + 1] == ',')
            break;
        else
        {
            aux1[i] = aresta[i + 1];
            i++;
        }
    }
    stringstream converte1(aux1);
    converte1 >> *x;

    i = i + 2;
    int j = 0;
    while (true)
    {
        if (aresta[i] == ')')
            break;
        else
        {
            aux2[j] = aresta[i];
            i++;
            j++;
        }
    }
    stringstream converte2(aux2);
    converte2 >> *y;
}

Graph *leitura(ifstream &inputFile, int directed, int weightedEdge, int weightedNode)
{

    // Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;
    int numEdges;
    int clusters;
    string palavra;

    while (inputFile >> palavra)
    {
        if (palavra == "p")
        {
            inputFile >> palavra;
            inputFile >> clusters;
            cout << "cluster:" << clusters << endl;
            inputFile >> palavra;
            inputFile >> palavra;
            inputFile >> order;
            cout << "nodes:" << order << endl;
            break;
        }
    }
    numEdges = order * (order - 1) / 3;
    // Criando objeto grafo
    Graph *graph = new Graph(order, directed, weightedEdge, weightedNode);
    graph->clusters = clusters;

    while (inputFile >> palavra)
    {
        int x;
        int y;
        if (palavra == "w")
        {

            inputFile >> palavra;
            for (int i = 0; i < order; i++)
            {
                ;
                inputFile >> x;
                inputFile >> y;
                graph->insertNode(x, y);
            }
            break;
        }
    }

    // Leitura de arquivo
    while (inputFile >> palavra)
    {
        if (palavra == "E")
        {
            inputFile >> palavra;
            int x, y;
            while (true)
            {
                inputFile >> palavra;
                if (palavra == ";")
                    break;
                parOrdenado(palavra, &x, &y);
                graph->insertEdge(x, y, 0, graph->getNumberEdges());
            }
            break;
        }
    }
    // graph->imprimir();

    graph->setFirstEdge(graph->getFirstNode()->getFirstEdge());

    return graph;
}

int menu()
{

    int selecao;

    cout << "============ MENU ============" << endl;
    cout << "[1] Algoritimo Guloso" << endl;
    cout << "[2] Algoritimo Guloso Randomizado" << endl;
    cout << "[3] Algoritimo Guloso Randomizado Reativo" << endl;
    cout << "[4] Imprimir Grafo" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

void escrever(Graph *graph, double tempo, int menor, string grafo, string funcao, string cores)
{
    //============ ESCRITA ============
    string nome = "Output_";
    string order = inputTooutput;
    string arqTxt = nome + funcao + order;
    ofstream saida(arqTxt);
    saida << "=========== Gap ===========" << endl;
    if(menor == 0)
        saida << graph->somaCores() << endl;
    else
        saida << menor << endl;
    saida << endl << "========== Tempo ==========" << endl;
    saida << tempo << endl;

    saida << endl << "========== Cores ==========";
    saida << endl << cores;

    saida << endl << "========== Grafo ==========" << endl;
    saida << grafo << endl;
}

void Attalpha(float alpha[],float chance[],float media[],int melhor[],int escolhido[])
{
    float aux[10];

    int ajudinha[10];

    for(int i=0;i<10;i++){
        media[i]=media[i]/escolhido[i];
        aux[i]=melhor[i]/media[i];
    }

    float somatorio=0;
    for(int i=0;i<10;i++){
        somatorio=somatorio+aux[i];
    }

    for(int i=0;i<10;i++){
        ajudinha[i]=0;
    }

    float ajuda=0;
    for(int i=0;i<10;i++){
        chance[i]=ajuda+(aux[i]/somatorio)*100;
        ajuda=chance[i];
    }

}

int selecionar(int selecao, Graph *graph, string output)
{
    ofstream output_file;
    output_file.open(output, ios::out | ios::trunc);
    switch (selecao)
    {
    // sai do programa
    case 0:
    {
        output_file.close();
        return 0;
    }
    case 1:
    {
        string grafo;
        high_resolution_clock::time_point inicio = high_resolution_clock::now();
        graph->drawGraph(0);
        high_resolution_clock::time_point fim = high_resolution_clock::now();
        double tempo = duration_cast<duration<double>>(fim - inicio).count();

        //============ PRINTA =============
        cout << graph->somaCores();
        cout << endl
             << tempo << endl;

        grafo = graph->Saida();

        string cores = graph->integridade();
        escrever(graph, tempo, 0,grafo ,"Guloso_", cores);
    }
    case 2:
    {

        string cores;
        string grafo;

        high_resolution_clock::time_point inicio = high_resolution_clock::now();
        srand(time(NULL));
        int menor = 999999999;
        for (int i = 0; i < 30000; i++)
        {
            if (i % 1000 == 0)
                cout << i << endl;
            graph->drawGraph(0.1);
            if (graph->somaCores() < menor)
            {
                menor = graph->somaCores();
                grafo = graph->Saida();
                cores = graph->integridade();
                escrever(graph, 0, menor, grafo ,"Randomizado_", cores);
            }
            graph->apaga();
        }
        for (int i = 0; i < 30000; i++)
        {
            if (i % 1000 == 0)
                cout << i << endl;
            graph->drawGraph(0.2);
            if (graph->somaCores() < menor)
            {
                menor = graph->somaCores();
                grafo = graph->Saida();
                cores = graph->integridade();
                escrever(graph, 0, menor, grafo ,"Randomizado_", cores);
            }
            graph->apaga();
        }
        for (int i = 0; i < 30000; i++)
        {
            if (i % 1000 == 0)
                cout << i << endl;
            graph->drawGraph(0.3);
            if (graph->somaCores() < menor)
            {
                menor = graph->somaCores();
                grafo = graph->Saida();
                cores = graph->integridade();
                escrever(graph, 0, menor, grafo ,"Randomizado_", cores);
            }
            graph->apaga();
        }
        high_resolution_clock::time_point fim = high_resolution_clock::now();
        double tempo = duration_cast<duration<double>>(fim - inicio).count();
        escrever(graph, tempo, menor, grafo ,"Randomizado_", cores);
    }
    case 3:
    {
        high_resolution_clock::time_point inicio = high_resolution_clock::now();
        
        string cores;
        string grafo;

        srand(time(NULL));
        int melhorgap=99999999;

        for(int h=0;h<30;h++)
        {   
            float alpha[10]={0.05,0.10,0.15,0.20,0.25,0.30,0.35,0.40,0.45,0.5};

            float chance[10]={10,20,30,40,50,60,70,80,90,100};
            int escolhido[10];
            for(int i=0;i<10;i++){
                escolhido[i]=0;
            }

            float media[10];

            for(int i=0;i<10;i++){
                media[i]=0;
            }

            int melhor[10];
            for(int i=0;i<10;i++)
            {
                melhor[i]=9999999; ///inf
            }

            for(int j=1;j<4000;j++)
            {
                cout << "|";
                if(j % 10 == 0){
                    cout << "MENOR";
                }

                int valorSorteado = rand()%100;
                int sorteado=0;
                for(int i=0;i<10;i++){
                    if(valorSorteado<chance[i]){
                        sorteado=i;
                        break;
                    }

                }

                escolhido[sorteado]++;

                graph->drawGraph(alpha[sorteado]);
                int soma=graph->somaCores();
                media[sorteado]=soma+media[sorteado];
                if(soma<melhorgap){
                    melhorgap=soma;
                    grafo = graph->Saida();
                    cores = graph->integridade();
                }
                if(soma<melhor[sorteado]){
                    melhor[sorteado]=soma;
                }
                if(j%100==0){

                    for(int i=0;i<10;i++)
                    {
                    //cout << escolhido[i] << " " << endl;
                    }
                    Attalpha(alpha,chance,media,melhor,escolhido);

                    float sominha=0;
                    for(int i=0;i<10;i++){
                        media[i]=0;
                    }

                    for(int i=0;i<10;i++){
                        escolhido[i]=0;
                    }
                    for(int i=0;i<10;i++)
                    {
                    //cout << chance[i] << " " ;
                    }
                }

                 graph->apaga();
             }
        }

        high_resolution_clock::time_point fim = high_resolution_clock::now();
        double tempo = duration_cast<duration<double>>(fim - inicio).count();
        escrever(graph, tempo, melhorgap, grafo, "Reativo_", cores);
        cout << endl << melhorgap << "!!!! " << endl;

        break;
    }
    case 4:
    {
        graph->imprimir();
        break;
    }
    case 5:
    {
        graph->somaCores();
        break;
    }
    default:
    {
        cout << " Error!!! invalid option!!" << endl;
    }
    }
    return 0;
}

int mainMenu(string output_file, Graph *graph)
{

    int selecao = 1;

    while (selecao != 0)
    {

        selecao = menu();

        selecionar(selecao, graph, output_file);
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    // int argc, char const *argv[]
    // int argc=6;
    // char *argv[]= {"Bom","grafo_10.txt","output.txt","1","1","0"};

    // Verifica��o se todos os par�metros do programa foram entrados
    if (argc != 6)
    {

        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
        return 1;
    }

    inputTooutput = argv[1];

    string program_name(argv[0]);
    string input_file_name(argv[1]);

    string instance;
    if (input_file_name.find("v") <= input_file_name.size())
    {
        string instance = input_file_name.substr(input_file_name.find("v"));
        cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
    }

    // Abrindo arquivo de entrada
    ifstream input_file;

    input_file.open(argv[1], ios::in);

    Graph *graph;

    if (input_file.is_open())
    {

        graph = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    }
    else
        cout << "Unable to open " << argv[1];

    mainMenu(argv[2], graph);

    // Fechando arquivo de entrada
    input_file.close();

    return 0;
}
