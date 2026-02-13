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
  printf("Based on pony file version %s\n", PONY_VERSION);
  printf("Based on Pony Town version %s\n", PONY_TOWN_VERSION);
}

void print_usage(char* execpath) {
  int optionlength = 8;
  char *options[][2] = {
    { "-a", "process files as multi-character files" },
    { "-I", "print information title and exit" },
    { "-h", "print this help message and quit" },
    { "-q", "skip printing welcome title" },
    { "-x", "print remaining hex values" },
  };

  printf("Usage: %s ", execpath);
  for (int i=0; i<sizeof(options)/sizeof(options[0]); i++)
    printf("[%s] ", options[i][0]);
  printf("file(s)\n\n");

  printf("Ptcextract - extract .ptc character information\n\n");

  printf("options:\n");
  for (int i=0; i<sizeof(options)/sizeof(options[0]); i++)
    printf("  %-*s\t%s\n", optionlength, options[i][0], options[i][1]);
}
