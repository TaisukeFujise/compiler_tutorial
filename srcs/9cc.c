#include "../includes/cc9.h"

char	*user_input;
Token 	*token;

int	main(int argc, char **argv)
{	
	Node	*node;	
	if (argc != 2)
	{
		error("invalid arg");	
		return (1);
	}
	user_input = argv[1];	
	token = tokenize(); // lexer 
	node = expr(); // parser
 
	// assembly first section //	
	printf(".intel_syntax noprefix\n");
	printf(".globl main\n");
	printf("main:\n");
	
	// generate code by traverse AST //	
	gen(node);	

	// load stack top value to rax //	
	printf("	pop rax\n"); 
	printf("	ret\n");
	return (0);
}
