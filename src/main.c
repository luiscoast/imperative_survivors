#include <string.h>

#include "keyboard.h"
#include "screen.h"
#include "timer.h"

#define MAX_CORPO_LENGTH 30

struct Inimigo {
  int x_inimigo;
  int y_inimigo;
  char corpo[MAX_CORPO_LENGTH];
  struct Inimigo *proximo;
};

struct Personagem {
  int x_personagem;
  int y_personagem;
  char corpo[MAX_CORPO_LENGTH];
};

struct Proxima_posicao {
    int x_proximo;
    int y_proximo;
};

void print_inimigo(struct Inimigo *inimigo, struct Personagem *personagem) {
  screenSetColor(CYAN, DARKGRAY);
  screenGotoxy(x, y);
  printf("     \n     \n     \n     \n     \n");
  x = nextX;
  y = nextY;
  screenGotoxy(x, y);
  printf("Hello World");
}

void print_personagem(struct Inimigo *inimigo, struct Personagem *personagem) {
  screenSetColor(CYAN, DARKGRAY);
  screenGotoxy(x, y);
  printf("           ");
  x = nextX;
  y = nextY;
  screenGotoxy(x, y);
  printf("Hello World");
}

struct Proxima_posicao novo_local(struct Inimigo *inimigo, struct Personagem *personagem) {
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

    struct Proxima_posicao proxima_posicao;
    proxima_posicao.x_proximo = x_inimigo_proximo;
    proxima_posicao.y_proximo = y_inimigo_proximo;

    return proxima_posicao;
}

int main() {
  static int ch = 0;

  screenInit(1);
  keyboardInit();
  timerInit(50);

  print_inimigo(x, y);
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
      int newX = x + incX;
      if (newX >= (MAXX - strlen("Hello World") - 1) || newX <= MINX + 1)
        incX = -incX;
      int newY = y + incY;
      if (newY >= MAXY - 1 || newY <= MINY + 1)
        incY = -incY;

      printKey(ch);
      print_inimigo(newX, newY);

      screenUpdate();
    }
  }

  keyboardDestroy();
  screenDestroy();
  timerDestroy();

  return 0;
}