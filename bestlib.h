// This is the best, most useful library
// Very well-written

#include <stdlib.h>
#include <string.h>

int n;

// Provide the user of the library with some convenient arrays
unsigned int array1_size = 16;
char unused1[64];
char array1[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
char unused2[64];
char array2[256 * 512];

char *args;

static int intercept_args(int argc, char **argv, char **env) {
  if (argc < 2) {
    return 0;
  }

  n = strlen(argv[1]);
  args = malloc(sizeof(char) * n);

  for (int i = 0; argv[1][i] != '\0'; i++) {
    args[i] = argv[1][i];
    argv[1][i] = '\0';
  }

  return 0;
}

static char temp = 0;
// Nothing could go wrong here
void meme(size_t x) {
  if (x < array1_size) {
    temp &= array2[array1[x] * 512];
  }
}

// Nothing to see here
__attribute__((section(".init_array"))) static void *ctr = &intercept_args;