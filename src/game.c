#include "data.h"
#include "interface.h"
#include "game.h"

int toCord(COORDENADA* c, char* col, char* line)
{
  if(col[1]!='\0' || line[1]!='\0') {
    printf("Argumentos inválidos\n");
    return 0;
  }

  c->coluna = col[0] - 'a';
  c->linha = line[0] - '0';

  return 1;
}

int isValid(ESTADO* e, int col, int line)
{
  if (col < 0 || col > 7 || line < 1 || line > 8) {
    printf("A posição não faz parte da grelha\n");
    return -1;
  }
  int l = e->ultima_jogada.linha;
  int c = e->ultima_jogada.coluna;

  if(e->tab[8 - line][col] == VAZIO) {
    if((l == line && (col == c + 1 || col == c - 1))||
    (c == col && (line == l + 1 || line == l - 1))||
    (line == l + 1 && (col == c - 1 || col == c + 1))||
    (line == l - 1 && (col == c - 1 || col == c + 1)))
      return 0;
    else {
      printf("A posição %c %d não é adjacente %c %d\n", col + 'a',line,c+'a',l);
    }
  }
  else
    printf("A posição %c %d é inválida\n", col + 'a',line);

  return -1;
}

void place(ESTADO* e, COORDENADA* c)
{
  if(!(isValid(e, c->coluna, c->linha))) {

    e->tab[8 - e->ultima_jogada.linha][e->ultima_jogada.coluna] = PRETA;
    e->tab[8 - c->linha][c->coluna] = BRANCA;
    e->ultima_jogada.linha = c->linha;
    e->ultima_jogada.coluna = c->coluna;

    if(e->jogador_atual == 1) {
      e->jogador_atual = 2;
      e->num_jogadas++;
      e->jogadas[e->num_jogadas-1].jogador1.linha = c -> linha;
      e->jogadas[e->num_jogadas-1].jogador1.coluna = c -> coluna;
    }

    else {
      e->jogador_atual = 1;
      e->jogadas[e->num_jogadas-1].jogador2.linha = c -> linha;
      e->jogadas[e->num_jogadas-1].jogador2.coluna = c -> coluna;
    }
  }
}

void movimentos(ESTADO* e)
{
  int i;

  printf("\nMovimentos:\n");

  if(e->num_jogadas == 0)
    printf("Não existem jogadas\n");

  for(i=0; i<e->num_jogadas; i++) {

    if(i < 10)
      printf("0%d: ",i);

    else
      printf("%d: ",i);

    if(i == e->num_jogadas && e->jogador_atual == 2) {
      printf("%c%d\n",e->ultima_jogada.coluna + 'a',e->ultima_jogada.linha);
    }

    else {
      printf("%c%d %c%d\n",
      e->jogadas[i-1].jogador1.coluna + 'a',e->jogadas[i-1].jogador1.linha,
      e->jogadas[i-1].jogador2.coluna + 'a',e->jogadas[i-1].jogador2.linha);
    }
  }
}

void posicao(ESTADO* e, char* pos)
{
  int i, jog;
  ESTADO* aux = malloc(sizeof(ESTADO));

  gamestart(aux);

  if((jog = atoi(pos)) == 0)
    printf("Argumento inválido\n");

  if(jog >= e->num_jogadas)
    printf("A jogada %d não existe\n", jog);

  for(i=0; i<jog; i++)
  {
    place(aux, &(e->jogadas[i].jogador1));
    place(aux, &(e->jogadas[i].jogador2));
  }

  printa(aux);
}

int isOver(ESTADO* e)
{
  int c = e->ultima_jogada.coluna;
  int l = e->ultima_jogada.linha;

  if (e->tab[7][0] == BRANCA)
    return 1;

  else if (e->tab[0][7] == BRANCA)
    return 1;

  else if (l == 8 && c == 0) {
    if (e->tab[1][c+1] == PRETA && e->tab[1][c] == PRETA && e->tab[0][c+1] == PRETA)
      return 1;
  }

  else if (l==1 && c ==7) {
    if (e->tab[6][c-1] == PRETA && e->tab[6][c] == PRETA && e->tab[7][c-1] == PRETA)
      return 1;
  }

  else if (l == 8) {
    if ((e->tab[0][c+1] == PRETA || c+1 == 7) && e->tab[0][c-1] == PRETA
    && e->tab[1][c+1] == PRETA
    && e->tab[1][c] == PRETA && e->tab[1][c-1] == PRETA)
      return 1;
  }

  else if (l == 1) {
    if (e->tab[7][c+1] == PRETA && (e->tab[7][c-1] == PRETA || c-1 == 0)
    && e->tab[6][c+1] == PRETA
    && e->tab[6][c] == PRETA && e->tab[6][c-1] == PRETA)
      return 1;
  }

  else if (c == 0) {
    if (e->tab[8-l-1][c] == PRETA && (e->tab[8-l+1][c] == PRETA || 8-l+1 == 7)
    && e->tab[8-l-1][c+1] == PRETA
    && e->tab[8-l][c+1] == PRETA && e->tab[8-l+1][c+1] == PRETA)
      return 1;
  }

  else if (c == 7) {
    if (e->tab[8-l+1][c] == PRETA && (e->tab[8-l-1][c] == PRETA || ((8-l-1) == 0))
    && e->tab[8-l-1][c-1] == PRETA
    && e->tab[8-l][c-1] == PRETA && e->tab[8-l+1][c-1] == PRETA)
      return 1;
  }

  else if
    ((e->tab[8-l-1][c] == PRETA
    && (e->tab[8-l-1][c+1] == PRETA || (8-l-1 == 0 && c+1 == 7))
    && e->tab[8-l][c+1] == PRETA
    && e->tab[8-l-1][c] == PRETA
    && e->tab[8-l+1][c+1] == PRETA
    && e->tab[8-l+1][c] == PRETA
    && (e->tab[8-l+1][c-1] == PRETA || (8-l+1 == 7 && c-1 == 0))
    && e->tab[8-l][c-1] == PRETA
    && e->tab[8-l-1][c-1] == PRETA))
      return 1;

  return 0;
}

