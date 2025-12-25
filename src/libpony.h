/* mapping sizes for different fields. each field can have multiple members,
 * these values define the size of each value in bits. These values were
 * obtained from Pony Town's source code, but might be different today as the
 * version obtained is old */
#define VERSION_BITS 6 // max 63
#define COLORS_LENGTH_BITS 10 // max 1023
#define BOOLEAN_FIELDS_LENGTH_BITS 4 // max 15
#define NUMBER_FIELDS_LENGTH_BITS 4 // max 15
#define COLOR_FIELDS_LENGTH_BITS 4 // max 15
#define SET_FIELDS_LENGTH_BITS 6 // max 63
#define CM_LENGTH_BITS 5 // max 31
#define NUMBERS_BITS 6 // max 63
#define PONY_STRING_LENGTH 2048 // ponystring char limit

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
  struct linkedlist colors; // ints converted to hex upon display
  struct linkedlist setFields; // will store char*s
  struct linkedlist colorFields; // will store 
  struct linkedlist numberFields; // will store ints
  struct linkedlist booleanFields; // will store boolean values
  int cm; // color management? possibly unrequired
};

/* base64 decode entire pony string. this function relies on libb64 */
char* decode(char* input, int length) {
  char* output = (char*)malloc(PONY_STRING_LENGTH);
  char* c=output;
  int cnt=0;
  base64_decodestate s;

  base64_init_decodestate(&s);
  cnt=base64_decode_block(input, strlen(input), c, &s);
  c+=cnt;

  return output;
}

/* determine filesize, from which we will allocate the appropriate space in
 * memory for the pony string */
int fsize(int fd) { 
  struct stat st;
  fstat(fd, &st);
  return ((st.st_mode & S_IFMT) == S_IFREG) ? st.st_size : -1;
}
