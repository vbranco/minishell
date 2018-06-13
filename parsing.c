#include "mini.h"

static int		ft_nb(char *s)
{
	int			i;
	int			word;

	i = 0;
	word = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
			i++;
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
		{
			word++;
			while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
				i++;
		}
		while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
			i++;
	}
	return (word);
}

char			**ft_split(char *str)
{
	char		**s;
	int			nb_words;
	int			i;
	int			start;
	int			w;

	i = 0;
	w = 0;
	nb_words = 0;
	if (!str)
		return (NULL);
	nb_words = ft_nb(str);
	if (!(s = (char**)malloc(sizeof(char*) * (nb_words + 1))))
		return (NULL);
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		start = i;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			i++;
		if (w < nb_words)
			s[w++] = ft_strsub(str, start, i - start);
	}
	s[w] = NULL;
	return (s);
}



static	t_pars_head	*ft_ini_pars_head(void)
{
	t_pars_head		*p;

	p = NULL;
	if (!(p = (t_pars_head*)malloc(sizeof(t_pars_head))))
		return (NULL);
	p->next = NULL;
	return (p);
}

static	void	ft_p(t_pars_head *head)
{
	t_pars		*tmp;
	
	tmp = head->next;
	while (tmp)
	{
		ft_printf("get>>%s\n", tmp->get);
		tmp = tmp->next;
	}
}

static	char	**ft_create_pars(t_pars_head *head)
{
	char		**ret;
	int			i;
	t_pars		*tmp;

	i = 0;
	ret = NULL;
	tmp = head->next;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (tmp->get)
			i++;
		tmp = tmp->next;
	}
	if (!(ret = (char**)malloc(sizeof(char) * (i + 1))))
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

static	void	ft_free_pars(t_pars_head **head)
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

//--a supp
void			ft_pi(char **p)
{
	int			i = 0;

	while (p[i])
	{
		ft_printf(">>%s\n", p[i]);
		i++;
	}
}
//--
static	void	ft_add_pars(t_pars_head *head, char *s)
{
	t_pars		*p;
	t_pars		*tmp;

	p = NULL;
	if (!(p = (t_pars*)malloc(sizeof(t_pars))))
		return ;
	p->get = ft_strdup(s);
	free(s);
	p->next = NULL;
	tmp = head->next;
	if (tmp == NULL)
		head->next = p;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = p;
	}
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
			if (swap)
				tmp->get = ft_strdup(swap);
			else
				tmp->get = NULL;
		}
		if (tmp->get[0] == '$')
		{
			swap = searching_on_env(start, tmp->get + 1);
			free(tmp->get);
			if (swap)
				tmp->get = ft_strdup(swap);
			else
				tmp->get = NULL;
		}
		tmp = tmp->next;
//		ft_printf("dans if ft_update_parse\n");
	}
}

static	void	ft_create_parse_lst(t_env_head *env, t_pars_head *head, char *s)
{
	int			i;
	int			start;
	
	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\n'))
			i++;
		start = i;
		while (s[i] && s[i] != ' ' && s[i] != '\n')
			i++;
		ft_add_pars(head, ft_strsub(s, start, i - start));
		while (s[i] && (s[i] == ' ' || s[i] == '\n'))
			i++;
	}
//	ft_p(head);
	ft_update_parse(env, head);
//	ft_printf("apres update_parse\n");
}

char			**ft_parsed(t_env_head *start, char *line)
{
	t_pars_head	*head;
	char		**ret;//tester sans

	ret = NULL;
	head = NULL;
	if (!line)
		return (NULL);
	if (!(head = ft_ini_pars_head()))
		return (NULL);
	ft_create_parse_lst(start, head, line);
	ret = ft_create_pars(head);
	ft_pi(ret);
//	ft_p(head);
//	ft_printf("\n\n");
	//---prob a partir d'ici---
//	ft_pi(parsed);//debug
//	ret = ft_create_pars(head, start, parsed);
	ft_free_pars(&head);
//	ft_pi(ret);//debug
	return (ret);//tester return(ft_create_pars(head...)
}
