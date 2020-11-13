//
// Created by suprog on 11.11.2020.
//

#include "../headers/mp3.h"
#include "../headers/error.h"

FILE *open_mp3(const char *mp3_name, const char *mode) {
  FILE *mp3 = fopen(mp3_name, mode);
  if (!mp3)
    error(1, "can't open mp3 file");
  return mp3;
}
