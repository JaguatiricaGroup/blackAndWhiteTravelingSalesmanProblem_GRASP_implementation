/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Aresta.h"


Aresta::Aresta(int peso,int info){
    this->peso=peso;
    this->info=info;
}

Aresta::~Aresta(){}


int Aresta::getPeso(){
    return this->peso;
}
void Aresta::setPeso(int peso){
    this->peso=peso;
}     
int Aresta::getInfo(){
    return this->info;
}
void Aresta::setInfo(int info){
    this->info=info;
}
