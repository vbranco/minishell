/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_setenv.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/02 17:47:51 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 19:31:13 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

static int	ft_count_args(char **parsed)
{
	int		i;

	i = 0;
	if (parsed[i])
	{
		while (parsed[i])
			i++;
	}

	return (i);
}

static int	test_var(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if ((s[i] >= 'a' && s[i] <= 'z') ||
				(s[i] >= 'A' && s[i] <= 'Z') ||
				(s[i] >= '0' && s[i] <= '9'))
			i++;
		else
			return (1);
	}
	return (0);
}

int			setenvi(t_env_head *head, char **parsed)
{
	if (parsed[1] == NULL)
		return (ft_print_env(head));
	else if (ft_count_args(parsed) > 3)
		return (ft_error("setenv: Too many arguments", NULL, 0));
	else if (parsed[2] == NULL || !ft_strcmp(parsed[1], "-h"))
	{
		ft_printf("Usage: setenv [var_name] [var_info]\n");
		return (1);
	}
	else if (test_var(parsed[1]))
		return (ft_error(ENV_VAR, NULL, 0));
	else
	{
		if (searching_on_env(head, parsed[1]))//penser a changer parsed[1] par un parsed[i] car des flags peuvent intervenir
			ft_updating_var(head, parsed[1], parsed[2]);
		else
			ft_create_var(head, parsed[1], parsed[2]);
	}
	return (1);
}
