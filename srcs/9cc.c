#include "../includes/cc9.h"

Token *token;

int	main(int argc, char **argv)
{	
	if (argc != 2)
	{
		error("invalid arg");	
		return (1);
	}
	token = tokenize(argv[1]);	
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
