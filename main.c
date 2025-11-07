#include "shell.h"

int main(int argc, char **argv)
{
	(void)argc;

	shell_loop(argv);
	return (0);
}
