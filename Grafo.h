/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Grafo.h
 * Author: gabrieldias
 *
 * Created on November 10, 2016, 1:45 PM
 */
#include <stack>
#include "Vertice.h"
#include <vector>
#include <algorithm>
#include "Aresta.h"
#include "Vertice.h"
#include <fstream>
#ifndef GRAFO_H
#define GRAFO_H

typedef struct {
    int grau;
    int info;
}NoOrdenaGrau;
/*
 Estrutura utilizada para ordenar pelo Grau os vértices
 */


struct CompareDijkstra
{
  bool operator()( Aresta& lhs, Aresta& rhs) 
  {
    return lhs.getPeso() > rhs.getPeso();
  }
};/*Estrutura para ordenar os sorts de dijkstra*/

typedef struct {
    int peso;
    int info1,info2;
}ArestaAGM;
/*
 Estrutura utilizada para auxiliar o algoritmo de Kruskal, e representar seu retorno
 */
struct ResultadoDijkstra {
    int info,distMin;
    ResultadoDijkstra(int info,int distMin){this->info=info;this->distMin=distMin;};
};
/*
 Estrutura utilizada para otimizar o retorno de dijkstra
 */

class Grafo{
    private:
        int n;//numero vertices
        int maxVertices;//tamanho Máximo de vertices alocaveis
        int m;//numero arestas que existem iniciadas
        bool flagDir;//1 se é direcionado,0 caso nao
        int D;//Grau do grafo
        //Caixeiro Preto e Branco
        int Q;//restrição de cardinalidade
        int L;//restrição de distância
        int P;//número de pretos
        Vertice *grafo;//Vetor de vertices do grafo
//      bool ordenaGrau(const NoOrdenaGrau& i,const NoOrdenaGrau& j);
        void incluirArestaAux(int info, int peso,int vertice);//encapsula a função de exclusao 
        void auxBuscaProfundidade(int info, bool visitados[],std::list<int>* busca);//recursão da busca em profundidade        
        void ordenacaoTopologicaAux(int info, bool visitados[], std::stack<int> &Stack);//recursão para a ordenação topologica
        bool **auxFecho(); 
        
