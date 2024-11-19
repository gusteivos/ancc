#include "main.h"

NOTRET STATIC
void usage(const char *name, bool show_help, int exit_status)
{

    FILE *out_fd = exit_status == EXIT_FAILURE ? stderr : stdout;

    fprintf(
        out_fd,
        "\n"
        "Usage: %s\n"
        "\n"
        "\t-if <file>\n"
        "\t-ir <name>\n"
        "\t-of <file>\n",
        name == NULL ? ANCC_NAME : name
        );

if (show_help)
{

    fprintf(
        out_fd,
        "\t-h\n"
        );

}

    fputc('\n', out_fd);

    exit(exit_status);

}

STATIC
char *shift_argcv(int *argc, char **argv[])
{

    assert(argc && argv);
    assert(*argc > 0 && *argv);

    char *arg = (*argv)[0];

    --(*argc);
    ++(*argv);

    return arg;

}

int main(int argc, char *argv[])
{

    const char *name = (const char *)shift_argcv(&argc, &argv);

    char *ifpatch = NULL;
    char *irtype = NULL;
    char *ofpatch = NULL;

    while (argc > 0)
    {

        bool show_help = true;

        int exit_status = EXIT_FAILURE;

        const char *arg = (const char *)shift_argcv(&argc, &argv);

        if (argc > 0)
        {

            char *val = shift_argcv(&argc, &argv);

            if      (strcmp(arg, "-if") == 0)
            {
                ifpatch = val;
            }
            else if (strcmp(arg, "-ir") == 0)
            {
                irtype = val;
            }
            else if (strcmp(arg, "-of") == 0)
            {
                ofpatch = val;
            }

        }
        else
        {

            if      (strcmp(arg, "-h") == 0)
            {
                show_help = false;
                exit_status = EXIT_SUCCESS;
            }

        }

        usage(name, show_help, exit_status);

    }

    error_novarg(EXIT_FAILURE, "We haven't implemented anything yet.");

    return EXIT_SUCCESS;

}
