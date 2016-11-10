#include "b40.h"
#include <ctype.h>
#include <string.h>

// Set to 0 to replace bad characaters with character 0 (default space)
#ifndef ERR_ON_BAD_CHAR
#define ERR_ON_BAD_CHAR 0
#endif


const char *charset=NULL;

int encode(int ch, void (*out)(unsigned num))
{
  static unsigned digit=0;
  static unsigned num=0;
  const char *p;
  char c;
  int rv=0;
  if (charset==NULL) charset=b40char;
  if (c==-1)
    {
      if (digit==0) return 0;
      while (digit++<3) num*=40;
      if (out) out(num);
      return 0;
    }
  if (isspace(c)) c=' ';  // all white space to space
  c=toupper(ch);
  p=strchr(charset,c);
#if ERR_ON_BAD_CHAR
    if (!p) return -1;
#else
  if (!p)
    {
      rv=-1;
      p=charset;  // replace with character 0 (space by default)
    }
#endif  
  num*=40;
  num+=p-charset;
  if (++digit==3)
    {
      digit=0;
      if (out) out(num);
      num=0;
    }
  return rv;
}

#ifndef LIBONLY

void nout(unsigned n)
{
  printf("%u\n",n);
}

int main(int argc, char *argv[])
{
  unsigned ct=0;
  char c;
  while (!feof(stdin))
    {
      c=getchar();
      if (c==EOF) break;
      if (encode(c,nout) && !isspace(c)) fprintf(stderr,"Unknown character %c (0x%x)\n",c,c);
      ct++;
    }
  encode(-1,nout);
  fprintf(stderr,"Characters in=%u\n",ct);
  return 0;
}

#endif
