//
//  DiagramaVoronoi.cpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 23/08/23.
//  Copyright © 2023 Márcio Sarroglia Pinho. All rights reserved.
//

#include "DiagramaVoronoi.h"

ifstream input; // ofstream arq;

Voronoi::Voronoi()
{
}

// cria mapa de vizinhos

Poligono Voronoi::LeUmPoligono()
// Le um poligono do arquivo de entrada
{
    Poligono P;                           // Cria um poligono vazio
    unsigned int qtdVertices;             // Numero de vertices do poligono
    input >> qtdVertices;                 // arq << qtdVertices
    for (int i = 0; i < qtdVertices; i++) // Le os vertices do poligono
    {
        double x, y;
        // Le um ponto
        input >> x >> y;
        Ponto(x, y).imprime(); // arq << x << " " << y << endl;
        if (!input)            // if (!arq)
        {
            cout << "Fim inesperado da linha." << endl; // imprime na tela
            break;
        }
        P.insereVertice(Ponto(x, y)); // Insere o ponto no poligono
    }
    cout << "Poligono lido com sucesso!" << endl;
    return P;
}

void Voronoi::ObtemVizinhosdasArestas()
{
    for (int i = 0; i < qtdDePoligonos; i++)
    {
        for (int j = 0; j < Diagrama[i].getNVertices(); j++)
        {
            Ponto A = Diagrama[i].getVertice(j);
            Ponto B = Diagrama[i].getVertice((j + 1) % Diagrama[i].getNVertices());
            for (int k = 0; k < qtdDePoligonos; k++)
            {
                if (k != i)
                {
                    for (int l = 0; l < Diagrama[k].getNVertices(); l++)
                    {
                        Ponto C = Diagrama[k].getVertice(l);
                        Ponto D = Diagrama[k].getVertice((l + 1) % Diagrama[k].getNVertices());
                        if (A == D && B == C)
                        {
                            cout << "Vizinho de " << i << " na aresta " << j << " eh " << k << endl;
                            Diagrama[i].setVizinho(j, k);
                            cout << "Vizinho de " << k << " na aresta " << l << " eh " << i << endl;
                            Diagrama[k].setVizinho(l, i);
                        }
                    }
                }
            }
        }
    }
}

void Voronoi::LePoligonos(const char *nome)
// Le os poligonos do arquivo de entrada
{
    input.open(nome, ios::in); // arq.open(nome, ios::out);
    if (!input)                // if (!arq)
    {
        cout << "Erro ao abrir " << nome << ". " << endl;
        exit(0);
    }
    string S; // Le o cabecalho do arquivo

    input >> qtdDePoligonos;
    cout << "qtdDePoligonos:" << qtdDePoligonos << endl;
    Ponto A, B;                              // Limites do poligono
    Diagrama[0] = LeUmPoligono();            // Le o primeiro poligono
    Diagrama[0].obtemLimites(Min, Max);      // obtem o envelope do poligono
    for (int i = 1; i < qtdDePoligonos; i++) // Le os demais poligonos
    {
        Diagrama[i] = LeUmPoligono();   // Le o poligono
        Diagrama[i].obtemLimites(A, B); // obtem o envelope do poligono
        Min = ObtemMinimo(A, Min);      // Atualiza o envelope
        Max = ObtemMaximo(B, Max);      // Atualiza o envelope
    }
    cout << "Lista de Poligonos lida com sucesso!" << endl;
}

Poligono Voronoi::getPoligono(int i)
// Retorna o poligono i
{
    if (i >= qtdDePoligonos) // Se o poligono nao existe
    {
        cout << "Nro de Poligono Inexistente" << endl;
        return Diagrama[0]; // Retorna o primeiro poligono
    }
    return Diagrama[i]; // Retorna o poligono i
}
unsigned int Voronoi::getNPoligonos() // Retorna o numero de poligonos
{
    return qtdDePoligonos; // Retorna o numero de poligonos
}
void Voronoi::obtemLimites(Ponto &min, Ponto &max)
// Retorna os limites do diagrama
{
    min = this->Min; // Retorna o limite minimo
    max = this->Max; // Retorna o limite maximo
}
