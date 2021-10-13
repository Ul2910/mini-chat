#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	errors(void)
{
	write(2, "Signal error\n", 13);
	exit(-1);
}

int	ft_atoi(char *nptr)
{
	int	i;
	int	number;

	i = 0;
	number = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + (nptr[i] - 48);
		i++;
	}
	return (number);
}

void	send_char(int pid, char c)
{
	int	index;
	int	i;
	int	kill_ret;

	index = (int)c;
	i = -1;
	while (++i < 8)
	{
		if (index % 2 == 1)
			kill_ret = kill(pid, SIGUSR1);
		else
			kill_ret = kill(pid, SIGUSR2);
		if (kill_ret == -1)
			errors();
		index = index / 2;
		usleep(50);
		if (index < 2 && index != 0)
		{
			if (kill(pid, SIGUSR1) == -1)
				errors();
			index = 0;
			i++;
			usleep(50);
		}
	}
}

int	main(int argc, char *argv[])
{
	int	i;
	int	pid;

	if (argc != 3)
	{
		write(2, "Usage: ./client PID \"Message\"\n", 30);
		exit(-2);
	}
	pid = ft_atoi(argv[1]);
	i = -1;
	while (argv[2][++i] != '\0')
		send_char(pid, argv[2][i]);
	send_char(pid, argv[2][i]);
}
