#include <b64/cdecode.h>
#include <fcntl.h>
#include <stdint.h>
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

  // read file
  char* ponystring = malloc(filesize);
  read(fd, ponystring, filesize);
  // malloc() buffer size for decoding
  uint8_t decoded[strlen(ponystring)];
  // base64 decode string
  decode(ponystring, decoded);
  close(fd); // close file as it is no longer required

  // // debug print all decoded hex codes
  // for (int i=0; i<657; i++) printf("0x%.2x ", *(decoded+i));
  // printf("\n");

  // debug print character count for pony name
  int namelen = (int)*(decoded+8)-1;
  printf("character name length: %d\n", namelen);

  // debug print character name
  printf("character name: ");
  for (int i=9; i<=(8+namelen); i++) {
    printf("%c", *(decoded+i));
  }
  printf("\n");

  return 0;
}
