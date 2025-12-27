#include <ctype.h>
#include <stdio.h>

void char_dump(const char *filename) {
  FILE *fp = fopen("data1.csv", "rb");
  if (fp == NULL) {
    printf("Dosya acilamadi.\n");
    return;
  }

  int c;
  while ((c = fgetc(fp)) != EOF) {

    if (c == '\n') {
      printf("\\n ");
    } else if (c == '\r') {
      printf("\\r ");
    } else if (c == '\t') {
      printf("\\t ");
    } else if (c == '\0') {
      printf("\\0 ");
    }

    else if (isprint(c)) {
      printf("%c  ", c);
    }

    else {
      printf("?  ");
    }
  }

  printf("\n"); // Sonunda temiz bir alt satıra geç
  fclose(fp);
}

int main() {
  // Test verisi oluştur: "AB,C" (satır sonu) "12"

  printf("Dosya Icerigi: ");
  char_dump("test_char.txt");

  return 0;
}
