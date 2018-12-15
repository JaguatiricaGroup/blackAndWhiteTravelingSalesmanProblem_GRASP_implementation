/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DisjointSet.h
 * Author: user
 *
 * Created on 20 de Novembro de 2016, 14:58
 */

#ifndef DISJOINTSET_H
#define DISJOINTSET_H

class DisjointSet {
public:
    DisjointSet();//construtor 
    DisjointSet(int n);//sobrecarga do construtor
    DisjointSet(const DisjointSet& orig);//sobrecarga do construtor
    virtual ~DisjointSet(){;};//Destrutor
    int *parent, *rnk;
    int n;
    int find(int u);//encontra um elemento
    void merge(int x, int y);//une dois elementos para formar um conjunto
};

#endif /* DISJOINTSET_H */

