#include "../includes/cc9.h"

Token	*new_token(TokenKind kind, Token *cur, char *str)
{
	Token	*tok;

	tok = calloc(1, sizeof(Token));
	tok->kind = kind;
	tok->str = str;
	tok->len = strlen(str);
	cur->next = tok;
	return (tok);	
}	

int	multiple_tokenize(Token *cur, char *user_input)
{
	if (
			memcmp(user_input, "<=", 2) == 0
			|| memcmp(user_input, ">=", 2) == 0
			|| memcmp(user_input, "==", 2) == 0
			|| memcmp(user_input, "!=", 2) == 0
	   )
	{
		cur = new_token(TK_RESERVED, cur,user_input);
		return (true);
	}
	return (false);	
}

int	single_tokenize(Token *cur, char *user_input)
{
	if (
		*user_input == '+' || *user_input == '-'\
		|| *user_input == '*' || *user_input == '/'\
		|| *user_input == '(' || *user_input == ')'\
		|| *user_input == '<' || *user_input == '>'\
	   )
	{
		cur = new_token(TK_RESERVED, cur, user_input);
		return (true);	
	}
	return (false);	
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
		if (multiple_tokenize(cur, user_input))
		{
			user_input += 2;
			continue;	
		}		
		if (single_tokenize(cur, user_input))
		{
			user_input++;
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
