#include <stdio.h>

int main() {
  int tate, yoko;
  int unmatchCount = 0;
  printf("height width:\n");
  scanf("%d %d", &tate, &yoko);
  char s[257][257], t[257][257];
  //copy the goal board in s[h][w]
  printf("paste goal board:");
  for(int i = 0; i < tate; i++) {
    scanf("%s", s[i]);
  }

  printf("paste board:");
  for(int i = 0; i < tate; i++){
    scanf("%s", t[i]);
  }

  for(int i = 0; i < tate; i++) {
    for(int j = 0; j < yoko; j++) {
      if(s[i][j] != t[i][j]) {
        unmatchCount++;
        printf("(%d, %d) = %d, %d unmatched\n",i , j, s[i][j], t[i][j]);
      }
    }
  }

  printf("unmatchCount: %d\n", unmatchCount);
}