#include <stack>
#include "DisjointSet.h"
#include "Grafo.h"
#include "Aresta.h"
#include "Vertice.h"
#include <iostream>
#include <limits.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <cstdio>
#include <fstream>
#include<cstdlib>
#include<ctime>
#include <time.h>

using namespace std;
Grafo::Grafo() {}
Grafo::~Grafo(){
    for(int i=0;i<maxVertices;i++){
        grafo[i].getList().clear();
   //     delete grafo[i].getList();
    }
    delete [] grafo;
}

Grafo::Grafo(int maxVertices,bool flagDir){    
    /*construtor da estrutura Grafo,
     configura todos os campos da mesma*/
    
    //maxVertices=1.2;
    maxVertices++;
    grafo = new Vertice[maxVertices];
    this->n=0;
    this->m=0;
    this->maxVertices=maxVertices;
    this->flagDir=flagDir;
    for(int l=0;l<maxVertices;l++){
        grafo[l].setInfo(-1);
        grafo[l].setPeso(INT_MAX);
    }        
}

void Grafo::incluirVertice(int info, int peso) {
    /*Inclui um vértice,configurando todos os seus campos. 
     Só inclui um vértice se houver espaço para sua criação.Se houver espaço, 
     * verifica se ele já existe, e se não existir, o insere */ 
    if(n < maxVertices){
    if(grafo[info].getInfo()==-1){
        grafo[info].setInfo(info);
        grafo[info].setPeso(peso);
        this->n++;
        //std::cout << "vertice incluido" << std::endl;
    }else
        std::cout << "ja existe o vertice "<< info << std::endl;
    }else
        std::cout << "Grafo cheio" << std::endl;
}

void Grafo::incluirVertice(int info, int peso, bool cor,int x,int y) {
    /*Inclui um vértice,configurando todos os seus campos. 
     Só inclui um vértice se houver espaço para sua criação.Se houver espaço, 
     * verifica se ele já existe, e se não existir, o insere */ 
    if(n < maxVertices){
    if(grafo[info].getInfo()==-1){
        grafo[info].setInfo(info);
        grafo[info].setPeso(peso);
        grafo[info].setCor(cor);
        grafo[info].setX(x);
        grafo[info].setY(y);
        this->n++;
        //std::cout << "vertice incluido" << std::endl;
    }else
        std::cout << "ja existe o vertice "<< info << std::endl;
    }else
        std::cout << "Grafo cheio" << std::endl;
}

void Grafo::incluirVertice(int info) {
    /*Função para incluir vértice em caso de Grafo não ponderado nos vértices*/
    incluirVertice(info,1);
}

void Grafo::incluirAresta(int info, int peso,int vertice){
    /*Funão encapsuladora de  incluirArestaAux.Se o Grafo não for direcionado, inclui uma aresta para cada sentido*/
    if(!flagDir)
        incluirArestaAux(vertice,peso,info);
    incluirArestaAux(info,peso,vertice);
    this->m++;
}

void Grafo::incluirAresta(int info,int vertice){
    /*Inclui aresta em um Grafo não ponderado nas arestas*/
    incluirAresta(info, 1, vertice);
}

void Grafo::incluirArestaAux(int info, int peso,int vertice){  
    /*Função auxiliar para inclusão de aresta.Verifica se o vértice "vértice" existe,se sim faz a aresta até o vértice "info"*/
    if(grafo[vertice].getInfo()!=-1){        
        grafo[vertice].incluirAresta(peso,info);
    }else {
        std::cout << "impossivel inserir aresta, vertice nao existe "<< vertice;
    }
}

void Grafo::excluiAresta(int info,int info2){  
    /*Exclui uma aresta*/
        if(info<maxVertices && info2<maxVertices && grafo[info].getInfo()!=-1 && grafo[info2].getInfo()!=-1  ){ 
            /*verifica a condição de existência da operação*/
            if(!flagDir){
                if(grafo[info2].excluiAresta(info)){
                    //verifica se "info" é um vétice da vizinhança de "info2",se for, o exlui.Este é um método da classe Vértice
                    // É executada apenas quando o Grafo não é direcioando, pois se o Grafo não for direcionado 
                    //deve-se deletar os dois sentidos
                    std::cout << "aresta excluida no vertice "<< info2 << std::endl;                    
                }else{
                    cout << "aresta nao encontrada" << endl;                    
                }
            }
            if(grafo[info].excluiAresta(info2)){
              //a mesma função descrita na condição acima.Essa condição é executada em caso de direcionado ou não.
                std::cout << "aresta excluida no vertice "<< info << std::endl;
                this->m--;
            }else{
                    cout << "aresta nao encontrada" << endl;                    
                }
        }else{
            cout << "impossivel excluir aresta, vertice nao existe" << endl;
            exit(3);
        }
}

void Grafo::excluiVertice(int info){
    /*exclui vértice do Grafo*/
    //int l=0;
    if( n >=0){
        /*se o número de vértices é válido*/
        if(grafo[info].getInfo()!=-1){
            /*se o vértice existe*/
            for(int i=0;i<maxVertices ;i++){//&& l <=  ;i++){
                if(grafo[i].getInfo()!=-1){
                    /*exclui a aresta que se liga a ele*/
                    excluiAresta(i,info);    
                    //l++;
                }
            }
            grafo[info].setInfo(-1);
            /*configura seu info para -1, flag para vértices vazios*/
            this->n--;
            /*decrementa o número de vértices do Grafo*/
        }else{
            cout << "impossivel excluir vertice" << endl;
        }
    }else{
        cout << "Numero de Vertices negativo" << endl;
        exit(7000000);
    }
}

