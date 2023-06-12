#include "Dio.h"
#include "delay.h"
#define led DIO_CHANNEL_PC13
int main(void){
	config(led,OUTPUT);
	Dio_WriteChannel(led,STD_HIGH); 
	
	while(1)
	{
			Dio_WriteChannel(led,STD_LOW);
			DelayMs(1000);
			Dio_WriteChannel(led,STD_HIGH);
			DelayMs(1000);
	}
}
