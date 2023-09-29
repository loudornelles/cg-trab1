//
//  Poligono.cpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 18/08/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//
#include <iostream>
#include <fstream>
using namespace std;

#include "Poligono.h"

#include <list>

Poligono::Poligono()
{
}

// std::map<std::int8_t, int> neighborDictionary;

bool Poligono::domina(Ponto a, Ponto b)
{
    if ((a.x >= b.x) && (a.y >= b.y))
        return true;
    return false;
}

bool Poligono::estaDentro(Ponto p)
{
    if (E.pontoEstaDentro(p))
    {
        return estaDentroConvexo(p);
    }
}

bool Poligono::estaDentroConcavo(Ponto ponto)
{
    // pego (0, p.y) e p em si e vejo quantas intersecções com as arestas do polígono existem.
    int contadorIntersecoes = 0;
    Ponto Esq;
    Ponto Dir(-1, 0);
    Esq = ponto + Dir * (1000);

    for (int i = 0; i < Vertices.size(); i++)
    {
        Ponto A = Vertices[i];
        Ponto B = Vertices[(i + 1) % Vertices.size()];
        if (HaInterseccao(Esq, ponto, A, B))
        {
            contadorIntersecoes++;
        }
    }
    return contadorIntersecoes % 2 != 0;
}

bool Poligono::estaDentroConvexo(Ponto ponto)
{
    Ponto V1;
    Ponto V2;
    Ponto resultado;

    for (int i = 0; i < Vertices.size(); i++)
    {
        Ponto A = Vertices[i];
        Ponto B = Vertices[(i + 1) % Vertices.size()];
        V1 = ponto - A; // ponto
        V2 = B - A;     // aresta

        ProdVetorial(V1, V2, resultado);

        if (resultado.z < 0)
        {
            return false;
        }
    }
    return true;
}

void Poligono::insereVertice(Ponto p)
{
    Vertices.push_back(p);
    NeighborDictionary.push_back(-1);
}

void Poligono::insereVertice(Ponto p, int pos)
{
    if ((pos < 0) || (pos > Vertices.size()))
    {
        cout << "Metodo " << __FUNCTION__ << ". Posicao Invalida. Vertice nao inserido." << endl;
        return;
    }
    Vertices.insert(Vertices.begin() + pos, p);
    NeighborDictionary.push_back(-1);
}

Ponto Poligono::getVertice(int i)
{
    return Vertices[i];
}

void Poligono::pintaPoligono()
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < Vertices.size(); i++)
        glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
    glEnd();
}

void Poligono::setVizinho(int edgeIndex, int neighborIndex)
{
    // Ensure that edgeIndex is within bounds
    if (edgeIndex >= 0)
    {
        // Set the neighbor index for the specified edge
        // cout << "tamanho antes de inserir " << NeighborDictionary.size() << endl;
        NeighborDictionary[edgeIndex] = neighborIndex;
        // cout << "inserindo {" << edgeIndex << ": " << neighborIndex << "}\n";
        int elementoInserido = NeighborDictionary[edgeIndex];
    }
    else
    {
        // Handle the case when edgeIndex is out of bounds (e.g., display an error message)
        cout << "Invalid edge index: " << edgeIndex << endl;
    }
    // cout << "tamanho depois do processo: " << NeighborDictionary.size() << endl;
    for (int num : NeighborDictionary)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    cout << "-----" << endl;
}

void Poligono::mostraVizinhos()
{
    for (int i = 0; i < NeighborDictionary.size(); i++)
    {
        cout << i << ": " << NeighborDictionary[i] << endl;
    }
}

void Poligono::desenhaPoligono()
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < Vertices.size(); i++)
        glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
    glEnd();
    E.Desenha();
}
void Poligono::desenhaVertices()
{
    glBegin(GL_POINTS);
    for (int i = 0; i < Vertices.size(); i++)
        glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
    glEnd();
}
void Poligono::imprime()
{
    for (int i = 0; i < Vertices.size(); i++)
        Vertices[i].imprime();
}
unsigned long Poligono::getNVertices()
{
    return Vertices.size();
}

void Poligono::envelopa()
{
    Ponto Max = Vertices[0];
    Ponto Min = Vertices[0];

    for (int i = 0; i < Vertices.size(); i++)
    {
        Min = ObtemMinimo(Vertices[i], Min);
        Max = ObtemMaximo(Vertices[i], Max);
    }

    E.GeraEnvelope(Min, Max);
    std::cout << " gerou envelope " << std::endl;
    E.imprime();
    E.Desenha();
}

void Poligono::obtemLimites(Ponto &Min, Ponto &Max)
{
    Max = Min = Vertices[0];

    for (int i = 0; i < Vertices.size(); i++)
    {
        Min = ObtemMinimo(Vertices[i], Min);
        Max = ObtemMaximo(Vertices[i], Max);
    }
}

// **********************************************************************
//
// **********************************************************************
void Poligono::LePoligono(const char *nome)
{
    ifstream input;            // ofstream arq;
    input.open(nome, ios::in); // arq.open(nome, ios::out);
    if (!input)
    {
        cout << "Erro ao abrir " << nome << ". " << endl;
        exit(0);
    }
    cout << "Lendo arquivo " << nome << "...";
    string S;
    // int nLinha = 0;
    unsigned int qtdVertices;

    input >> qtdVertices; // arq << qtdVertices

    for (int i = 0; i < qtdVertices; i++)
    {
        double x, y;
        // Le cada elemento da linha
        input >> x >> y; // arq << x  << " " << y << endl
        if (!input)
            break;
        // nLinha++;
        insereVertice(Ponto(x, y));
    }
    // cout << "Envelopando!" << endl;
    // envelopa();
    // cout << "Poligono lido com sucesso!" << endl;
    input.close();
}

void Poligono::getAresta(int n, Ponto &P1, Ponto &P2) // Retorna os pontos da aresta n
{
    P1 = Vertices[n];                   // P1 recebe o ponto n
    int n1 = (n + 1) % Vertices.size(); // n1 recebe o ponto seguinte
    P2 = Vertices[n1];                  // P2 recebe o ponto seguinte
}

void Poligono::desenhaAresta(int n)
{
    glBegin(GL_LINES);
    glVertex3f(Vertices[n].x, Vertices[n].y, Vertices[n].z);
    int n1 = (n + 1) % Vertices.size();
    glVertex3f(Vertices[n1].x, Vertices[n1].y, Vertices[n1].z);
    glEnd();
    // Ponto P1, P2;
    // getAresta(n, P1, P2);
    // addAresta(P1, P2);
}

// void Poligono::addAresta(Ponto P1, Ponto P2)
// {
//     Arestas.push_back(P1, P2);
// }
