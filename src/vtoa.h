#include <stdio.h>
#include <stdlib.h>

//converts a integer into a string
char *itoa(int i) {

	char *str = calloc(8, sizeof(char));

	sprintf(str, "%d", i);

	return str;
}

//converts a long integer into a string
char *ltoa(long i) {

	char *str = calloc(16, sizeof(char));

	sprintf(str, "%ld", i);

	return str;
}

//converts a float into a string
char *ftoa(float i) {

	char *str = calloc(16, sizeof(char));

	sprintf(str, "%f", i);

	return str;
}
