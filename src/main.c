#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

void print_personagem( struct Personagem *personagem, int ch) {
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(personagem->x_personagem, personagem->y_personagem);
    printf(" ");//print que aoaga o personagem

    if (ch == 115) {
        personagem->y_personagem++;
    }
    if (ch == 119){
        personagem->y_personagem--;
    }
    if (ch == 97){
        personagem->x_personagem--;
    }
    if (ch == 100){
        personagem->x_personagem++;
    }

    screenGotoxy(personagem->x_personagem, personagem->y_personagem);
    printf("x");//Print do personagem aonde ele vai ficar
}


void print_inimigo(struct Inimigo *inimigo, struct Personagem *personagem) {
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(inimigo->x_inimigo, inimigo->y_inimigo);
    printf("  \n  ");
    void novo_local_inimigo(struct Inimigo *inimigo, struct Personagem *personagem);
    screenGotoxy(inimigo->x_inimigo, inimigo->y_inimigo);
    printf("██\n██");
}

void spawnar_inimigo(struct Inimigo **exercito){
    struct Inimigo *novo_inimigo = malloc(sizeof(struct Inimigo));
    novo_inimigo->x_inimigo = 70;
    novo_inimigo->y_inimigo = 20;
    novo_inimigo->proximo = *exercito;
    *exercito = novo_inimigo;
}

void print_de_todos_os_inimigos(struct Inimigo *inimigo, struct Personagem *personagem){
    while(inimigo){
        print_inimigo(inimigo, personagem);
        inimigo = inimigo->proximo;
    }
}


void novo_local_inimigo(struct Inimigo *inimigo, struct Personagem *personagem) {
    int x_inimigo_proximo, y_inimigo_proximo;
    int x_inimigo_atual = inimigo->x_inimigo;
    int y_inimigo_atual = inimigo->y_inimigo;
    int x_personagem_atual = personagem->x_personagem;
    int y_personagem_atual = personagem->y_personagem;

    if (x_inimigo_atual > x_personagem_atual) {
        x_inimigo_proximo = x_inimigo_atual - 1;
    } else if (x_inimigo_atual < x_personagem_atual) {
        x_inimigo_proximo = x_inimigo_atual + 1;
    } else {
        if (y_inimigo_atual > y_personagem_atual) {
            y_inimigo_proximo = y_inimigo_atual - 1;
        } else if (y_inimigo_atual < y_personagem_atual) {
            y_inimigo_proximo = y_inimigo_atual + 1;
        }
    }

    if (y_inimigo_atual > y_personagem_atual) {
        y_inimigo_proximo = y_inimigo_atual - 1;
    } else if (y_inimigo_atual < y_personagem_atual) {
        y_inimigo_proximo = y_inimigo_atual + 1;
    } else {
        if (x_inimigo_atual > x_personagem_atual) {
            x_inimigo_proximo = x_inimigo_atual - 1;
        } else if (x_inimigo_atual < x_personagem_atual) {
            x_inimigo_proximo = x_inimigo_atual + 1;
        }
    }
    inimigo->x_inimigo = x_inimigo_proximo;
    inimigo->y_inimigo = y_inimigo_proximo;
}

int main() {
    static int ch = 0;
    struct Personagem personagem;
    personagem.x_personagem = 10;
    personagem.y_personagem = 10;
    struct Inimigo *exercito = NULL;

    screenInit(1);
    keyboardInit();
    timerInit(500);

    print_personagem( &personagem, ch);
    spawnar_inimigo(&exercito);
    screenUpdate();
    while (ch != 10) // enter
    {
        if (keyhit())
        {
            ch = readch();
            print_personagem(&personagem, ch);
            screenUpdate();
        }

        if (timerTimeOver() == 1) {
            print_de_todos_os_inimigos(exercito, &personagem);
            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}