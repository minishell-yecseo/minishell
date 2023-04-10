#include "minishell.h"

static char	*get_logo(void);

void	print_init_msg(void)
{
	char	*logo;
	char	*author1;
	char	*author2;

	logo = get_logo();
	author1 = "yecnam@student.42seoul.kr";
	author2 = "saseo@student.42seoul.kr";
	printf("\x1b[38;5;87m\x1b[48;5;17m%s\x1b[0;m", logo);
	printf("\t\t\x1b[38;5;74m%34s\x1b[0;m", author1);
	printf("\n\t\t\x1b[38;5;74m%34s\n\n\x1b[0;m", author2);
}

static char	*get_logo(void)
{
	char	*logo;

	logo = " __  __  _  __  _   ____  _   _  ____  _     _    \n\
|  \\/  || ||  \\| | (_ (_`| |_| || ===|| |__ | |__ \n\
|_|\\/|_||_||_|\\__|.__)__)|_| |_||____||____||____|\n";
	return (logo);
}
