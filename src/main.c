/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 09:59:01 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/18 14:06:59 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
cd ~/repos/pipex/PIPEXaminator

~/repos/pipex/pipex_tester_42
bash pipex_tester.sh m

~/repos/pipex/PIPEXaminator
bash all_tests.sh
*/

int			openfile(char *filename, int mode);
void		pipex(char *cmd, char **env, int fdin);
void		run_cmd(char *cmd, char **env);
char		**ft_split(char const *s, char c);
int			find_char_pos(char *str, char c);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strndup(char *src, int len);
char		*find_cmd_path(char *cmd, char **env);
size_t		ft_strlen(const char *s);
int			ft_strchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strdup(const char *s1);

int	main (int ac, char **av, char **env)
{
	int	fdin;
	int	fdout;

	if (ac == 5)
	{
		fdin = openfile(av[1], INFILE);
		fdout = openfile(av[4], OUTFILE);
		dup2(fdin, STDIN);
		dup2(fdout, STDOUT);
		pipex(av[2], env, fdin);
		run_cmd(av[3], env);
	}
	else
		write(STDERR, "Invalid number of arguments.\n", 29);
	return (1);
}

int	openfile(char *filename, int mode)
{
	if (mode == INFILE)
	{
		if (access(filename, F_OK))
		{
			write(STDERR, "pipex: ", 7);
			write(STDERR, filename, find_char_pos(filename, 0));
			write(STDERR, ": No such file or directory\n", 28);
			return (STDIN);
		}
		return (open(filename, O_RDONLY));
	}
	else
		return (open(filename, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!(dup))
		return (NULL);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	pipex(char *cmd, char **env, int fdin)
{
	pid_t	pid;
	int		fd_pipes[2];

	pipe(fd_pipes);
	pid = fork();
	if (pid) // parent
	{
		close(fd_pipes[1]);
		dup2(fd_pipes[0], STDIN);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(fd_pipes[0]);
		dup2(fd_pipes[1], STDOUT);
		if (fdin == STDIN)
			exit(1);
		else
		{
			run_cmd(cmd, env);
		}
	}
}

void	run_cmd(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	
	if (find_char_pos(args[0], '/') != -1) // als niet erin staat
	{
		path = args[0];
	}
	else
	{
		path = find_cmd_path(args[0], env);
	}
	execve(path, args, env);
	write(STDERR, "pipex: ", 7);
	write(STDERR, cmd, find_char_pos(cmd, 0));
	write(STDERR, ": command not found\n", 20);
	exit(127);
}






int	find_char_pos(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	i = 0;
	j = 0;
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!s3)
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	s3[i] = '/';
	i++;
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_uc;
	unsigned char	*s2_uc;

	i = 0;
	s1_uc = (unsigned char *)s1;
	s2_uc = (unsigned char *)s2;
	while (i < n)
	{
		if ((!s1_uc[i]) && (s1_uc[i] == s2_uc[i]))
			return (0);
		if (s1_uc[i] != s2_uc[i])
			return (s1_uc[i] - s2_uc[i]);
		i++;
	}
	return (0);
}

int	ft_strchr(const char *s, int c)
{
	int		i;
	char	*s_uc;

	i = 0;
	s_uc = (char *)s;
	while (s_uc[i])
	{
		if (s_uc[i] == (char)c)
			return (i);
		i++;
	}
	if (s_uc[i] == (char)c)
		return (i);
	return (-1);
}

char	*ft_strndup(char *src, int len)
{
	int		i;
	char	*s;

	i = 0;
	if ((!(src)) || (len == 0))
		return (NULL);
	s = malloc(sizeof(char) * len + 1);
	while ((src[i]) && (i < (len - 1)))
	{
		s[i] = src[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*find_cmd_path(char *cmd, char **env)
{
	char *path;
	int	i;
	char *dir;
	char *tmp_cmd_path;
	path = ft_strdup("");

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PATH", env[i], ft_strlen("PATH")))
		{
			path = ft_strdup(&env[i][ft_strchr(env[i], '=') + 1]);
			break ;
		}
		i++;
	}
	if ((!path) || (path && path[0] == '\0'))
		return (NULL); // new onzin
	while (path && find_char_pos(path, ':') > -1)
	{
		dir = ft_strndup(path, find_char_pos(path, ':') + 1);
		tmp_cmd_path = ft_strjoin(dir, cmd);
		free(dir);
		if (access(tmp_cmd_path, F_OK) == 0)
		{
			return (tmp_cmd_path);
		}
		free(tmp_cmd_path);
		path += find_char_pos(path, ':') + 1;
	}
	return (cmd);
}






