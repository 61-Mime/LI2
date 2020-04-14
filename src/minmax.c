/**
 * @file    minmax.c
 * @brief   Módulo que contém a implementação das funções que utilizam a eurística minmax
 */

#include "minmax.h"

CVAL jogadasValidas(ESTADO *e) {
  CVAL cr;
  int l = getultimaJogLinha(e);
  int c = getultimaJogColuna(e);
  int i = 0, l2 = l,c2;

  if(l2 == 1) l2++;

  for(l2 = l - 1;l2 <= l + 1 && l2 < 9;l2++) {
    for(c2 = c - 1;c2 <= c + 1;c2++)
      if(c2 >= 0 && c2 <=7 && getCasa(e, l2, c2) == VAZIO) {
        cr.coords[i].linha = l2;
        cr.coords[i].coluna = c2;
        i++;
      }
  }
  cr.validas = i;
  return cr;
}

ESTADO jogadaBot(ESTADO e,COORDENADA *c) {
  setCasa(&e,PRETA,getultimaJogLinha(&e),getultimaJogColuna(&e));
  setCasa(&e,BRANCA,c->linha, c->coluna);
  setUltimaJog(&e, c->linha, c->coluna);

  if(getjogAtual(&e) == 1)
    setJogAtual(&e, 1);
  else
    setJogAtual(&e, 2);

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
  int j = getjogAtual(&e),p;
  ESTADO a = jogadaBot(e,&c);
  int l = getultimaJogLinha(&e),cl = getultimaJogColuna(&e);

  p = isOver(&a);
  if(p != j && p)
    p = 1;
  else if(p == j)
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
      a = jogadaBot(e, &cr.coords[i]);
      if(!p || isOver(&a))
        pontos = avaliaJogada(e,  cr.coords[i]);
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
      a = jogadaBot(e, &cr.coords[i]);
      if(!p || isOver(&a))
        pontos = avaliaJogada(e,  cr.coords[i]) - 7;
      else
        pontos = minmax(jogadasValidas(&a),a,1,p-1);

      if(pontos < min)
        min = pontos;
    }
    pontos = min;
  }
  return pontos;
}

COORDENADA bot(ESTADO *e) {
  CVAL cr;
  COORDENADA c;
  int r = 1, t;
  int best = -100,curr,p;
  ESTADO a;

  cr = jogadasValidas(e);

  for(int i = 0; i < cr.validas && r;i++) {
    t = isOver(&a);
    if(t == getjogAtual(e))
      return cr.coords[i];
    else if (t != 0 || getnumJogadas(e) < 5)
      curr = avaliaJogada(*e,cr.coords[i]);
    else {
      a = jogadaBot(*e,&cr.coords[i]);
      curr = minmax(jogadasValidas(&a),a,0,3);
    }

    if(curr > best || (curr == best && avaliaJogada(*e,  cr.coords[i]) > p)) {
      best = curr;
      c =   cr.coords[i];
      p = avaliaJogada(*e,  cr.coords[i]);
    }
    //printf("%d%c%d\n", curr,'a' +   cr.coords[i].coluna,  cr.coords[i].linha);
  }
  return c;
}