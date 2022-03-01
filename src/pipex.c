/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:02:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/01 15:06:26 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */



	dup2(pipefd[1], STDOUT_FILENO);


Als een process de stdoutput gebruikt om te printen,
gaat het niet naar stdout, maar naar de write deel van de pipe

	dup2(pipefd[0], STDIN_FILENO);

Als een proces uit stdin leest, doet het dat niet,
maar leest het uit read gedeelte van pipe


#include "pipex.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define PIPE_WRITE 1
#define PIPE_READ 0

int		ft_error(char *s, int errno);
size_t	ft_strlen(const char *s);
//int	pipex_error(char *s);
int		pipex_open_mode(char *filename, int mode);
void	pipex(int fd_input, int fd_output, char *cmd1, char *cmd2, char **envp);
int		child_process(int fd_input, char *cmd1);
static int	ft_countparts(const char *s, char c);
static char	**dp_clean(char **dp, size_t dp_i);
static char	**ft_split_helper(char **dp, const char *s, char c);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);

static int	ft_countparts(const char *s, char c)
{
	size_t	i;
	int		nparts;

	i = 0;
	nparts = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			nparts++;
			while (s[i] && s[i] != c)
				i++;
		}
		else if (s[i] && s[i] == c)
			i++;
	}
	return (nparts);
}

char	**ft_split(char const *s, char c)
{
	char	**dp;

	if (!(s))
		return (NULL);
	dp = ft_calloc((ft_countparts(s, c) + 1), sizeof(char *));
	if (!(dp))
		return (NULL);
	return (ft_split_helper(dp, s, c));
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

static char	**dp_clean(char **dp, size_t dp_i)
{
	while (dp_i > 0)
	{
		dp_i--;
		free(dp[dp_i]);
	}
	free(dp);
	return (NULL);
}

static char	**ft_split_helper(char **dp, const char *s, char c)
{
	size_t	s_i;
	size_t	dp_i;
	size_t	wordstart;

	s_i = 0;
	dp_i = 0;
	while (s_i < ft_strlen(s))
	{
		if ((s[s_i] != c) && (s_i < ft_strlen(s)))
		{
			wordstart = s_i;
			while ((s[s_i] != c) && (s_i < ft_strlen(s)))
				s_i++;
			dp[dp_i] = ft_substr(s, wordstart, (s_i - wordstart));
			if (!dp[dp_i])
				return (dp_clean(dp, dp_i));
			dp_i++;
		}
		s_i++;
	}
	return (dp);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	size_t			i;
	size_t			len;
	unsigned char	*b_uc;
	unsigned char	c;

	ptr = malloc(count * size);
	if (!(ptr))
		return (NULL);
	i = 0;
	len = count * size;
	b_uc = (unsigned char *)ptr;
	c = 0;
	while (i < len)
	{
		b_uc[i] = c;
		i++;
	}
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;
	size_t	s_len;

	if (!(s))
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	s_len = (ft_strlen(s) - start);
	if (s_len < len)
		len = s_len;
	sub_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!(sub_s))
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub_s[i] = s[(start + i)];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}



size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
int	pipex_error(char *s)
{
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	// free?
	return (1);
}
*/





int	pipex_open_mode(char *filename, int mode)
{
	if (mode == MODE_INPUT)
	{
		open(filename, O_RDONLY);
	}
	else if (mode == MODE_OUTPUT)
	{
		open(filename, O_CREAT | O_RDWR | O_TRUNC);
	}
	else
		perror("Could not open file.");
	return (1);
}

void	pipex(int fd_input, int fd_output, char *cmd1, char *cmd2, char **envp)
{
	int	fd_pipe[2];
	int processes;
	
	pipe(end);
	processes = fork();
	
	if (processes < 0)
		return (perror("Fork: "));
	
	// child
	// is simply used to REDIRECT OUTPUT
	// dup2(X,Y), whatever X had opened, is now also opened by Y
	if (processes == 0)
	{
		dup2(fd_input, STDIN_FILENO); // STDIN haalt nu data uit input file
		close(fd_pipe[0]); // close read end of pipe, because not used
		dup2(fd_pipe[1], STDOUT_FILENO); // STDOUT gebeurt nu in writing end of pipe
	}
	// parent
	if (processes > 0)
	{
		dup2(fd_output, STDOUT_FILENO);
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN_FILENO);
	}
		
}

/*
int	child_process(int fd_input, char *cmd1)
{
	//
	return (0);
}
*/

int	main(int argc, char **argv, char **envp)
{
	int fd_input;
	int fd_output;

	if (argc != 5)
		pipex_error("Invalid input. Please input 4 arguments.\n");
	fd_input = pipex_open_mode(argv[1], MODE_INPUT);
	fd_output = pipex_open_mode(argv[4], MODE_OUTPUT);


	pipex(fd_input, fd_output, cmd1, cmd2, envp);
	//close(fd_input);
	//close(fd_output);
	return (0);
}