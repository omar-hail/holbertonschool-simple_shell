#include "shell.h"

int main(int argc, char **argv)
{
	int status;

	(void)argc;

	status = shell_loop(argv);
	return (status);
}