void Grafo::imprime(){
    /*imprime o Grafo, percorrendo todos os vértices, caso o vértice seja válido, imprime toda a sua vizinhança*/
    cout << "iniciando impressao" << endl;
    for(int i=0; i < maxVertices ;i++){
        if(grafo[i].getInfo()!=-1){
            std::cout << "vertice " << i << std::endl;
            grafo[i].imprimeAresta();
        }
    }
}

void Grafo::exportaGrafo(string saida) {
    /*cria um arquivo txt com os vértices do Grafo e suas vizinhanças*/
    ofstream l(saida.c_str());    
    l << "iniciando Grafo" << '\n';
    for(int i=0; i < maxVertices ;i++){
        if(grafo[i].getInfo()!=-1){
            l << "vertice " << i << '\n';
            grafo[i].exportaGrafoAresta(l);
        }
    }

}

int Grafo::GrauNo(int info){
    /*retorna o Grau do Vértice, se o vértice não existe ele volta -1.*/
    if(grafo[info].getInfo()==-1)
        return -1;
    return grafo[info].getGrau();
}

bool ordenaGrau(const NoOrdenaGrau& i,const NoOrdenaGrau& j){ 
    /*ordena de maneira crescente os graus dos vértices*/
    return (i.grau > j.grau); 
};

vector<NoOrdenaGrau>* Grafo::sequenciaGraus(){
    /*retorna um vector com a sequência de graus de um Grafo*/
    vector<NoOrdenaGrau>* l=new vector<NoOrdenaGrau>;
    //l->resze(n);int cont=0;
    for(int i=0;i<n;i++){
        /*para todos os vértices do Grafo*/
        if(grafo[i].getInfo()!=-1){
            /*se o vértice existe*/
            /*coloca-o em uma estrutura auxiliar e o inclui no vector*/
            NoOrdenaGrau aux;//=new NoOrdenaGrau();
            aux.grau=grafo[i].getGrau();
            aux.info=grafo[i].getInfo();
            l->push_back(aux);            
        }
    }
    /*ordena o vector*/
    std::sort(l->begin(),l->end(),ordenaGrau);  
    return l;
}

/*CONSERTAR ISSO*/
bool Grafo::eKRegular(){
    /*verifica se  cada vértice do Grafo tem mesmo número de vizinhos.*/
    int k=0;   
    while(grafo[k].getInfo()==-1)k++;    
    int grauBase=grafo[k].getGrau();
    for(int i=k;i<maxVertices;i++){
        /*percorre todos os vértices*/
        if(grafo[i].getInfo()!=-1)
            /*se o vértice for válido*/
                if(grafo[i].getGrau()!=grauBase) // compara Grau de k e i
                    return false;          
    }
    return true;
}

bool Grafo::eCompleto(){
    if(!this->flagDir){//caso o Grafo seja não direcionado
        /*segue do teorema de Euler*/
       if(this->getNumArestas()==(this->getNumVertices())*((this->getNumVertices())-1)/2){
         return true; 
       }else 
           return false;
    }else{//caso seja direcionado
        vector<NoOrdenaGrau>* graus = this->sequenciaGraus();        
        //se o menor da ordenção for igual ao maior, todos seus vértices
        //terão grau máximo, e portanto, completo
        if(graus->front().grau!=graus->back().grau)
            return false;                    
        delete graus;
    }
    return true;    
}

bool Grafo::eAdjacente(int info1, int info2){
    if(grafo[info1].getInfo()!=-1){
        //garante que é um vértice válido
        if(grafo[info1].buscaAresta(info2))
            //aresta existe na vizinhança
            return true;
        else 
            return false;
    }else{
        cout << "Vertice nao existe" << endl;
        exit(1);                
    }    
}

std::list<int>* Grafo::buscaLargura(int info){    
    list<int>* L = new list<int>;
    if(info >= maxVertices || grafo[info].getInfo()==-1){
        /*se sair do range do grafo ou se o vértice não existir*/
        cout << "nao existe esse vertice"<< endl;
        exit(2);
    }
    //Marca todos os vértices como não visitados
    bool *visitado = new bool[maxVertices];
    for(int i = 0; i < maxVertices; i++)
        visitado[i] = false;
    
    // Cria uma fila para a Busca em Largura
    list<int> queue;
    //Marca o nó atual como visitado e o retira da fila
    visitado[info] = true;
    queue.push_back(info); 
    //'i' será usado para pegar todos os adjacentes do vértice
    list<Aresta>::iterator i;
    list<Aresta> adj; 
    while(!queue.empty())
    {
        // Retira o vértice da fila e pode imprimi-lo para fins de teste
        info = queue.front();
        adj=grafo[queue.front()].getList();
        //grafo[queue.front()].imprimeAresta();
        //cout << info << " ";
        L->push_back(info);
        queue.pop_front();   
        /*Pega todos os vértices adjacentes do vértice s que saiu da fila
         Se um vértice adjacente não foi visitado ,então o 
         * marca como visitado e retira-o da fila*/
        //Vertice::auxBuscaLargura(&queue,visitado);
        for(i = adj.begin(); i != adj.end(); ++i){           
            //cout <<"info"<< i->getInfo() << endl;
            if(!visitado[i->getInfo()]){
                visitado[i->getInfo()] = true;
               queue.push_back(i->getInfo());
           }
        }
    }
    return L;
}

void Grafo::auxBuscaProfundidade(int info, bool visitados[],list<int>* busca){
    // Marca o nó atual como visitado e possivelmente o imprime para fins de teste    
    visitados[info] = true;
    //cout << info << " ";
    busca->push_back(info);
    //Recursivamente, chama a função para todos os nós adjacentes do vértice
    list<Aresta>::iterator i;
    list<Aresta> adj=grafo[info].getList();
    for (i = adj.begin(); i != adj.end(); ++i){
        if (!visitados[i->getInfo()]){
            auxBuscaProfundidade(i->getInfo(), visitados, busca);
        }
    }
}
 

