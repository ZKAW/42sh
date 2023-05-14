/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** if
*/

#ifndef IF_H_
    #define IF_H_


    typedef struct shell shell_t;
    typedef struct command cmd_t;

    #define IF_PARAMS char *str1, char *str2

bool if_equal(IF_PARAMS);
bool if_not_equal(IF_PARAMS);
bool if_greater(IF_PARAMS);
bool if_lower(IF_PARAMS);
bool if_greater_equal(IF_PARAMS);
bool if_lower_equal(IF_PARAMS);

typedef struct if_s {
    char **conditions;
    char *cmd;
    bool is_true;
} if_t;

struct if_conditionner {
    const char *op;
    bool (*func)(IF_PARAMS);
};

static const struct if_conditionner if_conditions[] = {
    {"==", if_equal},
    {"!=", if_not_equal},
    {">", if_greater},
    {"<", if_lower},
    {">=", if_greater_equal},
    {"<=", if_lower_equal},
    {NULL, NULL}
};

#endif /* !IF_H_ */
