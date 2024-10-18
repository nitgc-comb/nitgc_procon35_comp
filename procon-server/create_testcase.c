#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
  int tate, yoko;
  printf("tate yoko:");
  scanf("%d %d", &tate, &yoko);

  int start[256][256], goal[256][256];

  // generate random seed
  srand((unsigned int)time(NULL));

  for(int i = 0; i < tate; i++){
    for(int j = 0; j < yoko; j++) {
      start[i][j] = rand() % 4;
      goal[i][j] = start[i][j];
    }
  }

  for(int i = 0; i < 100000; i++) {
    int x1,x2,y1,y2;
    x1 = rand() % yoko;
    x2 = rand() % yoko;
    y1 = rand() % tate;
    y2 = rand() % tate;

    int w = goal[y1][x1];
    goal[y1][x1] = goal[y2][x2];
    goal[y2][x2] = w;

  }


  // create json file
  char filename[256];
  printf("json filename:");
  scanf("%s", filename);

  strcat(filename, ".json");

  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
      fprintf(stderr, "ファイルを開けませんでした\n");
      return 1;
  }

  // JSON形式のテキストを手動で書き出す
  fprintf(fp, "{\n");
  fprintf(fp, "  \"teams\": [\n");
  fprintf(fp, "    \"token1\",\n");
  fprintf(fp, "    \"token2\",\n");
  fprintf(fp, "    \"token3\"\n");
  fprintf(fp, "  ],\n");
  fprintf(fp, "  \"duration\": 86400,\n");
  fprintf(fp, "  \"problem\": {\n");
  fprintf(fp, "    \"board\": {\n");
  fprintf(fp, "      \"width\":%d,\n",yoko);
  fprintf(fp, "      \"height\": %d,\n",tate);
  fprintf(fp, "      \"start\": [\n");
  // startboard
  for(int i = 0; i < tate; i++) {
    fprintf(fp, "        \"");
    for(int j = 0; j < yoko; j++) {
      fprintf(fp, "%c", start[i][j] + '0');
    }
    fprintf(fp, "\"");
    if(i != tate-1) {
      fprintf(fp, ",");
    }
    fprintf(fp, "\n");
  }
  fprintf(fp, "      ],\n");
  fprintf(fp, "      \"goal\": [\n");
  // goalboard
  for(int i = 0; i < tate; i++) {
    fprintf(fp, "        \"");
    for(int j = 0; j < yoko; j++) {
      fprintf(fp, "%c", goal[i][j] + '0');
    }
    fprintf(fp, "\"");
    if(i != tate-1) {
      fprintf(fp, ",");
    }
    fprintf(fp, "\n");
  }
  fprintf(fp, "      ]\n");
  fprintf(fp, "    },\n");
  fprintf(fp, "    \"general\": {\n");
  fprintf(fp, "      \"n\": 2,\n");
  fprintf(fp, "      \"patterns\": [\n");
  fprintf(fp, "        {\n");
  fprintf(fp, "          \"p\": 25,\n");
  fprintf(fp, "          \"width\": 4,\n");
  fprintf(fp, "          \"height\": 2,\n");
  fprintf(fp, "          \"cells\": [\n");
  fprintf(fp, "            \"0111\",\n");
  fprintf(fp, "            \"1001\"\n");
  fprintf(fp, "          ]\n");
  fprintf(fp, "        },\n");
  fprintf(fp, "        {\n");
  fprintf(fp, "          \"p\": 26,\n");
  fprintf(fp, "          \"width\": 2,\n");
  fprintf(fp, "          \"height\": 2,\n");
  fprintf(fp, "          \"cells\": [\n");
  fprintf(fp, "            \"10\",\n");
  fprintf(fp, "            \"01\"\n");
  fprintf(fp, "          ]\n");
  fprintf(fp, "        }\n");
  fprintf(fp, "      ]\n");
  fprintf(fp, "    }\n");
  fprintf(fp, "  }\n");
  fprintf(fp, "}\n");


  // ファイルを閉じる
  fclose(fp);

  printf("start board:\n");
  for(int i = 0; i < tate; i++) {
    for(int j = 0; j < yoko; j++) {
      printf("%d", start[i][j]);
    }
    printf("\n");
  }
  printf("goal board:\n");
  for(int i = 0; i < tate; i++) {
    for(int j = 0; j < yoko; j++) {
      printf("%d", goal[i][j]);
    }
    printf("\n");
  }



  printf("created\n");
}