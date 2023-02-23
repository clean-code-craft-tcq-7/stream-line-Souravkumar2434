#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "receiver.h"
#include "jsonParser.h"
#include "lib/jsmn.h"

int convertJsonToData(char* buff, jsonData* data)
{
    int keyCount = 0;
    int i = 0, r;
    jsmn_parser p;
    jsmntok_t token[300]; /* We expect no more than 300 JSON tokens */

    jsmn_init(&p);
    r = jsmn_parse(&p, buff, strlen(buff), token, 1000); // "s" is the char array holding the json content
    printf("%d\n",r);
    if(r > 0)
    {
       while(i < r)
       {
           if(token[i].type == JSMN_STRING)
           {
               memset(data[keyCount].key,0,20);
               memset(data[keyCount].value,0,300);
               strncpy(data[keyCount].key, &buff[token[i].start], (token[i].end - token[i].start));
               strncpy(data[keyCount].value, &buff[token[i+1].start + 1], (token[i+1].end - token[i+1].start - 2));
               data[keyCount].valCnt = token[i+1].size;
               keyCount++;
           }
           i++;
       }
    }
    return keyCount;
}

int dataSampleStringToNum(char* string, float* samples)
{
    int count = 0;
    char * strtok_res;

    strtok_res = strtok(string, ", ");
    while (strtok_res != NULL)
    {
        *samples = atof(strtok_res);
        samples++;
        count++;
        strtok_res = strtok (NULL, ", ");
    }
    return count;
}