list<int>* Grafo::buscaProfundidade(int info){

    if(info >= maxVertices || grafo[info].getInfo()==-1){
        cout << "nao existe esse vertice"<< endl;
        exit(2);
    }
    list<int>* busca=new list<int>;
    bool *visitados = new bool[maxVertices];
    for (int i = 0; i < maxVertices; i++)
        visitados[i] = false;
 
    // Chama a função recursiva auxiliar  para preencher a lista "busca" 
    auxBuscaProfundidade(info, visitados,busca);
    return busca;
}

bool Grafo::eConexo(){   
    int info=0;
    if(!flagDir){
        while(grafo[info].getInfo()==-1)info++;//primeiro vertice valido
        list<int> *l=buscaProfundidade(info);//todos os caminhos que ele alcança
        if(l->size()==n){//garante que pode chegar em todos
            return true;
        }        
        l->clear();
        return false;
    }else{
        for(int i=0;i < maxVertices;i++){//mesmo de cima porém para todos
            if(grafo[i].getInfo()!=-1){
                list<int> *l=buscaProfundidade(i);
                if(l->size()!=n){
                    return false;
                }
                l->clear();
                delete l;
            }
        }
        return true;
    }
    
}

bool Grafo::mesmaComponenteConexa(int info1, int info2){
    /*verifica se dois vértices estão numa mesma componente conexa*/
    if(info1 >= maxVertices|| info2 >= maxVertices || grafo[info1].getInfo()==-1 || grafo[info2].getInfo()==-1){
        /*verifica a validade dos vértices dados*/
        cout << "nao existe esse vertice"<< endl;
        exit(2);
    }
    list<int> *l=buscaProfundidade(info1);
    //constrói uma list com todos os vértices alcançaveis a partir de info1
    for(int &k:*l){
        if(k==info2){
            //se info2 pertence a list formada acima, entao ele faz parte da componente conexa
            return true;
        }
    }
    l->clear();
    delete l;
    return false;
}

bool Grafo::eArticulacao(int info){
    /*verifica se é um vértice de articulação*/
    if(info >= maxVertices || grafo[info].getInfo()==-1){
        /*verifica se o vértice é válido*/
        cout << "nao existe esse vertice"<< endl;
        exit(2);
    }
    //Grafo l=(*this);
    Grafo* l=this->copiaGrafo((*this));
    /*cria uma cópia do Grafo*/
    l->excluiVertice(info);
    /*exclui um vértice  e verifica se o Grafo continua conexo,
     * caso não continue conexo ,este era um vértice de articulação*/    
    bool saida = !(l->eConexo());
    /*desaloca o Grafo cópia*/
    delete l;
    return saida;        
}

bool Grafo::ePonte(int info,int info2){
    /*verifica se a aresta é ponte*/
    if(info >= maxVertices || grafo[info].getInfo()==-1 || info2 >= maxVertices || grafo[info2].getInfo()==-1){
        /*verifica se os vértices são válidos*/
        cout << "nao existe esse vertice"<< endl;
        exit(2);
    }
    Grafo* l=this->copiaGrafo((*this));
    /*cria uma cópia do Grafo*/
    l->excluiAresta(info,info2);
    /*exclui a aresta formada pelo conjunto dos dois vértices e verifica se o Grafo continua conexo*/
    bool saida = !(l->eConexo());
    delete l;
    return saida;        
}

std::list<int>* Grafo::vizinhancaAberta(int info) {
    /*retorna uam lista com os vizinhos do vértice info, excluindo o próprio*/
    if(grafo[info].getInfo()==-1){
        /*verifica se o vértice é válido*/
        cout << "Vertice nao existe" << endl;
        exit(2);
    }
    list<int>* l=new list<int>; 
    /*forma uma lista de arestas composta pela vizinhança de vértice "info"*/
    list<Aresta> u=grafo[info].getList();
    /*percorre a lista de vizinhanças e preenche l */
    for(Aresta &k:u)        
        l->push_back(k.getInfo());
    return l;
}

int Grafo::getNumArestas() {
    /*retorna o numero de arestas*/
    return m;
}

int Grafo::getNumVertices() {
    /*retorna o numero de vertices*/
    return n;
}

std::list<int>* Grafo::vizinhancaFechada(int info){
    /*retorna uma lista com os vizinhos do vértice info, incluindo o próprio*/
    if(grafo[info].getInfo()==-1){
        /*verifica se o vértice é válido*/
        cout << "Vertice nao existe" << endl;
        exit(2);
    }
    list<int>* l=new list<int>; 
    list<Aresta> u=grafo[info].getList();
    /*cria uma lista com a vizinhança do vértice "info" e inclui apenas sua informação na lista l*/
    for(Aresta &k:u)// =3        
        l->push_back(k.getInfo());
    /*inclui o próprio vértice "info"*/
    l->push_back(info);
    return l;
}

bool ** Grafo::auxFecho() {
    /*retorna uma matriz com a existencia de caminho entre cada par de vértices*/
    //bool temCaminho[maxVertices][maxVertices];    
    bool **temCaminho = new bool*[maxVertices];
    for(int i=0; i< maxVertices; i++){
        temCaminho[i] = new bool[maxVertices];
    }    
    /*inicializa a matriz*/
    for(int i=0;i<maxVertices;i++){
        //if(grafo[i].getInfo()!=-1){
            for(int j=0;j<maxVertices;j++){
                if(i==j)
                    temCaminho[i][i]=true;                 
                else
                    temCaminho[i][j]=false;
            }
    }
    for (int k = 0; k < maxVertices; k++){
        if(grafo[k].getInfo()!=-1){
            for (int i = 0; i < maxVertices; i++){
                //Pega todos os vértices como destino para o nó escolhido anteriormente
                for (int j = 0; j < maxVertices; j++){
                    //Se o vértice k esta no caminho mais curto de i para j, então ele atuzaliza o valor de temCaminho[i][j]                 
                    //if(j!=-1&&i!=-1&&k!=-1){
                    if(!temCaminho[i][j])
                        temCaminho[i][j] = temCaminho[i][k] && temCaminho[k][j];
                    //}
                }
            }
        }
    }
    return temCaminho;
}


