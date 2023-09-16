#include "shell.h"

/**
 * main - Entry point of the shell program.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int argc, char **argv)
{
    // Initialize info_t structure
    info_t info = INFO_INIT;

    int fd = 2; // File descriptor for standard error (stderr)

    // Using inline assembly to modify fd (not clear from context)
    asm (
        "mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd)
    );

    // Check if a filename argument was provided
    if (argc == 2)
    {
        // Attempt to open the specified file for reading
        fd = open(argv[1], O_RDONLY);

        if (fd == -1)
        {
            // Handle file opening errors
            if (errno == EACCES)
            {
                exit(126); // Permission denied
            }
            else if (errno == ENOENT)
            {
                // Print an error message to stderr and exit
                _eputs(argv[0]);
                _eputs(": 0: Can't open ");
                _eputs(argv[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127); // File not found
            }
            return EXIT_FAILURE;
        }

        // Set the read file descriptor in the info structure
        info.readfd = fd;
    }

    // Populate environment variables list (function not shown)
    populate_env_list(&info);

    // Read history (function not shown)
    read_history(&info);

    // Execute the shell (function not shown)
    hsh(&info, argv);

    return EXIT_SUCCESS;
}

