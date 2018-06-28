/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_cd2.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/04 17:17:57 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/27 19:58:46 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

int				ft_count_signes(char *str, char c)
{
	int			i;
	int			a;

	i = 0;
	a = 0;
	while (str[i])
	{
		if (str[i] == c)
			a++;
		if (c == '.' && str[i] == '/' && str[i + 1] == '.')
			a--;
		i++;
	}
	return (a);
}

static	int		ft_path(char *s, char **dir)
{
	int			i;
	int			len;
	char		tmp[1096];

	i = 0;
	len = ft_strlen(s);
	ft_bzero(tmp, 1096);
	if (s[len - 1] != '/' && s[len - 1] != '.')
	{
		len--;
		while (len > 0)
		{
			if (s[len] == '/')
			{
				i = len;
				break ;
			}
			len--;
		}
		ft_strcat(tmp, "/");
		ft_strcat(tmp, (s + i + 1));
		(*dir == NULL) ? *dir = ft_strdup(tmp) : (*dir = ft_realloc(*dir, tmp));
	}
	return (0);
}

static	char	*ft_new_dir(char *parsed, char *pwd, int nb)
{
	int			len;
	char		*dir;

	dir = NULL;
	len = ft_strlen(pwd) - 1;
	while (len >= 0)
	{
		if (pwd[len] == '/')
		{
			nb--;
			if (nb == 0)
			{
				dir = ft_strsub(pwd, 0, len);
				break ;
			}
		}
		len--;
	}
	ft_path(parsed, &dir);
	return (dir);
}

char			*get_prev_dir(char **parsed, char *pwd, int index)
{
	char		*dir;
	int			i;
	int			z;
	int			a;

	i = ft_count_signes(parsed[index], '.');
	z = ft_count_signes(pwd, '/');
	dir = NULL;
	if (i >= 7)
		return (NULL);
	if (i == 1)
		return (pwd);
	i--;
	if (i >= z)
		return (ft_strdup("/"));
	else
		dir = ft_new_dir(parsed[index], pwd, i);
	return (dir);
}
