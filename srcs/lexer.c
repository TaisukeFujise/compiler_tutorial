#include "../includes/cc9.h"

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
	Token	head;
	Token	*cur;

	head.next = NULL;
	cur = &head;	

	while (*user_input != '\0')
	{
		if (isspace(*user_input))
		{
			user_input++;
			continue;	
		}	
		if (
			*user_input == '+' || *user_input == '-'\
			|| *user_input == '*' || *user_input == '/'\
			|| *user_input == '(' || *user_input == ')'\
			)
		{
			cur = new_token(TK_RESERVED, cur, user_input++);
			continue;	
		}	
		if (isdigit(*user_input))
		{
			cur = new_token(TK_NUM, cur, user_input);	
			cur->val = strtol(user_input, &user_input, 10);
			continue;	
		}	
		error_at(user_input, "can't tokenize");	
	}	
	new_token(TK_EOF, cur, user_input);
	return (head.next);	
}	
