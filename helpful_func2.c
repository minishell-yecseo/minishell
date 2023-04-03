#include "minishell.h"
#include "utils.h"

//size_t	ft_strlen(const char *s)
//{
//	size_t	size;

//	size = 0;
//	while (s[size] != 0)
//		size++;
//	return (size);
//}

char	*make_small(char const *s, int i, int save)
{
	int		j;
	char	*small;

	small = (char *)malloc(sizeof(char) * (i - save + 1));
	if (!small)
		return (0);
	j = 0;
	while (save + j < i)
	{
		small[j] = s[save + j];
		j++;
	}
	small[j] = 0;
	return (small);
}

int	check_big(char const *s, char c)
{
	int	i;
	int	check_size;

	check_size = 1;
	i = 0;
	if (s[i] == 0)
		return (0);
	if (s[i] == c)
		check_size--;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c && s[i])
				i++;
			check_size++;
		}
		else
			i++;
	}
	if (s[i - 1] == c)
		check_size--;
	return (check_size);
}

int	split_str(char const *s, char c, char **arr, int i)
{
	int	size;
	int	save;

	size = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			save = i;
			while (s[i] != c && s[i])
				i++;
			arr[size] = make_small(s, i, save);
			if (arr[size] == 0)
			{
				while (size >= 0)
					free(arr[size--]);
				return (0);
			}
			size++;
		}
	}
	arr[size] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;

	if (!s)
	{
		printf("it is null string\n");
		return (0);
	}
	arr = (char **)malloc(sizeof(char *) * (check_big(s, c) + 1));
	if (!arr)
		return (0);
	i = 0;
	if (!(split_str(s, c, arr, i)))
	{
		free(arr);
		return (0);
	}
	return (arr);
}

//char	*ft_strjoin(char const *s1, char const *s2)
//{
//	char	*str;
//	int		len1;
//	int		len2;
//	int		i;

//	i = 0;
//	len1 = ft_strlen(s1);
//	len2 = ft_strlen(s2);
//	str = (char *)malloc(sizeof(char) * (len1 + len2 + 2));
//	if (!str)
//		return (0);
//	while (i < len1)
//	{
//		str[i] = s1[i];
//		i++;
//	}
//	str[i++] = '/';
//	while (i < len1 + len2 + 1)
//	{
//		str[i] = s2[i - len1 - 1];
//		i++;
//	}
//	str[i] = 0;
//	return (str);
//}

////int main()
////{
////	printf("%s\n", ft_strjoin("/bin", "lasdffadsafdss"));
////}