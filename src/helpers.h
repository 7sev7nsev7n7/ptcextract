#include <b64/cdecode.h>
#include <b64/cencode.h>

char* decode(char* input) {
  char* output = (char*)malloc(PONY_STRING_LENGTH);
  char* c=output;
  int cnt=0;
  base64_decodestate s;

  base64_init_decodestate(&s);
  cnt=base64_decode_block(input, strlen(input), c, &s);
  c+=cnt;

  return output;
}
