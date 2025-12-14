#include "../includes/cc9.h"

Node	*equality();
Node	*relational();
Node	*add();
Node	*mul();
Node	*unary();
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
	return (equality());	
}

Node	*equality()
{
	Node	*node = relational();

	for (;;)
	{
		if (consume("=="))
			node = new_node(ND_EQ, node, relational());	
		else if (consume("!="))	
			node = new_node(ND_NEQ, node, relational());	
		else
			return (node);	
	}	
}	

Node	*relational()
{
	Node	*node = add();
	
	for(;;)
	{
		if (consume("<="))
			node = new_node(ND_COM_I, node, add());
		else if(consume(">="))
			node = new_node(ND_COM_I, add(), node);
		else if (consume("<"))
			node = new_node(ND_COM_N, node, add());
		else if (consume(">"))
			node = new_node(ND_COM_N, add(), node);	
		else
			return (node);	
	}	
}	

Node	*add()
{
	Node	*node = mul();

	for (;;)
	{
		/* left_associative, so pass a old node to lhs(second arg)*/
		if (consume("+"))
			node = new_node(ND_ADD, node, mul()); 
		else if (consume("-"))
			node = new_node(ND_SUB, node, mul());
		else
			return (node);
	}
}	

/* 「 mul = unary ("*" unary | "/" unary)* 」
 *  create a mul() Node */
Node	*mul()
{
	Node	*node = unary();

	for (;;)
	{
		/* left_associative */
		if (consume("*"))
			node = new_node(ND_MUL, node, unary());
		else if (consume("/"))
			node = new_node(ND_DIV, node, unary());
		else
			return (node);
	}
}

/* 「 unary = ("+" | "-")? primary 」
 * create a unary Node */
Node	*unary()
{
	if (consume("+"))	
		return (primary());
	if (consume("-"))
		return (new_node(ND_SUB, new_node_num(0), primary())); // "-x" -> "0-x"
	return (primary());	
}	

/* 「 primary = "(" expr"")" | num 」
 * create a primary Node */
Node	*primary()
{
	Node	*node;	

	if (consume("("))
	{	
		node = expr();
		expect(")");	
		return (node);	
	}	
	return (new_node_num(expect_number()));	
}	
