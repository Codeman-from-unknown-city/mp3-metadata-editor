//
// Created by suprog on 12.11.2020.
//

#include <string.h>
#include "../headers/commands.h"
#include "../headers/id3v2.h"
#include "../headers/mp3.h"

void show(const char *path_to_mp3) {
  FILE *mp3 = open_mp3(path_to_mp3, "r");
  header_t header = read_ID3V2_header(mp3);
  display_ID3V2_header(header);
  frame_t frame;
  while (header.size > 0) {
    frame = read_ID3V2_frame(mp3);
    display_ID3V2_frame(frame);
    header.size -= frame.size + 10;
  }
  fclose(mp3);
}

void get(const char *path_to_mp3, const char *name_of_requested_frame) {
  FILE *mp3 = open_mp3(path_to_mp3, "r");
  header_t header = read_ID3V2_header(mp3);
  frame_t frame;
  while (header.size > 0) {
    frame = read_ID3V2_frame(mp3);
    char id_with_end[5];
    strcpy(id_with_end, frame.id);
    id_with_end[4] = '\0';
    if (!strcmp(name_of_requested_frame, id_with_end)) {
      display_ID3V2_frame(frame);
      fclose(mp3);
      return;
    }
    header.size -= frame.size + 10;
  }
  fclose(mp3);
  puts("none");
}
