#include <stdio.h>      
#include <stdlib.h>      
#include <sys/stat.h>


int
main(int argc, char *argv[])
{
   int         i;
   struct stat   buf;
   char      *tekst;

   for (i = 1; i < argc; i++) {
      printf("%s: ", argv[i]);
      if (lstat(argv[i], &buf) < 0) {
         printf("lstat error");
         continue;
      }
      /* TU UZUPELNIC warunek rozpoznajacy zwykly plik*/
      if (S_ISREG(buf.st_mode))
         tekst = "zwykly plik";
      /* TU UZUPELNIC warunek rozpoznajacy katalog*/
      else if (S_ISDIR(buf.st_mode))
         tekst = "katalog";      
      /* TU UZUPELNIC warunek rozpoznajacy link symboliczny*/
      else if (S_ISLNK(buf.st_mode))
         tekst = "link symboliczny";
      else
         tekst = "**** cos innego !!! ****";
      printf("%s\n", tekst);
   }
   exit(0);
}