/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_cd.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/27 20:00:16 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/27 20:00:17 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

char		*get_dir_from_env(t_env *env, char *looking, char **error_message)
{
	t_env		*tmp;
	char		*dir;
	char		pwd[1096];

	tmp = env;
	dir = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, looking) == 0)
			dir = ft_strdup(tmp->data);
		tmp = tmp->next;
	}
	if (dir == NULL)
	{
		if (!ft_strcmp(looking, "OLDPWD"))
			*error_message = ft_strdup("cd: OLDPWD not set");
		if (!ft_strcmp(looking, "HOME"))
			*error_message = ft_strdup("cd: HOME not set");
	}
	if (!ft_strcmp(looking, "OLDPWD") && dir != NULL)
		ft_printf("%s\n", dir);
	return (dir);
}

static	void	ft_doing_cat(char **tmp, char *s, char *s2)
{
	if (s)
		ft_strcat(*tmp, s);
	ft_strcat(*tmp, "/");
	ft_strcat(*tmp, s2);
}

char			*get_stat(char **parsed, int i, int flag, char *pwd)
{
	struct stat	st;
	char		*dir;
	char		*tmp;

	if (flag < 0)
		return (NULL);
	if (lstat(parsed[i], &st) != 0)
		return (ft_strdup(parsed[i]));
	if (S_ISLNK(st.st_mode) && (!ft_strcmp(parsed[flag], "-L") || flag == 0))
	{
		tmp = ft_memalloc(1000);
		if (!ft_count_signes(parsed[i], '.'))
			ft_doing_cat(&tmp, pwd, parsed[i]);
		else
		{
			ft_doing_cat(&tmp, NULL, parsed[i]);
			dir = get_prev_dir(parsed, pwd, i);
			dir = ft_realloc(dir, tmp);
		}
		dir = ft_strdup(tmp);
		free(tmp);
	}
	else
		dir = ft_strdup(parsed[i]);
	return (dir);
}

int				looking_stat(char *dir)
{
	struct stat	st;

	if (lstat(dir, &st) != 0)
		return (1);
	if (!S_ISDIR(st.st_mode) && !S_ISLNK(st.st_mode))
		return (1);
	return (0);
}
