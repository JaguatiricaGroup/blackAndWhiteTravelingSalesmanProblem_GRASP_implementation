/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: gabrieldias
 *
 * Created on November 10, 2016, 1:26 PM
 */
//#include <bits/stringfwd.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include "Grafo.h"
#include <math.h>
using namespace std;
//#define algoritmo 'j'
Grafo* iniciaGrafoPretoEBranco(const char* arquivo,bool flagDir,bool ponderado){
    ifstream l;
    int numVertices,numPretos,Q,L;
    Grafo *grafo;
    string aux;
    l.open(arquivo);
    if(l.good() && l.is_open()){               
        getline(l,aux);
        //cout << aux << endl;
        getline(l,aux);
        //cout << aux << endl;
        getline(l,aux);
        //cout << aux << endl;
        getline(l,aux);
        //cout << aux << endl;
        getline(l,aux);
        //cout << aux << endl;
        getline(l,aux);
        numVertices= stoi(aux.substr(2));
        //numVertices++;
        getline(l,aux);
        //cout << aux << endl;
        numPretos= stoi(aux.substr(4));
        getline(l,aux);
        Q= stoi(aux.substr(2));
        //cout << aux << endl;
        getline(l,aux);
        //cout << aux << endl;
        L= stoi(aux.substr(2));
        getline(l,aux);
        grafo=new Grafo(numVertices,flagDir,Q,L,numPretos);
        while(!l.eof()){
            aux.clear();
            getline(l,aux);
            if(aux.empty())break;
            string info,x,y,cor;
            int i=0;            
            for(i=0;aux[i]!=' ';i++){               
                info.push_back(aux[i]);
//                cout <<peso[i]<<stoi << endl;
            }
            (++i);     
            //cout << stoi(info)<<" " ;
            for(;aux[i]!=' ';i++){               
                x.push_back(aux[i]);
                //cout <<peso[i]<< endl;
            }
            (++i);     
            //cout << stoi(x)<<" " ;
            for(;aux[i]!=' ';i++){               
                y.push_back(aux[i]);
            }
            //cout << stoi(y) <<" ";
            cor=aux.substr(++i);
            //cout << stoi(cor) << endl;
            //cout << info<< ". k ." << vertice << "peso." << peso << endl;            
            grafo->incluirVertice(stoi(info),INT_MAX,(bool) stoi(cor),stoi(x),stoi(y));
        }
        //cout << "TERMINEI DE GERAR" << endl;

        for(int k=1;k<=numVertices;k++){
            for(int j=1;j<=numVertices;j++){
                if(k==j)break;
                int u=ceil(sqrt(pow(grafo->getVertices()[k].getX() - grafo->getVertices()[j].getX(),2)+pow((grafo->getVertices()[k].getY() - grafo->getVertices()[j].getY()),2)));                
                grafo->incluirAresta(j,u,k);
            }
        }
        //cout << "DEI A LUZ" << endl;
    }
    return grafo;
}

Grafo* iniciaGrafo(string& arquivo,bool flagDir,bool ponderado){
    ifstream l;int i;
    Grafo *grafo;
    string aux;
    l.open(arquivo.c_str());
    if(l.good() && l.is_open()){        
        getline(l,aux);
        int numVertices = stoi(aux);
        //cout << stoi(aux) << endl;
        grafo=new Grafo(numVertices,flagDir);  
        for( i=1;i<=numVertices;i++)
            grafo->incluirVertice(i,INT_MAX);
        while(!l.eof()){
            aux.clear();
            getline(l,aux);            
            if(aux.empty())break;                
            string info,vertice,peso;
            i=0;
            if(ponderado){
  //              peso=aux[0];
    //            cout << aux << endl;
                for(i=0;aux[i]!=' ';i++){               
                    peso.push_back(aux[i]);
                    //cout <<peso[i]<< endl;
                }
                (++i);     
            }else{
                peso="1";
            }
            for(;aux[i]!=' ';i++){               
                info.push_back(aux[i]);
            }
            vertice=aux.substr(++i);
            //cout << info<< ". k ." << vertice << "peso." << peso << endl;            
            grafo->incluirAresta(stoi(vertice),stoi(peso),stoi(info));
        }
    }
    l.close();
    return grafo;
}/*Funçao para Gerar o Grafo a partir de arquivo testo*/

