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

void parOrdenado(string aresta,int *x,int *y){
    int i=1;
    char aux1[8];
    char aux2[8];

    aux1[0]=aresta[i];
    while(true){
        if(aresta[i+1]==',')
            break;
        else{
            aux1[i]=aresta[i+1];
            i++;
        }
    }
    stringstream converte1(aux1);
    converte1>>*x;

    i=i+2;
    int j=0;
    while(true){
        if(aresta[i]==')')
            break;
        else{
            aux2[j]=aresta[i];
            i++;
            j++;
        }
    }
    stringstream converte2(aux2);
    converte2>>*y;
}

Graph* leitura(ifstream& inputFile, int directed, int weightedEdge, int weightedNode)
{


//Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;
    int numEdges;
    int clusters;
    string palavra;

    while(inputFile >> palavra){
        if(palavra=="p"){
            inputFile>> palavra;
            inputFile>> clusters;
            cout <<"cluster:" <<clusters << endl;
            inputFile>> palavra;
            inputFile>> palavra;
            inputFile>> order;
            cout <<"nodes:"<< order << endl;
            break;
        }
    }
    numEdges=order*(order-1)/3;
    //Criando objeto grafo
    Graph* graph = new Graph(order, directed, weightedEdge, weightedNode);



    while(inputFile >> palavra){
        int x;
        int y;
        if(palavra=="w"){

            inputFile>> palavra;
            for(int i=0;i<order;i++){;
                inputFile>> x;
                inputFile>> y;
                graph->insertNode(x,y);
            }
            break;
        }
    }


    //Leitura de arquivo
    while(inputFile >> palavra){
        if(palavra=="E"){
            inputFile>> palavra;
            int x,y;
            while(true){
                inputFile>> palavra;
                if(palavra==";")
                    break;
                parOrdenado(palavra,&x,&y);
                graph->insertEdge(x,y,0,graph->getNumberEdges());
            }
            break;
          }
    }
    graph->imprimir();


    graph->setFirstEdge(graph->getFirstNode()->getFirstEdge());

    return graph;
}


int menu()
{

    int selecao;

    cout << "============ MENU ============" << endl;
    cout << "[1] Algoritimo Guloso" << endl;
    cout << "[2] Algoritimo Guloso Randomizado"<< endl;
    cout << "[3] Algoritimo Guloso Randomizado Reativo"<< endl;
    cout << "[4] Imprimir Grafo"<< endl;
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
    case 1:
        {            
            graph->drawGraph(0);

            //============ ESCRITA ============
            string nome = "output";
            string order = to_string(graph->getOrder());
            string type = ".txt";
            string arqTxt = nome + order + type;
            ofstream saida(arqTxt);
            saida << order;
            break;
        }
    case 2:
        {
            string nome = "output";
            string order = to_string(graph->getOrder());
            string type = ".txt";
            string arqTxt = nome + order + type;


            srand (time(NULL));
            int menor = 999999999;
            for(int i = 0; i < 30; i++){
                if(i % 1000 == 0)
                    cout << i << endl;
                graph->drawGraph(0.1);
                if(graph->somaCores() < menor){
                    menor = graph->somaCores();
                    graph->Saida(arqTxt);
                }
                graph->apaga();
            }     
            for(int i = 0; i < 30; i++){
                if(i % 1000 == 0)
                    cout << i << endl;
                graph->drawGraph(0.2);
                if(graph->somaCores() < menor){
                    menor = graph->somaCores();
                    graph->Saida(arqTxt);
                }
                graph->apaga();
            }     
            for(int i = 0; i < 30; i++){
                if(i % 1000 == 0)
                    cout << i << endl;
                graph->drawGraph(0.3);
                if(graph->somaCores() < menor){
                    menor = graph->somaCores();
                    graph->Saida(arqTxt);
                }
                graph->apaga();
            }           

            break;
        }
    case 3:
    {
        high_resolution_clock::time_point inicio = high_resolution_clock::now();
        float alphas[10];
        for(int i = 0; i < 10; i++){
            if(i == 0)
                alphas[i] = 0.05;
            else
                alphas[i] = alphas[i] + 0.05;
        }
        float medias[10];
        int menores[10];

        for(int i = 0; i < 120; i++){
            if(i % 100 == 0){
                //atualiza probabilidade
            }
            else{
                graph->randReativo(alphas, 0);
            }
        }

        //============= TEMPORIZADOR =============
        high_resolution_clock::time_point fim = high_resolution_clock::now();
        double tempo = duration_cast<duration<double>>(fim - inicio).count();
        cout << endl <<  tempo << endl;
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
