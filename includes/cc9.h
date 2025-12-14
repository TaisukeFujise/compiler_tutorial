#ifndef CC9_H
# define CC9_H

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* lexer */
typedef enum
{
	TK_RESERVED, // symbol
	TK_NUM, // integer token
	TK_EOF, // eof token
}	TokenKind;

typedef struct Token Token;

struct Token
{
	TokenKind	kind;
	Token		*next;
	int			val;
	char		*str; // token string
	int			len; // token length
};

Token	*tokenize();

extern char		*user_input;
extern Token	*token;

/* parser */
typedef enum
{
	ND_ADD,
	ND_SUB,
	ND_MUL,
	ND_DIV,
	ND_NUM,	
	ND_EQ,   // equality node
	ND_NEQ,  // non equality node 
	ND_COM_I,
	ND_COM_N,	
	// ND_LTEQ, // less than or equal to
	// ND_GTEQ, // greater than or equal to
	// ND_LT,   // less than
	// ND_GT,	 // greater than
}	NodeKind;

typedef struct Node Node;

struct Node
{
	NodeKind	kind; // node type
	Node		*lhs; // left-hand-side
	Node		*rhs; // right-hand-side
	int			val; // integer when this node is ND_NUM
};

/* error.c */
void	error(char *fmt, ...);
void	error_at(char *loc, char *fmt, ...);

/* utils.c */
bool	consume(char *op);
void	expect(char *op);
int		expect_number();
bool	at_eof();

/* parser.c */
Node	*expr();
/* gen.c */
void	gen(Node *node);

#endif
