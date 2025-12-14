#include "../includes/cc9.h"

/* generate assembly code from AST, by emulating x86-64 stack machine. */
void	gen(Node *node)
{	
	if (node->kind == ND_NUM)
	{
		printf("	push %d\n", node->val);
		return ;	
	}	
	gen(node->lhs);
	gen(node->rhs);

	printf("	pop rdi\n");
	printf("	pop rax\n");

		
	// switch(enum)==>> compiler check whether it covers all or not.	
	// enum and switch-case is good match. 
	switch (node->kind)
	{
		case ND_ADD:
			printf("	add rax, rdi\n");
			break;	
		case ND_SUB:
			printf("	sub rax, rdi\n");
			break;	
		case ND_MUL:
			printf("	imul rax, rdi\n");
			break;	
		case ND_DIV:
			printf("	cqo\n");
			printf("	idiv rdi\n");
			break;	
		case ND_EQ:
			printf("	cmp rax, rdi\n");
			printf("	sete al\n");
			printf("	movzx rax, al\n");	
			break;	
		case ND_NEQ:
			printf("	cmp rax, rdi\n");
			printf("	setne al\n");
			printf("	movzx rax, al\n");	
			break;	
		case ND_COM_I:
			printf("	cmp rax, rdi\n");
			printf("	setle al\n");
			printf("	movzx rax, al\n");	
			break;	
		case ND_COM_N:	
			printf("	cmp rax, rdi\n");
			printf("	setl al\n");
			printf("	movzx rax, al\n");	
			break;	
		default:
			break;	
	}	
	printf("	push rax\n");	
}	
