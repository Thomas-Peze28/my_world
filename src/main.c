/*
** EPITECH PROJECT, 2024
** day_13
** File description:
** main
*/

#include "window.h"

int is_tty(char **env)
{
    for (int i = 0; env[i]; i++) {
        if (my_strcmp(env[i], "XDG_SESSION_TYPE=tty") == 0) {
            write(2, "Wrong environement\n", 19);
            return 1;
        }
    }
    return 0;
}

int main(int argc, char **argv, char **env)
{
    // faire le -h !
    if (!env || !env[0] || is_tty(env))
        return 84;
    open_entry_window();
    return 0;
}
