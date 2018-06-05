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
	t_env	*add;
	t_env	*tmp;

	add = NULL;
	tmp = head->next;
	if (parsed[1] == NULL)
		return (ft_print_env(head));
	else if (ft_count_args(parsed) > 3)
		return (ft_error("setenv: Too many arguments", NULL, 0));
	else if (test_var(parsed[1]))
		return (ft_error(ENV_VAR, NULL, 0));
	else
	{
		add = ft_initialise();
		add->name = ft_strdup(parsed[1]);
		if (parsed[2])
			add->data = ft_strdup(parsed[2]);
		while (tmp->next)
			tmp = tmp->next;
		add->next = tmp->next;
		tmp->next = add;
	}
	return (1);
}
