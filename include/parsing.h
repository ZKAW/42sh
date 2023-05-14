/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** parsing.h
*/

#ifndef PARSING_H_
    #define PARSING_H_

        #include <stddef.h>

        typedef struct command cmd_t;
        typedef struct command_array list_t;
        typedef struct shell shell_t;

        #define PARAMS char* cmd_str, list_t** command_array, shell_t* shell

        char* parse_double_output(PARAMS);
        char* parse_single_output(PARAMS);
        char* parse_double_input(PARAMS);
        char* parse_single_input(PARAMS);
        char* parse_default_token(PARAMS);
        char* parse_pipe(PARAMS);
        char* parse_semicolon(PARAMS);
        char* parse_backticks(PARAMS);
        char* parse_parenthesis(PARAMS);
        char* parse_and(PARAMS);
        char* parse_or(PARAMS);
        char* parse_quotes(PARAMS);
        char* parse_var(PARAMS);
        char *parse_bg(PARAMS);
        char* parse_foreach(PARAMS);
        char* parse_if(PARAMS);

        static char* tokens[] = {
            "foreach", "if" ,">>", ">", "<<", "<", "&&", "&", "||" ,"|", \
            ";", "`", "\'", "\"", "$", "(", NULL
        };

        static char* (*parsers[]) (PARAMS) = {
            parse_foreach,
            parse_if,
            parse_double_output,
            parse_single_output,
            parse_double_input,
            parse_single_input,
            parse_and,
            parse_bg,
            parse_or,
            parse_pipe,
            parse_semicolon,
            parse_backticks,
            parse_quotes,
            parse_quotes,
            parse_var,
            parse_parenthesis,
        };

#endif
