#include <stdio.h>
#include <stdlib.h>

void load_obj_file_data(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    return;
  }

  char ch;
  while ((ch = fgetc(file)) != EOF) {
    putchar(ch);
  }

  fclose(file);
}

int main() {
  const char *filename = "../rifle_new.obj";
  load_obj_file_data(filename);
  return 0;
}
