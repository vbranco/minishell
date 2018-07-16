/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_parsing.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/27 20:00:39 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 14:55:11 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

static	char	*ft_is_dollar(char *search)
{
	if (!ft_strcmp(search, "$"))
		return (ft_strdup("$"));
	else
		return (NULL);
}

static	void	ft_update_parse(t_env_head *start, t_pars_head *head)
{
	t_pars		*tmp;
	char		*rest;

	tmp = head->next;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->get[0] == '~' && (tmp->get[1] == '/' || tmp->get[1] == '\0'))
		{
			rest = ft_strdup(tmp->get);
			free(tmp->get);
			tmp->get = ft_looking_for_home(start, rest);
			free(rest);
		}
		else if (ft_strchr(tmp->get, '$'))
		{
			rest = ft_strdup(tmp->get);
			free(tmp->get);
			tmp->get = ft_is_dollar(rest);
			(!tmp->get) ? tmp->get = ft_looking_for_var(start, rest) : 0;
			free(rest);
		}
		tmp = tmp->next;
	}
}

void			ft_create_parse_lst(t_env_head *env, t_pars_head *head, char *s)
{
	int			i;
	int			start;
	char		*tmp;

	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
			i++;
		start = i;
		while (s[i] && s[i] != ' ' && s[i] != '\n' && s[i] != '\t')
			i++;
		if (i > start)
		{
			tmp = ft_strsub(s, start, i - start);
			ft_add_pars(head, tmp);
			free(tmp);
		}
	}
	if (head->next)
		ft_update_parse(env, head);
}
