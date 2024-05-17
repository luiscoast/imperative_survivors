#include <string.h>
#include <stdio.h>

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
    printf("     \n     \n     \n     \n     \n");//print que aoaga o personagem

    if (ch == 119) {
        personagem->y_personagem++;
    }
    if (ch == 115){
        personagem->y_personagem--;
    }
    if (ch == 97){
        personagem->x_personagem--;
    }
    if (ch == 100){
        personagem->x_personagem++;
    }


    screenGotoxy(x, y);
    printf("  █  \n█████\n ███ \n ███ \n █ █ \n");//Print do personagem aonde ele vai ficar
}

void novo_local_personagem(struct Personagem *personagem, int ch) {

    if (ch == 119) {
        personagem->y_personagem++;
    }
    if (ch == 115){
        personagem->y_personagem--;
    }
    if (ch == 97){
        personagem->x_personagem--;
    }
    if (ch == 100){
        personagem->x_personagem++;
    }
}

void print_inimigo(struct Inimigo *inimigo, struct Personagem *personagem) {
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(inimigo->x_inimigo, inimigo->y_inimigo);
    printf("     \n     \n     \n     \n     \n");
    void novo_local_inimigo(struct Inimigo *inimigo, struct Personagem *personagem);
    screenGotoxy(inimigo->x_inimigo, inimigo->y_inimigo);
    printf("  █  \n█████\n ███ \n ███ \n █ █ \n");
}

void print_de_todos_os_inimigos(struct Inimigo **exercito, struct Personagem *personagem){
    struct Inimigo *aux, *inimigo = *exercito;
    if (*exercito == NULL){
        return;
    }
    aux = *exercito;
    while(aux->proximo){
        print_inimigo(aux, personagem);
        aux = aux->proximo;
    }
    return;
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
        } else {
            x_inimigo_proximo = x_inimigo_atual;
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
        } else {
            x_inimigo_proximo = x_inimigo_atual + 1;
            y_inimigo_proximo = y_inimigo_atual;
        }
    }
    inimigo->x_inimigo = x_inimigo_proximo;
    inimigo->y_inimigo = y_inimigo_proximo;
}

int main() {
    static int ch = 0;
    struct Personagem personagem;
    personagem.x_personagem = 1;
    personagem.y_personagem = 1;

    screenInit(1);
    keyboardInit();
    timerInit(50);

    screenUpdate();

    while (ch != 10) // enter
    {
        // Handle user input
        if (keyhit()) {
            ch = readch();
            printKey(ch);
            screenUpdate();
        }

        if (timerTimeOver() == 1) {
            print_de_todos_os_inimigos(Inimigo **exercito, Personagem *personagem);
            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}