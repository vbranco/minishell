#include "mini.h"

void	update_env(t_env **env, char *pwd)
{
	t_env	*tmp;
	t_env	*up;

	ft_printf("\n\ndebug  ||  pwd >> %s\n\n",pwd);
	tmp = *env;
	up = ft_initialise();
	tmp->prev->next = up;
	up->name = ft_strdup("PWD");
	up->data = ft_strdup(pwd);
	up->next = tmp->next;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
		{
			tmp->prev->next = *env;
			(*env)->next = tmp->next;
			free((*env)->name);
			(*env)->name = ft_strdup("OLDPWD");
			free(tmp->name);
			free(tmp->data);
			tmp->next = NULL;
			tmp->prev = NULL;
			free(tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

void	change_pwd_oldpwd(t_env *env, char *pwd)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD") == 0)
		{
			update_env(&tmp, pwd); 
			break ;
		}
		tmp = tmp->next;
	}
}

void	change_home(t_env *env)
{
	t_env	*tmp;
	char	*buf;

	tmp = env;
	buf = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "HOME") == 0)
		{
			chdir(tmp->data);
			buf = getcwd(buf, 10000);
			change_pwd_oldpwd(env, buf);
			break ;
		}
		tmp = tmp->next;
	}
	free(buf);
}

void	change_oldpwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
		{
			if ((chdir(tmp->data)) != 0)
			{
				ft_printf("\n\nProbleme avec chdir dans change_oldpwd\n\n");
				break ;
			}
			ft_printf("%s\n", tmp->data);
			change_pwd_oldpwd(env, tmp->data);
			break ;
		}
		tmp = tmp->next;
	}
}

int		change_dir(t_env *env, char **parsed, char *pwd)
{
	char		*dir;

	if (parsed[1] == NULL || (ft_strcmp(parsed[1], "~") == 0))
	{
//		ft_printf("ici >> HOME\n");
		change_home(env);
	}
	else if (ft_strcmp(parsed[1], "-") == 0)
	{
//		ft_printf("ici >> OLDPWD\n");
		change_oldpwd(env);
	}
	else
	{
//		ft_printf("ici >> others\n");
		if (parsed[1][0] != '/')
		{
			dir = ft_realloc(pwd, "/");
			dir = ft_realloc(pwd, parsed[1]); 
		}
		else //if (parsed[1][0] == '/')
			dir = ft_strdup(parsed[1]);
		if ((chdir(dir)) == -1)
		{
			ft_putstr_fd(CD_NO_FILE, 2);
			ft_putendl_fd(dir, 2);
			free(dir);
			return (1);
		}
//		change_pwd_oldpwd(env, dir);
		free(dir);
	}
	return (0);
}

int		cd(t_env *env, char **parsed)
{
	char	*pwd;
	int		args;

	args = 0;
	pwd = NULL;
	while (parsed[args])
		args++;
	if (args > 3)
	{
		ft_putendl_fd(CD_TOO_ARGS, 2);
		return (-1);
	}
	pwd = getcwd(pwd, 10000);
	if (change_dir(env, parsed, pwd))
	{
		free(pwd);
		return (-1);
	}
	free(pwd);
	return (0);
}
