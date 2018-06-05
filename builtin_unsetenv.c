/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_unsetenv.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/05 18:13:34 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/05 19:00:07 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

static void	ft_free_env(t_env_head *head, char *s)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = head->next;
	prev = NULL;
	while (tmp && ft_strcmp(tmp->name, s))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp && !ft_strcmp(tmp->name, s))
	{
		if (tmp->name)
			free(tmp->name);
		if (tmp->data)
			free(tmp->data);
		if (prev == NULL)
			head->next = tmp->next;
		else
			prev->next = tmp->next;
		free(tmp);
		tmp = NULL;
	}
}

int			unsetenvi(t_env_head *head, char **parsed)
{
	int		i;

	i = 1;
	if (parsed[i] == NULL)
		return (ft_error(UNSETENV_NO_ARG, NULL, 0));
	else
	{
		while (parsed[i])
		{
			ft_free_env(head, parsed[i]);
			i++;
		}
	}
	return (1);
}
