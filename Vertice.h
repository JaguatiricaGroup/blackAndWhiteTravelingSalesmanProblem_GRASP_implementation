/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vertice.h
 * Author: gabrieldias
 *
 * Created on November 10, 2016, 1:36 PM
 */

#ifndef VERTICE_H
#define VERTICE_H
#include <list>
#include "Aresta.h"
#include <fstream>

class Vertice{
    public:
        Vertice(int peso,int info);
        Vertice();
        virtual ~Vertice();
        int getPeso(); //retorna o peso do vértice
        void setPeso(int peso); //configura o peso do vértice       
        int getInfo(); //retorna a informação do vértice
        void setInfo(int info); //configura a informação do vértice
        int getGrau();  //retorna o grau do vértice 
        void incluirAresta(int peso,int info); //inclui uma aresta no Grafo
        bool excluiAresta(int info); //exclui uma aresta no Grafo
        void imprimeAresta(); // imprime a vizinhança
        bool buscaAresta(int info); //busca uma aresta
        int getPesoAresta(int info); //retorna o peso da aresta
        bool getCor(); //retorna a cor do vértice
        void setCor(bool cor); //configura a cor do vértice        
        std::list<Aresta>& getList(); // retorna o endereço da lista de arestas
        void exportaGrafoAresta(std::ofstream &l);  // cria arquivo de saída em .txt para impressão do Grafo
        int getX() ;
        int getY() ;
        void setX(int x);
        void setY(int y);
        bool getVisitado();
        void setVisitado(bool i);
private:                 
            bool cor;//cor do vertice
            int x,y;//coordenadas
            bool visitado;//se ja esta  na soluçao
            int peso; //peso do vértice
            int grauNo; //grau do vértice
            int info;  //informação do vértice
            std::list<Aresta> vizinhanca; // lista de vizinhanças do vértice
};


#endif /* VERTICE_H */