std::list<int>* Grafo::FechoTransDireto(int info) {
    /*todos os vértices alcançaveis a partir do vértice "info", 
     * fazendo uma busca em profundidade e retornando uma lista com o resultado da busca*/
    list<int>* l=buscaProfundidade(info);
    l->push_back(info);
    return l;
}

std::list<int>* Grafo::FechoTransIndireto(int info){
    /*retorna a lista de vértices a partir dos quais "info" é acessível*/    
    bool ** temCaminho = auxFecho();
    list<int>* L=new list<int>;
    for(int i=0;i<maxVertices;i++){
        /*para todos os vértices do Grafo*/ 
            if(!temCaminho[info][i])
                L->push_back(i);      
    }
    return L;
}


list<ResultadoDijkstra>* Grafo::dijkstra(int info) {  
    /*retorna o menor caminho de um vértice "info" até cada um dos vértices do Grafo*/
    int u, v, i, c, w;
    /*inicia um vetor de de distâncias do tamanho do Grafo*/
    int distancia[maxVertices];
    for(int u=0;u<maxVertices;u++){
        distancia[u]=INT_MAX;
    }
    /*ordena as arestas por ordem crescente de peso e coloca em uma fila*/
    priority_queue<Aresta,vector<Aresta>,CompareDijkstra > Q;     
    Q.push(Aresta(0, info));
    /*a distancia do vértice "info" a ele mesmo é 0 */
    distancia[info] = 0;
    
     /*enquanto a fila não estiver vazia*/
    while(!Q.empty()) {
          /*retira um elemento da fila*/
        Aresta o=Q.top();
        u = o.getInfo(); 
        c =o.getPeso(); 
        Q.pop();
        /*se  o vetor distancia na posição de info indica um custo menor que o custo atual, continua*/
        if(distancia[u] < c) continue;
        list<Aresta> l=grafo[u].getList();
        //for(i = 0; i < grafo[u].size(); i++) {
        for(Aresta &k:l){
            v =k.getInfo(); 
            w = k.getPeso();   
            /*passo de arrependimento*/
            if(distancia[v] > distancia[u] + w) {
                distancia[v] = distancia[u] + w;
                Aresta p(distancia[v], v);
                Q.push(p);
            }
        }
    }
    /* forma uma fila que possui elementos do tipo "informação e peso" para retorna-la */
    list<ResultadoDijkstra>* retorno=new list<ResultadoDijkstra>;        
     for(int u=0;u<maxVertices;u++){ 
        if(grafo[u].getInfo()!=-1){
           ResultadoDijkstra k(u,distancia[u]);
           retorno->push_back(k);
}
    } 
    return retorno;
}

/*Retorna um aquivo em saida/Floyd.txt com todo a tabela impressa*/

void Grafo::floyd() {   
    /*retorna uma matriz com o menor caminho entre cada par de vértices*/
    int dist[maxVertices][maxVertices];   
    /*inicializa a matriz*/
    for(int i=0;i<maxVertices;i++){
        //if(grafo[i].getInfo()!=-1){
            for(int j=0;j<maxVertices;j++){
                if(i==j){
                    dist[i][i]=0;
                }else
                    dist[i][j]=INT_MAX;
            }        
    }
    
    for(int i=0;i<maxVertices;i++){
        list<Aresta> vizinhaca = grafo[i].getList();
        //if(grafo[i].getInfo()!=-1){
            for(Aresta &l:vizinhaca){
                dist[i][l.getInfo()]=l.getPeso();
            }
        //}                    
    }
    
    for (int k = 0; k < maxVertices; k++){
        if(grafo[k].getInfo()!=-1){
            for (int i = 0; i < maxVertices; i++){
                //Pega todos os vértices como destino para o nó escolhido anteriormente
                for (int j = 0; j < maxVertices; j++){
                    //Se o vértice k esta no caminho mais curto de i para j, então ele atuzaliza o valor de dist[i][j]                 
                    //if(j!=-1&&i!=-1&&k!=-1){
                    if ( dist[i][k] != INT_MAX && 
                         dist[k][j] != INT_MAX && 
                         dist[i][k] + dist[k][j] < dist[i][j]
                        )
                     dist[i][j] = dist[i][k] + dist[k][j];
                    //}
                }
            }
        }
    }
    /*gera um arquivo txt com a matriz resultante*/
    ofstream o("saida/Floyd.txt");
        for(int u=0;u<maxVertices;u++){
            o << '\t' << u;
        }
        o << endl;
        for(int u=0;u<maxVertices;u++){      
            o << u ;
            for(int s=0;s < maxVertices;s++){
                 o << '\t' << dist[u][s];
            }
            o<< endl;
    }
}

Grafo* Grafo::subgrafoInduzido(vector<int>& verticesInd) {    
    /*gera o subgrafo induzido */
    /*cria uma cópia do Grafo*/
    Grafo *l=copiaGrafo((*this));
    l->imprime();
    //cout <<"tam"<< verticesInd.size() << endl ;
    /*exlcui os vértices indicados no vetor verticesInd */
    for(int i=0; i < verticesInd.size(); i++){
        l->excluiVertice(verticesInd[i]);
    }
    this->imprime();
    return l;
}


