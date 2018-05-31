/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/31 19:44:33 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/05/31 19:44:34 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

static void		print_env(t_env *env, char *s)
{
	t_env		*tmp;
	char		*try;

	try = ft_strdup(s+1);
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, try) == 0)
		{
			ft_printf("%s", tmp->data);
			free(try);
			return ;
		}
		tmp = tmp->next;
	}
	free(try);
}

int				echo(t_env *env, char **parsed)
{
	int			flag;
	int			i;

	flag = 0;
	if (*(parsed + 1))
	{
		if (ft_strcmp(*(parsed + 1), "-n") == 0)
			flag = 1;
	}
	i = 1;
	if (flag)
		i++;
	while (parsed[i])
	{
		if (parsed[i][0] == '$')
			print_env(env, parsed[i]);
		else
			ft_printf("%s", parsed[i]);
		i++;
		if (parsed[i])
			ft_printf(" ");
	}
	if (!flag)
		ft_printf("\n");
	return (1);
}
