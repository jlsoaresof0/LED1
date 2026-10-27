#include "raylib.h"
#include "entidade.h"
#include <stdlib.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600

int main(void) {

    InitWindow(
        LARGURA_JANELA,
        ALTURA_JANELA,
        "Atividade 8B - Reutilizacao do Modulo"
    );

    SetTargetFPS(60);

    Entidade *jogador = entidadeCriar(
        ENTIDADE_JOGADOR,
        (Vector2){200, 300}
    );

    Entidade *inimigo = entidadeCriar(
        ENTIDADE_INIMIGO,
        (Vector2){400, 300}
    );

    Entidade *item = entidadeCriar(
        ENTIDADE_ITEM,
        (Vector2){600, 300}
    );

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        entidadeDesenhar(jogador);
        entidadeDesenhar(inimigo);
        entidadeDesenhar(item);

        EndDrawing();
    }

    free(jogador);
    free(inimigo);
    free(item);

    CloseWindow();

    return 0;
}