#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/*This program allows you to 
  calculate the amount of time 
  it would approximately 
  take to download 
  a file of specified size at specified speed
*/
const char *version = "0.4";
char *heapPtr = NULL;
const char *mb = "mb";
const char *gb = "gb";
static const short defaultSpeed = 1024; //kB/s
static const char *progMsg_p1 = "Downloading a";
static const char *progMsg_p2 = "will take";
static const char *progErrMsg1 = "No parameters specified. Quitting";
static const char *progErrMsg2 = "Unrecognized parameter <unit>";
static const char *usageExample = "downloadtime 1 1024 gb";
bool inputValid(char *usrString) {
    return true;
}
//0 - mB to kB
//1 - gB - mB - kB
void displayHelp(void) {
        puts("Usage: downloadtime <size(GiB)> <speed(kB)> <unit(mB/gB)>");
        printf("Example: \nIn order to calculate the amount of time it would approximately \ntake to download a 1GiB file at the speed of 1024 kilobytes per second\ntype %s\n\
        ",usageExample);
}
void displayInfo(void) {
        printf("Last compiled on %s (UTC+3)",__TIMESTAMP__);
}
void unitConversion(double *num, short *mode) {
    (!(*mode))
    ?
        ((*num)*=1024)
    :
        ((*num)*=1024<<10);
}
char *_toLower(char *inputStr) {
    char *inputBuff = calloc(3,sizeof(char));
    strcpy(inputBuff,inputStr);
    int caseDistance = 32;
    for(register int x = 0;x<2;x++) {
            if(isupper(inputBuff[x]))
                inputBuff[x] = (int)inputBuff[x]+caseDistance;
            else
                continue;
            }
    heapPtr = inputBuff;
    return inputBuff;
}
void findTime(double *fileSize, short *mode, unsigned int *chosenSpeed) {
    double usrFileSizeDisplay = *fileSize;
    unitConversion(fileSize,mode);
    double seconds,minutes,hours,days;
    seconds = minutes = hours = days = 0;
    seconds = (*fileSize)/((*chosenSpeed)!=0?(*chosenSpeed):defaultSpeed);
    printf("%s %.2f %s file %s",progMsg_p1,usrFileSizeDisplay,!mode?"MiB":"GiB",progMsg_p2);
    if(seconds>60) {
        minutes = seconds/60;
        seconds = (int)seconds%60;
        if(minutes>60) {
            hours = minutes/60;
            minutes = (int)minutes%60;
            if(hours>24) {
                days = hours/24;
                hours = (int)hours%24;
                }
            }
        }
        puts("");
        if(days)
            printf("%d days\n",(int)days);
        if(hours)
            printf("%d hours\n",(int)hours);
        if(minutes)
            printf("%d minutes\n",(int)minutes);
        if(seconds)
            printf("%d seconds\n",(int)seconds);
}
//usage: downloadTime.exe <size/100> <size_type/MB|GB>
int main(int argc, char **argv) {
                if(!argv[1]) {
                        puts(progErrMsg1);
                        return 0;
                    }
                else {
                    if(!(strcmp(argv[1],"help")))
                            displayHelp();
                    else if(!(strcmp(argv[1],"info")) || !(strcmp(argv[1],"about")))
                            displayInfo();
                    else {
                            //main program loop
                            double usrFileSize = 1;
                            short mode = 0;
                            unsigned int chosenSpeed = 0;
                            sscanf(argv[1],"%lf",&usrFileSize);
                            sscanf(argv[2],"%d",&chosenSpeed);
                            if(!(strcmp(_toLower(argv[3]),mb)))
                                    mode = 0;
                            else if(!(strcmp(_toLower(argv[3]),gb))) 
                                    mode = 1;   
                            else 
                                    mode = -1;
                            if(!(mode<0)) {
                                findTime(&usrFileSize, &mode, &chosenSpeed);
                                free(heapPtr);
                            }
                            else {
                                puts(progErrMsg2);
                                }
                        }
                    }
                return ~0xFFFFFFFF;
}
