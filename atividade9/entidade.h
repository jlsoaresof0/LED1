
#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "raylib.h"
#include <stdbool.h>

typedef enum {
    ENTIDADE_JOGADOR,
    ENTIDADE_INIMIGO,
    ENTIDADE_ITEM
} TipoEntidade;

typedef struct Entidade {
    TipoEntidade tipo;
    Vector2 pos;
    int vida;
    float raio;

    union {
        int dano;
        int valor;
    } extra;

} Entidade;

Entidade *entidadeCriar(TipoEntidade tipo, Vector2 pos);
bool entidadeColidiu(Entidade *a, Entidade *b);
void entidadeDesenhar(Entidade *e);
void entidadeAplicarDano(Entidade *e, int dano);

#endif
