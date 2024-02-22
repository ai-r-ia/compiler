// // Loading rules
// int line_num = 0;
// Vector allRules = init_vector(RULE);
// char *line = strtok(strdup(buff), "\n");
// while (line)
// {
//     line_num++;

//     char *rest = line;

//     char *tokens = strtok_r(rest, "=", &rest);
//     int flag = 0;
//     Rule rule;
//     while (tokens)
//     {

//         if (flag == 0)
//         {
//             // printf("LHS %s \n", tokens);
//             struct string non_terminal = *init_str();

//             append(&non_terminal, tokens[0]);
//             int type = _getNonTerminal(&non_terminal);
//             if (type == -1)
//             {
//                 error("Non terminal type does not exist.");
//                 exit(1);
//             }

//             Token nonTerminal = init_Token(type, char_to_string(tokens), tokens, line_num, 1);
//             rule = init_rule(nonTerminal);

//             flag = 1;
//         }
//         else
//         {
//             printf("RHS %s \n", tokens);
//             printf("%s \n", (tokens));
//             char *tok2 = tokens;
//             char *terms = strtok_r(tok2, "|", &tok2);

//             while (terms)
//             {

//                 Token terminal = init_Token(5, char_to_string(terms), terms, line_num, 1);
//                 push_back(rule->derivables, terminal);

//                 terms = strtok_r(NULL, "|", &tok2);
//             }
//             flag = 0;
//         }

//         tokens = strtok_r(NULL, "~", &rest);
//     }

//     push_back(allRules, rule);

//     // printf("%s, %s \n", rule->NT->lexeme_str->text, ((Token)get(rule->derivables, 0))->lexeme_str->text);
//     line = strtok(NULL, "\n");
// }

// grammar->rules = allRules;