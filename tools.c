/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/04 17:16:03 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/19 19:57:43 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

char			*searching_on_env(t_env_head *head, char *looking)
{
	t_env		*tmp;
	if (head->next == NULL)
		return (NULL);
	tmp = head->next;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, looking))
			return (tmp->data);
		tmp = tmp->next;
	}
	return (NULL);
}

int				ft_error(char *error_message, char **parsed, int index)
{

	ft_putstr_fd(error_message, 2);
	if (parsed != NULL)
		ft_putendl_fd(parsed[index], 2);
	else
		ft_putchar_fd('\n', 2);
	return (1);
}

int				ft_count_args_shell(char **parsed)
{
	int			i;
	int			a;

	a = 1;
	i = 1;
	while (parsed[i])
	{
		if (parsed[i][0] != '-')
			a++;
		i++;
	}
	return (a);
}

void			ft_get_index_flag(char **parsed, int *i, int *flag)
{
	int			a;

	a = 1;
	while (parsed[a] && parsed[a][0] == '-')
	{
		if (!ft_strcmp(parsed[a], "-P"))
			*flag = a;
		else if (!ft_strcmp(parsed[a], "-L"))
			*flag = a;
		else
		{
			*flag = -1;
			break ;
		}
		a++;
	}
	*i = a;
}

void		shell_top(void)
{
	ft_printf("\e[0m");
	ft_printf("Welcome to Bsh\n");
}
