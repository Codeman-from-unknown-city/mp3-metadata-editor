//
// Created by suprog on 11.11.2020.
//

#ifndef TEXT_META_INFORMATION_EDITOR_PARAM_H
#define TEXT_META_INFORMATION_EDITOR_PARAM_H

typedef struct {
    char *name;
    char *val;
} param_t;

param_t parse_param(char *str);

#endif //TEXT_META_INFORMATION_EDITOR_PARAM_H
