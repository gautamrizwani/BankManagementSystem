#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
void main() {
	char* pass = getpass("Nakho kaik ");

	printf("%s\n", pass);
}
