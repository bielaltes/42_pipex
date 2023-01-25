/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:48:27 by baltes-g          #+#    #+#             */
/*   Updated: 2023/01/25 09:50:00 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	if (c == 32
		|| c == '\n'
		|| c == '\t'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r')
		return (c);
	return (0);
}