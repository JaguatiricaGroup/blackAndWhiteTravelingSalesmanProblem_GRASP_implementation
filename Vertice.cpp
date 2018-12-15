#include "Vertice.h"
#include  "Aresta.h"
#include <list>
#include <iostream>
#include <fstream>

using namespace std;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
Vertice::Vertice(){}
Vertice::Vertice(int peso,int info){
    this->info=info;
    this->peso=peso;     
}
Vertice::~Vertice(){
    vizinhanca.clear();
}

int Vertice::getPeso(){
    return this->peso;
}

void Vertice::setPeso(int peso){
    this->peso=peso;
}

int Vertice::getInfo(){
            return info;
}

void Vertice::setInfo(int info){
    this->info=info;
}

int Vertice::getGrau(){
    //std::cout << vizinhanca.size() << std::endl;
    return vizinhanca.size();        
}

void Vertice::incluirAresta(int peso,int info)
{    
    Aresta *l=new Aresta(peso,info);
    //std::cout << "inclui" << std::endl;
    this->vizinhanca.push_front(*l);
}

bool Vertice::excluiAresta(int info){    
    if(!vizinhanca.empty()){        
        for(list<Aresta>::iterator l=vizinhanca.begin(); l!=vizinhanca.end(); l++){            
            if(info == l->getInfo()){                                
                l=vizinhanca.erase(l);  
                return true;
            }//else{
             //   cout<< "nao achei a aresta" << endl;
            //}
        }        
    }else{
        cout << "vizinhaca vazia" << endl;
    }
    return false;
}

void Vertice::imprimeAresta(){
    std::cout << "aresta: " ;
    for(list<Aresta>::iterator l=vizinhanca.begin(); l!=vizinhanca.end(); l++){
        std::cout << " " << l->getInfo() << " " ;
    }
    std::cout << std::endl;
}

bool Vertice::buscaAresta(int info){
    for(Aresta &l:vizinhanca){
        if(l.getInfo()==info)
            return true;
    }     
    return false;
}

std::list<Aresta>& Vertice::getList(){
    return vizinhanca;
}

int Vertice::getPesoAresta(int info) {
    for(Aresta &u:vizinhanca){
        if(u.getInfo()==info){
            return u.getPeso();
        }
    }
//    cout << "nao existe a aresta" << endl;
    return -1;
}

void Vertice::exportaGrafoAresta(ofstream &k) {    
    k << "arestas: " ;
    for(list<Aresta>::iterator l=vizinhanca.begin(); l!=vizinhanca.end(); l++){
        k << " " << l->getInfo()<< "("<< l->getPeso() <<")" << " " ;
    }
    k << std::endl;
}

bool Vertice::getCor() {
    return cor;
}

void Vertice::setCor(bool cor) {
    this->cor=cor;
}

int Vertice::getX(){
        return x;
    }

int Vertice::getY()  {
        return y;
    }

void Vertice::setX(int x) {
        this->x = x;
    }

void Vertice::setY(int y) {
        this->y = y;
}

void Vertice::setVisitado(bool i) {
    visitado=i;
}

bool Vertice::getVisitado() {
    return visitado;
}