int main(int argc, char **argv) { //modo para testar o caixeiro preto e branco
    
    //srand (time(NULL)+rand());
    //string aux = "r";
    string aux1 = "instancias/10.txt";
    char algoritmo[2]={'R','\0'};//aux.c_str();//argv[1];
//    char* instancia[aux1.size()]=aux1.c_str();//"instancias/10.txt";//argv[2];
    bool ponderado=1,flagDir=0;
    //ofstream saida("saida/resultado");
//    for(int k=0;k<argc;k++)
//	   cout <<"aqui"<< argv[k] << endl;
    //saida <<"INICIANDO SAIDA DE TESTES"<< endl;
   // string Instacia="instancias/30.txt";//"instanciaTrab.txt";//"as_graph_weighted.txt";//"instanciaTrab.txt";//"instanciaTrab.txt";//"grafo_10000_7.txt"
    //Grafo *l=iniciaGrafo(Instancia,flagDir,ponderado);    
    
    Grafo *l=iniciaGrafoPretoEBranco(aux1.c_str(),flagDir,ponderado);    
    //saida << "Grafo gerado com " << l->getNumArestas() << " arestas " <<l->getNumVertices()<< " vertices " << l->eDirecionado() << " direcionado " << ponderado<<" ponderado" <<endl;
    //l->imprime();
    //l->exportaGrafo("saida/GrafoTeste");
    //cout << l->getP() << endl;
//    list<int>* L=l->geraHp(1);
//    for(int &u:*L){
//        cout << u << " ";
//    }
//    cout << endl;
//    l->insereBrancos(L,0);
//    for(int &u:*L){
//        cout << u << " ";
//    }
//    cout << endl;
//    cout <<"custo : "<< l->calculaCusto(L)<< endl;
    list<int>* L;
    if(algoritmo[0] == 'g'){        
        //cout << "guloso" << endl;
        L= l->guloso();
//        for(int &u:*L){
//            cout << u << " ";
//        }   
//        cout << endl;
//        cout <<"custo : "<< l->calculaCusto(L)<< endl;
        //cout <<"custo : "<< l->calculaCusto(L)<< endl;
        cout << l->calculaCusto(L)<< endl;
      //  saida <<"custo : "<< l->calculaCusto(L)<< endl;
    }else{
    //L->clear();
        if(algoritmo[0]=='r'){
;
            cout << "guloso Randomico" << endl;
            L=l->gulosoRandomico(0.25,5000);
//            for(int &u:*L){
//            cout << u << " ";
//            cout << endl;
            cout <<"custo : "<< l->calculaCusto(L)<< endl;
//            cout << l->calculaCusto(L)<< endl;
//            saida <<"custo : "<< l->calculaCusto(L)<< endl;
//            }
        }else{
            if(algoritmo[0]=='R'){
            //L->clear();
            	cout << "guloso Randomico Reativo" << endl;
                L=l->gulosoReativoRandomico(250);
                for(int &u:*L){
	                 cout << u << " ";
                }   
            cout << endl;
            //cout <<"custo : "<< l->calculaCusto(L)<< endl;
            //cout <<"custo : "<< l->calculaCusto(L)<< endl;
            cout << l->calculaCusto(L) << endl;
          //  saida <<"custo : "<< l->calculaCusto(L)<< endl;
            }else 
            cout <<"Erro na selecao de algoritmo"<< endl;
        }
        
    }
//    saida << "Testa Grau dos Nós" << endl;
//    for(int i=1;i<=l->getNumVertices();i++){
//        saida << i <<"-"<<l->GrauNo(i) << " " ;
//    }
//    saida << endl;
//    saida << "Testa sequencia graus" << endl;
//    vector<NoOrdenaGrau>* sequenciaGraus = l->sequenciaGraus();
//    for(NoOrdenaGrau &i:*sequenciaGraus){
//        saida << i.grau << " ";
//    }
//    delete sequenciaGraus;
//    saida << endl;
//    saida <<"Testa se é k-regular" << endl;
//    saida << l->eKRegular() << endl;    
//    saida <<"Testa se é Completo" << endl;
//    saida << l->eCompleto() << endl;    
//    saida <<"Testa se é adjacente" << endl;
//    //for(int i=0;i<l->getNumVertices();i++)
//    //    for(int j=0;i<l->getNumVertices();j
//    int i=4,j=1;//l->GeraVertice(),j=l->GeraVertice();    
//    saida << " " <<i <<"-("<< l->eAdjacente(i,j)<<")-"<<j;
//    saida << endl;
//    saida <<"Testa se é direcionado" << endl;
//    saida << l->eDirecionado() << endl;
//    saida <<"Testa Busca largura partindo de "<< j << endl;
//    list<int>* buscaLargura=l->buscaLargura(j);
//    for(int &k:*buscaLargura)
//        saida << k << " ";    
//    delete buscaLargura;
//    saida << endl;
//    saida <<"Testa Busca Profundidade partindo de "<< j << endl;
//    list<int>* busca=l->buscaProfundidade(j);
//    for(int &k:*busca)
//        saida << k <<" ";
//    delete busca;
//    saida << endl;
//    saida <<"Testa se é conexo" << endl;
//    saida << l->eConexo() << endl;
//    int u=l->GeraVertice();
//    saida << "testa se "<<u<<" e "<<j<<" estao na mesma componente conexa" << endl;    
//    //saida <<"os vertices  "<< o << " e "<< u << endl;
//    saida << l->mesmaComponenteConexa(u,j) << endl;    
//    saida << "Testa se é articulaçao o vertice"<< i << endl;
//    saida << l->eArticulacao(i)<< endl;
//    cout << i << " " << j << endl;
//    saida << "Testa se é articulaçao a aresta"<< i << j << endl;
//    saida << l->ePonte(i,j)<< endl;    
//    saida << "Testa Vizinhaca aberta "<< i  << endl;
//    busca=l->vizinhancaAberta(i);
//    for(int &k:*busca)
//        saida << k <<" ";
//    delete busca;
//    saida << endl;
//    saida << "Testa Vizinhaca fechada "<< i  << endl;
//     busca=l->vizinhancaFechada(i);
//    for(int &k:*busca)
//        saida << k <<" ";
//    delete busca;
//    saida << endl;
//    saida << "Testa Vizinhaca transDireto"<< i  << endl;
//    busca=l->FechoTransDireto(i);
//    for(int &k:*busca)
//        saida << k <<" ";
//    delete busca;
//    saida << endl;
//    saida << "Testa Vizinhaca TransIndireto"<< i  << endl;
//    list<int>* busca = l->FechoTransIndireto(5);
//    for(int &k:*busca)
//        cout << k <<" ";
//    delete busca;
//    saida << endl;
//    saida << "Testa dijkstra"<< i  << endl;
//    list<ResultadoDijkstra>* busca1=l->dijkstra(i);
//    for(ResultadoDijkstra &k:*busca1)
//        saida <<" "<< k.info << "-(" << k.distMin << ")" <<" ";
//    delete busca1;
//    saida << "Testa Vizinhaca aberta"<< endl;
//    l->floyd();
//    vector<int> aux;
//    aux.push_back(1);
//    aux.push_back(3);
//    aux.push_back(4);
//    cout << " l aqui"<< endl;
//    //l->imprime();
//    Grafo* k=l->subgrafoInduzido(aux);
//    cout << " k aqui"<< endl;
//    //k->imprime();
//    std::list<std::list<int>* >* L= l->componentesConexas();
//    for(std::list<int>* &p:*L){
//        for(int &w:*p)
//            cout << w << endl;
//        cout << "comp"<< endl;
//    }    
//    saida << "Testa Prim"  << endl;
//    list<ArestaAGM>* agm=l->prim();
//    for(ArestaAGM &k:*agm)
//        saida <<k.info1 <<"-"<< k.info2 << "(" << k.peso << ")" <<" ";
//    delete agm;
//    saida << "Testa Kruskal"  << endl;
//    agm=l->kruskal();
//    for(ArestaAGM &k:*agm)
//        saida <<k.info1 <<"-"<< k.info2 << "(" << k.peso << ")" <<" ";
//    delete agm;
    return 0;
}




