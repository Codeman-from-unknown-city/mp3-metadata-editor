//
// Created by suprog on 12.11.2020.
//

#ifndef TEXT_META_INFORMATION_EDITOR_COMMANDS_H
#define TEXT_META_INFORMATION_EDITOR_COMMANDS_H

void show(const char *path_to_mp3);
void get(const char *path_to_mp3, const char *name_of_requested_frame);
void set(const char *path_to_mp3, const char *frame_name, char *frame_body);

#endif //TEXT_META_INFORMATION_EDITOR_COMMANDS_H
