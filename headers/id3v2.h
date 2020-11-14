//
// Created by suprog on 11.11.2020.
//

#include <stdio.h>

#ifndef TEXT_META_INFORMATION_EDITOR_ID3V2_H
#define TEXT_META_INFORMATION_EDITOR_ID3V2_H

enum masks {
  Unsync = 0b01000000u,
  Extended_header = 0b00100000u,
  Experimental_indicator =  0b00010000u,
  Tag_alter_preservation = 0b1000000000000000,
  File_alter_preservation = 0b01000000000000000,
  Read_only = 0b00100000000000000,
  Compression = 0b0000000010000000,
  Encryption = 0b0000000001000000,
  Grouping_identity = 0b0000000000100000
};

#pragma pack(push,1)
typedef struct {
    char id[3];           // always are "ID3"
    int major_version: 8; // $03
    int revision_num: 8;  // $00
    int flags: 8;         // %abc00000
    unsigned size;        // 4 * %0xxxxxxx
} header_t;
#pragma pack(pop)

typedef struct {
  char id[5];
  unsigned size;
  short flags;
  char *body;
} frame_t;

unsigned convert_to_header_size_format(unsigned little_endian_in);
header_t read_ID3V2_header(FILE *mp3);
void display_ID3V2_header(header_t header);
frame_t read_ID3V2_frame(FILE *mp3);
void display_ID3V2_frame(frame_t *frame);
void write_ID3V2_frame(frame_t *frame, FILE *out);

#endif //TEXT_META_INFORMATION_EDITOR_ID3V2_H
