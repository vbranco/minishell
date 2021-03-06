/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   head_prompt.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/27 19:59:58 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 14:05:44 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

void		shell_top(void)
{
	ft_printf("\e[0m");
	ft_printf("Welcome to Bsh\n");
	ft_printf("********************\n*------------------*\n");
	ft_printf("*||   \e[31mvbranco\e[0m    ||*\n*------------------*\n");
	ft_printf("********************\n");
}

void		print_prompt(t_env_head *head)
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
		ft_printf("\xE2\x9C\x85  \e[1m\e[96m%s\e[0m:\e[32m%s\e[0m ", user,
				current + len);
	ft_printf("$> ");
}
