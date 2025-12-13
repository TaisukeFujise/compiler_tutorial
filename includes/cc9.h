#ifndef CC9_H
# define CC9_H

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	char		*str;
};

extern Token *token;

void	error(char *fmt, ...);
bool	consume(char op);
void	expect(char op);
int		expect_number();
bool	at_eof();
Token	*new_token(TokenKind kind, Token *cur, char *str);
Token	*tokenize(char *p);

#endif
