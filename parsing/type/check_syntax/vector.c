#include "minirt.h"

int good_chars_vector(char *str)
{
    int i;
    int coma;

    i = 0;
    coma = 0;
    while (str[i])
    {
        if (str[i] != '-' && str[i] != '.' && str[i] != ',' && !(str[i] >= '0' && str[i] <= '9'))
            return (0);
        if (str[i] == ',')
            coma++;
        i++;
    }
    return (coma);
}

int good_coordinate(char *str)
{
    int i;
    int stock;

    i = 0;
    if (str[i] == '-')
        i++;
    if (!(str[i] >= '0' && str[i] <= '9'))
        return (0);
    while (str[i] >= '0' && str[i] <= '9')
        i++;
    if ((str[i] != '\0' && str[i] != ',' && str[i] != '.') || i - (str[0] == '-') > 9)
        return (0);
    if (!str[i] || str[i] == ',')
        return (1);
    i++;
    stock = i;
    if (!(str[i] >= '0' && str[i] <= '9'))
        return (0);
    while (str[i] >= '0' && str[i] <= '9')
        i++;
    if ((str[i] != '\0' && str[i] != ',') || i - stock > 9)
        return (0);
    return (1);
}

int vector_coordinates(char *str)
{
    int i;
    int call;

    i = 0;
    call = 0;
    if (good_chars_vector(str) != 2)
        return (0);
    while (str[i])
    {
        call++;
        if (!good_coordinate(&str[i]))
            return (0);
        while (str[i] && str[i] != ',')
            i++;
        if (str[i] == ',' && str[i + 1])
            i++;
    }
    if (call != 3)
        return (0);
    return (1);
}

int good_coordinate_normal(char *str)
{
    int i;
    int stock;

    i = 0;
    if (str[i] == '-')
        i++;
    if (str[i] != '0' && !check_for_1(&str[i]))
        return (0);
    i++;
    if (str[i] != '\0' && str[i] != ',' && str[i] != '.')
        return (0);
    if (!str[i] || str[i] == ',')
        return (1);
    i++;
    stock = i;
    if (!(str[i] >= '0' && str[i] <= '9'))
        return (0);
    while (str[i] >= '0' && str[i] <= '9')
        i++;
    if ((str[i] != '\0' && str[i] != ',') || i - stock > 9)
        return (0);
    return (1);
}

int vector_normal_information(char *str)
{
    int i;
    int call;

    i = 0;
    call = 0;
    if (good_chars_vector(str) != 2)
        return (0);
    while (str[i])
    {
        call++;
        if (!good_coordinate_normal(&str[i]))
            return (0);
        while (str[i] && str[i] != ',')
            i++;
        if (str[i] == ',' && str[i + 1])
            i++;
    }
    if (call != 3 || !check_vector_null(str))
        return (0);
    return (1);
}