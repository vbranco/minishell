#include "mini.h"

static	char	*ft_get_before(char *s, int *i)
{
	char		*tmp;
	int			a;

	a = 0;
	*i = 0;
	tmp = NULL;
	while (s[a] && s[a] != '$')
		a++;
	if (a > 0)
	{
		tmp = ft_strsub(s, 0, a);
		*i = a;
	}
	return (tmp);
}

static	char	*ft_looking_for_var(t_env_head *start, char *s)
{
	int			i;
	int			a;
	char		*tmp;
	char		*swap;
	char		*search;

	tmp = ft_get_before(s, &i);
	while (s[i])
	{
		ft_looking_for_special(s, &i);
		a = i;
		(s[i] == '$') ? i++ : 0;
		while (s[i] && s[i] != '$')
			i++;
		if (i > a)
		{
			search = ft_strsub(s, a, i - a);
			swap = searching_on_env(start, search + 1);
			(!swap && search && ft_isalpha(search[0])) ? 
			tmp = ft_realloc(tmp, search) : 0;
			free(search);
			(swap) ? tmp = ft_realloc(tmp, swap) : 0;
		}
	}
	return (tmp);
}
//--------------------
static	char	*ft_looking_for_home(t_env_head *start, char *s)
{
	char		*rest;
	char		*swap;
	char		*tmp;
	char		*doll;

	swap = searching_on_env(start, "HOME");
	if (swap)
	{
		tmp = ft_strdup(swap);
		rest = ft_strsub(s, 1, ft_strlen(s) - 1);
		if (ft_strchr(rest, '$'))
		{
			doll = ft_looking_for_var(start, rest);
			free(rest);
			rest = ft_strdup(doll);
			free(doll);
		}
	}
	else
		return (NULL);
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
		else if (ft_strchr(tmp->get, '$'))
		{
			rest = ft_strdup(tmp->get);
			free(tmp->get);
			tmp->get = ft_looking_for_var(start, rest);
			free(rest);
		}
		tmp = tmp->next;
	}
}

void	ft_create_parse_lst(t_env_head *env, t_pars_head *head, char *s)
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
