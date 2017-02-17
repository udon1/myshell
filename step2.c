#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCMDLEN 256
#define MAXWORDNUM 80

void split_cmd(char* cmd, int* ac, char* av[]);


void print_arg(char* arg);
void print_args(int ac, char** av);


int main (){
	char *av[MAXWORDNUM];
	int ac;

	while(1) {
		ac = 1;
		char cmd[MAXCMDLEN] = {0};

		printf("mysh $: ");
		if(fgets(cmd, MAXCMDLEN, stdin) == NULL) {
			fprintf(stderr, "input error\n");
		}

		split_cmd(cmd, &ac, av);

		print_args(ac, av);
	}

	return 0;
}


void split_cmd(char* cmd, int* ac, char* av[]) {
	int i, j;
	j = 0;

	av[0] = &cmd[0];

	for (i = 1; i < MAXWORDNUM;i++) {
		for (; j < MAXCMDLEN; j++) {
			if(cmd[j] == '|' || cmd[j] == '>' ||
					cmd[j] == '<' || cmd[j] == '&') {
				if (cmd[j + 1] == ' ' || cmd[j + 1] == '\t') {
					// 終端文字に変える
					av[i] = &cmd[j];
					cmd[j + 1] = '\0';  
					i++;
					j++;	
					*ac += 1;   
				} else {
					printf("Error\n");
					exit(1);
				}

			} else if (cmd[j] == ' ' || cmd[j] == '\t') {
				cmd[j] = '\0';
				av[i] = &cmd[j + 1];
				i++;
				*ac += 1;
			}
		}
	}	
}

void print_arg(char* arg) {
	printf("%s\n", arg);
}

void print_args(int ac, char** av) {
	int i;
	for (i = 0; i < ac; i++) {
		print_arg(av[i]); 
	}
}