     public:         
        Grafo();//construtor trivial
        virtual ~Grafo();//destrutor trivial
        Grafo(int maxVertices,bool flagDir,int Q,int L, int P);
        Grafo(int maxVertices,bool flagDir);/*inicia o grafo tendo em  
        vista o número de Vértices máximo e 
        se é direcionado ou não*/
        int getNumVertices();//devolve número de vertices inicializados
        int getNumArestas();/*devolve número de Arestas inicializados       
        * em direcionados 1-2, 2-1 só conta uma*/ 
        void incluirVertice(int info,int peso);//inclui um vertice de posição info
        void incluirVertice(int info);//inclui um vertice de posição info com grafo nao ponderado
        void incluirVertice(int info, int peso, bool cor,int x,int y);//inclui vertice para Caixeiro Preto e Branco
        void incluirAresta(int info,int peso, int vertice);//inclui no vertice uma aresta para info.
        void incluirAresta(int info,int vertice);//inclui no vertice uma aresta para info em grafos nao ponderados
        void excluiAresta(int info,int info2);//exclui aresta de info para info2
        void excluiVertice(int info);//exclui vertice         
        void imprime();//imprime o Grafo
        int GrauNo(int info);//retorna o grau do no
        std::vector<NoOrdenaGrau>* sequenciaGraus();//retorna sequência de graus do maior pro menor
        bool eKRegular();//verifica se é k regular
        bool eCompleto();//verifica se é completa
        bool eAdjacente(int info1,int info2);//verifica se dois vértices são adjacentes
        bool eDirecionado();//verifica se é direcionado
        std::list<int>* buscaLargura(int info);//retorna uma lista com a sequencia da busca em largura
        std::list<int>* buscaProfundidade(int info);//retorna uma lista com a sequencia da busca em profundidade        
        bool eConexo();//Verifica se o grafo é conexo
        bool mesmaComponenteConexa(int info1,int info2);//verifica se dois vértices estão em uma mesma componente conexa
        bool eArticulacao(int info);//verifica se um vértice é de articulação
        bool ePonte(int info,int info2);//verifica se uma aresta é ponte
        std::list<int>* vizinhancaAberta(int info);//retorna a vizinhaça aberta
        std::list<int>* vizinhancaFechada(int info);//retorna a vizinhaça fechada
        std::list<int>* FechoTransDireto(int info);//retorna o Fecho transitivo direto
        std::list<int>* FechoTransIndireto(int info);//retorna o Fecho transitivo indireto
        std::list<ResultadoDijkstra>* dijkstra(int info);/*retorna o vetor das menores distancias em 
        relaçao ao vértice, ele utiliza a estrutura especial Retorno Dijkstra,
        que tem o No e sua distância*/
        void exportaGrafo(std::string saida);//Coloca Grafo em um documento txt 
        void floyd();//Gera uma matriz com a saida em um arquivo saida/Floyd.txt
        Grafo* subgrafoInduzido(std::vector<int>& verticesInd);/*retorna um 
        subgrafo induzido removendo o vector de arestas passado*/
        std::list<std::list<int>* >* componentesConexas();/*retorna uma lista
        de vetores com componentes conexas*/
        std::list<ArestaAGM>* kruskal();//retorna um lista de arestas com o tipo aresta kruskal, devolvendo o vertice a aresta e o peso
        std::list<ArestaAGM>* prim();//retorna uma lista de arestas com a subárvore de custo mínimo
        bool ekConexo();//retorna se é conexo
        std::vector<int>* ordenacaoTopologica();//retorna um vector com a ordenação topológica        
        bool eEuleriano();//retorna se o grafo é euleriano
        Grafo* produtoCartesiano(Grafo* l,Grafo* L);//Função removida( Não implementada) 
        int GeraVertice();//gera vertice valido para testes
        int getMaxVertices(){return maxVertices;};//max de vertices possivel no grafo
        Vertice* getVertices(){return grafo;};//retorn vetor de vertices do grafo
        void setVertices(Vertice* grafo){this->grafo=grafo;};//modifica vetor de vertices do grafo 
        Grafo* copiaGrafo( Grafo& l);//faz copia do grafo
        int getD() const ;//retorna grau do grafo
        void setD(int D) ;//muda grau do grafo
        bool isFlagDir() const ;//retorna se é direcionado
        void setFlagDir(bool flagDir);//muda se é direcionda
        Vertice* getGrafo() const ;//retorna vetor de vertices do grafo
        void setGrafo(Vertice* grafo) ;//troca vetor de vertices do grafo
        int getM() const ;//retorna  numero de arestas iniciadas
        void setM(int m) ;//muda numero de arestas do grafo
        int getN() const ;//retorna  numero de vertices iniciadas
        void setN(int n);//muda numero de vertices do grafo
        int getQ() const ;//retorna  restriçao de cardinalidade caixeiro preto e branco
        int getL() const ;//retorna  restriçao de distancia caixeiro preto e branco        
        int getP() const ;//retorna  numero de pretos caixeiro preto e branco        
        //std::vector<int>* Geni(int p);
        //std::vector<int>* Us(std::vector<int>* s);
        //int* gerarVizinhanca(int p, std::vector<int>* solucao,int info);
        int calculaCusto(std::list<int>* solucao);//calcula o custo total do ciclo hamiltoniano
        int calculaCusto(std::list<int>* solucao,int inicio,int fim);//calcula custo de uma parte do ciclo hamiltoniano
        //vector<int>*  insercaoPretoEBranco(int info, vector<int>* solucoes, vector<int*>* vizinhanca);
        std::list<int>* geraHp(float alfa);//construtivo
        void insereBrancos(std::list<int>* solucao,float alfa);//construtivo
        int melhorVertice();//retorna o vertice que esta na melhor aresta, usado no inicio da heuristica
        std::list<int>* guloso();//alfa igual a 0
        std::list<int>* gulosoRandomico(float alfa,int numIteracoes);//algoritmo guloso randomico
        std::list<int>* gulosoReativoRandomico(int max_iteracoes);//algoritmo guloso reativo randomico
        int calculaCustoEntrePretos(std::list<int>* solucao,int inicio);//calcula custo entre o vertice preto informado e o anterior
};


#endif /* GRAFO_H */

