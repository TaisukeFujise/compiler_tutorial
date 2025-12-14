#include "../includes/cc9.h"

Node	*mul();
Node	*primary();

/* create a new node from "kind", "lhs", and "rhs" */
Node	*new_node(NodeKind kind, Node *lhs, Node *rhs)
{
	Node	*node;

	node = calloc(1, sizeof(Node));
	node->kind = kind;
	node->lhs = lhs;
	node->rhs = rhs;
	return (node);
}

/* create a new number node from only "val" */
Node	*new_node_num(int val)
{
	Node	*node;

	node = calloc(1, sizeof(Node));
	node->kind = ND_NUM;
	node->val = val;
	return (node);
}

/* 「 expr = mul ("+" mul | "-" mul)* 」
 * create a expr() Node - it's top of AST in case of calc.
 * it returns one value as a result. */
Node	*expr()
{
	Node	*node = mul();

	for (;;)
	{
		/* left_associative, so pass a old node to lhs(second arg)*/
		if (consume('+'))
			node = new_node(ND_ADD, node, mul()); 
		else if (consume('-'))
			node = new_node(ND_SUB, node, mul());
		else
			return (node);
	}
}

/* 「 mul = primary ("*" primary | "/" primary)* 」
 *  create a mul() Node */
Node	*mul()
{
	Node	*node = primary();

	for (;;)
	{
		/* left_associative */
		if (consume('*'))
			node = new_node(ND_MUL, node, primary());
		else if (consume('/'))
			node = new_node(ND_DIV, node, primary());
		else
			return (node);
	}
}

/* 「 primary = "(" expr"")" | num 」
 * create a primary Node */
Node	*primary()
{
	Node	*node;	

	if (consume('('))
	{	
		node = expr();
		expect(')');	
		return (node);	
	}	
	return (new_node_num(expect_number()));	
}	
