/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:19:39 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/10 16:03:52 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_oneline(char *buffer)
{
	int		i;
	char	*s;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (i == 0 && buffer[i] == 0)
		return (0);
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (0);
	s[i + 1] = 0;
	while (i >= 0)
	{
		s[i] = buffer[i];
		i--;
	}
	return (s);
}

char	*read_line(int fd, char *buffer)
{
	int		byte;
	char	*buf;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	while (!fft_strchr(buffer))
	{
		byte = read(fd, buf, BUFFER_SIZE);
		if (byte == -1 || byte == 0)
			break ;
		buf[byte] = '\0';
		if (!buffer)
			buffer = make_empty();
		buffer = ft_strjoin(buffer, buf);
		if (!buffer)
			break ;
	}
	free(buf);
	if (byte == -1)
	{
		free(buffer);
		return (0);
	}
	return (buffer);
}

char	*update_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (0);
	}
	next = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!next)
		return (0);
	i++;
	j = 0;
	while (buffer[i])
		next[j++] = buffer[i++];
	next[j] = 0;
	free(buffer);
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (0);
	line = get_oneline(buffer);
	buffer = update_buffer(buffer);
	return (line);
}
