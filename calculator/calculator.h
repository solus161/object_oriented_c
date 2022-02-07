#ifndef CALCULATOR_H
#define CALCULATOR_H

#endif

// List of Tokens as operator
enum token_type {NUM_TOKEN, ADD_TOKEN, SUB_TOKEN, MUL_TOKEN, DIV_TOKEN, POW_TOKEN, LPAREN, RPAREN};
enum token_evaluate {LR, RL}; // Left-to-right or Right-to-left

// Structure of a token
struct Token {
    void * class;   // point to a specific class token
    double value;    // holding value
};

// Token Class in general
struct classToken {
    enum token_type type;
    enum token_evaluate evaluate;
    int precedence; // for operator
    double (* process) (struct Token * token_left, struct Token * token_right); // for operator
    void (* _str) (struct Token * token, int short_form);
};

// Type List of Token
struct List {
    int length;
    struct Token ** value; // Pointer to array of pointer to struct Token
};

// New list
struct List * new_list();

// Add a token to a list
void append(struct List * list, struct Token * token);

// Pop a token out off a list, pop last item if index not provided
struct Token * pop(struct List * list, int index);

// Reset list, include freeing all tokens
void reset_list(struct List * list);
struct Token * get_item(struct List * list, int index);

// Consume char at specified index, append to a list, return the next index
struct Token * parse(const char * expression, int * index);

// New, delete, print, get type for token
struct Token * new(enum token_type type, double value);
void delete(struct Token * token);
void process(struct Token * token, struct Token * token_left, struct Token * token_right);
void print(struct Token * token, int short_form);
enum token_type get_type(struct Token * token);

// Calculator class
struct Calculator {
    struct List * output; // Stack for output
    struct List * stack; // Stack for operator
};

struct Calculator * init_calculator();
double compute(struct Calculator * calculator, const char * expression, int debug);