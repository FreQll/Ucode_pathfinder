#include "../inc/pathfinder.h"

void mx_print_list(t_list *list)
{
    if (!list)
        return;

    while (list)
    {
        mx_printstr(list->data);
        mx_printchar('\n');
        list = list->next;
    }
}

void mx_print_error_line(int line)
{
    mx_printerr("error: line ");
    char *str = mx_itoa(line);

    mx_printerr(str);
    mx_strdel(&str);
    mx_printerr(" is not valid\n");
    exit(-1);
}

void print_results(int *distance, int startnode, int n, int **matrix, t_list *t_names, t_list **pred_lists)
{
    int i = 0;
    t_list *paths = generate_indexes(pred_lists, n, startnode);

    for (t_list *temp = paths; temp; temp = temp->next)
    {
        int *temp_list = (int *)temp->data;
        for (i = 0; temp_list[i + 1] != -1; i++)
            ;
        if (temp_list[i] > startnode)
        {
            mx_printstr("========================================\n");
            mx_printstr("Path: ");
            print_route(t_names, temp_list, i);
            mx_printstr("\n");
            mx_printstr("Distance: ");
            print_distance(matrix, temp_list, distance[temp_list[i]]);
            mx_printstr("========================================\n");
        }
    }
    mx_clear_list(&paths, true);
    for (int p = 0; p < n; p++)
    {
        mx_clear_list(&pred_lists[p], false);
    }
    free(pred_lists);
}

void print_distance(int **matrix, int *index, int dist)
{
    bool print_equal = 0;
    int i = 0;
    int j = 1;
    mx_printint(matrix[index[i++]][index[j++]]);
    for (; index[j] != -1; i++, j++)
    {
        mx_printstr(" + ");
        mx_printint(matrix[index[i]][index[j]]);
        print_equal = 1;
    }
    if (print_equal)
    {
        mx_printstr(" = ");
        mx_printint(dist);
    }
    mx_printstr("\n");
}

void print_route(t_list *names, int *path, int last)
{
    int j = 0;
    mx_printstr(find_by_i(names, path[0]));
    mx_printstr(" -> ");
    mx_printstr(find_by_i(names, path[last]));
    mx_printstr("\nRoute: ");
    for (; path[j + 1] != -1; j++)
    {
        mx_printstr(find_by_i(names, path[j]));
        mx_printstr(" -> ");
    }
    mx_printstr(find_by_i(names, path[j]));
}
