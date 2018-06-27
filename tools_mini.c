#include "mini.h"

int		ft_count_nb_env(t_env *lst)
{
	int			i;

	i = 0;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i + 1);
}

char	**making_env(t_env_head *head, char *exe)
{
	char		**envi;
	char		tmp[1096];
	int			nb_env;
	int			i;
	t_env		*lst;

	i = 0;
	if (head->next == NULL)
		return (NULL);
	lst = head->next;
	nb_env = ft_count_nb_env(head->next);
	if (!(envi = (char**)malloc(sizeof(char*) * (nb_env + 1))))
		return (NULL);
	while (lst)
	{
		ft_bzero(tmp, 1096);
		ft_strcat(tmp, lst->name);
		ft_strcat(tmp, "=");
		ft_strcat(tmp, lst->data);
		envi[i] = ft_strdup(tmp);
		i++;
		lst = lst->next;
	}
	envi[i] = NULL;
	return	(envi);
}

static	void	ft_err(char *s, char *err)
{
		ft_putstr_fd(s, 2);
		ft_putendl_fd(err, 2);
}

void			execute_2(char *exe, char **parsed, char **environment, int i)
{
	if (execve(exe, parsed, environment) == -1)
	{
		ft_err(parsed[i], ": execve ERROR");
		exit(1);
	}
}

void			execute(t_env_head *head, char **parsed, int i)
{
	pid_t		pid;
	char		*exe;
	char		**environment;
	int			a;

	environment = NULL;
	exe = NULL;
	a = test_exe(head->next, parsed, i, &exe);
	if (a > 0)
	{
		if (searching_on_env(head, "_"))
			ft_updating_var(head, "_", exe);
		else
			ft_create_var(head, "_", exe);
		printf("dans execute || exe > %s\n", exe);
		environment = making_env(head, exe);
		pid = fork();
		if (pid < 0)
			ft_putendl_fd("ERROR FORK()", 2);
		if (pid == 0)
			execute_2(exe, parsed, environment, i);
		else
			wait(&pid);
		ft_free_2char(&environment);
		free(exe);
	}
	else if (a == -1)
		ft_err(parsed[i], ": Permission denied");
	else
		ft_err(parsed[i], NO_CMD);
}
