#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
/*#include <spawn.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

//int posix_spawn(pid_t *pid, const char *path, const posix_spawn_file_actions_t *file_actions, const posix_spawnattr_t *attrp, char *argv[], char *const envp[])
int posix_spawn(pid_t *pid, const char *path, void *file_actions, void *attrp, char *argv[], char *const envp[])
{
    pid_t retpid;

    retpid = fork();
    if(retpid == -1){/* Failure to fork */
        return -1;
    } else if(retpid == 0){/* child */
        environ = (char **)envp;
        printf("About to spawn \"%s\" arg: \"%s\", \"%s\" \n", path, argv[1], argv[2]);
        execv(path, argv);
        printf("NONREACHED\n");
        exit(127);
    } else {/* parent */
        *pid = retpid;
        return 0;
    }
}

int
main (int argc, char **argv)
{
    pid_t pid, wpid;
    int status;

    
    if (argc != 3)
    {
        fprintf(stderr, "usage: %s hostname\n", argv[0]);
        return 1;
    }
    
    posix_spawn(&pid, argv[1], NULL, NULL, &argv[1] /*char *argv[]*/, NULL);
    wpid = waitpid(pid,&status,0);
    if (wpid == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }


    if (WIFEXITED(status)) {
        printf("child exited, status=%d\n", WEXITSTATUS(status));


    } else if (WIFSIGNALED(status)) {
        printf("child killed (signal %d)\n", WTERMSIG(status));


    } else if (WIFSTOPPED(status)) {
        printf("child stopped (signal %d)\n", WSTOPSIG(status));
    }
}
