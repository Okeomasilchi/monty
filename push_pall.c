#include "monty.h"

/**
 * _digits - cheaks if a string is all numbers
 * @ptr: pointer to the string
 *
 * Return: true if string is all integers else false
*/
bool _digits(char *ptr)
{
	while (*ptr)
	{
		if (!isdigit(*ptr))
			return (false);
		ptr++;
	}
	return (true);
}

/**
 * push - pushes to a stack
 * @stack: pointer to the stark to push to
 * @line_number: the current line where the command is comming from
 *
 * Return: void
*/
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new;

	if (_digits(num) && num != NULL)
	{
		new = malloc(sizeof(stack_t));
		new->n = atoi(num);
		new->prev = NULL;
		new->next = (*stack);
		(*stack) = new;
	}
	else
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		_free((*stack));
		exit(EXIT_FAILURE);
	}
}

/**
 * pall - prints all the values in a stark
 * @stack: pointer to the stark to push to
 * @line_number: the current line where the command is comming from
 *
 * Return: void
*/
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *cur = (*stack);

	(void)line_number;
	if (cur == NULL)
		return;
	while (cur != NULL)
	{
		printf("%d\n", cur->n);
		cur = cur->next;
	}
}

/**
 * pint - prints the value at the top of the stack
 * @stack: pointer to the stark to push to
 * @line_number: the current line where the command is comming from
 *
 * Return: void
*/
void pint(stack_t **stack, unsigned int line_number)
{
	if ((*stack) == NULL || (*stack)->n == '\0')
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

/**
 * pop - Removes the top element of the stack
 * @stack: pointer to the stark to push to
 * @line_number: the current line where the command is comming from
 *
 * Return: void
*/
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *nxt;

	if ((*stack) == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->next == NULL)
	{
		free(*stack);
		(*stack) = NULL;
		return;
	}
	nxt = (*stack)->next;
	(*stack)->next = NULL;
	nxt->prev = NULL;
	free(*stack);
	(*stack) = nxt;
}