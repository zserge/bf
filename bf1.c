#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

/*
 * Naive unoptimized interpreter
 */
static void bf(const char *c, unsigned char *m) {
  while (*c) {
    switch (*c++) {
    case '+': (*m)++; break;
    case '-': (*m)--; break;
    case '<': m--; break;
    case '>': m++; break;
    case ',': *m = getchar(); break;
    case '.': putchar(*m); break;
    case ']': return;
    case '[':
      while (*m) bf(c, m);
      for (int loop = 1; *c && loop; c++)
	loop += (*c == '[') - (*c == ']');
      break;
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }
  int fd = open(argv[1], O_RDONLY);
  int len = lseek(fd, 0, SEEK_END);
  void *code = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
  unsigned char mem[30000] = {0};
  bf(code, mem);
  return 0;
}
