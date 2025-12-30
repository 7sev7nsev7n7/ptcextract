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
  printf("ptcextract made with pony version: 3ca61ba6041902\n\n");

  // argument checking
  if (argc<2) {
    fprintf(stderr, "no files specified\n");
    exit(1);
  } 

  // process every argument as an input file, this might change in the future
  for (int mainloop=1; mainloop<argc; mainloop++) {
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
    char* raw_string = malloc(filesize);
    read(file, raw_string, filesize);
    // create uint8_t array for decoding
    uint8_t base64_decoded[strlen(raw_string)];
    // base64 decode string
    int decoded_length=decode(raw_string, base64_decoded);
    close(file); // close file as it is no longer required

    /* ---------- BEGIN UGLY DEBUG CODE ---------- */
    /* ---------- BEGIN UGLY DEBUG CODE ---------- */

    // print newline if we're processing more than one file
    if(mainloop>1) printf("\n");
    printf("-- processing file %s\n", argv[mainloop]);

    // debug print version
    printf("-- pony version: ");
    for (int i=0; i<7; i++)
      printf("%.2x", *(base64_decoded+i));
    printf("\n\n");

    // debug print character count for pony name
    int character_name_length = (int)*(base64_decoded+8)-1;
    printf("-- character name length: %d\n", character_name_length);

    // debug print character name
    // character name is always after the first nine bytes
    printf("-- character name: ");
    for (int i=9; i<=(character_name_length+8); i++) {
      printf("%c", *(base64_decoded+i));
    }
    printf("\n");

    // debug get byte count until end of file (or start of description if applicable)
    int remaining_byte_count = *(base64_decoded+character_name_length+9);
    if (remaining_byte_count>0x80) { // shitty necessary thing because of reasons
      remaining_byte_count = (*(base64_decoded+character_name_length+9)-0x80) + (*(base64_decoded+character_name_length+10)*0x80) + 1;
    }
      printf("\n");

    // debug get name name position 
    //
    // TODO remove and replace with superior byte count
    // (this will allow us to skip the description bytes at the end, if
    // applicable)
    int name_end_position = character_name_length+9;

    // debug print character count for pony description
    int character_description_length = (int)*(base64_decoded+name_end_position+remaining_byte_count)-1;
    if (character_description_length>0) {
      printf("-- character description length: %d\n", character_description_length);

      // debug print character description
      printf("-- character description: ");
      for (int i=0; i<character_description_length; i++) {
        printf("%c", *(base64_decoded+name_end_position+remaining_byte_count+i+1));
      }
      printf("\n\n");
    }

    // debug print hex values before colors
    int color_start_position=0;
    int color_count=0;
    for (int i=name_end_position; i<decoded_length; i++) {
      if (*(base64_decoded+i)==0x64) {
        color_start_position=i+1;
        color_count=(int)*(base64_decoded+i+1)*3;
        break;
      }
    }

    // debug print color count, position and list colors
    printf("-- color count: %d (using %d bytes)\n", color_count/3, color_count);
    printf("-- color hex codes:\n");
    for (int i=0; i<color_count; i++) {
      if (i%3==0) printf("#");
      printf("%.2x", *(base64_decoded+color_start_position+i+1));
      if (i%3==2) printf("\n");
    }
    printf("\n");

    // debug print rest of values as hex
    int rest_hex_start = color_start_position+color_count+1;
    int rest_hex_end=0;
    printf("-- rest of values as uint8 hex values (starting at index %d or 0x%.2x): \n", rest_hex_start, rest_hex_start);
    for (int i=1; i<decoded_length-rest_hex_start+1; i++) {
      rest_hex_end++;
      printf("%.2x", *(base64_decoded+i+rest_hex_start-1));
      if (i%2==0) printf(" ");
      if (i%16==0) printf("\n");
    }
    printf("\n-- total count of rest of hex codes: %d\n",rest_hex_end);
  }
  return 0;
}
