#include "../includes/cc9.h"

/* if next token's kind macthes argument "op", proceed token to the next one.(return true) */ 
bool	consume(char *op)
{
	if (token->kind != TK_RESERVED 
		|| strlen(op) != token->len
		|| memcmp(token->str, op, token->len))
		return false;
	token = token->next;
	return true;
}

/* if next token's kind macthes argument "op", proceed token to the next one. (void) 
 * The difference from consume is that it's the last parser so print error if the op does'nt macth.*/
void	expect(char *op)
{
	if (token->kind != TK_RESERVED
		|| strlen(op) != token->len
		|| memcmp(token->str, op, token->len))
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
	
