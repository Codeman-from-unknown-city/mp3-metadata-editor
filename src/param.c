//
// Created by suprog on 11.11.2020.
//

#include "../headers/param.h"
#include <stdlib.h>

param_t parse_param(char *str) {
  str += 2; // skip prefix
  param_t param;
  param.name = str;
  while (*str != '\0' && *str != '=')
    str++;
  if (*str != '\0' && *(str + 1) != '\0')
    param.val = str + 1;
  else
    param.val = NULL;
  *str = '\0'; // add separator between name and value
  return param;
}
