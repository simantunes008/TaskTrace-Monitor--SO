#include "../include/util.h"

void execute(int time, char * prog) {

    int fd1 = open("tmp/stats", O_WRONLY);
    if (fd1 == -1) {
		perror("Failed to open FIFO\n");
        return;
	}

    pid_t pid = getpid();
	char s_pid[20];

	sprintf(s_pid, "tmp/%d", pid);

    if (mkfifo(s_pid, 0777) == -1) {
        if (errno != EEXIST) {
            perror("Could not create fifo file\n");
            return;
        }
    }

    Task t;
    t.pid = pid;
    t.time = time;
    strcpy(t.cmd, "execute");
    strcpy(t.prog, prog);

    write(fd1, &t, sizeof(t));

    close(fd1);


    int fd2 = open(s_pid, O_RDONLY);
    if (fd2 == -1) {
		perror("Failed to open FIFO\n");
        return;
	}

    int a;

    read(fd2, &a, sizeof(int));

    printf("Task ID: %d\n", a);  

    close(fd2);

    unlink(s_pid);
}


void status() {
    int fd1 = open("tmp/stats", O_WRONLY);
    if (fd1 == -1) {
		perror("Failed to open FIFO\n");
        return;
	}

    pid_t pid = getpid();
	char s_pid[20];

	sprintf(s_pid, "tmp/%d", pid);

    if (mkfifo(s_pid, 0777) == -1) {
        if (errno != EEXIST) {
            perror("Could not create fifo file\n");
            return;
        }
    }

    Task t;
    t.pid = pid;
    t.time = 0;
    strcpy(t.cmd, "status");
    strcpy(t.prog, "");

    write(fd1, &t, sizeof(t));

    close(fd1);


    // int fd2 = open(s_pid, O_RDONLY);
    // if (fd2 == -1) {
		// perror("Failed to open FIFO\n");
        // return;
	// }
// 
    // int a;
// 
    // read(fd2, &a, sizeof(int));
// 
    // printf("Task ID: %d\n", a);  
// 
    // close(fd2);
// 
    // unlink(s_pid);
}


int main(int argc, char ** argv) {

    if (argc == 1) {
		printf("Invalid Input\n");
		return 0;
	}

	if (mkfifo("tmp/stats", 0777) == -1) {
        if (errno != EEXIST) {
            perror("Could not create fifo file\n");
            return 1;
        }
    }
    
    if (!strcmp(argv[1], "execute") && argc == 5) {
        if (!strcmp(argv[3], "-u")) {
            execute(atoi(argv[2]), argv[4]);


        } else if (!strcmp(argv[3], "-p")) {
			// TODO
            

		} else {
            printf("Invalid option\n");
        }


    } else if (!strcmp(argv[1], "status") && argc == 2) {
        status();


    } else {
        printf("Invalid option\n");
    }

    return 0;
}