typedef struct
{
    char key[30];
    char value[300];
    int valCnt;
}jsonData;

void processSensorData(char* input,  void (*fp_print)(char*));
void frameSMADataForPrint(float* data, int count, char* buff);
void calcMovingAverage(float* inputSeries, int inputSize, int window, float* output );
void getMinAndMax(float* arr, int n, float* min, float* max);
