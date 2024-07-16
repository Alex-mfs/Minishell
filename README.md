# JP_minitalk
This project consists of two programs that communicate between each other. The `client` program is designed to send messages, whereas `server` is designed to receive them. 

## General notes

### Functions from existing libraries
Functions from `signal.h` may require further context. It is recommended to read up on the structures behind them.

Function | Format | Description | Library
--- | --- | --- | ---
getpid | `int	getpid(void)` | Returns the current process ID | `signal.h`
kill | `int	kill(int pid, int sig)` | Sends signal sig to process pid. Returns 0 on success, -1 on error | `signal.h`
sigaction | `int	sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)` | Change action from a process based on the receipt of signal signum, according to either act or oldact. Returns 0 on success, -1 on error | `signal.h`
sigemptyset | `int	sigemptyset(sigset_t *set)` | Initializes and empties a signal set. Returns 0 on success, -1 on error | `signal.h`
pause | `int	pause(void)` | Pauses execution until a signal is delivered | `unistd.h`
sleep | `unsigned int	sleep(unsigned int s)` | Suspends execution for s seconds. Returns 0 (if interrupted, returns remaining time). | `unistd.h`
usleep | `int	usleep(unsigned int usec)` | Suspends execution for usec microseconds. Returns 0 (if interrupted, returns remaining time). | `unistd.h`

## Main Functions

### Libft functions

Function | Format | Modified?
--- | --- | ---
ft_atoi | `int	ft_atoi(const char *str)` | Same as libft
ft_isdigit | `bool	ft_isdigit(int c)` | Function now returns a boolean value

### ft_printf functions

Function | Format | Modified?
--- | --- | ---
ft_printf | `int	ft_printf(const char *string, ...)` | Same as ft_printf
ft_putchar_fd | `int	ft_putchar_fd(char c, int fd)` | Same as ft_printf
ft_putstr_fd | `int	ft_putstr_fd(char *str, int fd)` | Same as ft_printf
ft_putnbr_fd | `int	ft_putnbr_fd(long n, int fd)` | Same as ft_printf
ft_strlen | `size_t	ft_strlen(const char *str)` | Same as libft
ft_putnbr_ubase_fd | `int	ft_putnbr_ubase_fd(unsigned int nbr, char *base, int fd)` | Same as ft_printf
ft_putnbr_lbase_fd | `int	ft_putnbr_lbase_fd(unsigned long nbr, char *base, int fd)` | Same as ft_printf
ft_strchr | `char	*ft_strchr(const char *str, int c)` | Same as libft

### New functions

Function | Format | Description | Return
--- | --- | --- | ---
ft_print_error | `int	ft_print_error(char *str)` | Prints str as an error message, without exiting the program | 1
