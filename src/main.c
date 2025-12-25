#include <b64/cdecode.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "libpony.h"

void print_raw_decoded_string(char *decoded, int size) {
  // skipping version bits to only print name
  for (int pos=9; *(decoded+pos)!='\0'; pos++) printf("%c", *(decoded+pos));
}

int main(int argc, char *argv[]) {
  // argument checking
  if (argc<2) {
    printf("no files specified\n");
    exit(1);
  } 

  // opening file and reading contents
  int fd = open(argv[1], O_RDONLY); // file descriptor
  if (fd==-1) {
    printf("file not found\n");
    return 1;
  }

  int filesize=fsize(fd);
  if (filesize<=0) {
    printf("invalid file\n");
    return 1;
  }

  char* ponystring = malloc(filesize);
  read(fd, ponystring, filesize);
  char *decoded = decode(ponystring, filesize);

  // debug
  print_raw_decoded_string(decoded, filesize); printf("\n");

  return 0;
}
