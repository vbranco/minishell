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

static	void	ft_add_pars(t_pars_head *head, char *s)
{
	t_pars		*p;
	t_pars		*tmp;

	p = NULL;
	if (!(p = (t_pars*)malloc(sizeof(t_pars))))
		return ;
	p->info = ft_strdup(s);
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

static	t_pars_head	*ft_ini_pars_head(void)
{
	t_pars_head		*p;

	p = NULL;
	if (!(p = (t_pars_head*)malloc(sizeof(t_pars_head))))
		return (NULL);
	p->next = NULL;
	return (p);
}
/*
static	void	ft_p(t_pars_head *head)
{
	t_pars		*tmp;
	
	tmp = head->next;
	while (tmp)
	{
		ft_printf(">>%s\n", tmp->info);
		tmp = tmp->next;
	}
}
*/
static	char	*ft_update_var_pars(t_env_head *head, char *looking)
{
	char		*ret;
	t_env		*tmp;

	tmp = head->next;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, looking))
			break ;
		tmp = tmp->next;
	}
	ret = ft_strdup(tmp->data);
	return (ret);
}

static	void	ft_update_pars(t_pars_head *head, t_env_head *s, int *i)
{
	t_pars		*tmp;

	tmp = head->next;
	if (tmp)
	{
		while (tmp)
		{
			if (tmp->info[0] == '~')
			{
				free(tmp->info);
				if (searching_on_env(s, "HOME"))
					tmp->info = ft_update_var_pars(s, "HOME");
				else
					tmp->info = NULL;
			}
			if (tmp->info[0] == '$')
			{
				if (searching_on_env(s, tmp->info + 1))
				{
					free(tmp->info);
					tmp->info = ft_update_var_pars(s, tmp->info + 1);
				}
				else
				{
					free(tmp->info);
					tmp->info = NULL;
				}
			}
			tmp = tmp->next;
		}
	}
}

static	char	**ft_create_pars(t_pars_head *head, t_env_head *s, char **parsed)
{
	char		**ret;
	int			i;
	t_pars		*tmp;

	i = 0;
	ret = NULL;
	while (parsed[i])
	{
		ft_add_pars(head, parsed[i]);
		i++;
	}
//	ft_p(head);
	ft_update_pars(head, s, &i);
//	ft_p(head);
	if (!(ret = (char**)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	tmp = head->next;
	i = 0;
	while (tmp)
	{
		if (tmp->info != NULL)
		{
			ret[i] = ft_strdup(tmp->info);
			i++;
		}
		tmp = tmp->next;
	}
	ret[i] = NULL;
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
		if ((s)->info != NULL)
			free((s)->info);
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

char			**ft_parsed(t_env_head *start, char *line)
{
	char		**parsed;
	t_pars_head	*head;
	char		**ret;//tester sans

	ret = NULL;
	head = NULL;
	if (!(head = ft_ini_pars_head()))
		return (NULL);
	parsed = NULL;
	parsed = ft_split(line);
	if (parsed == NULL)
		return (NULL);
	//---prob a partir d'ici---
	ret = ft_create_pars(head, start, parsed);
	ft_pi(parsed);//debug
	ft_free_2char(&parsed);
	ft_free_pars(&head);
	ft_pi(ret);//debug
	return (ret);//tester return(ft_create_pars(head...)
}
