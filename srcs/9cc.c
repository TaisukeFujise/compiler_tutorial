#include "../includes/cc9.h"

char	*user_input;
Token 	*token;

int	main(int argc, char **argv)
{	
	if (argc != 2)
	{
		error("invalid arg");	
		return (1);
	}
	user_input = argv[1];	
	token = tokenize();		
	printf(".intel_syntax noprefix\n");
	printf(".globl main\n");
	printf("main:\n");
	printf("	mov rax, %d\n", expect_number());
	while (!at_eof())
	{
		if(consume('+'))
		{
			printf("	add rax, %d\n", expect_number());
			continue;	
		}	
		expect('-');
		printf("	sub rax, %d\n", expect_number());	
	}	
	printf("	ret\n");
	return (0);
}
