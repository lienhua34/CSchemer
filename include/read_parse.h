#ifndef READ_PARSE_H_INCLUDED
#define READ_PARSE_H_INCLUDED

extern t_stack parser_stack;
extern t_stack state_stack;
extern cellpoint current_state;
extern cellpoint state_constants;
extern boolean input_error;

extern void set_state_constants(void);
extern void parser_init(void);
extern cellpoint read_parse(char *, char **);

#endif // READ_PARSE_H_INCLUDED
