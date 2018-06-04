/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_env.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/04 17:56:33 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/04 19:23:09 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

int			environment(t_env *s)
{
	while (s)
	{
//		if (s->prev)
//			ft_printf("prev >> %s\n", s->prev->name);
//		ft_printf("current >> %s\n", s->name);
		ft_printf("%s=%s\n", s->name, (s->data == NULL) ? "\0" : s->data);
//		if (s->next)
//			ft_printf("next >> %s\n", s->next->name);
		s = s->next;
	}
	return (1);
}

void		update_env(t_env *env, char *pwd)
{
	t_env	*tmp;
	char	*datatmp;
	char	p[1096];

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD") == 0)
			break;
		tmp = tmp->next;
	}
	getcwd(p, 1096);
	datatmp = ft_strdup(tmp->data);
	free(tmp->data);
	tmp->data = ft_strdup(p);
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
			break ;
		tmp = tmp->next;
	}
	free(tmp->data);
	tmp->data = ft_strdup(datatmp);
	free(datatmp);
}
