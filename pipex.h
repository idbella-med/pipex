/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:45:22 by mohidbel          #+#    #+#             */
/*   Updated: 2025/03/08 11:15:41 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include "Libft/libft.h"

char	*find_path(char **env);
void	free_arr(char **arr);
char	*find_cmd_path(char **paths, char *cmd);
void	clear_exit(char **paths, char **cmd, int *fds, int status);

#endif