#include<stdio.h>
#include<string.h>
#include "receiver.h"
#include "jsonParser.h"

void processSensorData(char* input,  void (*fp_print)(char*))
{
    jsonData data[5];
    int keyCount = 0;
    int i = 1;
    char buff[1000];
    char str[500];
    float min,max,samples[50],sma[50];

    keyCount = convertJsonToData(input, data);

    if(keyCount)
    {
        memset(buff,0,1000);
        while(i < keyCount)
        {
            memset(str,0,500);
            sprintf(str, "%s\n",data[i].key);
            strcat(buff, str);
            dataSampleStringToNum(data[i].value, samples);
            getMinAndMax(samples, data[i].valCnt, &min, &max);
            memset(str,0,500);
            sprintf(str, "min:%0.2f  max:%0.2f\n", min, max);
            strcat(buff, str);
            memset(str,0,500);
            calcMovingAverage(samples, data[i].valCnt, 5, sma);
            frameSMADataForPrint(sma, data[i].valCnt, str);
            strcat(buff, str);
            i++;
        }
    }
    else
    {
        sprintf(buff,"%s\n", "No valid json data" );
    }
    fp_print(buff);
}

void getMinAndMax(float* arr, int n, float* min, float* max)
{
    int i;
    float mx = arr[0];
    float mn = arr[0];

    for(i = 1; i < n; i++)
    {
        if(arr[i] > mx)
        {
            mx = arr[i];
        }

        if(arr[i] < mn)
        {
            mn = arr[i];
        }
    }
    *min = mn;
    *max = mx;
}

void calcMovingAverage(float* inputSeries, int inputSize, int window, float* output )
{
    float sum = 0 ;
    int i=0;

    for( i = 0; i < inputSize; i++ )
    {
        sum += inputSeries[i] ;
        if( i >= window )
        {
            sum -= inputSeries[i - window] ;
        }
        output[i] = sum / window ;
    }
}

void frameSMADataForPrint(float* data, int count, char* buff)
{
    int i=0;
    char str[20];

    strcat(buff,"SMA:");
    while( i < count )
    {
        memset(str, 0, 20);
        sprintf(str,"%0.2f, ",data[i]);
        strcat(buff,str);
        i++;
    }

    buff[strlen(buff) - 2] = '\n';
    buff[strlen(buff) - 1] = '\0';
}
