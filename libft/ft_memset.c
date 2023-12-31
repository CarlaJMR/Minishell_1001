/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:09:13 by mneves-l          #+#    #+#             */
/*   Updated: 2023/04/13 19:43:17 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*string;
	size_t			i;

	string = (unsigned char *)b;
	i = 0;
	while (i < n)
	{
		string[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
