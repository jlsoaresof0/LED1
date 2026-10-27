
#include "entidade.h"
#include <stdlib.h>
#include <math.h>

Entidade *entidadeCriar(TipoEntidade tipo, Vector2 pos) {
    Entidade *e = malloc(sizeof(Entidade));

    if (e == NULL) return NULL;

    e->tipo = tipo;
    e->pos = pos;
    e->vida = 100;
    e->raio = 15.0f;

    switch (tipo) {
        case ENTIDADE_JOGADOR:
            e->vida = 100;
            break;

        case ENTIDADE_INIMIGO:
            e->vida = 40;
            e->extra.dano = 10;
            break;

        case ENTIDADE_ITEM:
            e->vida = 1;
            e->extra.valor = 10;
            break;
    }

    return e;
}

bool entidadeColidiu(Entidade *a, Entidade *b) {
    if (a == NULL || b == NULL) return false;

    float dx = a->pos.x - b->pos.x;
    float dy = a->pos.y - b->pos.y;
    float distancia = sqrtf(dx * dx + dy * dy);

    return distancia < a->raio + b->raio;
}

void entidadeDesenhar(Entidade *e) {
    if (e == NULL) return;

    Color cor;

    switch (e->tipo) {
        case ENTIDADE_JOGADOR:
            cor = BLUE;
            break;

        case ENTIDADE_INIMIGO:
            cor = RED;
            break;

        case ENTIDADE_ITEM:
            cor = GOLD;
            break;

        default:
            cor = GRAY;
            break;
    }

    DrawCircleV(e->pos, e->raio, cor);
}

void entidadeAplicarDano(Entidade *e, int dano) {
    if (e == NULL || dano <= 0) return;

    e->vida -= dano;

    if (e->vida < 0) {
        e->vida = 0;
    }
}
