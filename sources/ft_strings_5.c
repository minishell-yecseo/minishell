#include "ft_strings.h"

static int	get_size(int n);

char	*ft_itoa(int n)
{
	char			*ret;
	char			*tmp;
	unsigned int	positive_n;
	int				size;

	size = get_size(n);
	ret = (char *) ft_calloc((size + 1), sizeof(char));
	if (!ret)
		return (0);
	tmp = ret + size;
	if (n < 0)
	{
		ret[0] = '-';
		positive_n = n * (-1);
	}
	else
		positive_n = n;
	*tmp-- = 0;
	while (positive_n / 10)
	{
		*tmp-- = positive_n % 10 + '0';
		positive_n /= 10;
	}
	*tmp = positive_n % 10 + '0';
	return (ret);
}

static int	get_size(int n)
{
	int	size;

	size = 0;
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	else if (n == 0)
		return (1);
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	ret = malloc(count * size);
	if (!ret)
		return (NULL);
	ft_bzero(ret, count * size);
	return (ret);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)s;
	while (n--)
		*tmp++ = 0;
}