/*
 *  //cout << "arestas " << l->getNumArestas() << " vertices " << l->getNumVertices() << endl;
    //Teste para as funções
    //l.incluirVertice(2,3);
    //l.incluirVertice(3,3);
    //l.incluirAresta(2,20,3);    
    //l.incluirAresta(3,40,2);
    //l->imprime();
    l->exportaGrafo("saidaExportada");
    //l.excluiAresta(2);
    //l.excluiVertice(2);
    //l.imprime();
    
//    vector<NoOrdenaGrau> *u = l->sequenciaGraus();
    //for(int i=0;u->size();i++){
       // cout << u->at(i).info <<endl;
    ///}
//    for(NoOrdenaGrau &k:*u){
//        if(k.info!=0)   
//            cout << k.grau << "  ";
//    }
//  
    //l->buscaLargura(2);
    //
    //l->buscaProfundidade(4);
    //cout << l->eConexo(); 
   //cout << l->mesmaComponenteConexa(607,100);
   // l->excluiVertice(5);
    //cout << l->eConexo() << endl;
   //cout << l->eArticulacao(1180) << endl;
   //cout << l->ePonte(3,5) << endl;
   //list<int>* j=l->vizinhacaAberta(5);
   //vector<int>* j=l->FechoTransDireto(4);
   //for(int &k:*j)// =3        
   //     cout<<" "<< k<<endl;
//    int *let=l->dijkstra(6);
//    for(int i=1;i<8;i++){
//        cout << let[i] << endl;
//    }
//   int ** floyd = l->floyd();
//    for (i = 0; i < maxVertices; i++){            
//        cout << 
//        for (j = 0; j < maxVertices; j++){
//            cout 
//        }
//    }
//    l->floyd();
//    vector<int> h{6};
//    Grafo *s=l->subgrafoInduzido(h);
//    s->exportaGrafo();
    
   //cout <<  l->GrauNo(5660) <<l->GrauNo(8) << endl; 
    //cout <<  l->eKRegular() << endl; 
//    list<vector<int>* >* teste= l->componentesConexas();
//    for(vector<int>* j:*teste){
//        for(int &h:*j){
//            cout << h <<" ";
//        }
//        cout << endl;
//    }
//    list<ArestaKruskal>* w = l->kruskal();
//    for(ArestaKruskal &r:*w){
//        cout << r.info1 << "--" << r.info2 << " p: " << r.peso << endl; 
//    }
    l->prim();
    l->kruskal();
    //int * r= l->dijkstra(1);
//    for(int i=0;i< l->getNumVertices()+1 ; i++){
//        cout << r[i] << " ";
//    }
    l->imprime();
    cout << l->getNumVertices()<< endl;
 */
