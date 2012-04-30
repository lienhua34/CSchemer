#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

extern cellpoint char_eq(void);
extern cellpoint char_less(void);
extern cellpoint char_greater(void);
extern cellpoint char_less_eq(void);
extern cellpoint char_greater_eq(void);
extern cellpoint char_eq_ci(void);
extern cellpoint char_less_ci(void);
extern cellpoint char_greater_ci(void);
extern cellpoint char_less_eq_ci(void);
extern cellpoint char_greater_eq_ci(void);
extern cellpoint char_is_upcase(void);
extern cellpoint char_is_lowercase(void);
extern cellpoint char_is_alphabetic(void);
extern cellpoint char_is_numeric(void);
extern cellpoint char_is_whitespace(void);
extern cellpoint char_2_integer(void);
extern cellpoint integer_2_char(void);
extern cellpoint char_upcase(void);
extern cellpoint char_downcase(void);

#endif // CHARACTER_H_INCLUDED