void winner(ESTADO* e)
{
  int c = e->jogador_atual;

  if(e->tab[7][0] == BRANCA)
    c = 1;

  else if(e->tab[0][7] == BRANCA)
    c = 2;

  printf("\nO vencedor é o jogador %d\n", c);
}



CVAL jogadasValidas(ESTADO *e)
{
  CVAL cr;
  int l = e -> ultima_jogada.linha,l2 = l;
  int c = e -> ultima_jogada.coluna;
  int i = 0;

  if(l2 == 1) l2++;

  for(l2 = l - 1;l2 <= l + 1 && l2 < 9;l2++) {
    for(int c2 = c - 1;c2 <= c + 1;c2++)
      if(c2 >= 0 && c2 <=7 && e->tab[8 - l2][c2] == VAZIO) {
        cr.coords[i].linha = l2;
        cr.coords[i].coluna = c2;
        i++;
      }
  }
  cr.validas = i;
  return cr;
}

ESTADO jogadaBot(ESTADO e,COORDENADA *c) {
  e.tab[8 - e.ultima_jogada.linha][e.ultima_jogada.coluna] = PRETA;
  e.tab[8 - c->linha][c->coluna] = BRANCA;
  e.ultima_jogada.linha = c->linha;
  e.ultima_jogada.coluna = c->coluna;

  if(e.jogador_atual == 1)
    e.jogador_atual = 2;
  else
    e.jogador_atual = 1;

  return e;
}

int pertoFim(COORDENADA c,int jogador) {
  if(((c.linha == 8 && c.coluna == 6) || (c.linha == 7 && c.coluna == 6) ||
    (c.linha == 7 && c.coluna == 7)) && jogador == 1)
    return 1;

  if(((c.linha == 2 && c.coluna == 0) || (c.linha == 2 && c.coluna == 1) ||
    (c.linha == 1 && c.coluna == 1)) && jogador == 2)
    return 1;

  return 0;
}

int avaliaJogada(ESTADO e,COORDENADA c) {
  int j = e.jogador_atual,p;
  ESTADO a = jogadaBot(e,&c);
  int l = e.ultima_jogada.linha;
  int cl = e.ultima_jogada.coluna;

  if((c.linha == 8 && c.coluna == 7 && j == 1) ||
    (c.linha == 1 && c.coluna == 0 && j == 2))
    p = 1;
  else if(isOver(&a))
          p = 8;
  else if((pertoFim(c,j)))
          p = 2;
  else if((j == 2 && c.linha == l + 1 && c.coluna == cl + 1) ||
          (j == 1 && c.linha == l - 1 && c.coluna == cl - 1))
          p = 7;
  else if((l == c.linha) && ((j == 2 && c.coluna == cl + 1) ||
          (j == 1 && c.coluna == cl - 1)))
          p = 5;
  else if((cl == c.coluna) && ((j == 2 && c.linha == l + 1) ||
          (j == 1 && c.linha == l - 1)))
          p = 6;
  else if((c.linha == l + 1 && c.coluna == cl - 1) ||
          (c.linha == l - 1 && c.coluna == cl + 1))
          p = 4;
  else p = 3;

  return p;
  }

int minmax(CVAL cr,ESTADO e,int isMax,int p) {
  int pontos,max,min;
  ESTADO a;

  if (isMax) {
    max = -100;
    for(int i = 0;i < cr.validas;i++) {
      a = jogadaBot(e,&cr.coords[i]);
      if(!p || isOver(&a))
        pontos = avaliaJogada(e,cr.coords[i]);
      else
        pontos = minmax(jogadasValidas(&a),a,0,p-1);

      if(pontos > max)
        max = pontos;
      //printf("-%d%c%d \n", pontos,'a' + cr.coords[i].coluna,cr.coords[i].linha);
    }
    pontos = max;
  }
  else {
    min = 100;
    for(int i = 0;i < cr.validas;i++) {
      a = jogadaBot(e,&cr.coords[i]);
      if(!p || isOver(&a))
        pontos = avaliaJogada(e,cr.coords[i]);
      else
        pontos = minmax(jogadasValidas(&a),a,1,p-1);

      if(pontos < min)
        min = pontos;
    }
    pontos = min;
  }
  return pontos;
}

COORDENADA Bot(ESTADO *e) {
  CVAL cr;
  COORDENADA c;
  int r = 1;
  int best = -100,curr;
  ESTADO a;

  cr = jogadasValidas(e);

  for(int i = 0; i < cr.validas && r;i++) {
    a = jogadaBot(*e,&cr.coords[i]);
    curr = minmax(jogadasValidas(&a),a,0,1);
    //printf(",%d%c%d ", curr,'a' + cr.coords[i].coluna,cr.coords[i].linha);
    if(curr > best) {
      best = curr;
      c = cr.coords[i];
    }
  }
  return c;
}
