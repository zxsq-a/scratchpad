/*
 * src.c
 *
 *  Created on: Nov 28, 2018
 *      Author: zxsq
 */
#include <stdio.h>
#include <windows.h>

HANDLE hSerial;
char serialChar[1];


int hpglSplit() {
	FILE * plot;
	FILE * plotScratch;
	char cur[1];
	//char serialChar[1];
	//int curchar;

	plot = fopen("plot.hpgl", "r"); //open plot for reading
	plotScratch = fopen("plotScratch.txt", "w"); //open scratch space for writing

	while (!feof(plot)) {//while not at end of plot file

		fscanf(plot, "%c", cur);//read 1 char per loop into cur

		if(cur == 59){//if semicolon
			Sleep(1500);//sleep 1500 millisecs in windows
			//printf("%c\n", cur);//print the semicolon for testing
		}else if(cur == 83){//if its an S
			//figure how to skip SP# command in the hpgl file
		}else{//if any other character
			//serial send
			serialChar = cur;//set the serialchar to the cur char
			printSerial(serialChar);//print the character in serial
			//printf("%c\n", cur);//print the character in console for test
		}

	}
	if(feof(plot)){//if at end of plotfile
		printf("Plot complete\n");//print to console
	}
	fclose(plot);//close files
	fclose(plotScratch);//not actually used
	return 0;//return normally
}

int serialInit(){//initialize the serial connection in windows
	//HANDLE hSerial;
	DCB dcbSerialParams = {0};
	COMMTIMEOUTS timeouts = {0};

	printf(stderr, "Opening serial port...");
	hserial = CreateFile("\\\\.\\COM1", GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//change com1 to the appropriate comport
	if(hSerial == INVALID_HANDLE_VALUE){
		printf(stderr, "Error\n");
		return 1;

	}else printf(stderr, "OK\n");

	//set serial paramaters (9600baud 8bits no parity 1 stop bit)
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if(GetCommState(hSerial, &dcbSerialParams) == 0){
		printf(stderr, "Err getting device state\n");
		CloseHandle(hSerial);
		return 1;
	}
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if(SetCommState(hSerial, &dcbSerialParams) == 0){
		printf(stderr, "err setting device params 9600 8n1\n");
		closeHandle(hSerial);
		return 1;
	}
	//set comport timeout settings
	//####MAY NEED TO ADJUST FOR LOWER BAUD RATE??
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if(SetCommTimeouts(hSerial, &timeouts) == 0){
		printf(stderr, "Err setting timeouts\n");
		CloseHandle(hSerial);
		return 1;
	}
	return 0;

}
int serialPrint(char ctp){
	//send specified bytes
	DWORD bytes_written, total_bytes_written = 0;
	printf(stderr, "sending bytes..");
	if(!WriteFile(hSerial, serialChar, 1, &bytes_written, NULL)){
		printf(stderr, "Err\n");
		CloseHandle(hSerial);
		return 1;
	}
	printf(stderr, "%d bytes written\n", bytes_written);
	return 0;
}

int closeSerial(){
	printf(stderr, "closing comport");
	if(CloseHandle(hSerial) == 0){
		printf(stderr, "Error\n");
		return 1;
	}
	printf(stderr, "ok\n");
	return 0;
}

int main() {

	serialInit();
	hpglSplit();
	closeSerial();
	//system("pause");
	return 0;
}

