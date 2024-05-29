#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "keyboard.h"
#include "screen.h"
#include "timer.h"

struct Inimigo {
    int x_inimigo;
    int y_inimigo;
    struct Inimigo *proximo;
};

struct Personagem {
    int x_personagem;
    int y_personagem;
};

void print_personagem(struct Personagem *personagem, int ch);
void print_inimigo(struct Inimigo *inimigo, struct Personagem *personagem);
void spawnar_inimigo(struct Inimigo **exercito);
void print_de_todos_os_inimigos(struct Inimigo *inimigo, struct Personagem *personagem);
void novo_local_inimigo_y(struct Inimigo *inimigo, struct Personagem *personagem);
void novo_local_inimigo_x(struct Inimigo *inimigo, struct Personagem *personagem);
bool checa_colisao(struct Personagem *personagem, struct Inimigo *inimigo);
bool checa_colisoes(struct Personagem *personagem, struct Inimigo *exercito);
void mostra_tempo_vivo(int tempo_vivo);

void print_personagem(struct Personagem *personagem, int ch) {
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(personagem->x_personagem, personagem->y_personagem);
    printf(" ");

    if (ch == 115 && personagem->y_personagem < 19) {
        personagem->y_personagem++;
    }
    if (ch == 119 && personagem->y_personagem > 2) {
        personagem->y_personagem--;
    }
    if (ch == 97 && personagem->x_personagem > 2) {
        personagem->x_personagem--;
    }
    if (ch == 100 && personagem->x_personagem < 70) {
        personagem->x_personagem++;
    }

    screenGotoxy(personagem->x_personagem, personagem->y_personagem);
    printf("x");
}

void print_inimigo(struct Inimigo *inimigo, struct Personagem *personagem) {

    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(inimigo->x_inimigo, inimigo->y_inimigo);
    printf(" ");

    novo_local_inimigo_y(inimigo, personagem);
    novo_local_inimigo_x(inimigo, personagem);

    screenGotoxy(inimigo->x_inimigo, inimigo->y_inimigo);
    printf("█");

}

void spawnar_inimigo(struct Inimigo **exercito) {
    struct Inimigo *novo_inimigo = malloc(sizeof(struct Inimigo));
    novo_inimigo->x_inimigo = 70;
    novo_inimigo->y_inimigo = 15;
    novo_inimigo->proximo = *exercito;
    *exercito = novo_inimigo;
}

void print_de_todos_os_inimigos(struct Inimigo *inimigo, struct Personagem *personagem) {
    while(inimigo != NULL){
        print_inimigo(inimigo, personagem);
        inimigo = inimigo->proximo;
    }
}

void novo_local_inimigo_y(struct Inimigo *inimigo, struct Personagem *personagem) {
    int y_inimigo_atual = inimigo->y_inimigo;
    int y_personagem_atual = personagem->y_personagem;

    if (y_inimigo_atual > y_personagem_atual) {
        inimigo->y_inimigo--;
    } else if (y_inimigo_atual < y_personagem_atual) {
        inimigo->y_inimigo++;
    }
}

void novo_local_inimigo_x(struct Inimigo *inimigo, struct Personagem *personagem) {
    int x_inimigo_atual = inimigo->x_inimigo;
    int x_personagem_atual = personagem->x_personagem;

    if (x_inimigo_atual > x_personagem_atual) {
        inimigo->x_inimigo--;
    } else if (x_inimigo_atual < x_personagem_atual) {
        inimigo->x_inimigo++;
    }


}

bool checa_colisao(struct Personagem *personagem, struct Inimigo *inimigo) {
    return personagem->x_personagem == inimigo->x_inimigo && personagem->y_personagem == inimigo->y_inimigo;
}

bool checa_colisoes(struct Personagem *personagem, struct Inimigo *exercito) {
    struct Inimigo *atual = exercito;

    while (atual) {
        if (checa_colisao(personagem, atual)) {
            return true;
        }
        atual = atual->proximo;
    }
    return false;
}

void mostra_tempo_vivo(int tempo_vivo) {
    screenClear();
    screenSetColor(WHITE, BLACK);
    screenGotoxy(10, 10);
    printf("Tempo vivo: %d segundos\n", tempo_vivo);
    screenGotoxy(10, 11);
    printf("Parabéns, agora entre para a história:");
    screenUpdate();

}

void salvar_tabela(int tempo_vivo) {
    char nome[100];
    screenGotoxy(10, 12);
    printf("Digite seu apelido: ");
    screenUpdate();

    fgets(nome, sizeof(nome), stdin);

    FILE *file = fopen("tabela.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %d\n", nome, tempo_vivo);
        fclose(file);
    }

}


void wipar_exercito(struct Inimigo **exercito){
    struct Inimigo *atual = *exercito;
    struct Inimigo *aux;
    while (atual != NULL){
        aux = atual ->proximo;
        free(atual);
        atual = aux;
    }
    *exercito = NULL;


}

int main() {

    static int ch = 0;
    struct Personagem personagem;
    personagem.x_personagem = 10;
    personagem.y_personagem = 10;
    struct Inimigo *exercito = NULL;
    time_t inicio, fim;

    int inimigo_contador = 0;
    int inimigo_intervalo = 2;
    int contador_do_spawn = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);

    print_personagem(&personagem, ch);
    spawnar_inimigo(&exercito);
    screenUpdate();

    time(&inicio);

    while (true) {
        if (keyhit()) {
            ch = readch();
            if (ch == 10) break;
            print_personagem(&personagem, ch);
            screenUpdate();
        }

        if (timerTimeOver() == 1) {
            if (inimigo_contador % inimigo_intervalo == 0) {
                print_de_todos_os_inimigos(exercito, &personagem);
                if (checa_colisoes(&personagem, exercito)) {
                    time(&fim);
                    int tempo_total_vivo = difftime(fim, inicio);
                    mostra_tempo_vivo(tempo_total_vivo);
                    salvar_tabela(tempo_total_vivo);
                    wipar_exercito(&exercito);
                    break;

                }
                screenUpdate();
            }
            if(contador_do_spawn >= 100){
                spawnar_inimigo(&exercito);
                contador_do_spawn = 0;
            }
            inimigo_contador++;
            contador_do_spawn++;
        }
    }



    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}