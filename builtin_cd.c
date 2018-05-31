#include "mini.h"

static char		*get_dir_from_env(t_env *env, char *looking)
{
	t_env		*tmp;
	char		*dir;

	tmp = env;
	dir = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, looking) == 0)
			dir = ft_strdup(tmp->data);
		tmp = tmp->next;
	}
	if (ft_strcmp(looking, "HOME"))
		ft_printf("%s\n", dir);
	return (dir);
}

static	int		change_dir(t_env *env, char **parsed, char *dir)
{
	if (access(dir, F_OK))
		return (ft_error(CD_NO_FILE, parsed, 1));
	else if (access(dir, X_OK))
		return (ft_error(CD_DENIED, parsed, 1));
	if ((chdir(dir)) == -1)
		return (ft_error("CHDIR: cannot open: ", parsed, 1));
	update_env(env, dir);
	return (0);
}

char			*ft_get_dir(t_env *env, char **parsed, char *pwd)
{
	char		*dir;

	if (parsed[1] == NULL || (ft_strcmp(parsed[1], "~") == 0))
		return (dir = get_dir_from_env(env, "HOME"));
	else if (ft_strcmp(parsed[1], "-") == 0)
		return (dir = get_dir_from_env(env, "OLDPWD"));
	else
		return (dir = ft_strdup(parsed[1]));
}

int				cd(t_env *env, char **parsed)
{
	char		pwd[1096];
	int			args;
	char		*dir;

	dir = NULL;
	args = 0;
	while (parsed[args])
		args++;
	if (args > 3)
		return (ft_error(CD_TOO_ARGS, NULL, 0));
	getcwd(pwd, 1096);
	dir = ft_get_dir(env, parsed, pwd);
	if (dir == NULL)
		return (ft_error(CD_NO_FILE, parsed, 1));
	change_dir(env, parsed, dir);
	(ft_strcmp(dir, pwd)) ? free(dir) : 0;
	return (1);
}
