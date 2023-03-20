/*
** EPITECH PROJECT, 2022
** my_getnbr.c
** File description:
** task05
*/

int my_strlen(char const *str);

int    check_number(long result, long new)
{
    long test = result * 10 + new;
    if (test > result) {
        return (1);
    }
    return (0);
}

int is_number(char c)
{
    if (c >= '0' && c <= '9') {
        return 1;
    }
    return 0;
}

long    store_numbers(char *str, int start)
{
    long result = 0;
    int intval = 0;
    for (int i = start; is_number(str[i]) && str[i] != '\0'; i++) {
        intval = str[i] - 48;
        if (check_number(result, intval)) {
            result = result * 10 + intval;
        } else
            return 0;
    }
    return result;
}

long    my_getnbr(char* str)
{
    int len = my_strlen(str);
    int exp = 1;
    long final_number;
    int i;

    for (i = 0; str[i] != '\0' ; i++) {
        if (str[i] <= '0' || str[i] > '9')
            continue;
        else
            break;
    }
    final_number = store_numbers(str, i);
    if (i != 0 && str[i - 1] == '-')
        final_number = final_number * -1;
    return final_number;
}
