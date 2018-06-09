/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exe.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/28 19:46:28 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/04 17:10:47 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

static char			*path_exist(t_env *env)
{
	t_env			*tmp;
	char			*data;

	data = NULL;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PATH") == 0)
		{
			data = ft_strdup(tmp->data);
			return (data);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static char			*making_path(char *s1, char *s2, int i)
{
	char			*tmp;

	tmp = ft_memalloc(1024);
	if (i)
	{
		ft_strcat(tmp, s1);
		ft_strcat(tmp, "/");
	}
	ft_strcat(tmp, s2);
	return (tmp);
}

static	int			inside_dir(char *path_dir, char *parsed, char **ret)
{
	DIR				*dir;
	struct dirent	*pdir;
	char			*path;
	char			*exe;

	if (!(dir = opendir(path_dir)))
		return (0);
	while ((pdir = readdir(dir)) != NULL)
	{
		path = making_path(path_dir, pdir->d_name, 1);
		if (parsed[0] != '/')
			exe = making_path(path_dir, parsed, 1);
		else
			exe = making_path(path_dir, parsed, 0);
		if (ft_strcmp (path, exe) == 0)
		{
			*ret = ft_strdup(exe);
			closedir(dir);
			free(path);
			free(exe);
			return (1);
		}
		free(path);
		free(exe);
	}
	closedir(dir);
	return (0);
}

static	int			ft_counter(char *s)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	while (s[i])
	{
		if (s[i] == '/')
			a = i;
		i++;
	}
	return (a);
}

static	int			try_exe_without_path(char *path, char **exe)
{
	char			*tmp;
	int				slach;

	slach = ft_counter(path);
	tmp = ft_strsub(path, 0, slach);
	if (inside_dir(tmp, path, exe))
	{
		free (tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

static	int			ft_count_p(char *s)
{
	int				i;
	int				a;

	i = 0;
	a = 0;
	while (s[i])
	{
		if (s[i] == '/')
			a = i;
		i++;
	}
	return (a);
}

static	int			exec_in_dir(char **parsed, char **exe)
{
	char			pwd[1096];
	int				p;

	p = 0;
	if (*parsed[0] == '.')
	{
	//	ft_printf("parsed >> %s\n", *parsed);
		p = ft_count_p(parsed[0]);
		getcwd(pwd, 1096);
		*exe = get_prev_dir(parsed, pwd, 0);
	//	ft_printf("*exe >> %s\n", *exe);
		*exe = ft_strjoin(*exe, &parsed[0][p]);
	//	ft_printf("apres *exe >> %s\n", *exe);
		return (1);
	}
	return (0);
}

int					test_exe(t_env *env, char **parsed, char **exe)
{
	char			**path;
	char			*tmp;
	int				i;

	i = 0;
	if (exec_in_dir(parsed, exe))
	{
		if (access(*exe, F_OK) || access(*exe, X_OK))
			return (0);
		else
			return (1);
	}
	tmp = path_exist(env);
	path = ft_strsplit(tmp, ':');
	free(tmp);
	if (path == NULL)
		return (try_exe_without_path(*parsed, exe));
	else
	{
		while (path[i])
		{
			if (inside_dir(path[i], *parsed, exe))
			{
				ft_free_2char(&path);
				return (1);
			}
			i++;
		}
	}
	ft_free_2char(&path);
	return (0);
}
