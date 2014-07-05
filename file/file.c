#include<stdlib.h>
#include<stdio.h>

int main(int argc, char** argv) {
  const char* file="file_test.txt";
  FILE *fp=fopen(file, "w");
  if(fp) {
    fprintf(fp, "It is a test\n");
  } else {
    fprintf(stderr, "cannot open file to write\n");
    exit(EXIT_FAILURE);
  }
  fclose(fp);
  return 0;
}
