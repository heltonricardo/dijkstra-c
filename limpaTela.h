#pragma once

#include <stdio.h>

#if defined _WIN32 || defined _WIN64
#include <windows.h>
void position(int linha, int coluna) {
   if (1 <= coluna && coluna <= 80 && 1 <= linha && linha <= 24) {
      HANDLE tela;
      COORD pos;
      tela = GetStdHandle(STD_OUTPUT_HANDLE);
      pos.X = coluna - 1;
      pos.Y = linha - 1;
      SetConsoleCursorPosition(tela, pos);
   }
}
void limparTela(void) {
   HANDLE tela;
   DWORD escrita = 0;
   COORD pos;
   tela = GetStdHandle(STD_OUTPUT_HANDLE);
   pos.X = 0;
   pos.Y = 0;
   FillConsoleOutputCharacter(tela, 32, 100 * 100, pos, &escrita);
   position(1, 1);
}
#else
void position(int linha, int coluna) {
   if (1 <= coluna && coluna <= 80 && 1 <= linha && linha <= 24)
      printf("\033[%d;%dH", linha, coluna);
}
void limparTela(void) {
   printf("\033[2J");
   position(1, 1);
}
#endif
