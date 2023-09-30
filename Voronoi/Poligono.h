//
//  Poligono.hpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 18/08/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//

#ifndef Poligono_hpp
#define Poligono_hpp

#include <iostream>
using namespace std;

#ifdef WIN32
#include <windows.h>
#include <glut.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <glut.h>
#endif

#include "Ponto.h"
#include <vector>
#include "Envelope.h"

class Poligono
{
    vector<Ponto> Vertices;
    Ponto Min, Max;
    vector<int> NeighborDictionary;
    Envelope E;

public:
    Poligono();
    Ponto getVertice(int);
    unsigned long getNVertices();
    void envelopa();
    void desenhaEnvelope();
    bool domina(Ponto a, Ponto b);
    bool estaDentro(Ponto p, int metodo);
    void interfaceEstaDentro(Ponto p, int metodo);
    bool estaDentroConcavo(Ponto p);
    bool estaDentroConvexo(Ponto ponto);
    int contadorDeFuncao();
    int estaForaVoronoi(Ponto ponto);
    void insereVertice(Ponto);
    void insereVertice(Ponto p, int pos);
    void desenhaPoligono();
    void desenhaVertices();
    void pintaPoligono();
    void setVizinho(int j, int k);
    void mostraVizinhos();
    int tamanhoVizinhos();
    int getVizinho(int i);
    vector<int> getNeighborDictionary();
    void imprime();
    void atualizaLimites();
    void obtemLimites(Ponto &Min, Ponto &Max);
    void LePoligono(const char *nome);
    void desenhaAresta(int n);
    void getAresta(int i, Ponto &P1, Ponto &P2);
};

#endif
