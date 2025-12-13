#include "../includes/cc9.h"

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
		error_at(token->str, "expected '%c'", op);
	token = token->next;
}

int	expect_number()
{
	int	val;

	if (token->kind != TK_NUM)
		error_at(token->str, "expected a number");
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

Token	*tokenize()
{
	char	*p;	
	Token	head;
	Token	*cur;

	p = user_input;	
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
		error_at(p, "can't tokenize");	
	}	
	new_token(TK_EOF, cur, p);
	return (head.next);	
}	
