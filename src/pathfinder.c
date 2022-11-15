#include "../inc/pathfinder.h"

void dijkstra(int **matrix, int n, int startnode, t_list *t_names)
{
    int cost[n][n];
    int distance[n];
    int pred[n];
    int visited[n];
    int count;
    int mindistance;
    int nextnode;
    int i;
    int j;
    int count_nums = 0;

    int arr_for_nums[200];
    t_list **pred_lists = malloc(n * sizeof(t_list *));

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            if (matrix[i][j] == 0)
                cost[i][j] = INFINITY;
            else
                cost[i][j] = matrix[i][j];
    }
    for (i = 0; i < n; i++)
    {
        distance[i] = cost[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
        int t = startnode;
        pred_lists[i] = mx_create_node((void *)&t);
    }
    distance[startnode] = 0;
    visited[startnode] = 1;
    count = 1;
    while (count < n - 1)
    {
        mindistance = INFINITY;
        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }
        visited[nextnode] = 1;
        for (i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                if (mindistance + cost[nextnode][i] < distance[i] && mindistance + cost[nextnode][i] > 0) /// mindistance + cost[nextnode][i] > 0
                {
                    arr_for_nums[count_nums] = nextnode;
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                    mx_clear_list(&pred_lists[i], false);
                    pred_lists[i] = mx_create_node((void *)(&arr_for_nums[count_nums++]));
                }
                else if (mindistance + cost[nextnode][i] == distance[i] &&
                         mindistance + cost[nextnode][i] > 0)
                {
                    arr_for_nums[count_nums] = nextnode;
                    mx_push_front(&pred_lists[i], (void *)(&arr_for_nums[count_nums++]));
                }
            }
        }
        count++;
    }

    print_results(distance, startnode, n, matrix, t_names, pred_lists);
}
