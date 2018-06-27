/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_lst_parse.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/27 20:00:30 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/27 20:00:31 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

t_pars_head			*ft_initialise_pars_head(void)
{
	t_pars_head		*p;

	p = NULL;
	if (!(p = (t_pars_head*)malloc(sizeof(t_pars_head))))
		return (NULL);
	p->next = NULL;
	return (p);
}

void			ft_free_pars(t_pars_head **head)
{
	t_pars		*tmp;
	t_pars		*s;
	
	s = (*head)->next;
	while (s)
	{
		tmp = (s)->next;
		if ((s)->get != NULL)
			free((s)->get);
		free(s);
		(s) = tmp;
	}
	s = NULL;
	free(*head);
	head = NULL;
}

void			ft_add_pars(t_pars_head *head, char *s)
{
	t_pars		*p;
	t_pars		*tmp;

	p = NULL;
	if (!(p = (t_pars*)malloc(sizeof(t_pars))))
		return ;
	p->get = ft_strdup(s);
	p->next = NULL;
	tmp = head->next;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = p;
	}
	else
		head->next = p;
}
