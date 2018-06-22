/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/18 16:46:05 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/19 19:57:42 by vbranco     ###    #+. /#+    ###.fr     */
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
//----------------------------------------------------------------

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
void	ft_looking_for_special(char *s, int *i)
{
	int			a;

	a = *i;
	while (s[a])
	{
		if (s[a] == '$' && s[a + 1] != '\0')
		{
			if (!ft_isalpha(s[a + 1]))
				a += 2;
			else
				break;
		}
		else
			break ;
	}
	*i = a;
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
