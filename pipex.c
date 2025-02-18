#include "pipex.h"

void ft_free(char **split)
{
    int i;

    i = 0;
    if (split == NULL)
        return;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}


char *find_path(char *cmd, char **env)
{
    char **all_paths;
    char *part;
    char *path;
    int i;

    i = 0;
    while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
        i++;
   if (!env[i])
    {
        write(2, "Error: PATH environment variable not found\n", 42);
        return (NULL);
    }
    all_paths = ft_split(env[i] + 5, ':');
    i = 0;
    while (all_paths[i])
    {
        part = ft_strjoin(all_paths[i], "/");
        path = ft_strjoin(part, cmd);
        free(part);
        if (access(path, F_OK) == 0)
        {
            ft_free(all_paths);
            return (path);
        }
        free(path);
        i++;
    }
    ft_free(all_paths);
    return (NULL);
}

void child_process(int pipefd[], char **av, char **env)
{
    char *path;
    char **cmd_args = ft_split(av[2], ' ');
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    path = find_path(cmd_args[0], env);
    if (path == NULL)
    {
        perror("Command not found");
        exit(1);
    }
    execve(path, cmd_args, env);
    perror("Execve failed");
    exit(1);
}

void parent_process(int pipefd[], char **av, char **env)
{
    char *path;
    char **cmd_args = ft_split(av[3], ' ');
    int fd_out;

    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);

    fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out == -1)
    {
        perror("Output file open failed");
        exit(1);
    }
    dup2(fd_out, STDOUT_FILENO);
    close(fd_out);
    path = find_path(cmd_args[0], env);
    if (path == NULL)
    {
        perror("Command not found");
        exit(1);
    }
    execve(path, cmd_args, env);
    perror("Execve failed");
    exit(1);
}


int main(int ac, char **av, char **env)
{
    int pipefd[2];
    pid_t pid;

    if (ac == 5)
    {
        if (pipe(pipefd) == -1)
            return (perror("Pipe failed"), 1);
        pid = fork();
        if (pid == 0)
            child_process(pipefd, av, env);
        else if (pid > 0)
        {
            waitpid(pid, NULL, 0);
            parent_process(pipefd, av, env);
        }
        else
            return (perror("Fork failed"), 1);
    }
    else
    {
        write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40);
        return (1);
    }
}