list<list<int>* >* Grafo::componentesConexas() {
    /*retorna as componentes conexas do grafo 
     * através da estrutura auxiliar "componentes" (uma lista em que cada elemento 
     * é uma lista com os elementos de uma componente conexa)*/
    list<int> vertices;    
    for(int i=0;i< maxVertices;i++){
        if(grafo[i].getInfo()!=-1)
            vertices.push_back(i);        
    }//coloca todos os vertices na lista
    list<list<int>* >* componentes=new list<list<int>*>;
    /*enquanto houver vértice */
    while(!vertices.empty()){
        list<int>* componente=buscaProfundidade(vertices.front());
        componentes->push_back(componente);
        /*se um vértice já existir em uma componente, sua busca em profundidade não será refeita*/
        for(list<int>::iterator y=componente->begin();y!=componente->end();y++){
            vertices.remove(*y);
        }        
    }
    return componentes;
}

bool ordenaPeso(const ArestaAGM& i,const ArestaAGM& j){ 
    /*ordena os pesos das Arestas da Árvore Geradora Mínima*/
    return (i.peso < j.peso); 
};

list<ArestaAGM>* Grafo::kruskal()
{
    vector<ArestaAGM> L;
    int mst_wt = 0; 
    for(int i=0;i<maxVertices;i++){
        if(grafo[i].getInfo()!=-1){
            list<Aresta> viz = grafo[i].getList();
            for(Aresta &n:viz){
                ArestaAGM aux;
                aux.info1=i;
                aux.info2=n.getInfo();
                aux.peso=n.getPeso();
                L.push_back(aux);
            }            
        }
    }
    //Ordena arestas de maneira crescente com base no peso
    std::sort(L.begin(), L.end(), ordenaPeso);
 
    //Cria conjuntos disjuntos
    DisjointSet l(maxVertices);
 
    //Itera através de todas as arestas ordenadas
    list<ArestaAGM>* arv=new list<ArestaAGM>;
    vector<ArestaAGM>::iterator i;
    int cont=0;
    for (i=L.begin(); i!=L.end(); i++)
    {
        //if(cont > n-1)break;
        int u = i->info1;
        int v = i->info2;
 
        int set_u = l.find(u);
        int set_v = l.find(v);
         
        /*verifica se as arestas selecionadas estão criando ou 
         * não um ciclo (Ciclo é criado se u e v pertencem ao mesmo conjunto)*/
        if (l.find(u) != l.find(v))
        {
            
            /* a aresta atual estará na MST 
             * então coloca ele na lista arv */
            cout << u << " - " << v << endl;
            arv->push_back(*i);
            
            //atualiza o custo de MST
            mst_wt += i->peso;
 
            // Funde 2 conjuntos
            l.merge(set_u, set_v);
        }
    } 
    return arv;
}

std::list<ArestaAGM>* Grafo::prim() {            
    int i=1;
    while(grafo[i].getInfo()==-1 && i < maxVertices)i++;
    //pega primeiro vertice q existir   
    int* distancia=new int[maxVertices];    
    priority_queue<Aresta,vector<Aresta>,CompareDijkstra > Q;     
    vector<bool> naArv(maxVertices,false);
    for(int u=0;u<maxVertices;u++){
        distancia[u]=INT_MAX;
    }    
    Q.push(Aresta(0, i));
    distancia[i] = 0;       
    naArv.at(i)=true;
    int *arv=new int[maxVertices];    
    for(int j=0;j<maxVertices;j++){
        arv[j]=-1;
    }

    while (!Q.empty())
    {        
        Aresta o=Q.top();
        int u = o.getInfo();     
        Q.pop();               
        naArv.at(u) = true;  // Inclui um vértice na AGM      
        list<Aresta> adj=grafo[u].getList();        
        list<Aresta>::iterator l;
        for (Aresta &l:adj){            
            int v = (l).getInfo();
            int peso = (l).getPeso();             
            if (naArv[v] == false && distancia[v] > peso){
                // att
                distancia[v] = peso;
                Q.push(Aresta(distancia[v],v));
                arv[v] = u;
            }
        }
    }
    list<ArestaAGM>* retorno = new list<ArestaAGM>;
    for (int i = 1; i < maxVertices; ++i){
        printf("%d - %d (%d)\n", arv[i], i,distancia[i]);
        ArestaAGM k;
        k.info1=i;
        k.info2=arv[i];
        k.peso=distancia[i];
        retorno->push_back(k);
    }
    return retorno;
}


/*O problema a seguir nao tem solucao rápida porem garantimos algumas condiçoes em que é facil solucionar
 e deixamos o retorno indefinido para o problema np-dificil */
bool Grafo::ekConexo() {
     int k;
     /*se é completo, é n-1 k-conexo,portanto é k-conexo*/
    if(this->eCompleto()) 
        return true;
    else
    {   /*se não é conexo , ou é trivial, então não é k-conexo*/
        if(!this->eConexo() || (this->n == 1))
            return false;
        else
        {
            /*para casos gerais
             cria-se uma cópia do grafo*/
            Grafo* G = copiaGrafo((*this));
            /*para o menor grau do vértice*/
            vector<NoOrdenaGrau>* g = this->sequenciaGraus();
            int  l = g->back().grau;
            /*cria uma list com a vizinhança aberta e remove vértice a vértice dessa vizinhança*/
            list<int>* adj = G->vizinhancaAberta(g->back().info); 
            while(!adj->empty())
             {
               G->excluiVertice(adj->front());
               /*caso o Grafo deixe de ser conexo, ele não é k-conexo, caso não,nada se pode afirmar*/
              if(!G->eConexo())
               { 
                  delete G;
                  return false;
               }
               adj->pop_front();
            }
            
            std::cout <<"não é possível afirmar"<< std::endl;
             
        }
    }
}

