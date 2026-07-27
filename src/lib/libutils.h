/* base64 decode entire pony string and store as uint8_t array.
 * this function relies on libb64 */
int decode(const char* input, uint8_t* output) {
  // initialize decodestate struct
  base64_decodestate state;
  base64_init_decodestate(&state);
  // initialize control variables
  uint8_t *c = output;
  int count = 0;

  // decode input base64 string and store in output buffer
  count=base64_decode_block(input, strlen(input), output, &state);
  c+=count;

  return count;
}

void print_title() {
  printf("Extract .ptc character information (version %d.%d.%d)\n", VERSION_MAJOR, VERSION_MINOR, VERSION_HOTFIX);
  printf("Ptcextract is open software. For license details visit GitHub repository: https://github.com/7sev7nsev7n7/ptcextract\n");

  printf("Based on pony file version ");
  for (int i=0; i<7; i++)
    printf("%x", PONY_VERSION[i]);
  printf("\n");

  printf("Based on Pony Town version %s\n", PONY_TOWN_VERSION);
}

void print_usage(char* execpath) {
  int optionwidth = 8; // width of column where options will be printed. we
                       // hard code this since we're too lazy to check for the
                       // longest one and then add padding, etc.
  char *options[][2] = {
    { "-a", "process files as multi-character files" },
    { "-b", "print remaining values as binary" },
    { "-h", "print this help message and quit" },
    { "-I", "print information title and quit" },
    { "-q", "skip printing information title" },
    { "-x", "print remaining values as binary" },
  };

  printf("Usage: %s ", execpath);
  for (int i=0; i<sizeof(options)/sizeof(options[0]); i++)
    printf("[%s] ", options[i][0]);
  printf("file(s)\n\n");

  printf("Ptcextract - extract .ptc character information\n\n");

  printf("options:\n");
  for (int i=0; i<sizeof(options)/sizeof(options[0]); i++)
    printf("  %-*s\t%s\n", optionwidth, options[i][0], options[i][1]);
}
