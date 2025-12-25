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
  return (fstat(fd, &st)==0) ? st.st_size : -1;
}
