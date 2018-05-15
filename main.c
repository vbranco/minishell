#include <stdio.h>
#include "mini.h"

void	name(char *path, char *line)
{
	while (*line)
	{
		*path = *line;
		path++;
		line++;
	}
	*(path) = '\0';
}

static int	test(char *str)
{
	const char	*pwd = "PWD";
	char		tmp;

	tmp = str[3];
	str[3] = '\0';
	if (ft_strcmp(pwd, str) == 0)
	{
		str[3] = tmp;
		return (1);
	}
	str[3] = tmp;
	return (0);
}

void	ft_getenv(t_inf *info, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (test(env[i]) == 1)
			info->pwd = ft_strsub(env[i], 4, ft_strlen(env[i]) - 4);
		i++;
	}
	printf("%s\n", info->pwd);
}

int		main(int ac, char **av, char **env)
{
	t_inf	info;
	int		i = 0;

	ft_initialise(&info);
	ft_getenv(&info, env);

	return  (0);
}
