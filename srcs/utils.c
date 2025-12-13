#include "cc9.h"

void	error(char *fmt, ...)
{
	va_list	ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit (1);
}

bool	consume(char op)
{
	if (token->kind != TK_RESERVED || token->str[0] != op)
		return false;
	token = token->next;
	return true;
}

void	expect(char op)
{
	if (token->kind != TK_RESERVED || token->str[0] != op)
		error("'%c' is invalid", op);
	token = token->next;
}

int	expect_number()
{
	int	val;

	if (token->kind != TK_NUM)
		error("not number");
	val = token->val;
	token = token->next; 
	return (val);	
}

bool	at_eof()
{
	return token->kind == TK_EOF;	
}	

Token	*new_token(TokenKind kind, Token *cur, char *str)
{
	Token	*tok;

	tok = calloc(1, sizeof(Token));
	if (tok == NULL)
		return (NULL);
	tok->kind = kind;
	tok->str = str;
	cur->next = tok;
	return (tok);	
}	

Token	*tokenize(char *p)
{
	Token	head;
	Token	*cur;

	head.next = NULL;
	cur = &head;	

	while (*p != '\0')
	{
		if (isspace(*p))
		{
			p++;
			continue;	
		}	
		if (*p == '+' || *p == '-')
		{
			cur = new_token(TK_RESERVED, cur, p++);
			continue;	
		}	
		if (isdigit(*p))
		{
			cur = new_token(TK_NUM, cur, p);	
			cur->val = strtol(p, &p, 10);
			continue;	
		}	
		error("can't tokenize");	
	}	
	new_token(TK_EOF, cur, p);
	return (head.next);	
}	
