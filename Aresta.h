/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Aresta.h
 * Author: gabrieldias
 *
 * Created on November 10, 2016, 1:36 PM
 */

#ifndef ARESTA_H
#define ARESTA_H

class Aresta{
    public:
        Aresta();
        Aresta(int peso,int info);
        virtual ~Aresta();
        int getPeso(); // retorna o peso da aresta
        void setPeso(int peso); // configura o peso da aresta      
        int getInfo(); // retorna a informação da aresta
        void setInfo(int info); // configura a informação da aresta

    private:
        int info; // informação do vértice vizinho
        int peso; // peso da aresta
};



#endif /* ARESTA_H */

