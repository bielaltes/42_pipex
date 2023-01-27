/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:20:04 by baltes-g          #+#    #+#             */
/*   Updated: 2023/01/27 11:52:48 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define BASH "bash: "
# define PIPEX "pipex: "
# define COPEN ": Cannot open"
# define CNF ": command not found"
# define CCLOSE ": Fd can not be closed"
# define PERM ": Permission denied"
# define BFD ": Bad file descriptor"
# define EPIPE ": error creating pipe"
# define EFORK ": error creating fork"
# define NFILEDIR ": No such file or directory"
# define INARG ": Invalid number of arguments"
# define MALLOCER ": error trying to allocate memory"
# define NEXECVE ": error on execve"

void	error_exit(int status, char *str1, char *str2, char *str3);
char	**get_paths(char **envp, char *exe);
char	*get_path(char **envp, char *exe);

#endif