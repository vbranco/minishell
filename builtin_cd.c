/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_cd.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/02 10:26:07 by vbranco      #+#   ##    ##    #+#       */
/*   Updated: 2018/06/02 17:46:55 by vbranco     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mini.h"

int				ft_error(char *error_message, char **parsed, int index)
{

	ft_putstr_fd(error_message, 2);
	if (parsed != NULL)
		ft_putendl_fd(parsed[index], 2);
	else
		ft_putchar_fd('\n', 2);
	return (1);
}

static char		*get_dir_from_env(t_env *env, char *looking)
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
		getcwd(pwd, 1096);
		dir = ft_strdup(pwd);
	}
	if (ft_strcmp(looking, "HOME"))
		ft_printf("%s\n", dir);
	return (dir);
}

static	char	*get_stat(char **parsed, int i, int flag, char *pwd)
{
	struct stat	st;
	char		*dir;
	char		tmp[1000];

	if (flag < 0)
		return (NULL);
	if (lstat(parsed[i], &st) != 0)
		return (ft_strdup(parsed[i]));
//	ft_printf("path >> %s\n", parsed[i]);
//	ft_printf("flag >> %s\n", parsed[flag]);
	if (S_ISLNK(st.st_mode) && (!ft_strcmp(parsed[flag], "-L") || flag == 0))
	{
		ft_bzero(tmp, 1000);
//		ft_printf("dans get_stat || parsed[i] >> %s\ni == %d\n", parsed[i], i);
		if (!ft_count_signes(parsed[i], '.'))
		{
			ft_strcat(tmp, pwd);
			ft_strcat(tmp, "/");
			ft_strcat(tmp, parsed[i]);
		}
		else
		{
			ft_strcat(tmp, "/");
			ft_strcat(tmp, parsed[i]);
			dir = get_prev_dir(parsed, pwd, i);
			dir = ft_realloc(dir, tmp);
		}
		dir = ft_strdup(tmp);
//		ft_printf("dir >> %s\n", dir);
	}
	else
		dir = ft_strdup(parsed[i]);
	return (dir);
}

static	int		looking_stat(char *dir)
{
	struct stat	st;

	if (lstat(dir, &st) != 0)
		return (1);
	if (!S_ISDIR(st.st_mode) && !S_ISLNK(st.st_mode))
		return (1);
	return (0);
}

static	int		change_dir(t_env *env, char **parsed, char *dir)
{
	if (access(dir, F_OK))
		return (ft_error(CD_NO_FILE, parsed, 1));
	else if (looking_stat(dir))
		return (ft_error(CD_NO_DIR, &dir, 0));
	else if (access(dir, X_OK))
		return (ft_error(CD_DENIED, parsed, 1));
//	ft_printf("dir >> %s\n", dir);
	if ((chdir(dir)) == -1)
		return (ft_error("CHDIR: cannot open: ", parsed, 1));
	update_env(env, dir);
	return (0);
}

static	void	ft_get_index_flag(char **parsed, int *i, int *flag)
{
	int			a;

	a = 1;
	while (parsed[a] && parsed[a][0] == '-')
	{
		if (!ft_strcmp(parsed[a], "-P"))
			*flag = a;
		else if (!ft_strcmp(parsed[a], "-L"))
			*flag = a;
		else
		{
			*flag = -1;
			break ;
		}
		a++;
	}
	*i = a;
}

char			*ft_get_dir(t_env *env, char **parsed, char *pwd)
{
	char		*dir;
	int			i;
	int			flag;

	flag = 0;
	i = 0;
	if (parsed[1] == NULL || (ft_strcmp(parsed[1], "~") == 0))
		return (dir = get_dir_from_env(env, "HOME"));
	else if (ft_strcmp(parsed[1], "-") == 0)
		return (dir = get_dir_from_env(env, "OLDPWD"));
	else
	{
		ft_get_index_flag(parsed, &i, &flag);
//		return(dir = get_stat(parsed, i, flag, pwd));
		return (dir = ft_strdup(parsed[i]));
	}
}

static	int		ft_count_args(char **parsed)
{
	int			i;
	int			a;

	a = 1;
	i = 1;
	while (parsed[i])
	{
		if (parsed[i][0] != '-')
			a++;
		i++;
	}
	return (a);
}

int				cd(t_env *env, char **parsed)
{
	char		pwd[1096];
	int			args;
	char		*dir;

	dir = NULL;
	args = ft_count_args(parsed);
	if (args >= 3)
		return (ft_error(CD_TOO_ARGS, NULL, 0));
	getcwd(pwd, 1096);
	dir = ft_get_dir(env, parsed, pwd);
	if (dir == NULL)
	{
		ft_putendl_fd("Usage: cd [-L | -P] [dir]", 2);
		return (1);
	}
	change_dir(env, parsed, dir);
	free(dir);
	return (1);
}
