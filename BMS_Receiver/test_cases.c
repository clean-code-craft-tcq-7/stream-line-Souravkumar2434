#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "receiver.h"
#include "jsonParser.h"
#include "test_cases.h"

char test_buff[200];

void test_print(char* buff)
{
    memset(test_buff, 0, 200);
    strncpy(test_buff, buff, strlen(buff));
}

void test_functions(void)
{
    test_jsonParser();
    test_receiver();
}

void test_jsonParser(void)
{
    // Test case ti test convert data sting array to floating point array
    char input[] = "23, 24, 25.5, 26";
    int count, i = 0;
    float output[4];
    float result[] = {23.0, 24.0, 25.5, 26};
    count = dataSampleStringToNum(input,output);
    assert(count == 4);
    while(i < 4)
    {
        assert(fabs(output[i] - result[i]) < 0.01);
        i++;
    }

    // Test case to check convertJsonToData with non Json input
    char data[] = "{}";
    jsonData json[5];
    count = convertJsonToData(data, json);
    assert(count == 0);

    // Test case to check convertJsonToData with one key value pair
    char data1[] = "{\"Age\" : [25]}";
    count = convertJsonToData(data1, json);
    assert(count == 1);
    assert(strcmp(json[0].key, "Age") == 0);
    assert(strcmp(json[0].value, "25") == 0);
    assert(json[0].valCnt == 1);

    // Test case to check convertJsonToData with one key value pair with multiple values
    char data2[] = "{\"Age\" : [25, 26, 27]}";
    count = convertJsonToData(data2, json);
    assert(count == 1);
    assert(strcmp(json[0].key, "Age") == 0);
    assert(strcmp(json[0].value, "25, 26, 27") == 0);
    assert(json[0].valCnt == 3);

    // Test case to check convertJsonToData with two key value pair with multiple values
    char data3[] = "{\"Age\" : [25, 26, 27], \"Marks\" : [95, 96, 97]}";
    count = convertJsonToData(data3, json);
    assert(count == 2);
    assert(strcmp(json[0].key, "Age") == 0);
    assert(strcmp(json[0].value, "25, 26, 27") == 0);
    assert(json[0].valCnt == 3);
    assert(strcmp(json[1].key, "Marks") == 0);
    assert(strcmp(json[1].value, "95, 96, 97") == 0);
    assert(json[1].valCnt == 3);

    // Test case to check convertJsonToData with nested key value pair with single values
    char data4[] = "{\"data\":{\"Age\" : [25, 26, 27], \"Marks\" : [95, 96, 97]}}";
    count = convertJsonToData(data4, json);
    assert(count == 3);
    assert(strcmp(json[0].key, "data") == 0);
    assert(strcmp(json[0].value, "\"Age\" : [25, 26, 27], \"Marks\" : [95, 96, 97]") == 0);
    assert(strcmp(json[1].key, "Age") == 0);
    assert(strcmp(json[1].value, "25, 26, 27") == 0);
    assert(json[1].valCnt == 3);
    assert(strcmp(json[2].key, "Marks") == 0);
    assert(strcmp(json[2].value, "95, 96, 97") == 0);
    assert(json[2].valCnt == 3);
}
void test_receiver(void)
{
    // Test case to get min and max in an array
    float data1[] = {2.5, 2.1, 3.0, 4.5, 6.0, 20.1, 13.5};
    float min, max;
    getMinAndMax(data1, 7, &min, &max);
    assert(fabs(min - 2.1) < 0.01);
    assert(fabs(max - 20.1) < 0.01);

    // Test case to check frameSMADataForPrint
    char buff[100];
    frameSMADataForPrint(data1, 7, buff);
    assert(strcmp(buff, "2.50, 2.10, 3.00, 4.50, 6.00, 20.10, 13.5\n"));

    // Test case for moving average
    float input[] = {1, 2, 2, 3, 6, 8, 9, 2, 1, 2, 1};
    float ouput[11];
    float result[11] = {0.20, 0.60, 1.00, 1.60, 2.80, 4.20, 5.60, 5.60, 5.20, 4.40, 3.00};
    int i = 0;
    calcMovingAverage(input, 11, 5, ouput);
    while(i < 11)
    {
        assert(fabs(ouput[i] - result[i]) < 0.01);
        i++;
    }

    //Test case to check processSensorData with invalid json content
    char data[] = "{}";
    processSensorData(data,&test_print);
    assert(strcmp(test_buff, "No valid json data\n") == 0);

    //Test case to check processSensorData with one sensor json content
    char data2[] = "{\"data\":{\"Temperature\" : [25, 26, 27]}}";
    processSensorData(data2,&test_print);
    assert(strcmp(test_buff,"Temperature\nmin:25.00  max:27.00\nSMA:5.00, 10.20, 15.60\n") == 0);

    char data3[] = "{\"data\":{\"Temperature\" : [25, 26, 27], \"ChargeRate\" : [0.5, 0.3, 0.7, 0.4]}}";
    processSensorData(data3,&test_print);
    assert(strcmp(test_buff,"Temperature\nmin:25.00  max:27.00\nSMA:5.00, 10.20, 15.60\nChargeRate\nmin:0.30  max:0.70\nSMA:0.10, 0.16, 0.30, 0.38\n") == 0);
}
