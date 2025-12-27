/* mapping sizes for different fields. each field can have multiple members,
 * these values define the size of each value in bits. These values were
 * obtained from Pony Town's source code, but might be different today as the
 * version obtained is old */
#define VERSION_BYTES 8 // first 8 bytes denoting version, max 255
#define COLORS_LENGTH_BYTES 10 // max 1023
#define BOOLEAN_FIELDS_LENGTH_BYTES 4 // max 15
#define NUMBER_FIELDS_LENGTH_BYTES 4 // max 15
#define COLOR_FIELDS_LENGTH_BYTES 4 // max 15
#define SET_FIELDS_LENGTH_BYTES 6 // max 63
#define CM_LENGTH_BYTES 5 // max 31
#define NUMBERS_BYTES 6 // max 63

/* linked list implementation that will allow storing multiple fields within
 * our struct */
struct linkedlist {
  void* value;
  int next;
};

/* pony struct which will hold all pony's details and values. this struct can
 * be of variable size, so the implementation must also use dynamic memory
 * allocation wherever possible */
struct pony {
  int version;
  char* name;
  struct linkedlist colors; // ints converted to hex upon display
  struct linkedlist setFields; // will store char*s
  struct linkedlist colorFields; // will store 
  struct linkedlist numberFields; // will store ints
  struct linkedlist booleanFields; // will store boolean values
  int cm; // color management? possibly unrequired
};

/* ----------- END VALUE DEFINITIONS, BEGIN FUNCTION DEFINITIONS ----------- */

/* determine filesize, from which we will allocate the appropriate space in
 * memory for the pony string */
int fsize(int fd) { 
  struct stat st;
  fstat(fd, &st);
  return ((st.st_mode & S_IFMT) == S_IFREG) ? st.st_size : -1;
}

/* base64 decode entire pony string and store as uint8_t array.
 * this function relies on libb64 */
void decode(const char* input, uint8_t* output) {
  // initialize decodestate struct
  base64_decodestate state;
  base64_init_decodestate(&state);
  // initialize control variables
  uint8_t *c = output;
  int count = 0;

  // decode input base64 string and store in output buffer
  count=base64_decode_block(input, strlen(input), output, &state);
  c+=count;

  *(output+strlen(input)-2)=EOF;
}
