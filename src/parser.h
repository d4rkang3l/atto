
/*
 *  parser.h
 *  part of Atto :: https://github.com/deveah/atto
 */

#include <stdlib.h>
#include <stdint.h>

#include "state.h"
#include "lexer.h"

#pragma once

struct atto_ast_node {
  #define ATTO_AST_NODE_IDENTIFIER  0
  #define ATTO_AST_NODE_NUMBER      1
  #define ATTO_AST_NODE_SYMBOL      2
  #define ATTO_AST_NODE_LIST        3
  uint32_t kind;

  union {
    char *identifier;
    double number;
    uint64_t symbol;
    struct atto_ast_node *list;
  } container;

  struct atto_ast_node *next;
};

struct atto_definition {
  char *identifier;
  struct atto_expression *body;
};

struct atto_lambda_expression {
  uint32_t number_of_parameters;
  char **parameter_names;
  struct atto_expression *body;
};

struct atto_if_expression {
  struct atto_expression *condition_expression;
  struct atto_expression *true_evaluation_expression;
  struct atto_expression *false_evaluation_expression;
};

struct atto_application_expression {
  char *identifier;
  uint32_t number_of_parameters;
  struct atto_expression **parameters;
};

struct atto_list_literal_expression {
  uint32_t number_of_elements;
  struct atto_expression **elements;
};

struct atto_expression {
  #define ATTO_EXPRESSION_KIND_NUMBER_LITERAL   0
  #define ATTO_EXPRESSION_KIND_SYMBOL_LITERAL   1
  #define ATTO_EXPRESSION_KIND_LIST_LITERAL     2
  #define ATTO_EXPRESSION_KIND_REFERENCE        3
  #define ATTO_EXPRESSION_KIND_LAMBDA           4
  #define ATTO_EXPRESSION_KIND_IF               5
  #define ATTO_EXPRESSION_KIND_APPLICATION      6
  uint32_t kind;

  union {
    double number_literal;
    uint64_t symbol_literal;
    struct atto_list_literal_expression *list_literal_expression;
    char *reference_identifier;
    struct atto_lambda_expression *lambda_expression;
    struct atto_if_expression *if_expression;
    struct atto_application_expression *application_expression;
  } container;
};

struct atto_ast_node *atto_parse_token_list(struct atto_state *a, struct atto_token *root, struct atto_token **left);
struct atto_expression *parse_expression(struct atto_ast_node *e);
struct atto_if_expression *parse_if_expression(struct atto_ast_node *head);
struct atto_application_expression *parse_application_expression(struct atto_ast_node *head);
struct atto_list_literal_expression *parse_list_literal_expression(struct atto_ast_node *head);
struct atto_lambda_expression *parse_lambda_expression(struct atto_ast_node *head);
struct atto_definition *parse_definition(struct atto_ast_node *head);

void destroy_ast(struct atto_ast_node *root);

void puts_times(const char *what, size_t times);
void pretty_print_ast(struct atto_ast_node *root, size_t level);
void pretty_print_list_literal_expression(struct atto_list_literal_expression *e, int level);
void pretty_print_lambda_expression(struct atto_lambda_expression *e, int level);
void pretty_print_if_expression(struct atto_if_expression *e, int level);
void pretty_print_application_expression(struct atto_application_expression *e, int level);
void pretty_print_expression(struct atto_expression *e, int level);
void pretty_print_definition(struct atto_definition *d);

void destroy_expression(struct atto_expression *e);

