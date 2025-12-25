#include <b64/cdecode.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "lib/libpony.h"

int main(int argc, char *argv[]) {
  // argument checking
  if (argc<2) {
    fprintf(stderr, "no files specified\n");
    exit(1);
  } 

  // opening file and reading contents
  int fd = open(argv[1], O_RDONLY);
  if (fd==-1) {
    fprintf(stderr, "file not found\n");
    return 1;
  }

  // obtain filesize
  int filesize=fsize(fd);
  if (filesize<=0) {
    fprintf(stderr, "file is empty, quitting\n");
    return 1;
  }

  // read and decode file
  char* ponystring = malloc(filesize);
  read(fd, ponystring, filesize);
  char *decoded = decode(ponystring, filesize);
  close(fd); // close file as it is no longer required

  // debug
  print_raw_decoded_string(decoded, filesize); printf("\n");

  return 0;
}
