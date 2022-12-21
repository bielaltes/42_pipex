/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:54:52 by baltes-g          #+#    #+#             */
/*   Updated: 2022/12/21 15:12:06 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void error(char *str)
{
	perror(str);
	exit(2);
}

char *get_path(char **envp, char *exe)
{
	char **paths;
	//write(2, "h", 1);
	while (envp && ft_strncmp(*envp, "PATH=", 4))
		++envp;
	if (!envp)
	{
		error("no environment");
	}
	paths = ft_split(*envp + 5, ':');
	while (paths++)
	{
		char *tmp = ft_strjoin(*paths, "/");
		char *path = ft_strjoin(tmp, exe);
		free(tmp);
		if (access(path, 0) == 0)
			return path;
		free(path);
	}
	return (NULL);
}

int main(int argc, char **argv, char **envp)
{
	int fd_file1;
	int fd_file2;
	char **args;

	if (argc != 5)
		error("input");
	int p[2];
	if ((pipe(p)) == -1)
		error("pipe");
	int chl1 = fork();
	if (chl1 == 0)
	{
		fd_file1 = open(argv[1], O_RDONLY);
		if (fd_file1 == -1) error("pipex: input");
		dup2(fd_file1,0);
		dup2(p[1], 1);
		close(p[1]);
		close(p[0]);
		args = ft_split(argv[2], ' ');
		execve(get_path(envp, args[0]), args, envp);
	}
	int chl2 = fork();
	if (chl2 == 0)
	{
		fd_file2 = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (fd_file2 == -1) error("pipex: output");
		dup2(fd_file2,1);
		dup2(p[0], 0);
		close(p[1]);
		close(p[0]);
		args = ft_split(argv[3], ' ');
		execve(get_path(envp, args[0]), args, envp);
	}
	close(p[0]);
	close(p[1]);
	waitpid(chl1, NULL, 0);
	waitpid(chl2, NULL, 0);
}