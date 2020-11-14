//
// Created by suprog on 14.11.2020.
//

#include "../headers/utils.h"

void filecpy(FILE *to, FILE *from) {
  int c;
  while ((c = getc(from)) != EOF)
    putc(c, to);
}
