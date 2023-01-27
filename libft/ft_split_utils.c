/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:19:52 by baltes-g          #+#    #+#             */
/*   Updated: 2023/01/27 11:21:21 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isscaped(char *s)
{
	int	count;

	count = 0;
	if (*(s - 1))
		s--;
	else
		return (0);
	while (*(s - count) && *(s - count) == 92)
		count++;
	if (count % 2)
		return (*(s + 1));
	return (0);
}

int	ft_isquote(char *s, char quote)
{
	if (*s != quote)
		return (0);
	if (!ft_isscaped(s))
		return (*s);
	return (0);
}

void	ft_check_escaped(char *str)
{
	int	i;

	while (*str != '\0')
	{
		if ((*str == 34 || *str == 39) && ft_isscaped(str))
		{
			i = 0;
			while (str[i] != '\0')
			{
				str[i - 1] = str[i];
				++i;
			}
			str[i - 1] = '\0';
		}
		++str;
	}
}
