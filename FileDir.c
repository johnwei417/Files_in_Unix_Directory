#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

//Search method
/*recursive searching in the dir*/
void Search(char *dir, void (*fname)(char *))
    {
    struct dirent *dp;
    char name[1024];
    DIR *df;

     if ((df = opendir(dir)) == NULL) {
         fprintf(stderr, "Can not open this dir %s\n", dir);
         return;
     }
     while ((dp = readdir(df)) != NULL) {
         if ((strcmp(dp->d_name, ".") == 0) || (strcmp(dp->d_name, "..") == 0)){
             continue; //skip self and its parent dir
         } else {
             //store the ouput file name on the char buffer
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fname)(name);
        }
     }
     closedir(df);
 }

//fileInfo: print the name of the file "name"
void fileInfo(char *name)
 {
    struct stat buf;
    if (stat(name, &buf) != 0) {
        //get filename and file info, store into the struc st_buf
        fprintf(stderr, "Can not access to %s\n", name);
        //return value: return 0 if success else return 1 if failed, 
        //store errors into the std errno 
        return;
   }
  if ((buf.st_mode & S_IFMT) == S_IFDIR) {
       Search(name, fileInfo);
   }
     printf("FileName: %s\n", name);
 }

//main method;
int main(int argc, char *argv[])
 {
     printf("All files under this directory:\n");
  if (argc == 1) //default: current dir
  {
       fileInfo(".");
  }
    else{
        while (--argc > 0){
            fileInfo(*++argv);
            }
    }
    return 0;
}
