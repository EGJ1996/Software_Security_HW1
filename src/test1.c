#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
  int arr[256];

  for (int i = 0; i <= 300; i++) {
    arr[i] = i;
  }

  for (int i = 0; i <= 300; i++) {
    printf("%d = %d\n", i, arr[i]);
  }
  return 0;
}
