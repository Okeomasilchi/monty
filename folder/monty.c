#include "monty.h"
#include "dic.h"

/**
 * _free - free's memory allocated for a stack
 * @stack: pointer to the stack to free
 *
 * Return: void
*/
/* void _free(struct stack_s *stack)
{
	free(monty);
	free_line(stack);
}

void free_line()
{
	if (monty->line)
		free(monty->line);
}
 */
/**
 * _opcode - gets the function to run from the command
 * @opcode: command from the command line
 *
 * Return: void
*/
struct instruction_s *_opcode(const char *opcode)
{
	unsigned long i;
	static struct instruction_s opcodes[] = {
		{"push", push}, {"pall", pall},
		{"pint", pint}, {"pop", pop},
	/* 	{"swap", swap}, {"add", add},
		{"nop", nop}, {"sub", sub},
		{"div", Div}, {"mul", mul},
		{"mod", mod}, {"#", nop},
		{"pchar", pchar}, {"pstr", pstr},
		{"rotl", rotl}, {"rotr", rotr},
		{"stack", stack}, {"queue", queue}, */
	};

	for (i = 0; i < sizeof(opcodes) / sizeof(opcodes[0]); i++)
	{
		if (strcmp(opcodes[i].opcode, opcode) == 0)
			return (&opcodes[i]);
	}
	return (NULL);
}

/**
 * file_handle - handles all file processing
 * @argc: argument count
 * @av: argument vectors
 *
 * Return: ponter of type FILE
*/
FILE  *file_handle(int argc, char *av)
{
	FILE *file = NULL;

	(void)av, (void)argc;
/* 	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	} */
	file = fopen("./file", "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", av);
		exit(EXIT_FAILURE);
	}
	return (file);
}

/**
 * op_cd - does the funtion setting for execution
 * @line: the command to run
 * @line_number: the number of the current line being executed
 *
 * Return: pointer of type instruction_t
*/
instruction_t *op_cd(char *line, unsigned int line_number)
{
	instruction_t *opcode;

	opcode = _opcode(line);
	if (opcode == NULL)
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", line_number, line);
		exit(EXIT_FAILURE);
	}
	return (opcode);
}

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
*/
int main(int argc, char **argv)
{
	FILE *file;
	unsigned int line_number = 1;
	ssize_t r;
	instruction_t *opcode = NULL;
	size_t line_length;
	char *tok;

	file = file_handle(argc, argv[1]);
	monty = malloc(sizeof(struct opcode));
	monty->que = false;
	monty->num = NULL;
	monty->stack = NULL;
	while (1)
	{
		monty->line = NULL;
		line_length = 0;
		r = getline(&monty->line, &line_length, file);
		if (r == EOF)
			break;
		
		remov(monty->line), line_space(monty->line);
		printf("%s", monty->line);
		if (monty->line[0] == '\0' || monty->line[0] == '\n')
		{
			line_number++;
			continue;
		}
		monty->line[strcspn(monty->line, "\n")] = '\0';
		printf("%s", monty->line);
		tok = strtok(monty->line, "\n\t \r");
		monty->line = tok;
		if (strcmp(monty->line, "push") == 0)
		{
			tok = strtok(NULL, "\n\t \r");
			if (tok != NULL)
				monty->num = tok;
			else
				monty->num = NULL;
		}
		opcode = op_cd(monty->line, line_number);
		opcode->f(&monty->stack, line_number);
		line_number++;
	}
	fclose(file);
	return (EXIT_SUCCESS);
}