void Grafo::ordenacaoTopologicaAux(int info, bool visitados[], stack<int> &Stack){
    visitados[info] = true;   
    //Faz recursão por todos os vértices adjacentes a este vétice
    list<Aresta>::iterator i;
    list<Aresta> adj=grafo[info].getList();
    for (i = adj.begin(); i != adj.end(); ++i){
        if (!visitados[i->getInfo()]){
            ordenacaoTopologicaAux(i->getInfo(), visitados, Stack);
        }
    }        
    Stack.push(info);
}
 

std::vector<int>* Grafo::ordenacaoTopologica(){
    stack<int> Stack;
    vector<int>* busca= new vector<int>;
    //Marca todos os vértices como não visitados
    bool *visitados = new bool[maxVertices];
    for (int i = 0; i < maxVertices; i++)
        visitados[i] = false; 
    //Chama a função recursiva auxiliar para armazenar a Ordenação Topológica começando de um vértice e indo um a um
    for (int i = 0; i < maxVertices; i++)
      if (visitados[i] == false)
        ordenacaoTopologicaAux(i, visitados, Stack);
    
    // Armazena o conteúdo da pilha no vector de retorno
    while (! Stack.empty() ){
        int l= Stack.top();
        busca->push_back(l);
        cout << l<< " ";
        Stack.pop();
    }
    return busca;
}

bool Grafo::eEuleriano() {
//Verifica as condições para um Grafo ser Euleriano
    if(eConexo()){
        vector<NoOrdenaGrau> *k=sequenciaGraus();        
        for(NoOrdenaGrau &u:*k){
            if(u.grau % 2 == 1 ){
                 return true;                
            }
        }
    }else{
        return false;
    }    
}

bool Grafo::eDirecionado() {
    return flagDir;
}

int Grafo::GeraVertice() {
    srand(time(0));
    int vertice=rand()%maxVertices;
    while(grafo[vertice].getInfo()==-1){
        vertice=rand()%maxVertices;
        cout << "ainda nao gerei certo" << endl;
    }
    return vertice;
}


Grafo* Grafo::copiaGrafo( Grafo& l){
    Grafo* L= new Grafo(l.getMaxVertices(),l.eDirecionado());
    L->setD(l.getD());
    L->setM(l.getM());
    L->setN(l.getN());
    //inicia um grafo com tamanho e direcionamento identicos ao antigo
    for(int i=0;i<l.getMaxVertices();i++){
        //itera todo vetor de vertices copiando-o 
        L->getVertices()[i].setInfo(l.getVertices()[i].getInfo());
        L->getVertices()[i].setPeso(l.getVertices()[i].getPeso());
        //copia info e peso para vetor de vertices um a um
        if(L->getVertices()[i].getInfo()!=-1){
            list<Aresta> aux= l.getVertices()[i].getList();
            for(Aresta u:aux){
                L->getVertices()[i].getList().push_back(u);
            }
        }
    }
    //cout << "imprimindo a copia" <<endl;
    //l.imprime();
    //L->imprime();
    return L;
}

int Grafo::getD() const {
    return D;
}

void Grafo::setD(int D) {
    this->D = D;
}

bool Grafo::isFlagDir() const {
    return flagDir;
}

void Grafo::setFlagDir(bool flagDir) {
    this->flagDir = flagDir;
}

Vertice* Grafo::getGrafo() const {
    return grafo;
}

void Grafo::setGrafo(Vertice* grafo) {
    this->grafo = grafo;
}

int Grafo::getM() const {
    return m;
}

void Grafo::setM(int m) {
    this->m = m;
}

int Grafo::getN() const {
    return n;
}

void Grafo::setN(int n) {
    this->n = n;
}

Grafo::Grafo(int maxVertices, bool flagDir, int Q, int L, int P) {
    /*construtor da estrutura Grafo,
     configura todos os campos da mesma*/        
    maxVertices++;
    grafo = new Vertice[maxVertices];
    this->n=0;
    this->m=0;
    this->maxVertices=maxVertices;
    this->flagDir=flagDir;
    for(int l=0;l<maxVertices;l++){
        grafo[l].setInfo(-1);
        grafo[l].setVisitado(false);
        grafo[l].setPeso(INT_MAX);
    } 
    this->L=L;
    this->Q=Q;
    this->P=P;    
}

int Grafo::getL() const {
    return L;
}

int Grafo::getQ() const {
    return Q;
}

int Grafo::getP() const {
    return P;                       
}
/*********************** Caixeiro Preto e Branco ***********************/
//implementaçao baseada em um dos melhores construtivos para encontrar ciclo hamiltoniano de custo minímo
//preferimos seguir a nossa, de forma a melhor aproveitar o trabalho, porém deixamos a possível implementação
//vector<int>* Grafo::Geni(int p) {
//    vector<int>* solucao=new vector<solucao>(P,0);
//    vector<int*>* vizinhancas=new vector<int*>(P);
//    int i=1;int numPretosInicio=P;
//    while(i<=3){
//        int v;        
//        do{
//            v=(rand()%P)+1;
//        }while(grafo[v].getVisitado()==-1);
//        //gera um número válido aleatório
//        solucao->push_back(v);
//        //this->excluiVertice(v);
//        this->grafo[v].setVisitado(true);
//        P--;
//        i++;
//    }
//    i=1;
//    while(i<=numPretosInicio){//assumindo que são sempre os p primeiros no inicio
//        //if(grafo[i].getInfo()==-1){i++;continue;}
//        if(grafo[i].getVisitado()){i++;continue;}
//        vizinhancas->at(i)=gerarVizinhanca( p, solucao, grafo[i].getInfo());
//    }
//    while(P>=0){
//        int v;
//        do{
//            v=(rand()%P)+1;
//        }while(grafo[v].getInfo()==-1);
//        //inserir na solucao
//        //excluiVertice(v);
//        this->grafo[v].setVisitado(true);
//        i=1;
//        while(i<=P){
//            if(grafo[i].getVisitado()){i++;continue;}
//            vizinhancas->at(i)=gerarVizinhanca( p, solucao, grafo[i].getInfo());
//            i++;
//        }
//    }
//    return solucao;
//           
//}

