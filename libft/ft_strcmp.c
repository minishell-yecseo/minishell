/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:33:59 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:34:00 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned char	s1_c;
	unsigned char	s2_c;

	if (!s1 || !s2)
		return (-1);
	s1_c = *s1;
	s2_c = *s2;
	while (s1_c == s2_c)
	{
		if (!s1_c || !s2_c)
			return (s1_c - s2_c);
		s1_c = *(++s1);
		s2_c = *(++s2);
	}
	return (s1_c - s2_c);
}
