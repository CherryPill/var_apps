#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
/* This program allows you to mask all 
   image file names inside a particular directory 
   to hide their original name.
*/
#define BUFF_SIZE 1024
static char *imageType[4] = {
    ".jpg",
    ".gif",
    ".png",
    ".webm"
    };
unsigned int maxRandDigits = 13;
char *isImage(char *fileName){
        for(int x = 0;x<4;x++){
            if(strstr(fileName, imageType[x])){
                return imageType[x];
            }
        }
        return NULL;
}
void generateFileName(char *fileName, char *extension){
        strcpy(fileName,"14"); //it makes sense, even if it doesn't make sense for you
        for(int x = 2;x<maxRandDigits;x++){
                int rNumber = rand() % 10;
                char temp[2] = {0};
                sprintf(temp, "%d", rNumber);
                strcat(fileName, temp);
        }
        strcat(fileName, extension);
}
bool isFile(const char* fullPath) {
    struct stat fileInfo;
    if(stat(fullPath, &fileInfo) == -1) {
        perror("ERROR");
        return true;
        }
    if (S_ISDIR(fileInfo.st_mode)){
        return false;
    }
    else{
        return true;
    }
}
int main(int argc, char **argv) {
    if(argc < 2){
        puts("ERROR: Insufficient number of command line arguments");      
    }
    else{
        int modifiedFilesCount = 0;
        srand(time(0));
        struct dirent *dirElement;
        DIR *root = NULL;
        root = opendir(argv[1]);
        while((dirElement = readdir(root))){
            if(dirElement->d_name[0]!='.'){
                char fullName[BUFF_SIZE] = {0};
                strcpy(fullName, argv[1]);
                strcat(fullName,"\\");
                strcat(fullName, dirElement->d_name);
                if(isFile(fullName)){
                     char *detectedImageExtension = NULL;
                     if((detectedImageExtension = isImage(dirElement->d_name))!=NULL){
                         chdir(argv[1]);
                         char newFileName[BUFF_SIZE] = {0};
                         generateFileName(newFileName, detectedImageExtension);
                         int retResult = rename(dirElement->d_name, newFileName);
                         if(!retResult){
                               ++modifiedFilesCount;
                            }
                         else{
                                perror("ERROR");
                            }
                      }
                 }   
             }     
        }
        if(modifiedFilesCount!=0){
            printf("Successfully renamed %d files\n", modifiedFilesCount);
        }
        else{
            puts("No images detected");
        }
        closedir(root);  
    }
        return 0;
}
