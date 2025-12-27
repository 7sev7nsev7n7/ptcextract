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

  // process every argument as an input file, this might change in the future
  for (int i=1; i<argc; i++) {
    // print newline if we're processing more than one file
    if(i>1) printf("\n");
    printf("processing file %s\n", argv[i]);

    // opening file and reading contents
    int fd = open(argv[i], O_RDONLY);
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
    // malloc() uint8_t array for decoding
    uint8_t bas64_decoded[strlen(ponystring)];
    // base64 decode string
    int decoded_length=decode(ponystring, bas64_decoded);
    close(fd); // close file as it is no longer required

    // debug print character count for pony name
    int namelen = (int)*(bas64_decoded+8)-1;
    printf("character name length: %d\n", namelen);

    // debug print character name
    // character name is always after the first nine bytes
    printf("character name: ");
    for (int ii=9; ii<=(8+namelen); ii++) {
      printf("%c", *(bas64_decoded+ii));
    }
    printf("\n");
  }
  return 0;
}

// // debug print all bas64_decoded hex codes
// for (int ii=1; ii<decoded_length; ii++) { // start on 1 to avoid modulus evaluating to zero before necessary
//   printf("%.2x", *(bas64_decoded+ii-1));
//   if (ii%2==0) printf(" ");
//   if (ii%16==0) printf("\n");
// }
// printf("\n");
// // debug print all hex values as characters
// for (int ii=0; ii<decoded_length; ii++) printf("%c", *(bas64_decoded+ii));
// printf("\n");

