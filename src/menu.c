#include "headers.h"

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

void execute(char* buffer, ESTADO* e, COORDENADA* c)
{
  char* s = strsep(&buffer, " ");
  char *line, *col;

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

  else if(strcmp(s, "movs") == 0) {
    printf("%s\n", s);
  }

  else if(strcmp(s, "jog") == 0) {
    printf("%s\n", s);
  }

  else if(strcmp(s, "pos") == 0) {
    printf("%s\n", s);
  }

  else if(toupper(s[0]) == 'Q' && s[1] == '\n') {
    printf("A sair do jogo\n");
  }

  else {
    printf("Comando Inválido\n");
  }

}