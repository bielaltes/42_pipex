/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:54:52 by baltes-g          #+#    #+#             */
/*   Updated: 2023/01/26 20:22:50 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../libft/libft.h"

void	error(char *str)
{
	perror(str);
	exit(2);
}

void	cmd_not_found(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n", 21);
	exit(127);
}

char	*get_path(char **envp, char *exe)
{
	char	**paths;
	char	*path;
	char	*tmp;

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
		tmp = ft_strjoin(*paths, "/");
		path = ft_strjoin(tmp, exe);
		if (ft_strchr(exe, '/') == exe)
			path = exe;
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		else if (access(path, F_OK) == 0)
			exit (126);
		free(path);
		paths++;
	}
	cmd_not_found(ft_strjoin("pipex: ", exe));
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd_file1;
	int		fd_file2;
	char	**args;
	int		status;
	int		p[2];
	int		chl1;
	int		chl2;

	if (argc != 5)
		error("input");
	if ((pipe(p)) == -1)
		error("pipe");
	chl1 = fork();
	if (chl1 == 0)
	{
		fd_file1 = open(argv[1], O_RDONLY);
		if (fd_file1 == -1)
			error("pipex: input");
		dup2(fd_file1, 0);
		dup2(p[1], 1);
		close(p[1]);
		close(p[0]);
		args = ft_split(argv[2], ' ');
		execve(get_path(envp, args[0]), args, envp);
		exit(2);
	}
	chl2 = fork();
	if (chl2 == 0)
	{
		fd_file2 = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (!access(argv[4], X_OK))
			exit(1);
		if (fd_file2 == -1)
			error("pipex: output");
		dup2(fd_file2, 1);
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
