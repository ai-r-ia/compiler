#ifndef RULES
#define RULES

#include "lexical_token.h"
#include "vectors.h"
#include "stdio.h"

#define GRAMMAR_LENGTH 1000

// enum GrammarTokenKind
// {
//     <program>,
//     <otherFunctions>,
//     <mainFunction>,
//     <stmts>,
//     <function>,
//     <input_par>,
//     <output_par>,
//     <parameter_list>,
//     <dataType>,
//     <remaining_list>,
//     <primitiveDatatype>,
//     <constructedDatatype>,
//     <typeDefinitions>,
//     <declarations>,
//     <otherStmts>,
//     <returnStmt>,
//     <typeDefinition>,
//     <definetypestmt>,
//     <fieldDefinitions>,
//     <fieldDefinition>,
//     <moreFields>,
//     <fieldtype>,
//     <declaration>,
//     <global_or_not>,
//     <otherStmts>,
//     <assignmentStmt>,
//     <iterativeStmt>,
//     <conditionalStmt>,
//     <ioStmt>,
//     <funCallStmt>,
//     <singleOrRecId>,
//     <arithmeticExpression>,
//     <recId>,
//     <outputParameters>,
//     <inputParameters>,
//     <idList>,
//     <booleanExpression>,
//     <var>,
//     < operator>, // DEBUG:
//     <term>,
//     <factor>,
//     <termPrime>,
//     <var1>,
//     <logicalOp>,
//     <relationalOp>,
//     <returnStmt>,
//     <optionalReturn>,
//     <idList>,
//     <more_ids>,
//     <definetypestmt>,
//     <A>,

//         // Do not belong to non terminals
//         TERMINAL,
//     INVALID_GTOK,
//     EOF_GTOK
// };

// static char *grammarTokenKindString[] =
//     {
//         "E",
//         "A",
//         "T",
//         "B",
//         "F",

//         // Not non terminals
//         "Terminal",
//         "INVALID_GTOK",
//         "EOF_GTOK"};

enum GrammarTokenKind
{
    E,
    A,
    T,
    B,
    F,

    // Do not belong to non terminals
    TERMINAL,
    EPSILON,
    INVALID_GTOK,
    EOF_GTOK
};

static char *grammarTokenKindString[] =
    {
        "E",
        "A",
        "T",
        "B",
        "F",

        // Not non terminals
        "Terminal",
        "Epsilon",
        "INVALID_GTOK",
        "EOF_GTOK"};

typedef struct grammar *Grammar;
struct grammar
{
    char *filename;
    Vector rules;
    Vector first;
    Vector follow;
} grammar;

typedef struct rule *Rule;
struct rule
{
    Token NT;          // non terminal
    Vector derivables; // rhs of rule
} rule;

Rule init_rule(Token NT);

Grammar init_grammar(char *filename);

void printRule(Rule rule);

void populateFirst(Grammar grammar);

// private functions

void _loadGrammar(Grammar grammar);

int _getNonTerminal(String nonTerminal);

#endif