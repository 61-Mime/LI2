#include "data.h"
#include "files.h"
#include "game.h"

// Função que imprime o Estado
void printa(ESTADO *e)
{
    int i, j;
    char c = ' ';

    printf("\n  a b c d e f g h\n");

    for (i=0; i<8; i++) {
      printf("%d ", 8-i);

      for (j=0; j<8; j++) {
        switch(e->tab[i][j]) {
          case PRETA:
            c = '#';
            break;

          case BRANCA:
            c='*';
            break;

          case VAZIO:
            if(i == 7 && j == 0) c = '1';
            else if  (i == 0 && j == 7) c = '2';
            else c = '.';
            break;

          default:
            break;
        }
        printf("%c ", c);
      }
      printf("\n");
    }
    printf("Jogador: %d\n", e->jogador_atual);
}

// Função que mostra o menu de comandos
void menu()
{
  printf("\nSelecione a sua opção:\n");
  printf("- coordenada <coluna> <linha>\n");
  printf("- gr <nome>\n");
  printf("- ler <nome>\n");
  printf("- movs\n");
  printf("- jog\n");
  printf("- pos <numero_da_jogada>\n");
  printf("- Q\n");
  printf("\nIntroduza o seu comando: ");
}

// Intrepertador
void execute(ESTADO* e, COORDENADA* c)
{
  char *buffer = NULL;
  buffer = malloc(MAX*sizeof(char));
  char* s = NULL;
  char *line = NULL, *col = NULL;
  buffer[0] = 'a';

  printa(e); // imprime o estado inicial

  while(1)
  {
    menu();
    fgets(buffer, MAX, stdin);

    // Intrepertação do comando
    if(toupper(buffer[0])=='Q' || buffer[0]=='j' || buffer[0]=='m')
      s = strsep(&buffer, "\n");

    else
      s=strsep(&buffer, " ");

    // Execução do comando
    if(strcmp(s, "coordenada") == 0) {
      col = strsep(&buffer, " ");
      line = strsep(&buffer, "\n");

      place(e, c, col, line);
    }

    else if(strcmp(s, "gr") == 0) {
      s = strsep(&buffer, "\n");

      output(e,s);
    }

    else if(strcmp(s, "ler") == 0) {
      s = strsep(&buffer, "\n");

      input(e, s);
    }

    else if(strcmp(s, "movs") == 0)
      movimentos(e);

    else if(strcmp(s, "jog") == 0) {
      printf("%s\n", s);
    }

    else if(strcmp(s, "pos") == 0) {
      printf("%s\n", s);
    }

    else if((strcmp(s, "q") == 0) || (strcmp(s, "Q") == 0)) {
      printf("A Sair do Jogo!\n");
      return;
    }

    else
      printf("Comando Inválido\n");

    // O teste do jogo acabar tem de estar fora, porque se não só na jogada a seguir é que valida

    if (isOver(e)) {
      winner(e);
      return;
    }
  }
}