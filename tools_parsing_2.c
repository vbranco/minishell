/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_parsing_2.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 14:53:44 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 14:58:56 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

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

char			*ft_looking_for_var(t_env_head *start, char *s)
{
	int			i;
	int			a;
	char		*tmp;
	char		*swap;
	char		*se;

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
			se = ft_strsub(s, a, i - a);
			swap = searching_on_env(start, se + 1);
			(!swap && se && ft_isalpha(se[0])) ? tmp = ft_realloc(tmp, se) : 0;
			free(se);
			(swap) ? tmp = ft_realloc(tmp, swap) : 0;
		}
	}
	return (tmp);
}

char			*ft_looking_for_home(t_env_head *start, char *s)
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
