// #ifndef GRAMMAR
// #define GRAMMAR

// #include "vectors.h"
// #include "strings.h"
// #include "lexer.h"
// #include "lexical_token.h"
// #include <stdbool.h>

// enum GrammarTokenKind
// {
//     program,
//     otherFunctions,
//     mainFunction,
//     stmts,
//     function,
//     input_par,
//     output_par,
//     parameter_list,
//     dataType,
//     remaining_list,
//     primitiveDatatype,
//     constructedDatatype,
//     typeDefinitions,
//     declarations,
//     otherStmts,
//     returnStmt,
//     typeDefinition,
//     definetypestmt,
//     fieldDefinitions,
//     fieldDefinition,
//     moreFields,
//     fieldtype,
//     declaration,
//     global_or_not,
//     otherStmts,
//     assignmentStmt,
//     iterativeStmt,
//     conditionalStmt,
//     ioStmt,
//     funCallStmt,
//     singleOrRecId,
//     arithmeticExpression,
//     recId,
//     outputParameters,
//     inputParameters,
//     idList,
//     booleanExpression,
//     var,
//     operator, // DEBUG:
//     term,
//     factor,
//     termPrime,
//     var1,
//     logicalOp,
//     relationalOp,
//     optionalReturn,
//     idList,
//     more_ids,
//     A,

//     // Do not belong to non terminals
//     TERMINAL,
//     INVALID_GTOK,
//     EOF_GTOK
// };

// // static char *grammarTokenKindString[] =
// //     {
// //         "E",
// //         "A",
// //         "T",
// //         "B",
// //         "F",

// //         // Not non terminals
// //         "Terminal",
// //         "INVALID_GTOK",
// //         "EOF_GTOK"};
// // ;

// static char *grammarTokenKindString[] =
//     {
//         "program",
//         "otherFunctions",
//         "mainFunction",
//         "stmts",
//         "function",
//         "input_par",
//         "output_par",
//         "parameter_list",
//         "dataType",
//         "remaining_list",
//         "primitiveDatatype",
//         "constructedDatatype",
//         "typeDefinitions",
//         "declarations",
//         "otherStmts",
//         "returnStmt",
//         "typeDefinition",
//         "definetypestmt",
//         "fieldDefinitions",
//         "fieldDefinition",
//         "moreFields",
//         "fieldtype",
//         "declaration",
//         "global_or_not",
//         "otherStmts",
//         "assignmentStmt",
//         "iterativeStmt",
//         "conditionalStmt",
//         "ioStmt",
//         "funCallStmt",
//         "singleOrRecId",
//         "arithmeticExpression",
//         "recId",
//         "outputParameters",
//         "inputParameters",
//         "idList",
//         "booleanExpression",
//         "var",
//         "operator", // DEBUG:
//         "term",
//         "factor",
//         "termPrime",
//         "var1",
//         "logicalOp",
//         "relationalOp",
//         "optionalReturn",
//         "idList",
//         "more_ids",
//         "A",

//         // Do not belong to non terminals
//         "TERMINAL",
//         "INVALID_GTOK",
//         "EOF_GTOK"};

// // enum GrammarTokenKind
// // {
// //     E,
// //     R,
// //     T,
// //     Y,
// //     F,

// //     // Do not belong to terminals
// //     TERMINAL,
// //     INVALID_GTOK,
// //     EOF_GTOK
// // };

// // static char *grammarTokenKindString[] =
// // {
// //     "E",
// //     "R",
// //     "T",
// //     "Y",
// //     "F",

// //     // Not terminals
// //     "Terminal",
// //     "INVALID_GTOK",
// //     "EOF_GTOK"
// // };

// typedef struct _Grammar
// {
//     char *filename;
//     Lexer lexer;
//     Vector rules;
//     Vector first;
//     Vector follow;
//     bool *isNullRule;
//     Vector parseTable;
// } Grammar;

// typedef struct _Rule
// {
//     Token lhs;
//     Vector rhs;
// } Rule;

// Rule *iRule(Token lhs);

// Grammar *iGrammar(char *filename);

// void printRule(Rule *rule);

// void _calculateFirst(Grammar *grammar);

// void _calculateFollow(Grammar *grammar);

// void _computeParseTable(Grammar *grammar);

// void printFirstSet(Grammar *grammar);

// void printFollowSet(Grammar *grammar);

// void printParseTable(Grammar *grammar);

// int _getTerminal(String value);

// Rule *copy_rule(Rule *destination, Rule *source);

// // For internal workings

// void _loadGrammar(Grammar *grammar);

// Rule *_nextGrammarRule(FILE *fp);

// int _getNonTerminal(String nonTerminal);

// Vector _findFirst(Grammar *grammar, Token element, bool terminal);

// Vector _findFollow(Grammar *grammar, Token element);

// #endif