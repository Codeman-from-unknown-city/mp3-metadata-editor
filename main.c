#include <string.h>
#include "headers/commands.h"
#include "headers/error.h"
#include "headers/param.h"
#include "headers/mp3.h"
#include "headers/id3v2.h"

int main(int argc, char *argv[]) {
  const char *program_name = *argv;
  if (argc == 1)
    usage_err(program_name);
  char *path_to_mp3 = parse_param(*(++argv)).val;
  if (!path_to_mp3)
    usage_err(program_name);
  argc -= 2;
  param_t cmd;
  while (argc-- > 0) {
    cmd = parse_param(*(++argv));
    if (!strcmp(cmd.name, "show"))
      show(path_to_mp3);
    if (!strcmp(cmd.name, "get"))
      get(path_to_mp3, cmd.val);
  }
  return 0;
}