#include "mini.h"

void		shell_top(void)
{
	char	*top = "********************\n*------------------*\n*||   \e[31mvbranco\e[0m    ||*\n*------------------*\n********************\n";
	ft_printf("\e[0m");
	ft_printf("Welcome to Bsh\n");
	ft_printf("%s", top);
}

void	print_prompt(t_env_head *head)
{
		char	*user;
		char	current[1096];
		int		len;

		getcwd(current, 1096);
		len = (int)ft_strlen(current) - 1;
		while (len > 0)
		{
			if (current[len] == '/')
			{
				len++;
				break ;
			}
			len--;
		}
		ft_printf("\e[0m");
		user = searching_on_env(head, "USER");
		if (user)
			ft_printf("\xE2\x9C\x85  \e[1m\e[96m%s\e[0m:\e[32m%s\e[0m ", user, current + len);
		ft_printf("$> ");
}
