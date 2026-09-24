#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	int i = 0;
	pid_t pid;
	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork falhou\n");
		return 1;
	}
	else if (pid == 0) {
		// printf("Eu sou o processo filho. Meu PID é %d\n", getpid());
		// printf("O PID do meu processo pai é %d\n", getppid());
		for (int j = 0; j < 10; j++) {
			i += 100;
			printf("Processo Filho: i -> %d\n", i);
		}
	}
	else {
		// sleep(2);
		// printf("Eu sou o processo pai. Meu PID é %d\n", getpid());
		// printf("O PID do meu processo filho é %d\n", pid);
		for (int j = 0; j < 10; j++) {
			i += 100;
			printf("Processo Pai: i -> %d\n", i);
		}

	}
	return 0;
}

