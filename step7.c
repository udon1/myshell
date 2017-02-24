#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXCMDLEN 256
#define MAXWORDNUM 80
#define PATHNAME_SIZE 512

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
	pid_t pid;
	int *status;
	char *home = getenv("HOME");
	char cur[PATHNAME_SIZE];
	int *inpnum;

	while(1) {
		procID = 0;
		ac = 1;
		char cmd[MAXCMDLEN] = {0};

		printf("mysh $: ");
		if(fgets(cmd, MAXCMDLEN, stdin) == NULL) {
			fprintf(stderr, "input error\n");
		}


		split_cmd(cmd, &ac, av);

		//print_args(ac, av);
		//printf("count_pipe: %d\n", count_pipe(ac, av));
		av[ac] = NULL;

		for (i = 0; i < count_pipe(ac, av) + 1; i++) {
			split_proc(procID, ac, av, &pac, pav);
			procID++;

			if (!strcmp(pav[0], "exit")) {
				exit(0);
			} else if (!strcmp(pav[0], "cd")) {
				if (pac == 1) {
					chdir(home);
				} else {
					chdir(pav[1]);
				}
				pid = fork();
				if (pid < 0) {
					printf("Error\n");
				} else if(pid == 0) {
					execvp(pav[0] , pav);
				} else {
					wait(status);
				}

			fd = open(pav[inpnum + 1], O_WRONLY|O_CREAT|O_TRUNC, 0644);
			close(1);
			dup(fd);
			close(fd);

			}
			//printf("pav[0]: %s\n", pav[0]);
			//printf("pav[pac]: %s\n", pav[pac]);
			//printf("av[ac - 1]: %s\n", av[ac - 1]);
			//printf("av[ac]: %s\n", av[ac]);
			//printf("pid: %d\n", pid);
			//printf("HomePath: %s\n", home);
		}
		return 0;
	}
}

	void split_cmd(char* cmd, int* ac, char* av[]) {
		int i, j;
		j = 0;

		av[0] = &cmd[0];

		for (i = 0; i < MAXCMDLEN; i++) {
			if (cmd[i] == '\n') {
				cmd[i] = '\0';
			}
		}

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

		//for (i = 0; i < MAXWORDNUM; i++) {
		//if (*av[i] == '\n') {
		//*av[i] = '\0';
		//}
		//}


	}

	void print_args(int ac, char** av) {
		int i;
		printf("ac: %d\n", ac);
		for (i = 0; i < ac; i++) {
			printf("av[%d]: %s\n", i, av[i]);
		}
	}

	void split_proc(int procID, int ac, char *av[], int *pac, char *pav[]) {
		int i;
		static int avnum;
		int pavnum;

		if (procID == 0) {
			avnum = 0;
		} else {
			avnum++;
		}

		for (pavnum = 0; avnum < ac && *av[avnum] != '|'; avnum++, pavnum++) {
			pav[pavnum] = av[avnum];

			if (pav[pavnum] == '>') {
				*inpnum = avnum;
			}
		}

		pav[pavnum] = NULL;
		*pac = pavnum;

		//printf("ProcID: %d\n", procID);
		//printf("Pac: %d\n", *pac);

		for (i = 0; i <= *pac; i++) {
			//printf("Pav[%d]: %s\n", i, pav[i]);
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
