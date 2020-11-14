//
// Created by suprog on 12.11.2020.
//

#include <stdlib.h>
#include "../headers/id3v2.h"

unsigned change_byteorder(unsigned big_endian_word) {
  return ((big_endian_word >> 24) | (big_endian_word << 24)
          | (big_endian_word << 8) & 0xFF0000 |
          (big_endian_word >> 8) & 0xFF00);
}

static unsigned convert_header_size(unsigned big_endian_in) {
  unsigned in, out = 0ul, mask = 0x7F000000ul;
  in = change_byteorder(big_endian_in);
  while (mask) {
    out >>= 1;
    out |= (in & mask);
    mask >>= 8;
  }
  return out;
}

unsigned convert_to_header_size_format(unsigned int little_endian_in) {
  unsigned in, out = 0ul, mask = 0x0000007Ful;
  in = change_byteorder(little_endian_in);
  while (mask) {
    out <<= 1;
    out |= (in & mask);
    mask <<= 8;
  }
  return out;
}

header_t read_ID3V2_header(FILE *mp3) {
  header_t header;
  fread(&header, sizeof(header_t), 1, mp3);
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
  fread(&frame.id, 4, 1, mp3);
  frame.id[4] = '\0';
  fread(&frame.size, sizeof(frame.size), 1, mp3);
  frame.size = change_byteorder(frame.size);
  fread(&frame.flags, sizeof(frame.flags), 1, mp3);
  frame.body = malloc(frame.size + 1);
  fread(frame.body, frame.size, 1, mp3);
  frame.body[frame.size] = '\0';
  return frame;
}

void display_ID3V2_frame(frame_t *frame) {
  puts("--------------------------------------------------------------------");
  puts("Frame:");
  printf("ID: %s\nsize: %u bytes\nflags: Tag alter preservation: %u, "
      "File alter preservation: %u, Read only: %u, Compression: %u, "
      "Encryption: %u, Grouping_identity %u\ncontent: ",
      frame->id, frame->size, frame->flags & Tag_alter_preservation,
      frame->flags & File_alter_preservation, frame->flags & Read_only,
      frame->flags & Compression, frame->flags & Encryption,
      frame->flags & Grouping_identity);
  unsigned count = frame->size;
  while (count-- > 0)
    putchar(*frame->body++);
  putchar('\n');
}

void write_ID3V2_frame(frame_t *frame, FILE *out) {
  fwrite(&frame->id, 4, 1, out);
  unsigned converted_size = change_byteorder(frame->size);
  fwrite(&converted_size, sizeof(frame->size), 1, out);
  fwrite(&frame->flags, sizeof(frame->flags), 1, out);
  fwrite(frame->body, frame->size, 1, out);
}
