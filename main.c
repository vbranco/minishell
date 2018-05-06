#include <stdlib.h>
#include <stdio.h>


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


void	gtenv(char *str)
{
	int		i;
	int		a;
	char	*path;

	path = (char*)malloc(sizeof(char) * (51));
	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (str[i] == '=')
		a = i;
	else
		return ;
	*(str+i) = '\0';
	if (strcmp("PATH", str) == 0)
	{
		str = str + i + 1;
		name(path, str);
//		*(str + i) = '=';
		printf("PATH is  %s\n", path);
	}
	free(path);
}

int		main(int ac, char **av, char **env)
{
	int		i = 0;
	char	exe[500];
	while (env[i] != NULL)
	{
		gtenv(env[i]);
//		printf("%s\n",  env[i]);
		i++;
	}
	printf("i = %d\n", i);
//	getcwd(exe, 50);
//	printf("\nexe >> %s\n", exe);
	return  (0);
}
