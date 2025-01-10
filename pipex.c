#include "pipex.h"

char *find_path(char *cmd, char **env)
{
    char **paths;
    char *part_path;
    char *path;
    int i = 0;
    while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
    while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void    child_process(char **av, char **env)
{
    char *path;
    path = find_path(av[2], env);
    execve(&av[1], &av[2], &path);
}

void    parent_process(char **av, char **env)
{
    char *path;
    path = find_path(av[3], env);
    execve(&av[4], &av[3], &path);
}

int main(int ac, char **av, char **env)
{
    pid_t pid;
    pid = fork();
    if (pid == 0)
        child_process(av, env);
    parent_process(av, env);
}