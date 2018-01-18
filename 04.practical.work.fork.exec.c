#include <stdio.h>
#include <unistd.h>


int main() {
	printf("Main before fork() \n");
	int pid1 = fork();
	if (pid1 == 0) {
		char *args[]= { "/bin/ps", "-ef" , NULL};
		execvp("/bin/ps", args);
		printf("Finished launching ps -ef\n");
	}
	int pid2 = fork();
	if (pid2 == 0) {
		char *args[]= { "free", "-h", NULL};
		execvp("free", args);
		printf("Finished launching free -h\n");
	}
	return 0;
}
