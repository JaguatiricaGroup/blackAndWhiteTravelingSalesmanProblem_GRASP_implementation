/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DisjointSet.cpp
 * Author: user
 * 
 * Created on 20 de Novembro de 2016, 14:58
 */

#include "DisjointSet.h"

DisjointSet::DisjointSet(int n){
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;            
            parent[i] = i;
        }
    }
    int DisjointSet::find(int u){        
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
     
    void DisjointSet::merge(int x, int y){
        x = find(x), y = find(y);        
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else 
            parent[x] = y;
 
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }