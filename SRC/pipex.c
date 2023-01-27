/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:54:52 by baltes-g          #+#    #+#             */
/*   Updated: 2023/01/27 11:52:22 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/pipex.h"
#include "../libft/libft.h"

void	first_chld(char **argv, char **envp, int p[2])
{
	int		fd_file1;
	char	**args;

	fd_file1 = open(argv[1], O_RDONLY);
	if (fd_file1 == -1)
		error_exit(2, PIPEX, argv[1], NFILEDIR);
	if (dup2(fd_file1, 0) < 0 || dup2(p[1], 1) < 0)
		error_exit(2, BASH, "dup2", BFD);
	if (close(p[1]) < 0 || close(p[0]) < 0)
		error_exit(2, BASH, "close", CCLOSE);
	args = ft_split(argv[2], ' ');
	if (!args)
		error_exit(2, BASH, "malloc", MALLOCER);
	if (execve(get_path(envp, args[0]), args, envp) < 0)
		error_exit(2, "bash", NEXECVE, NULL);
}

void	second_chld(char **argv, char **envp, int p[2])
{
	int		fd_file2;
	char	**args;

	fd_file2 = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (!access(argv[4], X_OK))
		error_exit(1, PIPEX, argv[4], PERM);
	if (fd_file2 == -1)
		error_exit(2, PIPEX, argv[4], NFILEDIR);
	if (dup2(fd_file2, 1) < 0 || dup2(p[0], 0) < 0)
		error_exit(2, BASH, "dup2", BFD);
	if (close(p[1]) < 0 || close(p[0]) < 0)
		error_exit(2, BASH, "close", CCLOSE);
	args = ft_split(argv[3], ' ');
	if (!args)
		error_exit(2, BASH, "malloc", MALLOCER);
	if (execve(get_path(envp, args[0]), args, envp) < 0)
		error_exit(2, "bash", NEXECVE, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	int		p[2];
	int		chl1;
	int		chl2;

	if (argc != 5)
		error_exit(2, "bash", INARG, NULL);
	if ((pipe(p)) == -1)
		error_exit(2, "bash", EPIPE, NULL);
	chl1 = fork();
	if (chl1 < 0)
		error_exit(2, "bash", EFORK, NULL);
	if (chl1 == 0)
		first_chld(argv, envp, p);
	chl2 = fork();
	if (chl2 < 0)
		error_exit(2, "bash", EFORK, NULL);
	if (chl2 == 0)
		second_chld(argv, envp, p);
	if (close(p[1]) < 0 || close(p[0]) < 0)
		error_exit(2, BASH, "close", CCLOSE);
	waitpid(chl1, &status, 0);
	waitpid(chl2, &status, 0);
	return (WEXITSTATUS(status));
}
