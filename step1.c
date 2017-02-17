#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define MAX 256

int main(void)
{
	char str[MAX];
	int len = strlen(str);

	memset(str, '\0', len);

	while (1) {
		fprintf(stdout, "mysh $");

		if ((fgets(str,MAX,stdin)) == NULL){
			exit(1);
		}
		printf("%s", str);
	}
	return 0;
}
