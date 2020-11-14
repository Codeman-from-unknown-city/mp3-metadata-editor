//
// Created by suprog on 12.11.2020.
//

#include <string.h>
#include "../headers/error.h"
#include "../headers/commands.h"
#include "../headers/id3v2.h"
#include "../headers/mp3.h"
#include "../headers/utils.h"

void show(const char *path_to_mp3) {
  FILE *mp3 = open_mp3(path_to_mp3, "r");
  header_t header = read_ID3V2_header(mp3);
  display_ID3V2_header(header);
  frame_t frame;
  while (header.size > 0) {
    frame = read_ID3V2_frame(mp3);
    display_ID3V2_frame(&frame);
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
      display_ID3V2_frame(&frame);
      fclose(mp3);
      return;
    }
    header.size -= frame.size + 10;
  }
  fclose(mp3);
  puts("none");
}

void set(const char *path_to_mp3, const char *frame_name, char *frame_body) {
  FILE *tmp_file = fopen("tmp.mp3", "w+");
  if (!tmp_file)
    error(1, "can't create temporary file");
  FILE *mp3 = open_mp3(path_to_mp3, "r");
  frame_t frame;
  header_t header = read_ID3V2_header(mp3);
  unsigned count = header.size;
  while (count > 0) {
    frame = read_ID3V2_frame(mp3);
    if (!strcmp(frame_name, frame.id))
      header.size -= frame.size + 10;
    else
      write_ID3V2_frame(&frame, tmp_file);
    count -= frame.size + 10;
  }
  filecpy(tmp_file, mp3);
  count = header.size;
  fclose(mp3);
  fseek(tmp_file, 0, SEEK_SET);
  mp3 = open_mp3(path_to_mp3, "w");
  frame_t new_frame;
  strncpy(new_frame.id, frame_name, 4);
  new_frame.size = strlen(frame_body);
  new_frame.flags = 0;
  new_frame.body = frame_body;
  header.size = convert_to_header_size_format(header.size + new_frame.size + 10);
  fwrite(&header, sizeof(header_t), 1, mp3);
  while (count > 0) {
    frame = read_ID3V2_frame(tmp_file);
    write_ID3V2_frame(&frame, mp3);
    count -= frame.size + 10;
  }
  write_ID3V2_frame(&new_frame, mp3);
  filecpy(mp3, tmp_file);
  remove("tmp.mp3");
  fclose(mp3);
  fclose(tmp_file);
}
