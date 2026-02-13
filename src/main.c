#define PONY_VERSION "3ca61ba6041902" // pony version upon which tool was based upon
#define PONY_TOWN_VERSION "v0.124.0" // pony town version upon which tool was based upon
#define VERSION_MAJOR 2
#define VERSION_MINOR 1
#define VERSION_HOTFIX 2

#include <b64/cdecode.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "lib/libpony.h"

int main(int argc, char *argv[]) {
  // argument handling
  if (argc==1) { // print usage if no arguments are supplied
        print_usage(argv[0]);
        exit(1);
  }

  // flags array, might switch to bitmap later but i'm lazy lol
  bool flags[] = { 
    true,  // print intro
    false, // print rest of hex values
  };

  opterr=0;
  int opt;

  while ((opt = getopt(argc, argv, "hqvx")) != -1) {
    switch(opt) {
      case 'q': // quiet (no title)
        flags[0]=false;
        break;
      case 'x':
        flags[1]=true;
        break;
      case 'v':
        print_version();
        exit(0);
      case '?':
        fprintf(stderr, "unknown option '-%c', ignoring\n", optopt);
        break;
      case 'h': // print usage and exit
      default:
        print_usage(argv[0]);
        exit(1);
    }
  }

  // check if no non-option arguments passed, and quit if so
  if(optind==argc) {
    fprintf(stderr, "no files supplied, aborting\n");
    exit(1);
  }

  // print title if quiet flag not set
  if (flags[0])
    print_title();

  // take action upon every non-option argument. this avoids having to create a
  // dedicated filename variable, array or whatever :)
  for (int index=optind; index<argc; index++) { 
    // opening file and reading contents
    int file;
    file = open(argv[index], O_RDONLY);
    if (file==-1) {
      fprintf(stderr, "file access error, aborting (error %d)\n", errno);
      exit(1);
    }

    // stat file to get information such as type and size
    struct stat statbuf;
    if (stat(argv[index], &statbuf)==-1) {
      printf("stat error, aborting (error %d)\n", errno);
      exit(1);
    }

    // check file type and size, to avoid processing invalid file types
    if (statbuf.st_size==0) {
      fprintf(stderr, "file is empty, aborting\n");
      exit(1);
    } else if (!S_ISREG(statbuf.st_mode)) {
      fprintf(stderr, "not regular file, aborting\n");
      exit(1);
    }

    // read file
    char* raw_string = malloc(statbuf.st_size);
    read(file, raw_string, statbuf.st_size);

    // create uint8_t array for decoding
    uint8_t base64_decoded[statbuf.st_size];

    // base64 decode string
    int decoded_length=decode(raw_string, base64_decoded);

    // close file as it is no longer required
    close(file); 

    // free raw string as it is no longer required, and could eventually cause
    // memory leak
    free(raw_string); 

    /* ---------- BEGIN UGLY DEBUG CODE ---------- */
    /* ---------- BEGIN UGLY DEBUG CODE ---------- */

    // print newline if we're processing more than one file
    printf("Processing file: %s\n", argv[index]);

    // debug print version
    printf("Pony version: ");
    for (int i=0; i<7; i++)
      printf("%.2x", *(base64_decoded+i));
    printf("\n\n");

    // debug print character name
    // character name is always after the first nine bytes
    int character_name_length = (int)*(base64_decoded+8);
    printf("Character name: ");
    for (int i=1; i<character_name_length; i++) {
      printf("%c", *(base64_decoded+i+8));
    }
    printf("\n");

    // debug get byte count until end of file (or start of description if applicable)
    int remaining_byte_count = *(base64_decoded+character_name_length+8);
    if (remaining_byte_count>0x80) { // shitty necessary thing because of reasons
      remaining_byte_count = (*(base64_decoded+character_name_length+8)-0x80) + (*(base64_decoded+character_name_length+9)*0x80) + 1;
    }

    // debug print character description
    if (int character_description_length = decoded_length-(remaining_byte_count+character_name_length+9); character_description_length>0) {
      printf("Character description: ");
      for (int i=0; i<character_description_length; i++) {
        printf("%c", *(base64_decoded+character_name_length+remaining_byte_count+i+9));
      }
      printf("\n");
    }
    printf("\n");

    // debug get color start position and count
    int color_start_position=0;
    int color_count=0;
    for (int i=(character_name_length+9); i<remaining_byte_count; i++) {
      if (*(base64_decoded+i)==0x64) {
        color_start_position=i+1;
        color_count=(int)*(base64_decoded+i+1)*3;
        break;
      }
    }

    // debug print color count and list colors
    printf("Color count: %d (using %d bytes)\n", color_count/3, color_count);
    printf("Color hex codes:\n");
    for (int i=0; i<color_count; i++) {
      if (i%3==0) printf("   #");
      printf("%.2x", *(base64_decoded+color_start_position+i+1));
      if (i%3==2) printf("\n");
    }

    // debug print rest of values as hex
    if (flags[1]) {
      printf("\n");
      int rest_hex_start = color_start_position+color_count+1;
      int rest_hex_end=0;
      printf("Printing rest of values as uint8 hex values (starting at index %d or 0x%.2x): \n", rest_hex_start, rest_hex_start);
      for (int i=1; i<decoded_length-rest_hex_start+1; i++) {
        rest_hex_end++;
        printf("%.2x ", *(base64_decoded+i+rest_hex_start-1));
        if (i%16==0 && i+1!=decoded_length-rest_hex_start+1) printf("\n");
      }
      printf("\n-- Total count of rest of hex codes: %d\n",rest_hex_end);
    }
  }
  exit(0);
}
