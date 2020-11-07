#include <stdio.h>
#include <string.h>
#include <libtcc.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }
  FILE *f = fopen(argv[1], "r");
  if (!f) {
    perror("fopen");
    return 1;
  }

  TCCState *tcc = tcc_new();
  tcc_set_options(tcc, "-nostdlib");
  tcc_add_symbol(tcc, "p", putchar);
  tcc_add_symbol(tcc, "g", getchar);

  int c;
  char bfcode[100000] = "int g(); int p(int); void bf(unsigned char *m) {";
  while ((c = fgetc(f)) != EOF) {
    switch (c) {
      case '+': strcat(bfcode, "++*m;"); break;
      case '-': strcat(bfcode, "--*m;"); break;
      case '<': strcat(bfcode, "--m;"); break;
      case '>': strcat(bfcode, "++m;"); break;
      case '.': strcat(bfcode, "p(*m);"); break;
      case ',': strcat(bfcode, "*m=g();"); break;
      case '[': strcat(bfcode, "while(*m){"); break;
      case ']': strcat(bfcode, "}"); break;
    }
  }
  strcat(bfcode, "}");

  tcc_compile_string(tcc, bfcode);
  tcc_relocate(tcc, TCC_RELOCATE_AUTO);
  void (*bf)(unsigned char *) = tcc_get_symbol(tcc, "bf");

  unsigned char mem[30000] = {0};
  bf(mem);

  tcc_delete(tcc);
}
