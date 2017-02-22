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

int main (){
	int i;

	char *av[MAXWORDNUM];
	char *pav[MAXWORDNUM];
	int ac;
	int pac;
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
			split_proc(procID, ac, av, &pac, pav);
			procID++;
		}
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



void split_proc(int procID, int ac, char *av[], int *pac, char *pav[]) {
	int i;
	*pac = 0;
	static int avnum;
	int pavnum = 0;

	if (procID == 0) {
		avnum = 0;
	} else {
		avnum++;
	}


	for (i = 0; i < ac && *av[avnum] == '|'; avnum++) {
		pav[pavnum] = av[avnum];
		pavnum++;
	}

	pav[pavnum] = NULL;
	*pac = pavnum;

	printf("ProcID: %d\n", procID);
	//	printf("Pac: %d\n", count_pipe(pac, &pav));
	printf("Pac: %d\n", *pac);
	//	printf("Pav: %s\n", *pav);

	for (i = 0; i < *pac; i++) {
		printf("Pav[%d]: %s\n", procID, pav[pavnum]);
	}

}

int count_pipe(int ac, char *av[]){
	int i;
	int n = 0;

	for (i = 0; i < ac; i++) {
		if (*av[i] == '|') {
			n++;
		}
	}

	return n;
}
