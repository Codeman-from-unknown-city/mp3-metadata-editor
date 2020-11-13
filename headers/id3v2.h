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

#pragma pack(push,1)
typedef struct {
    unsigned size;
    short flags;
    unsigned size_of_padding;
} extended_header_t;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
  char id[4];
  unsigned size;
  short flags;
  char *body;
} frame_t;
#pragma pack(pop)

header_t read_ID3V2_header(FILE *mp3);
void display_ID3V2_header(header_t header);
frame_t read_ID3V2_frame(FILE *mp3);
void display_ID3V2_frame(frame_t frame);

#endif //TEXT_META_INFORMATION_EDITOR_ID3V2_H
