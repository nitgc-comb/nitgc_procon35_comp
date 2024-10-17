#include <stdio.h>

int main() {
  int tate, yoko;
  int unmatchCount = 0;
  printf("height width:\n");
  scanf("%d %d", &tate, &yoko);
  char s[256][260], t[256][256];
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
        printf("y=%d, x=%d unmatched\n",i , j);
      }
    }
  }

  printf("unmatchCount: %d\n", unmatchCount);
}