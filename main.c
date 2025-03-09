/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:45:15 by mohidbel          #+#    #+#             */
/*   Updated: 2025/03/09 15:07:52 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	handle_fds_one(char **av, int *fds)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror(av[1]);
		return (1);
	}
	if (dup2(fd, 0) < 0 || dup2(fds[1], 1) < 0)
	{
		perror("dup2 Error");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static pid_t	exec_cmd_one(char **path, char **av, char **env, int *fds)
{
	char	*path_v;
	char	**cmd;
	pid_t	id_one;

	id_one = fork();
	if (id_one == -1)
		clear_exit(path, NULL, fds, 1);
	if (id_one == 0)
	{
		cmd = ft_split(av[2], ' ');
		if (!cmd || !*cmd)
			clear_exit(path, cmd, fds, 1);
		if (handle_fds_one(av, fds))
			clear_exit(path, cmd, fds, 1);
		path_v = find_cmd_path(path, cmd[0]);
		if (!path_v)
			clear_exit(path, cmd, fds, 127);
		free_arr(path);
		(close(fds[0]), close(fds[1]));
		execve(path_v, cmd, env);
		perror("exec Error");
		free(path_v);
		clear_exit(NULL, cmd, NULL, 1);
	}
	return (id_one);
}

static int	handle_fds_two(char **av, int *fds)
{
	int	fd;

	fd = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(av[4]);
		return (1);
	}
	if (dup2(fds[0], 0) < 0 || dup2(fd, 1) < 0)
	{
		perror("dup2 Error");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static pid_t	exec_cmd_two(char **path, char **av, char **env, int *fds)
{
	char	*path_v;
	char	**cmd;
	pid_t	id_two;

	id_two = fork();
	if (id_two == -1)
		clear_exit(path, NULL, fds, 1);
	if (id_two == 0)
	{
		cmd = ft_split(av[3], ' ');
		if (!cmd || !*cmd)
			clear_exit(path, cmd, fds, 1);
		if (handle_fds_two(av, fds))
			clear_exit(path, cmd, fds, 1);
		path_v = find_cmd_path(path, cmd[0]);
		if (!path_v)
			clear_exit(path, cmd, fds, 127);
		free_arr(path);
		(close(fds[0]), close(fds[1]));
		execve(path_v, cmd, env);
		perror("exec Error");
		free(path_v);
		clear_exit(NULL, cmd, NULL, 1);
	}
	return (id_two);
}

int	main(int ac, char **av, char **env)
{
	char	**paths;
	int		fds[2];
	int		status;
	pid_t	id_one;
	pid_t	id_two;
 
	if (ac != 5 || pipe(fds) == -1)
		return (1);
	paths = ft_split(find_path(env), ':');
	if (!paths)
		return (close(fds[0]), close(fds[1]), 1);
	id_one = exec_cmd_one(paths, av, env, fds);
	id_two = exec_cmd_two(paths, av, env, fds);
	close(fds[1]);
	close(fds[0]);
	waitpid(id_one, NULL, 0);
	waitpid(id_two, &status, 0);
	free_arr(paths);
	return (status);
}
