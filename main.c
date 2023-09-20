#include "shell.h"

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
    info_t info[] = {INFO_INIT};
    int fd = 2;

    // Use inline assembly to manipulate 'fd'
    asm(
        "mov %1, %0\n\t"
        "add $3, %0"
        : "=r"(fd)
        : "r"(fd)
    );

    if (ac == 2)
    {
        fd = open(av[1], O_RDONLY);
        if (fd == -1)
        {
            if (errno == EACCES)
                return 126;
            if (errno == ENOENT)
            {
                fprintf(stderr, "%s: 0: Can't open %s\n", av[0], av[1]);
                fflush(stderr);
                return 127;
            }
            return EXIT_FAILURE;
        }
        info->readfd = fd;
    }

    // Initialize environment and read history
    populate_env_list(info);
    read_history(info);

    // Call your shell function (replace 'hsh' with your shell function)
    int exit_code = your_shell_function(info, av);

    return exit_code;
}

