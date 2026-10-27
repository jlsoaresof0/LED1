
#include "raylib.h"
#include "entidade.h"
#include "inventario.h"
#include <stdlib.h>
#include <time.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600
#define MAX_ENTIDADES 30
#define TOTAL_INIMIGOS 5
#define TOTAL_ITENS 6
#define DANO_TIRO 20

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(LARGURA_JANELA, ALTURA_JANELA,
               "Atividade 9 - TAD Inventario");
    SetTargetFPS(60);

    Inventario *inventario = inventarioCriar(MAX_ENTIDADES);

    if (inventario == NULL) {
        CloseWindow();
        return 1;
    }

    Entidade *jogador = entidadeCriar(
        ENTIDADE_JOGADOR,
        (Vector2){LARGURA_JANELA / 2.0f,
                  ALTURA_JANELA / 2.0f}
    );

    if (jogador == NULL ||
        !inventarioAdicionar(inventario, jogador)) {
        free(jogador);
        inventarioDestruir(inventario);
        CloseWindow();
        return 1;
    }

    for (int i = 0; i < TOTAL_INIMIGOS; i++) {
        Vector2 pos = {
            (float)GetRandomValue(30, LARGURA_JANELA - 30),
            (float)GetRandomValue(30, ALTURA_JANELA - 30)
        };

        Entidade *inimigo = entidadeCriar(ENTIDADE_INIMIGO, pos);

        if (inimigo == NULL ||
            !inventarioAdicionar(inventario, inimigo)) {
            free(inimigo);
            inventarioDestruir(inventario);
            CloseWindow();
            return 1;
        }
    }

    for (int i = 0; i < TOTAL_ITENS; i++) {
        Vector2 pos = {
            (float)GetRandomValue(30, LARGURA_JANELA - 30),
            (float)GetRandomValue(30, ALTURA_JANELA - 30)
        };

        Entidade *item = entidadeCriar(ENTIDADE_ITEM, pos);

        if (item == NULL ||
            !inventarioAdicionar(inventario, item)) {
            free(item);
            inventarioDestruir(inventario);
            CloseWindow();
            return 1;
        }
    }

    int pontuacao = 0;

    while (!WindowShouldClose()) {
        float vel = 250.0f * GetFrameTime();

        if (IsKeyDown(KEY_RIGHT)) jogador->pos.x += vel;
        if (IsKeyDown(KEY_LEFT))  jogador->pos.x -= vel;
        if (IsKeyDown(KEY_UP))    jogador->pos.y -= vel;
        if (IsKeyDown(KEY_DOWN))  jogador->pos.y += vel;

        // Colisoes
        for (int i = 1; i < inventarioTotal(inventario); i++) {
            Entidade *e = inventarioObter(inventario, i);

            if (e == NULL || !entidadeColidiu(jogador, e)) {
                continue;
            }

            if (e->tipo == ENTIDADE_ITEM) {
                pontuacao += e->extra.valor;
                inventarioRemover(inventario, i);
                i--;
            } else if (e->tipo == ENTIDADE_INIMIGO) {
                entidadeAplicarDano(jogador, e->extra.dano);
            }
        }

        // Ataque com ESPACO
        if (IsKeyPressed(KEY_SPACE)) {
            for (int i = 1; i < inventarioTotal(inventario); i++) {
                Entidade *e = inventarioObter(inventario, i);

                if (e == NULL || e->tipo != ENTIDADE_INIMIGO) {
                    continue;
                }

                if (!entidadeColidiu(jogador, e)) {
                    entidadeAplicarDano(e, DANO_TIRO);

                    if (e->vida <= 0) {
                        inventarioRemover(inventario, i);
                    }

                    break;
                }
            }
        }

        int itensRestantes = inventarioContarPorTipo(
            inventario, ENTIDADE_ITEM
        );

        bool inventarioCheio = inventarioEstaCheio(inventario);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < inventarioTotal(inventario); i++) {
                Entidade *e = inventarioObter(inventario, i);

                if (e != NULL) {
                    entidadeDesenhar(e);
                }
            }

            DrawText(
                TextFormat("Vida: %d   Pontuacao: %d",
                           jogador->vida, pontuacao),
                10, 10, 22, DARKGRAY
            );

            DrawText(
                TextFormat("Entidades no inventario: %d",
                           inventarioTotal(inventario)),
                10, 36, 18, GRAY
            );

            DrawText(
                TextFormat("Itens restantes: %d", itensRestantes),
                10, 60, 18, DARKGREEN
            );

            if (inventarioCheio) {
                DrawText("AVISO: INVENTARIO CHEIO!",
                         10, 88, 20, RED);
            }

            DrawText(
                "Setas movem | ESPACO ataca | ESC sai",
                10, ALTURA_JANELA - 25, 16, GRAY
            );

        EndDrawing();
    }

    inventarioDestruir(inventario);
    CloseWindow();

    return 0;
}
