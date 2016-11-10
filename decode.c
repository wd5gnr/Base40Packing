#include "b40.h"

const char *charset=NULL;

const char *decode(unsigned word)
{
  static char buf[4];
  unsigned int div=1600, i;
  buf[3]='\0';
  if (charset==NULL) charset=b40char;
  for (i=0;i<3;i++)
    {
      buf[i]=charset[word/div];
      word-=(word/div)*div;
      div=div/40;
    }
  return buf;
}

#ifndef LIBONLY
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char *buf;  // hold entire line
  unsigned bufinc=512;  // must be at least 4, but ought to be more
  unsigned bufsiz=bufinc;  // start with one chunk
  unsigned bufptr=0;
  unsigned n;
  unsigned ct=0;
  buf=malloc(bufsiz);  // alocate first chunk
  if (!buf)
      fprintf(stderr,"Out of memory\n");
  while (scanf("%u",&n)==1)
    {
      const char *str=decode(n);
      ct++;
      printf("(%u)\t%s\n",n,str);
      if (buf && bufptr+4>=bufsiz)
	{
	  bufsiz+=bufinc;   // if out of space, make more
	  buf=realloc(buf,bufsiz);
	  if (!buf)
	    {
	      fprintf(stderr,"Out of memory\n");
	    } 
	}
      if (buf) strcpy(buf+bufptr,str);
      bufptr+=3;
    }
  if (buf) buf[bufptr]='\0';
  fprintf(stderr,"Bytes out=%u\n",ct*2);
  if (buf) fprintf(stderr,"Full String (length=%u):\n%s\n",strlen(buf),buf);
  if (buf) free(buf);
  return 0;
}
#endif
