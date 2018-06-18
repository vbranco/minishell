/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 16:46:05 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/18 20:11:17 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

//--supp
static	void	ft_p(t_pars_head *head)
{
	t_pars		*tmp;

	tmp = head->next;
	while (tmp)
	{
		ft_printf("dans ft_p get>>%s\n", tmp->get);
		tmp = tmp->next;
	}
}
//---
//--a supp
void			ft_pi(char **p)
{
	int			i = 0;

	while (p[i])
	{
		printf("dans ft_pi>>%s\n", p[i]);
		i++;
	}
}
//--

static	int		ft_count_lst_elem(t_pars_head *head)
{
	int			i;
	t_pars		*tmp;

	i = 0;
	tmp = head->next;
	if (!tmp)
		return (i);
	while (tmp)
	{
		if (tmp->get)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static	char	**ft_create_pars(t_pars_head *head)
{
	char		**ret;
	int			i;
	t_pars		*tmp;

	ret = NULL;
	tmp = head->next;
	if (!tmp)
		return (NULL);
	i = ft_count_lst_elem(head);
	if (!(ret = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	ret[i] = NULL;
	tmp = head->next;
	i = 0;
	while (tmp)
	{
		if (tmp->get != NULL)
		{
			ret[i] = ft_strdup(tmp->get);
			i++;
		}
		tmp = tmp->next;
	}
	return (ret);
}
//Travailler pour resoudre "$$" et "$$LESS"
static	char	*ft_looking_for_var(t_env_head *start, char *s)
{
	int			i;
	int			a;
	char		*tmp;
	char		*swap;
	char		*search;

	i = 0;
	tmp = NULL;
	while (s[i])
	{
		while (s[i] && s[i] != '$')
		{
//			if (s[i] == '$' && s[i + 1] == '$')
//				i += 2;
//			else
				i++;
		}
		(!tmp) ? tmp = ft_strsub(s, 0, i) : 0;
		i++;
		if (!s[i])
			break ;
		a = i;
		while (s[i] && s[i] != '$')
			i++;
		search = ft_strsub(s, a, i - a);
		ft_printf("dans ft_looking_for_var || search >> %s\n", search);
		swap = searching_on_env(start, search);
		free(search);
		tmp = ft_realloc(tmp, swap);
	}
	return (tmp);
}
//--------------------
static	char	*ft_looking_for_home(t_env_head *start, char *s)
{
	char		*rest;
	char		*swap;
	char		*tmp;

	rest = ft_strsub(s, 1, ft_strlen(s) - 1);
	swap = searching_on_env(start, "HOME");
	tmp = ft_strdup(swap);
	tmp = ft_realloc(tmp, rest);
	free(rest);
	return (tmp);
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
		if (ft_strchr(tmp->get, '$'))
		{
			rest = ft_strdup(tmp->get);
			free(tmp->get);
			tmp->get = ft_looking_for_var(start, rest);
			free(rest);
		}
		tmp = tmp->next;
	}
}

static	void	ft_create_parse_lst(t_env_head *env, t_pars_head *head, char *s)
{
	int			i;
	int			start;
	char		*tmp;

	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\n'))
			i++;
		start = i;
		while (s[i] && s[i] != ' ' && s[i] != '\n')
			i++;
		tmp = ft_strsub(s, start, i - start);
		ft_add_pars(head, tmp);
		free(tmp);
		while (s[i] && (s[i] == ' ' || s[i] == '\n'))
			i++;
	}
	ft_update_parse(env, head);
}

char			**ft_parsed(t_env_head *start, char *line)
{
	t_pars_head	*head;
	char		**ret;

	ret = NULL;
	head = NULL;
	if (!line)
		return (NULL);
	if (!(head = ft_initialise_pars_head()))
		return (NULL);
	ft_create_parse_lst(start, head, line);
	ret = ft_create_pars(head);
//	ft_p(head);
	ft_free_pars(&head);
	return (ret);
}
