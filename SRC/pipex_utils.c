/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:14:28 by baltes-g          #+#    #+#             */
/*   Updated: 2023/01/27 13:13:07 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/pipex.h"
#include "../libft/libft.h"

void	error_exit(int status, char *str1, char *str2, char *str3)
{
	write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	if (str3)
		write(2, str3, ft_strlen(str3));
	write(2, "\n", 1);
	exit(status);
}

char	**get_paths(char **envp, char *exe)
{
	char	**paths;

	while (envp && *envp && ft_strncmp(*envp, "PATH=", 4))
		++envp;
	if (!envp || !(*envp))
	{
		paths = ft_split("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", ':');
		if (!paths)
			error_exit(2, BASH, "malloc", MALLOCER);
	}
	else
	{
		if (ft_strchr(exe, '/'))
		{
			*envp = ft_strjoin(*envp, ":.");
			if (!envp)
				error_exit(2, BASH, "malloc", MALLOCER);
		}
		paths = ft_split(*envp + 5, ':');
		if (!paths)
			error_exit(2, BASH, "malloc", MALLOCER);
	}
	return (paths);
}

char	*get_path(char **envp, char *exe)
{
	char	**paths;
	char	*path;
	char	*tmp;

	paths = get_paths(envp, exe);
	while (paths && *paths)
	{
		tmp = ft_strjoin(*paths, "/");
		if (!tmp)
			error_exit(2, BASH, "malloc", MALLOCER);
		path = ft_strjoin(tmp, exe);
		if (!path)
			error_exit(2, BASH, "malloc", MALLOCER);
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
	error_exit(127, PIPEX, exe, CNF);
	return (NULL);
}
