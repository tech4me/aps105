#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double gaussFunc(double x, double spread);

int main(void)
{
    double spreadNum, limitA, limitB, midX, outResult=0;
    int inputN, i;
    do
    {
        printf("Enter the spread value (must be >0): ");
        scanf("%lf",&spreadNum);
    }
    while(spreadNum<=0);
    do
    {
        printf("Please enter the numbeer of rectangles (n): ");
        scanf("%d", &inputN);  
        printf("Enter the interval of integration (a b): ");
        scanf("%lf %lf", &limitA, &limitB);
        midX=limitA;
        for(i=0;i<inputN;i++)
        {
            midX=((limitB-limitA)/inputN)+midX;
            outResult=outResult+gaussFunc(midX,spreadNum)*((limitB-limitA)/inputN);
        }
        printf("Integral of Gaussian with spread %.3f on [%.3f, %.3f] with n = %d is: %.3f\n", spreadNum, limitA, limitB, inputN, outResult);
        outResult=0;
    }
    while(inputN>=1);
}

double gaussFunc(double x, double spread)
{
    double outArea;
    outArea=pow(M_E, -(x*x)/spread);
    return outArea;
}