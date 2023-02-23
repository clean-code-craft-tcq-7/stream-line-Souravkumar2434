#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "receiver.h"
#include "test_cases.h"


void correctUsageInfoAndExit(char* exeName)
{
    printf("Usage: %s [-t]/[-r]\n[-t]: To run the unit test cases\n[-r]: To read the sensors data via console input\n", exeName);
    exit(0);
}

void printToConsole(char* buff)
{
    write(STDOUT_FILENO, buff, strlen(buff));
}

void executeProgram(void)
{
    char data[1000];

    fgets (data, 1000, stdin);
    processSensorData(data, &printToConsole);
}

int main(int argc, char **argv)
{
    if(argc == 1)
    {
        correctUsageInfoAndExit(argv[0]);
    }

    if(strcmp(argv[1],"-t") == 0)
    {
        test_functions();
    }
    else if(strcmp(argv[1],"-r") == 0)
    {
        executeProgram();
    }
    else
    {
        correctUsageInfoAndExit(argv[0]);
    }

    return 0;
}
