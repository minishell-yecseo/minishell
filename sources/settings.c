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
	printf("\x1b[38;5;18m%s", logo);
	printf("\x1b[0mcreated by \x1b[38;5;74m%s\x1b[0m", author1);
	printf(" | \x1b[38;5;74m%s\n\n\x1b[0m", author2);
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
	logo = (char *) ft_calloc(3000, sizeof(char));
	if (!logo)
		return ("(Logo malloc fail)\n");
	read_byte = read(logo_fd, logo, 3000);
	if (read_byte <= 0)
		return ("(Logo read fail)\n");
	close(logo_fd);
	return (logo);
}