bool compareArestaPeso ( Aresta& first,  Aresta& second){
    if(first.getPeso()<second.getPeso())return true;
    return false;     
}

//int* Grafo::gerarVizinhanca(int p, vector<int>* solucao, int info) {
//    int i=0;int* vizinhaca=new int[p];
//    list<Aresta> adj=grafo[info].getList();
//    adj.sort(compareArestaPeso);
//    for(Aresta &k:adj){
//        if(grafo[k.getInfo()].getVisitado())continue;
//        for(int &l:*solucao)
//            if(k.getInfo()==l){
//                vizinhaca[i]=l;
//                i++;
//            }
//        if(i>=p)return vizinhaca;
//    }
//    return vizinhaca;
//}
//
//int Grafo::calculaCusto(vector<int>* solucao){
//    int soma=0;
//    vector<int>::iterator u;
//    for(u=solucao->begin();u!=solucao->end()-1;u++){
//        soma+=grafo[*u].getPesoAresta(*(u++));
//    }
//    soma+=grafo[solucao->end()].getPesoAresta(solucao->begin());
//    return  soma;
//}
//
//vector<int>* Grafo::Us(vector<int>* solucao){
//    vector<int>* solucaoUs = new vector<int>();
//    solucaoUs->assign(solucao->begin(),solucao->end());
//    vector<int>* solucaoUsAux = new vector<int>();
//    int i=1;
//    while(i<=solucao->size()){
//        //remove da solucao'
//        //inserir na solucao'
//        if(calculaCusto(solucaoUsAux)<calculaCusto(solucaoUs)){
//            solucao->clear();
//            delete solucao;
//            solucao=solucaoUsAux;
//            solucaoUs->clear();
//            delete solucaoUs;
//            solucaoUs=solucaoUsAux;
//            i=1;            
//        }else{
//            i++;
//        }
//    }
//    return solucaoUs;    
//}

//vector<int>*  Grafo::insercaoPretoEBranco(int info, vector<int>* solucoes, vector<int*>* vizinhanca){
//    vector<int>* solucao2=new vector<int>;
//    solucao2->assign(solucoes->begin(),solucoes->end());
//    int Vj[2],Vk[2],Vi[2],_Vj[2],_Vi[2],_Vk[2];
//    Vi[0]=vizinhanca->at(info)[0];
//    Vj[0]=vizinhanca->at(info)[1];    
//    for(int i=0;i<solucoes->size();i++){
//        if(Vi[0]==solucoes[i]){
//            Vi[1]=i;
//            _Vi[0]=solucoes[i+1];
//            _Vi[1]=i+1;
//        }
//        if(Vj[0]==solucoes[i]){
//            Vj[1]=i;
//            _Vj[0]=solucoes[i+1];
//            _Vj[1]=i+1;
//        }
//    }
//    Vk[0]=vizinhanca->at(Vi+1)[0];
//    for(int i=0;i<solucoes->size();i++){
//        if(Vk[0]==solucoes[i]){
//            Vk[1]=i;
//        }
//    }
//}
int Grafo::melhorVertice(){
    ArestaAGM melhorAresta;
    melhorAresta.info1=1;
    melhorAresta.info2=2;    
    for(int i=1;i<=P;i++){
        list<Aresta> l=grafo[i].getList();
        for(Aresta &j:l){
            if(grafo[i].getPesoAresta(j.getInfo())>grafo[melhorAresta.info1].getPesoAresta(melhorAresta.info2)){
                melhorAresta.info1=i;
                melhorAresta.info2=j.getInfo();
            }
        }
    }
    return melhorAresta.info1;
}


list<int>* Grafo::geraHp(float alfa) {
/*Gera um ciclo hamiltoniano de custo mínimo para pretos*/
    for(int s=0;s<maxVertices;s++){
        grafo[s].setVisitado(false);
    }
    list<int>* solucao=new list<int>;int i=0;
    vector<Aresta> adjDePretos;
    int restricao=(alfa*P);//num entre max e min
    int v=melhorVertice();//parte do vertice com melhor aresta do grafo
    solucao->push_back(v);
    grafo[v].setVisitado(true);
    int j;
    for(int i=0;i<(P-1);i++) { //percorre todos os pretos, supondo que os pretos estejam no inicio do grafo
        adjDePretos.clear();
        list<Aresta> adj=grafo[v].getList();//pega a adjacencia
        int r=0;
        for(Aresta &k:adj){//cria vetor com candidatos de onde sera selecionado o próximo elemento da solucao
            if(grafo[k.getInfo()].getCor() && !grafo[k.getInfo()].getVisitado()  ){                
                adjDePretos.push_back(k);
                r++;
            }if(r>P)break;            
        }
        sort(adjDePretos.begin(),adjDePretos.end(),compareArestaPeso);//ordena por custo
        j=(((int)rand())%(adjDePretos.size())%(restricao+1));//0<=j-size()<=P//escolhe uma
        v=adjDePretos.at(j).getInfo();
        solucao->push_back(v);//coloca na solucao
        grafo[v].setVisitado(true);        
    }
    return solucao;           
}

