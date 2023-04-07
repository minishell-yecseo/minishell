#include "minishell.h"

void	print_init_msg(void)
{
	char	*logo;
	char	*author1;
	char	*author2;

	logo = get_init_logo();
	if (!logo)
		logo = "";
	author1 = "yecnam@student.42seoul.kr";
	author2 = "saseo@student.42seoul.kr";
	printf("\033[0;34m%s", logo);
	printf("\033[0mcreated by \033[0;36m%s\033[0m", author1);
	printf(" | \033[0;36m%s\n\n\033[0m", author2);
	if (*logo != '\0')
		free(logo);
}

char	*get_init_logo(void)
{
	char	*logo;
	int	logo_fd;
	int	read_byte;
	char	*path;

	path = "settings/logo.txt";
	logo_fd = open(path, O_RDONLY);
	if (!logo_fd)
		return ("(Logo file cannot found)\n");
	logo = (char *) ft_calloc(5400, sizeof(char));
	if (!logo)
		return ("(Logo malloc fail)\n");
	read_byte = read(logo_fd, logo, 5400);
	if (read_byte <= 0)
		return ("(Logo read fail)\n");
	close(logo_fd);
	return (logo);
}
