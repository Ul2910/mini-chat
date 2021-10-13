#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void	ft_putnbr(int n)
{
	char	c;

	if (n >= 10)
	{
		ft_putnbr(n / 10);
		c = n % 10 + 48;
		write(1, &c, 1);
	}
	else
	{
		c = n % 10 + 48;
		write(1, &c, 1);
	}
}

int	ft_atoi_c(char c)
{
	int	number;

	number = c - 48;
	return (number);
}

void	print_ascii(char *str)
{
	int		index;
	char	c;

	index = ft_atoi_c(str[0]) * 1 + ft_atoi_c(str[1]) * 2
		+ ft_atoi_c(str[2]) * 4 + ft_atoi_c(str[3]) * 8
		+ ft_atoi_c(str[4]) * 16 + ft_atoi_c(str[5]) * 32
		+ ft_atoi_c(str[6]) * 64 + ft_atoi_c(str[7]) * 128;
	c = (char)index;
	if (c == '\0')
	{
		write(1, "\n", 1);
		return ;
	}
	write(1, &c, 1);
}

void	handler(int signum, siginfo_t *t_info, void *something)
{
	static int	counter = 1;
	char		str[9];

	if (signum == SIGUSR1)
		str[counter - 1] = '1';
	else
		str[counter - 1] = '0';
	if (counter - 8 == 0)
	{
		str[counter] = '\0';
		counter = 0;
		print_ascii(str);
	}
	counter++;
	(void)something;
	(void)t_info;
}

int	main(void)
{
	int					pid;
	struct sigaction	s_action;
	sigset_t			t_set;

	pid = getpid();
	write(1, "Server PID: ", 12);
	ft_putnbr(pid);
	write(1, "\n", 1);
	s_action.sa_sigaction = handler;
	s_action.sa_flags = SA_SIGINFO;
	if (sigemptyset(&t_set) == -1 || sigaddset(&t_set, SIGUSR1) == -1
		|| sigaddset(&t_set, SIGUSR2) == -1
		|| sigaction(SIGUSR1, &s_action, 0) == -1
		|| sigaction(SIGUSR2, &s_action, 0) == -1)
	{
		write(2, "Server signal error\n", 20);
		exit(-1);
	}
	while (1)
		pause();
}
