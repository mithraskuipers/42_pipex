/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 09:59:01 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/19 18:30:52 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
~/repos/pipex/PIPEXaminator
bash all_tests.sh

~/repos/pipex/pipex_tester_42
bash pipex_tester.sh m
*/

int		openfile(char *filename, int mode);
void	pipex(char *cmd, char **envp, char *base_path);
void	run_cmd(char *cmd, char **envp, char *base_path);
char	**ft_split(char const *s, char c);
char	*px_strjoin(char *s1, char *s2);
char	*ft_strndup(char *src, int len);
char	*find_cmd_path(char *cmd, char *path);
int		ft_strlen(const char *s);
int		ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
void	dp_clean(char **dp);
void	ft_putstr_fd(char *s, int fd);
void	error_msg(char	*cmd);
int		read_file(char	*file);


char	*get_path_base(char **envp);

int		main(int argc, char **argv, char **envp)
{
	int	fdin;
	int	fdout;
	char *base_path;

	if (argc != 5)
		ft_putstr_fd("Invalid number of arguments.\n", 2);
	else
	{
		fdin = read_file(argv[1]);
		fdout = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fdin == -1)
			exit(1);
		dup2(fdin, 0);
		dup2(fdout, 1);
		base_path = get_path_base(envp);
		pipex(argv[2], envp, base_path);
		run_cmd(argv[3], envp, base_path);
	}
	return (1);
}

int		read_file(char	*file)
{
	if (access(file, F_OK) == 0)
		return (open(file, O_RDONLY));
	error_msg(file);
	return (-1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	error_msg(char	*cmd)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int		ft_strlen(const char *s)
{
	int	i;

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

void	pipex(char *cmd, char **envp, char *base_path)
{
	pid_t	process_id;
	int		fd_pipes[2];

	pipe(fd_pipes);
	process_id = fork();
	if (process_id == 0)
	{
		close(fd_pipes[0]);
		dup2(fd_pipes[1], 1);
		run_cmd(cmd, envp, base_path);
	}
	else if (process_id > 0)
	{
		close(fd_pipes[1]);
		dup2(fd_pipes[0], 0);
		waitpid(process_id, NULL, 0);
	}
}

char	*get_path_base(char **envp)
{
	int		i;
	char	*base_path;
	
	base_path = ft_strdup("");
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], ft_strlen("PATH")))
		{
			base_path = ft_strdup(&envp[i][ft_strchr(envp[i], '=') + 1]);
			return (base_path);
		}
		i++;
	}
	exit (1);
}

void	run_cmd(char *cmd, char **envp, char *base_path)
{
	char	**args;
	char	*cmd_path;
	args = ft_split(cmd, ' ');
	cmd_path = find_cmd_path(args[0], base_path);
	if (cmd_path == args[0])
	{
		dp_clean(args);
		error_msg(cmd);
		exit(127);
	}
	execve(cmd_path, args, envp);
}

char	*px_strjoin(char *s1, char *s2)
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

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = n * -1;
	}
	else
		nbr = n;
	if (nbr >= 10)
		ft_putnbr_fd(nbr / 10, fd);
	ft_putchar_fd(nbr % 10 + '0', fd);
}

char	*find_cmd_path(char *cmd, char *path)
{	
	char	*dir;
	char	*tmp_cmd_path;
	
	while (path && ft_strchr(path, ':') > -1)
	{
		dir = ft_strndup(path, ft_strchr(path, ':') + 1);
		tmp_cmd_path = px_strjoin(dir, cmd);
		free(dir);
		if (access(tmp_cmd_path, F_OK) == 0)
			return (tmp_cmd_path);
		free(tmp_cmd_path);
		path = path + ft_strchr(path, ':') + 1;
	}
	return (cmd);
}
