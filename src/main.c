#include "../inc/pathfinder.h"

int main(int argv, char **argc)
{
    int islands;
    t_list *names = NULL;
    int **paths;

    names = error_check(argv, argc[1], &islands, &paths);

    for (int i = 0; i < islands; i++)
    {
        dijkstra(paths, islands, i, names);
    }

    for (int j = 0; j < islands; j++)
        free(paths[j]);
    free(paths);
    mx_clear_list(&names, true);
}
