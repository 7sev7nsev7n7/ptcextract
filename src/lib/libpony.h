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
  printf("Ptcextract is open software. For license details, please visit GitHub repository: https://github.com/7sev7nsev7n7/ptcextract\n");
  printf("Based on pony file version %s\n", PONY_VERSION);
  printf("Based on Pony Town version %s\n\n", PONY_TOWN_VERSION);
}

void print_version() {
  printf("Ptcextract version %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_HOTFIX);
  printf("Based on pony file version %s\n", PONY_VERSION);
  printf("Based on Pony Town version %s\n", PONY_TOWN_VERSION);
}

void print_usage(char* execpath) {
  int flaglength = 8;
  char *options[][2] = {
    { "-h", "show this help message and quit" },
    { "-q", "skip printing welcome title" },
    { "-v", "print ptcextract version info and quit"},
    { "-x", "print remaining hex values"},
  };

  fprintf(stderr, "Usage: %s ", execpath);
  for (int i=0; i<sizeof(options)/sizeof(options[0]); i++)
    fprintf(stderr, "[%s] ", options[i][0]);
  fprintf(stderr, "file(s)\n");

  fprintf(stderr, "Ptcextract - extract .ptc character information\n\n");

  fprintf(stderr, "options:\n");
  for (int i=0; i<sizeof(options)/sizeof(options[0]); i++)
    fprintf(stderr, "  %-*s\t%s\n", flaglength, options[i][0], options[i][1]);
}
