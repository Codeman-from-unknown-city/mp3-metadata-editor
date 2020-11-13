//
// Created by suprog on 12.11.2020.
//

#include <stdlib.h>
#include "../headers/id3v2.h"

static unsigned big_endian_to_little_endian(unsigned int big_endian_word) {
  return ((big_endian_word >> 24) | (big_endian_word << 24)
        | (big_endian_word << 8) & 0xFF0000 | (big_endian_word >> 8) & 0xFF00);
}

static unsigned convert_header_size(unsigned big_endian_in) {
  unsigned in, out = 0ul, mask = 0x7F000000ul;
  in = big_endian_to_little_endian(big_endian_in);
  while (mask) {
    out >>= 1;
    out |= (in & mask);
    mask >>= 8;
  }
  return out;
}

header_t read_ID3V2_header(FILE *mp3) {
  header_t header;
  fread(&header, sizeof(header), 1, mp3);
  header.size = convert_header_size(header.size);
  return header;
}

void display_ID3V2_header(header_t header) {
  puts("Header:");
  printf("%s %u.%u\nflags: Unsynchronisation = %d, Extended header = %d, "
         "Experimental indicator = %d\nsize: %u bytes\n",
         header.id, header.major_version, header.revision_num,
         header.flags & Unsync, header.flags & Extended_header,
         header.flags & Experimental_indicator, header.size);
}

frame_t read_ID3V2_frame(FILE *mp3) {
  frame_t frame;
  fread(&frame.id, sizeof(frame.id), 1, mp3);
  fread(&frame.size, sizeof(frame.size), 1, mp3);
  frame.size = big_endian_to_little_endian(frame.size);
  fread(&frame.flags, sizeof(frame.flags), 1, mp3);
  frame.body = malloc(frame.size);
  fread(frame.body, frame.size, 1, mp3);
  return frame;
}

static void display_text_frame_body(char *body) {
  body += 1; // skip encoding byte
  puts(body);
}

void display_ID3V2_frame(frame_t frame) {
  puts("----------------------------------------------------------------");
  puts("Frame:");
  printf("ID: %s\nsize: %u bytes\nflags: %x\ncontent: ",
         frame.id, frame.size, frame.flags);
  switch (frame.id[0]) {
    case 'T':
      display_text_frame_body(frame.body);
      break;
    default:
      puts(frame.body);
  }
}
