//
//  Envelope.cpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 28/08/22.
//  Copyright © 2022 Márcio Sarroglia Pinho. All rights reserved.
//

#include "Envelope.h"

Envelope::Envelope()
{
}
Envelope::Envelope(Ponto P1, Ponto P2)
// Cria um envelope a partir de dois pontos
{
    GeraEnvelope(P1, P2);
}
bool Envelope::temColisao(Envelope E)
{
    /*
    cout << "Campo de Visao: ";
    imprime();
    cout << endl;
    cout << "Env 2: ";
    E.imprime();
    cout << endl;
     */
    float distancia;                                   // Distancia entre os centros dos envelopes
    distancia = fabs(Meio.x - E.Meio.x);               // fabs = valor absoluto
                                                       // cout << "distancia X: " << distancia << endl;
    if (distancia > (MeiaLargura.x + E.MeiaLargura.x)) // Se a distancia for maior que a soma das meias larguras, nao ha colisao
        return false;
    distancia = fabs(Meio.y - E.Meio.y); // fabs = valor absoluto
    // cout << "distancia Y: " << distancia << endl;
    if (distancia > (MeiaLargura.y + E.MeiaLargura.y)) // Se a distancia for maior que a soma das meias larguras, nao ha colisao
        return false;
    return true;
}
void Envelope::GeraEnvelope(Ponto P1, Ponto P2)
// Cria um envelope a partir de dois pontos
{
    Min = ObtemMinimo(P1, P2); // Obtem o minimo entre os dois pontos
    Max = ObtemMaximo(P1, P2); // Obtem o maximo entre os dois pontos

    Meio = (Max + Min) * 0.5;        // Calcula o ponto medio do envelope
    MeiaLargura = (Max - Min) * 0.5; // Calcula a meia largura do envelope

    // Min.imprime("Minimo: ", "\n");
    // Max.imprime("Maximo: ", "\n");
    // Meio.imprime("Meio: ", "\n");
    // MeiaLargura.imprime("Meia Largura: ", "\n");
}
void Envelope::AtualizaEnvelope()
// Atualiza o envelope a partir dos pontos Min e Max
{
    Meio = (Max + Min) * 0.5;        // Calcula o ponto medio do envelope
    MeiaLargura = (Max - Min) * 0.5; // Calcula a meia largura do envelope
}

bool Envelope::pontoEstaDentro(Ponto P)
// Verifica se um ponto esta dentro do envelope
{
    if (P.x < Min.x)
        return false;
    if (P.x > Max.x)
        return false;
    if (P.y < Min.y)
        return false;
    if (P.y > Max.y)
        return false;

    return true;
}
void Envelope::imprime()
{
    Min.imprime("Minimo: ");
    Max.imprime(" Maximo: ");
}
void Envelope::Desenha()
// Desenha o envelope
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);    // Desenha um poligono
    glVertex2d(Min.x, Min.y); // Vertice 1
    glVertex2d(Min.x, Max.y); // Vertice 2
    glVertex2d(Max.x, Max.y); // Vertice 3
    glVertex2d(Max.x, Min.y); // Vertice 4
    glEnd();                  // Finaliza o poligono
}
