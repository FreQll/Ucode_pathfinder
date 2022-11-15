#include "../inc/pathfinder.h"

void mx_del_arr_with_data(char ***arr)
{
    char **temp = *arr;
    for (int i = 0; temp[i] != NULL; i++)
        mx_strdel(&temp[i]);
    free(temp);
    *arr = temp;
}

t_list *error_check(int argv, const char *filename, int *islands, int ***paths)
{
    //тут идет очень страшный код, не советую тебе его смотреть, я предупреждал)
    if (argv != 2)
    {
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(-1);
    }

    int file = open(filename, O_RDONLY);

    if (file == -1)
    {
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" does not exist\n");
        exit(-1);
    }

    char *text = mx_file_to_str(filename);
    if (mx_strlen(text) == 0)
    {
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" is empty\n");
        mx_strdel(&text);
        exit(-1);
    }

    int first_string = 0;
    for (int i = 0; text[i] != '\n'; i++)
    {
        if (!mx_isdigit(text[i]))
        {
            mx_strdel(&text);
            mx_print_error_line(1);
        }
        first_string++;
    }

    // check for lines
    int line = 2;
    int coma_count = 0;
    int defis_count = 0;
    bool coma = false;
    for (int i = first_string + 1; text[i] != '\0'; i++)
    {
        if (text[i] != '-' && text[i] != ',' && !mx_isalpha(text[i]) && !mx_isdigit(text[i]) && text[i] != '\n')
        {
            mx_strdel(&text);
            mx_print_error_line(line);
        }

        if (!mx_isalpha(text[i - 1]) && (text[i] == '-'))
        {
            mx_strdel(&text);
            mx_print_error_line(line);
        }

        if (text[i] == '-' && !mx_isalpha(text[i + 1]))
        {
            mx_strdel(&text);
            mx_print_error_line(line);
        }
        if (text[i] == '-')
            defis_count++;
        if (text[i] == ',')
        {
            coma = true;
            coma_count++;
            i++;
        }

        if (coma && !mx_isdigit(text[i]) && text[i] != '\n')
        {
            mx_strdel(&text);
            mx_print_error_line(line);
        }

        if (text[i] == '\n')
        {
            coma = false;
            if (defis_count != 1 || coma_count != 1)
            {
                mx_strdel(&text);
                mx_print_error_line(line);
            }
            line++;
            coma_count = 0;
            defis_count = 0;
        }
    }

    char **num = mx_strsplit(text, '\n');
    *islands = mx_atoi(num[0]);
    mx_del_strarr(&num);

    char *names = mx_file_to_str(filename);
    char *numbers = mx_file_to_str(filename);
    for (int i = 0; i < mx_strlen(names); i++)
    {
        if (mx_isdigit(names[i]) || names[i] == ',')
        {
            names[i] = ' ';
        }
        if (names[i] == '\n')
        {
            names[i] = '-';
        }
        if (mx_isalpha(numbers[i]) || numbers[i] == '-' || i < first_string)
            numbers[i] = ' ';
    }

    char *trim_names = mx_strtrim(names);
    char *trim_numbers = mx_strtrim(numbers);
    char **names_splitted = mx_strsplit(trim_names, '-');
    char **numbers_splitted = mx_strsplit(trim_numbers, ',');
    mx_strdel(&trim_names);
    mx_strdel(&trim_numbers);
    mx_strdel(&names);
    mx_strdel(&numbers);

    for (int i = 0; names_splitted[i] != NULL; i++)
    {
        char *temp_split = mx_strdup(names_splitted[i]);
        mx_strdel(&names_splitted[i]);
        names_splitted[i] = mx_strtrim(temp_split);
        mx_strdel(&temp_split);
    }
    for (int i = 0; numbers_splitted[i] != NULL; i++)
    {
        char *temp_split = mx_strdup(numbers_splitted[i]);
        mx_strdel(&numbers_splitted[i]);
        numbers_splitted[i] = mx_strtrim(temp_split);
        mx_strdel(&temp_split);
    }

    // check for islands
    if (validate_islands(names_splitted, *islands, &text, &names_splitted, &numbers_splitted) != 0)
    {
        mx_printerr("error: invalid number of islands\n");
        mx_del_arr_with_data(&numbers_splitted);
        mx_del_arr_with_data(&names_splitted);
        mx_strdel(&text);
        exit(-1);
    }

    // check for length
    int bridges_length[line - 2];
    for (int i = 0; i < line - 2; i++)
    {
        bridges_length[i] = mx_atoi(numbers_splitted[i]);
    }
    int sum = 0;
    for (int i = 0; i < line - 2; i++)
    {
        sum += bridges_length[i];
    }
    if (sum <= -INFINITY || sum >= INFINITY)
    {
        mx_printerr("error: sum of bridges lengths is too big\n");
        mx_del_arr_with_data(&numbers_splitted);
        mx_del_arr_with_data(&names_splitted);
        mx_strdel(&text);
        exit(-1);
    }

    t_list *unique_islands = unique_names(names_splitted, *islands);
    char *lines = mx_file_to_str(filename);
    char **lines_text = mx_strsplit(lines, '\n');
    *paths = make_paths_matrix(unique_islands, lines_text, line, *islands);
    mx_del_arr_with_data(&numbers_splitted);
    mx_del_arr_with_data(&names_splitted);
    mx_strdel(&text);
    mx_strdel(&lines);
    mx_del_strarr(&lines_text);
    return unique_islands;
}

int validate_islands(char **names, int num, char **text, char ***names_splitted, char ***numbers_splitted)
{
    int len = 1;
    for (; names[len] != NULL; len++)
        ;

    t_list *arr = unique_names(names, num);

    for (int i = 0; i < len; i += 2)
    {
        if (mx_strcmp(names[i], names[i + 1]) == 0)
        {
            mx_strdel(text);
            mx_clear_list(&arr, true);
            mx_del_arr_with_data(numbers_splitted);
            mx_del_arr_with_data(names_splitted);
            mx_print_error_line(i / 2 + 2);
        }
    }

    // check for duplicates
    for (int i = 0; i < len - 2; i += 2)
    {
        for (int j = i; j < len - 2; j += 2)
        {
            if (mx_strcmp(names[i], names[j + 2]) == 0 && mx_strcmp(names[i + 1], names[j + 3]) == 0)
            {
                mx_strdel(text);
                mx_clear_list(&arr, true);
                mx_del_arr_with_data(numbers_splitted);
                mx_del_arr_with_data(names_splitted);
                mx_printerr("error: duplicate bridges\n");
                exit(-1);
            }
            if (mx_strcmp(names[i], names[j + 3]) == 0 && mx_strcmp(names[i + 1], names[j + 2]) == 0)
            {
                mx_strdel(text);
                mx_clear_list(&arr, true);
                mx_del_arr_with_data(numbers_splitted);
                mx_del_arr_with_data(names_splitted);
                mx_printerr("error: duplicate bridges\n");
                exit(-1);
            }
        }
    }

    int real_length = mx_list_size(arr);
    mx_clear_list(&arr, true);
    return real_length - num;
}

t_list *unique_names(char **names, int count)
{
    count = 1;
    t_list *list = mx_create_node(mx_strdup(names[0]));
    for (int j = 1; names[j] != NULL; j++)
    {

        if (!mx_is_node(list, names[j]))
        {
            mx_push_back(&list, mx_strdup(names[j]));
        }
    }
    return list;
}
