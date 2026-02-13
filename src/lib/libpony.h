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
  printf("Extract .ptc character information (v%d.%d.%d)\n", VERSION_MAJOR, VERSION_MINOR, VERSION_HOTFIX);
  printf("Ptcextract is open software\n");
  printf("For license details, please visit GitHub repository: https://github.com/7sev7nsev7n7/ptcextract\n");
  printf("Based on pony version %s\n", PONY_VERSION);
  printf("Based on Pony Town %s\n\n", PONY_TOWN_VERSION);
}

void print_usage(char* execpath) {
  fprintf(stderr, "Usage: %s [-q] [-h] file(s)\n\n", execpath);
  fprintf(stderr, "ptcextract - extract .ptc character information\n\n");
  fprintf(stderr, "options:\n");
  fprintf(stderr, "  -h                 show this help message and exit\n");
  fprintf(stderr, "  -q                 do not print welcome title\n");
  fprintf(stderr, "  -x                 print remaining hex values\n");
}
