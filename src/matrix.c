#include "../inc/pathfinder.h"

int **make_paths_matrix(t_list *names, char **lines, int l_count, int islands_count)
{
	int size = islands_count;
	int fro_i;
	int to_i;
	int **paths = malloc(size * sizeof(int *));

	for (int i = 0; i < size; i++)
	{
		paths[i] = malloc(size * sizeof(int));
		for (int j = 0; j < size; j++)
		{
			paths[i][j] = 0;
		}
	}
	for (int i = 1; i < l_count - 1; i++)
	{
		char **names_count = mx_strsplit(lines[i], ',');
		char **names_lines = mx_strsplit(names_count[0], '-');
		int dist = mx_atoi(names_count[1]);
		fro_i = get_i_by_value(names, names_lines[0]);
		to_i = get_i_by_value(names, names_lines[1]);
		if (fro_i != -1 && to_i != -1)
		{
			paths[fro_i][to_i] = dist;
			paths[to_i][fro_i] = dist;
		}
		else
		{
			mx_del_strarr(&names_count);
			mx_del_strarr(&names_lines);
			return NULL;
		}
		mx_del_strarr(&names_count);
		mx_del_strarr(&names_lines);
	}

	return paths;
}

int get_i_by_value(t_list *list, void *value)
{
	int i = 0;
	for (t_list *temp = list; temp != NULL; temp = temp->next, i++)
	{
		if (!mx_strcmp(value, temp->data))
			return i;
	}
	return -1;
}

static void index_of(t_list **paths, t_list **lists, int *buf, int index, const int cur, int start)
{
	if (cur == start)
	{
		buf[index++] = start;
		int i = 0;
		int j = 0;
		int *arr = malloc((index + 1) * sizeof(int));
		for (i = index - 2; i >= 0; i--)
		{
			arr[j++] = buf[i];
		}
		mx_push_back(paths, arr);
	}
	else
	{
		for (t_list *temp = lists[cur]; temp; temp = temp->next)
		{
			buf[index++] = *(int *)temp->data;
			index_of(paths, lists, buf, index, *(int *)temp->data, start);
			index--;
		}
	}
}

t_list *generate_indexes(t_list **lists, int len, int startnode)
{
	int nums[200];
	t_list *permutations = mx_create_node("");
	for (int i = 0; i < len; i++)
	{
		if (i != startnode)
		{
			nums[0] = -1;
			nums[1] = i;
			index_of(&permutations, lists, nums, 2, i, startnode);
		}
	}
	mx_pop_front(&permutations);
	return permutations;
}

void *find_by_i(t_list *list, int i)
{
	int j = 0;
	for (t_list *temp = list; temp; temp = temp->next)
	{
		if (j++ == i)
			return temp->data;
	}
	return NULL;
}