void Grafo::insereBrancos(std::list<int>* solucao,float alfa) { 
/*Acrescenta vértices brancos ao ciclo gerado em GeraHp*/
    int qtdBrancoEntrePreto[P]={0};//registra quantos brancos tem antes do Preto    
    vector<Aresta> adjDeBrancos;
    int restricao=(alfa*solucao->size());//num entre max e min
    for(int i=P+1;i<=n;i++){//percorre todos os brancos que vao ser colocados na solucao
        adjDeBrancos.clear();
        list<Aresta> l=grafo[i].getList();  
        //int r=0;
        for(Aresta &L:l){//forma a lista do que sera selecionado
            if(grafo[L.getInfo()].getCor() && qtdBrancoEntrePreto[L.getInfo()]<=Q && calculaCustoEntrePretos(solucao,L.getInfo()) <= this->L ){
                adjDeBrancos.push_back(L);//insere depois de garantir a restricao de cardinalidade e distancia
          //      r++;
            }
        }
        sort(adjDeBrancos.begin(),adjDeBrancos.end(),compareArestaPeso);//ordena a lista por distancia ate o branco em questao     
        int j=(((int)rand())%(adjDeBrancos.size())%(restricao+1));//0<=j-size()<=P//escolhe um preto da lista
        int candidato=adjDeBrancos.at(j).getInfo();
        //cout << candidato << endl;
        for(list<int>::iterator L=solucao->begin();L!=solucao->end();L++){//insere ele na solucao
            if(*L==candidato){
                //if(qtdBrancoEm''1Preto[*L]<=Q){
                    //L++;
                    L = solucao->insert(L,i);//insere o branco na frente do preto mais perto
                    qtdBrancoEntrePreto[candidato]++;
                    break;
                //}
            }
        }
    }
}

int Grafo::calculaCusto(list<int>* solucao){//percorre a solucao calculando o custo das arestas
    int soma=0;
    list<int>::iterator u;
    for(u=solucao->begin();u!=--(solucao->end());){
        soma+=grafo[*u].getPesoAresta(*(u++));
    }
    soma+=grafo[solucao->back()].getPesoAresta(solucao->front());
    return  soma;
}

std::list<int>* Grafo::guloso(){//inicia o randomico com parametro de guloso
    list<int>* solucao=geraHp(0);
    insereBrancos(solucao, 0);
    return solucao;
}

std::list<int>* Grafo::gulosoRandomico(float alfa,int numIteracoes) {//executa com parametro determinado
    //cout <<"começando randomico"<< endl;
    list<int>* melhorSolucao=geraHp(alfa);    
    insereBrancos(melhorSolucao,alfa);
    int melhorCusto=calculaCusto(melhorSolucao);        
    while((numIteracoes--)>=0){
        //if(vezesSemMelhora%p==0)
        //    cout <<"iteraçao "<< vezesSemMelhora << endl;
        list<int>* solucao=geraHp(alfa);
        insereBrancos(solucao,alfa);
        int custo= calculaCusto(solucao);
        if(custo < melhorCusto){
            melhorSolucao->clear();
            delete melhorSolucao;
            melhorSolucao=solucao;
            melhorCusto=custo;
            //vezesSemMelhora=0;
        }//else
          //  vezesSemMelhora++;
    }    
    return melhorSolucao;
}

std::list<int>* Grafo::gulosoReativoRandomico(int max_iteracoes) {//ajusta com base nas operacoes o alfa
    float si[]={0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50};
    int nSi[10]={  1,    1,    1,    1,    1,    1 ,   1,    1,    1,    1};
    int numeroTotalSucessos=10;//total de experimentos realizados com sucesso, ou seja, melhora
    int i=(rand()%numeroTotalSucessos);
    list<int>* melhorSolucao=geraHp(si[i]);
    insereBrancos(melhorSolucao,si[i]);
    int melhorCusto=calculaCusto(melhorSolucao);
    //int p=max_iteracoes/10;
    //int vezesSemMelhora=0;
    //while(vezesSemMelhora<max_iteracoes){        
    while((max_iteracoes--)>=0){        
        //if(vezesSemMelhora%p==0)
          //  cout <<"iteraçao "<< vezesSemMelhora << endl;        
        i=0;//indice de onde esta o alfa
        for(int o=(rand()%numeroTotalSucessos);o>0;i++){//sorteia um alfa 
            o-=nSi[i];//garante as probabilidades de cada alfa
        }
        list<int>* solucao=geraHp(si[i]);
        insereBrancos(solucao,si[i]);
        int custo=calculaCusto(solucao);
        if(custo<=melhorCusto){//sempre que melhorar a solucao recalcula as probabilidades
            nSi[i]++;//atualiza a qtd de vezes que aquele alfa proporcionou melhora, aumentando sua probabilidade de ocorrer
            numeroTotalSucessos++;//atualiza o numero de experimentos com sucesso
            melhorCusto=custo;
            melhorSolucao->clear();
            delete melhorSolucao;
            melhorSolucao=solucao;
          //  vezesSemMelhora=0;
        }//else
            //vezesSemMelhora++;
    }
    return melhorSolucao;
}

int Grafo::calculaCustoEntrePretos(list<int>* solucao,int inicio){//calcula o custo de um preto até outro preto
    int soma=0;
    list<int>::iterator u;
    for(u=solucao->begin();u!=solucao->end();u++){
        if(*u==inicio){
            break;
        }
    }
    for(;u!=solucao->begin() && !grafo[*u].getCor();){
        soma+=grafo[(*u)].getPesoAresta(*(--u));
    }
    if(u==solucao->begin()){
        soma+=grafo[*u].getPesoAresta(solucao->back());
    }
    return  soma;
}
