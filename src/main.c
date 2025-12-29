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
  for (int mainloop=1; mainloop<argc; mainloop++) {
    // print newline if we're processing more than one file
    if(mainloop>1) printf("\n");
    printf("processing file %s\n", argv[mainloop]);

    // opening file and reading contents
    int file = open(argv[mainloop], O_RDONLY);
    if (file==-1) {
      fprintf(stderr, "file not found\n");
      return 1;
    }

    // obtain filesize
    int filesize=fsize(file);
    if (filesize<=0) {
      fprintf(stderr, "file is empty, quitting\n");
      return 1;
    }

    // read file
    char* ponystring = malloc(filesize);
    read(file, ponystring, filesize);
    // create uint8_t array for decoding
    uint8_t base64_decoded[strlen(ponystring)];
    // base64 decode string
    int decoded_length=decode(ponystring, base64_decoded);
    close(file); // close file as it is no longer required

    /* ---------- BEGIN UGLY DEBUG CODE ---------- */
    /* ---------- BEGIN UGLY DEBUG CODE ---------- */

    // debug print character count for pony name
    int namelen = (int)*(base64_decoded+8)-1;
    printf("character name length: %d\n", namelen);

    // debug print character name
    // character name is always after the first nine bytes
    printf("character name: ");
    for (int i=9; i<=(namelen+8); i++) {
      printf("%c", *(base64_decoded+i));
    }
    printf("\n");

    // debug get name start position
    int name_end_position = namelen+9;

    // debug print hex values before colors
    printf("first hex values before colors begin:\n",*(base64_decoded+name_end_position));
    int color_start_position=0;
    int color_count=0;
    for (int i=name_end_position; i<decoded_length; i++) {
      printf("0x%.2x\n", *(base64_decoded+i));
      if (*(base64_decoded+i)==0x64) {
        printf("0x%.2x (this indicates the color count)\n", *(base64_decoded+i+1));
        color_start_position=i+1;
        color_count=(int)*(base64_decoded+i+1)*3;
        break;
      }
    }

    // debug print color count, position and list colors
    printf("color count: %d\n", color_count/3);
    printf("rest of colors as hex codes:\n");
    for (int i=0; i<color_count; i++) {
      if (i%3==0) printf("#");
      printf("%.2x", *(base64_decoded+color_start_position+i+1));
      if (i%3==2) printf("\n");
    }

    // debug print rest of values as hex
    printf("rest of values as uint8 hex values: \n");
    for (int i=color_start_position+color_count+1; i<decoded_length; i++) {
      printf("0x%.2x\n", *(base64_decoded+i));
    }

    printf("\n");
  }
  return 0;
}
