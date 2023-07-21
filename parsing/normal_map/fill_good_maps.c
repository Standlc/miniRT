#include "minirt.h"

int is_bump_map(char *str)
{
	if (!ft_strncmp(str, "bm-1", 4))
		return (0);
	if (!ft_strncmp(str, "bm-2", 4))
		return (1);
	if (!ft_strncmp(str, "bm-3", 4))
		return (2);
	if (!ft_strncmp(str, "bm-4", 4))
		return (3);
	if (!ft_strncmp(str, "bm-5", 4))
		return (4);
	return (-1);
}

int found_bump_map(char *row)
{
    int i;

    i = 0;
    while (row[i])
        i++;
    if (i == 0)
        return (-1);
    i--;
    while (row[i] == ' ')
        i--;
    i -= 3;
    if (i < 0)
        return (-1);
    return (is_bump_map(&row[i]));
}

int *fill_good_maps(char **rows)
{
    int *arr;
    int i;
    int index_bm;

    i = 0;
    index_bm = 0;
    arr = ft_calloc(sizeof(int), NB_MAP);
    if (!arr)
        return (error_allocation(), NULL);
    while (rows[i])
    {
        index_bm = found_bump_map(rows[i]);
        if (index_bm != -1)
            arr[index_bm] = 1;
        i++;
    }
    return (arr);
}