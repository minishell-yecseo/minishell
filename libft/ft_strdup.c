/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:34:03 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:34:04 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;

	res = (char *) ft_calloc(1, sizeof(char) * (ft_strlen(s1) + 1));
	if (!res)
		return (NULL);
	ft_strcpy(res, s1);
	return (res);
}
