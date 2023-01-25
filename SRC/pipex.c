/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:54:52 by baltes-g          #+#    #+#             */
/*   Updated: 2023/01/25 14:46:20 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void error(char *str)
{
	perror(str);
	exit(2);
}

void cmd_not_found(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n", 21);
	exit(127);
}

char *get_path(char **envp, char *exe)
{
	char **paths;
	
	while (envp && *envp && ft_strncmp(*envp, "PATH=", 4))
		++envp;
	if (!envp || !(*envp))
		paths = ft_split("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", ':');
	else
	{
		if (ft_strchr(exe, '/'))
				*envp = ft_strjoin(*envp, ":.");
		paths = ft_split(*envp + 5, ':');
	}
	while (paths && *paths)
	{
		char *tmp = ft_strjoin(*paths, "/");
		char *path = ft_strjoin(tmp, exe);
		if (ft_strchr(exe, '/') == exe)
			path = exe;
		free(tmp);
		if (access(path, X_OK) == 0)
			return path;
		free(path);
		paths++;
	}
	char *error_msg = ft_strjoin("pipex: ", exe);
	cmd_not_found(error_msg);
	return (NULL);
}

/*static void check_file(char *file, int mode)
{
	if (mode == R_OK)
	{
		if (access(file, F_OK))
			exit(2);
		else if (access(file, mode))
			exit(2);
	}
	else
	{
		if (!access(file, F_OK))
		{
			if (access(file, mode))
				exit(2);
		}
	}
}*/

int main(int argc, char **argv, char **envp)
{
	int fd_file1;
	int fd_file2;
	char **args;
	int status;

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
		//check_file(argv[1], R_OK);
		dup2(fd_file1,0);
		dup2(p[1], 1);
		close(p[1]);
		close(p[0]);
		args = ft_split(argv[2], ' ');
		execve(get_path(envp, args[0]), args, envp);
		exit(2);
	}
	int chl2 = fork();
	if (chl2 == 0)
	{
		//check_file(argv[1], W_OK);
		fd_file2 = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (fd_file2 == -1) error("pipex: output");
		dup2(fd_file2,1);
		dup2(p[0], 0);
		close(p[1]);
		close(p[0]);
		args = ft_split(argv[3], ' ');
		execve(get_path(envp, args[0]), args, envp);
		exit(2);
	}
	close(p[0]);
	close(p[1]);
	waitpid(chl1, &status, 0);
	waitpid(chl2, &status, 0);
	return (WEXITSTATUS(status));
}