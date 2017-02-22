#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCMDLEN 256
#define MAXWORDNUM 80

void split_cmd(char *cmd, int *ac, char *av[]);

void split_proc(int procID, int ac, char *av[], int *Pac, char *Pav[]);

void print_arg(char* arg);

void print_args(int ac, char **av);

int count_pipe(int ac, char *av[]);

int avnum = 0;

int main (){
	int i;

	char *av[MAXWORDNUM];
	char *Pav[MAXWORDNUM];
	int ac;
	int Pac;
	int procID;
	while(1) {
		procID = 0;
		ac = 1;
		char cmd[MAXCMDLEN] = {0};

		printf("mysh $: ");
		if(fgets(cmd, MAXCMDLEN, stdin) == NULL) {
			fprintf(stderr, "input error\n");
		}

		split_cmd(cmd, &ac, av);

		print_args(ac, av);
		printf("count_pipe: %d\n", count_pipe(ac, av));

		for (i = 0; i < count_pipe(ac, av) + 1; i++) {
			procID++;
			split_proc(procID, ac, av, &Pac, Pav);
		}
		avnum = 0;
	}

	return 0;
}


void split_cmd(char* cmd, int* ac, char* av[]) {
	int i, j;
	j = 0;
	// *ac = 0;

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
				j++;
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
	printf("ac: %d\n", ac);
	for (i = 0; i < ac; i++) {
		printf("av[%d]: %s\n", i, av[i]);
		// print_arg(av[i]);
	}
}



void split_proc(int procID, int ac, char *av[], int *Pac, char *Pav[]) {
	int i;
	int Pac2;
	Pac2 = 0;

	for (i = avnum ; i < ac; i++) {
		if (*av[i] == '|') {
			// *procID += 1;
			avnum++;
			break;
		}
	
//		if (*av[i] == ' ' || *av[i] == '\t' || *av[i] == '<' ||
//			*av[i] == '>' || *av[i] == '&') {
//			i++;
//		} else {
			Pav[procID - 1] = av[avnum];
//			Pac++;
			Pac2++;
			avnum++;
//		}
	}
	// procID += 1;
	printf("ProcID: %d\n", procID);
//	printf("Pac: %d\n", count_pipe(Pac, &Pav));
	printf("Pac: %d\n", Pac2);
//	printf("Pav: %s\n", *Pav);
	
	for (i = 0; i < Pac2; i++) {
		printf("Pav[%d]: %s\n", i, Pav[i]); 
	}

}

int count_pipe(int ac, char *av[]){
	int i;
	int n = 0;

	for (i = 0; i < ac; i++) {
		if (*av[i] == '|') {
		// if (strcmp(av[i], "|")) {
			n++;
		}
	}

	return n;
}
