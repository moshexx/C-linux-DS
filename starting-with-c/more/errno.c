#include <stdio.h>
#include <errno.h>

int main () {
   FILE *fp;

   /* first rename if there is any file */
   rename("file.txt", "newfile.txt");

   /* now let's try to open same file */
   fp = fopen("file.txt", "r");
   if( fp == NULL ) {
      perror("Error ");
      printf("ERROR number: %d\n" ,strerror(errno));
      return(-1);
   }
   fclose(fp);
      
   return(0);
}
