#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

// 2.5b
#define TITLE	"******************************\n"\
				" DECIMAL TO RADIX-i converter\n"\
				" Written by: %s\n"\
				" Date: %d\n"\
				"******************************\n"
#define AUTHOR "Theon Smith"
#define YEAR 2022

// 2.5i 
void Dec2RadI(unsigned int decValue, int radValue, char* str, int size);
void clear_buffer();

int main() {
	// 2.5a
	printf(TITLE, AUTHOR, YEAR);				// print introduction

	// 2.5c
	int32_t decValue;							// signed so that it can take in exit input int32 is what my system uses
	int32_t radValue;
	while (true) {
		printf("Enter a decimal number: ");		// request number for conversion
		int error = scanf("%u", &decValue);
		if (error == 0) {						// catch non-numerical input
			printf("Invalid input\n");
			clear_buffer();
			continue;
		}
		if (decValue < 0) {						// exit program on negative numbers
			break;
		}
		printf("The number you have entered is %d\n", decValue);

		// 2.5d & 2.5e	
		printf("Enter a radix for the converter between 2 and 16: ");
		error = scanf("%d", &radValue);
		if ((error == 0) || (radValue == 1) || (radValue == 0) || (radValue > 16)) {
			printf("Invalid input\n");
			clear_buffer();						// otherwise invalid remains in buffer, disrupting program
			continue;
		}
		if (radValue < 0) {
			break;
		}
		printf("The radix you have entered is %d\n", radValue);

		// 2.5 f
		double shannons = log2((double)decValue);
		if (decValue != 0) {					// catch undefined numbers
			printf("The log2 of the number is %.2f\n", shannons);
		}
		else {
			shannons = 0;
			printf("The log2 of the number is undefined\n");
		}
		

		// 2.5g
		int int_div = decValue / radValue;
		printf("The integer result of the number divided by %d is %d\n", radValue, int_div);

		// 2.5h
		int remainder = decValue % radValue;
		printf("The remainder is %d\n", remainder);

		// 2.5i call conversion function
		int size = (int)floor(shannons / log2(radValue)) + 1;			// double has sufficient accuracy for 32bit in inputs and will not fail on log_x (x ^ n)
		char *output = (char*)calloc((int64_t)size + 1, sizeof(char));	// dynamically allocate string to store output
		Dec2RadI(decValue, radValue, output, size);	
		printf("The radix-%d value is %s\n", radValue, output);
		free(output);													// free heap allocated string
	}
	printf("EXIT");
	return 0;
}

void Dec2RadI(unsigned int decValue, int radValue, char* str, int size) {
	static const char char_set[] = "0123456789ABCDEF";				// declare lookup that shouldn't get reallocated on every function call
	if ((radValue & (radValue - 1))) {								// if not a power of 2
		for (int i = size - 1; i > -1; i--) {
			int rem = decValue % radValue;
			decValue /= radValue;
			str[i] = char_set[rem];									// pick relevant character from lookup
		}
	}
	else {
		// The above algorithm works for all bases, however,
		// the below algorithm should take fewer clock cycles on applicable values
		// more an exercise on bitwise operators
		int shift = 0;
		int tempRad = radValue;
		while (tempRad > 1) {					// take log2 of radix 
			shift++;
			tempRad >>= 1;
		}		
		for (int i = size - 1; i > -1; i--) {
			int current = decValue & (radValue - 1);	// mask relevant bits
			decValue >>= shift;							// shift converted bits
			str[i] = char_set[current];
		}
	}
	str[size] = '\0';									// append string end character
}

void clear_buffer() {
	while (getchar() != '\n') {							// read all input left on current line
		continue;
	}
}