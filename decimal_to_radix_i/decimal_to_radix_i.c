#include <stdio.h>
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
void Dec2RadixI(int decValue, int radValue);
void clear_buffer();

int main() {
	// 2.5a
	printf(TITLE, AUTHOR, YEAR);			// print introduction

	// 2.5c
	int32_t input;
	int32_t radix;
	while (true) {
		printf("Enter a decimal number: ");		// request number for conversion
		int error = scanf("%u", &input);	
		if (error == 0) {
			printf("Invalid input\n");
			clear_buffer();
			continue;
		}
		if (input < 0) {
			break;
		}
		printf("The number you have entered is %d\n", input);

		// 2.5d & 2.5e	
		printf("Enter a radix for the converter between 2 and 16: ");
		error = scanf("%d", &radix);
		if (error == 0) {
			printf("Invalid input\n");
			clear_buffer();
			continue;
		}
		if (radix < 0) {
			break;
		}
		printf("The radix you have entered is %d\n", radix);

		// 2.5 f
		float shannons = log2f((float)input);
		printf("The log2 of the numer is %.2f\n", shannons);

		// 2.5g
		int int_div = input / radix;
		printf("The integer result of the number divided by %d is %d\n", radix, int_div);

		// 2.5h
		int remainder = input - int_div * radix;
		printf("The remainder is %d\n", remainder);

		// 2.5i call conversion function
		Dec2RadixI(input, radix);
	}
	printf("EXIT");
	return 0;
}

void Dec2RadixI(int decValue, int radValue) {
	static const char char_set[] = "0123456789ABCDEF";
	char output[100];
	if ((radValue % 2)) {
		int iterations = ceil(log(decValue) / log(radValue));
		for (int i = iterations; i > 0; i--) {
			int current = decValue / pow(radValue, i - 1);
			decValue -= current * (int)pow(radValue, i - 1);
			output[iterations - i] = char_set[current];
		}
		output[iterations] = '\0';
	}
	else {
		int it = log2(radValue);
		int iterations = floor(log2(decValue) / log2(radValue))+1;
		for (int i = 0; i < iterations; i++) {
			int current = decValue & (radValue - 1);
			decValue = decValue >> it;
			output[iterations - i - 1] = char_set[current];
		}
		output[iterations] = '\0';
	}

	printf("%s\n", output);
}

void clear_buffer() {
	while (getchar() != '\n') {
		continue;
	}
}