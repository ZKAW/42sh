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
        
        #define TOKENS 6

        char* parse_double_output(char* cmd_str, cmd_t* cmd);
        char* parse_single_output(char* cmd_str, cmd_t* cmd);
        char* parse_double_input(char* cmd_str, cmd_t* cmd);
        char* parse_single_input(char* cmd_str, cmd_t* cmd);
        char* parse_default_token(char* cmd_str, cmd_t* cmd);
        char* parse_pipe(char* cmd_str, cmd_t* cmd);


        static char* tokens[TOKENS] = {">>",">", "<<", "<", "|", NULL};

        char* (*parsers[TOKENS])(char* cmmd_str, cmd_t* cmd) = {
            parse_double_output,
            parse_single_output,
            parse_double_input,
            parse_single_input,
            parse_pipe
        };

#endif
