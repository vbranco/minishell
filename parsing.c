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



static	void	ft_update_parse(t_env_head *start, t_pars_head *head)
{
	t_pars		*tmp;
	char		*swap;

	tmp = head->next;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (!ft_strcmp(tmp->get, "~"))
		{
			swap = searching_on_env(start, "HOME");
			free(tmp->get);
			tmp->get = ft_strdup(swap);
		}
		if (tmp->get && tmp->get[0] == '$' && tmp->get[1] != '\0')
		{
			swap = searching_on_env(start, tmp->get + 1);
			free(tmp->get);
			tmp->get = ft_strdup(swap);
		}
//pas de free de swap car c'est un return de la liste des env
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
	char		**ret;//tester sans

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
	return (ret);//tester return(ft_create_pars(head...)
}
