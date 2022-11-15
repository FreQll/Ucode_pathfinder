#ifndef PATHFINDER_H
#define PATHFINDER_H

#define INFINITY 2147483645

#include "libmx.h"

// check errors functions
t_list *error_check(int argv, const char *filename, int *islands, int ***paths);
int validate_islands(char **names, int num, char **text, char ***names_splitted, char ***numbers_splitted);
t_list *unique_names(char **names, int count);

// pathfinder functions
void dijkstra(int **matrix, int n, int startnode, t_list *t_names);
int **make_paths_matrix(t_list *names, char **lines, int l_count, int islands_count);
t_list *generate_indexes(t_list **lists, int len, int startnode);

// print functions
void print_results(int distance[], int startnode, int n, int **matrix, t_list *t_names, t_list **pred_lists);
void print_distance(int **matrix, int *index, int dist);
void print_route(t_list *names, int *path, int last);
void mx_print_error_line(int line);

// other functions
int get_i_by_value(t_list *list, void *value);
void mx_del_arr_with_data(char ***arr);
void mx_clear_list(t_list **list, bool is_free);
bool mx_is_node(t_list *list, char *data);
void *find_by_i(t_list *list, int i);

#endif
