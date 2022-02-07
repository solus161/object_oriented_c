#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calculator.h"

const char NUMERICS[] = ".0123456789";
const char OPERATORS[] = "+-*/^()";

// Type Numeric
void NumPrint(struct Token * token, int short_form) {
    printf("%f", token->value);
};
static struct classToken Num = {NUM_TOKEN, 0, LR, NULL, NumPrint};

// Type Addition
static double AddProcess(struct Token *token_left, struct Token *token_right) {
    double value_left = 0.0;
    double value_right = 0.0;
    if (token_left != NULL) value_left = token_left->value;
    if (token_right != NULL) value_right = token_right->value;
    return value_left + value_right;
};
void AddPrint(struct Token * token, int short_form) {
    if (!short_form) {
        printf("(+, %f)", token->value);
    } else {
        printf("+");
    };
};
static struct classToken Add = {ADD_TOKEN, LR, 1, AddProcess, AddPrint};

// Type Substraction
static double SubProcess(struct Token *token_left, struct Token *token_right) {
    double value_left = 0.0;
    double value_right = 0.0;
    if (token_left != NULL) value_left = token_left->value;
    if (token_right != NULL) value_right = token_right->value;
    return value_left - value_right;
};
void SubPrint(struct Token * token, int short_form) {
    if (!short_form) {
        printf("(-, %f)", token->value);
    } else {
        printf("-");
    };
};
static struct classToken Sub = {SUB_TOKEN, LR, 1, SubProcess, SubPrint};

// Type Multiplication
static double MulProcess(struct Token *token_left, struct Token *token_right) {
    double value_left = 1.0;
    double value_right = 1.0;
    if (token_left != NULL) value_left = token_left->value;
    if (token_right != NULL) value_right = token_right->value;
    return value_left*value_right;
};
void MulPrint(struct Token * token, int short_form) {
    if (!short_form) {
        printf("(*, %f)", token->value);
    } else {
        printf("*");
    };
};
static struct classToken Mul = {MUL_TOKEN, LR, 2, MulProcess, MulPrint};

// Type Division
static double DivProcess(struct Token *token_left, struct Token *token_right) {
    double value_left = 1.0;
    double value_right = 1.0;
    if (token_left != NULL) value_left = token_left->value;
    if (token_right != NULL) value_right = token_right->value;
    return value_left/value_right;
};
void DivPrint(struct Token * token, int short_form) {
    if (!short_form) {
        printf("(/, %f)", token->value);
    } else {
        printf("/");
    };
};
static struct classToken Div = {DIV_TOKEN, LR, 2, DivProcess, DivPrint};

// Type Power
static double PowProcess(struct Token * token_left, struct Token * token_right) {
    double value_left = 1.0;
    double value_right = 1.0;
    if (token_left != NULL) value_left = token_left->value;
    if (token_right != NULL) value_right = token_right->value;
    return pow(value_left, value_right);
};
void PowPrint(struct Token * token, int short_form) {
    if (!short_form) {
        printf("(^, %f)", token->value);
    } else {
        printf("^");
    };
};
static struct classToken Pow = {POW_TOKEN, RL, 3, PowProcess, PowPrint};

// Type left parenthese
void LParenPrint(struct Token * token, int short_form) {
    printf("(");
};
static struct classToken LParen = {LPAREN, LR, 4, NULL, LParenPrint};

// Type right parenthese
void RParenPrint(struct Token * token, int short_form) {
    printf(")");
}
static struct classToken RParen = {RPAREN, LR, 4, NULL, RParenPrint};

// New token, should be clear after calculation done
struct Token * new(enum token_type type, double value) {
    struct Token * ptr = malloc(sizeof(struct Token));
    ptr->value = value;
    switch (type) {
        case NUM_TOKEN:
            ptr->class = &Num;
            break;
        case ADD_TOKEN:
            ptr->class = &Add;
            break;
        case SUB_TOKEN:
            ptr->class = &Sub;
            break;
        case MUL_TOKEN:
            ptr->class = &Mul;
            break;
        case DIV_TOKEN:
            ptr->class = &Div;
            break;
        case POW_TOKEN:
            ptr->class = &Pow;
            break;
        case LPAREN:
            ptr->class = &LParen;
            break;
        case RPAREN:
            ptr->class = &RParen;
            break;
    };
    return ptr;
};

// Delete token
void delete(struct Token * token) {
    free(token);
    token = NULL;
};

// Process token, doing the calculation
void process(struct Token * token, struct Token * token_left, struct Token * token_right) {
    const struct classToken * class = token->class;
    token->value = class->process(token_left, token_right);
};

// Print token
void print(struct Token * token, int short_form){
    // assert(token);
    struct classToken * classptr = token->class;
    assert(classptr);
    assert(classptr->_str);
    if (classptr->_str) classptr->_str(token, short_form);
};

// New list
struct List * new_list() {
    struct List * list = malloc(sizeof(struct List));
    list->length = 0;
    list->value = malloc(sizeof(struct Token *) * 0);
    return list;
};

// Append token to a list
void append(struct List * list, struct Token * token) {
    int new_length = list->length + 1;
    struct Token ** new_value = realloc(list->value, sizeof(struct Token *) * new_length);
    if (new_value) {
        new_value[new_length - 1] = token;
        list->value = new_value;
        list->length = new_length;
    };
};

// Get item from a list
struct Token * get_item(struct List * list, int index) {
    if (list->length > 0) {
        if (index == -1) index = list->length - 1;
        if (index < -1) return NULL;
        if (index >= list->length) return NULL;
        return list->value[index];
    } else {
        return NULL;
    };
    return NULL;
};

// Pop out a token from the list
struct Token * pop(struct List * list, int index) {
    // index = -1 -> last item
    // index >= length -> do nothing
    // index < -1 -> do nothing
    if (index >= list->length || index < -1) {
        return NULL;
    };
    if (index == -1) index = list->length - 1;

    // Get pop out item
    struct Token * pop_item = get_item(list, index);

    // Shrink array
    int new_length = list->length - 1;
    struct Token * last_item = list->value[list->length - 1];
    struct Token ** new_value = realloc(list->value, sizeof(struct Token *) * new_length);

    
    if (list->length > 1) {
        if (new_value) {
            if (index == list->length - 1) {
                // Pop out last item
                list->value = new_value;
                list->length = new_length;
                return pop_item;
            } else {
                // Pop out an item in between
                for (int i = index; i < new_length; i++) {
                    memmove(&new_value[i], &new_value[i + 1], sizeof(struct Token *));
                };
                new_value[new_length - 1] = last_item;
                list->value = new_value;
                list->length = new_length;
                return pop_item;
            };
        } else {
            exit(0);
        }
    } else {
        list->value = new_value;
        list->length = new_length;
        return pop_item;
    };
};

// Reset list, include freeing all tokens
void reset_list(struct List * list) {
    for (int i = 0; i < list->length; i++) {
        free(list->value[i]);
        list->value[i] = NULL;
    };
    
    struct Token ** new_value = realloc(list->value, 0);
    list->value = new_value;
    list->length = 0;
};

// Parsing operators
struct Token * parse_operator(const char * expression, int * index) {
    char current_char = expression[*index];
    *index = *index + 1;
    switch (current_char) {
        case '+':
            return new(ADD_TOKEN, 0.0);
        case '-':
            return new(SUB_TOKEN, 0.0);
        case '*':
            return new(MUL_TOKEN, 0.0);
        case '/':
            return new(DIV_TOKEN, 0.0);
        case '^':
            return new(POW_TOKEN, 0.0);
        case '(':
            return new(LPAREN, 0.0);
        case ')':
            return new(RPAREN, 0.0);
    };
    return NULL;
};

// Parsing number
struct Token * parse_number(const char * expression, int * index) {
    int start_index = * index;
    int end_index = * index;
    double number;
    int decimal_separator = 0;
    int zero_padded = 0;
    int buff_length = 1;
    char current_char;
    char * char_found;

    // printf("Start parsing number\n");

    while (1) {
        current_char = expression[end_index];
        // printf("Current char %c at index %d\n", current_char, end_index);
        if (current_char == '.') {
            if (end_index == start_index) zero_padded = 1;
            decimal_separator++;
        };

        // Conditions for ending
        if (decimal_separator > 1) {
            *index = end_index;
            break;
        };

        char_found = strchr(NUMERICS, current_char);
        if (char_found == NULL) {
            *index = end_index;
            break;
        };
        end_index++;
    };
    buff_length = end_index - start_index + zero_padded;
    // printf("start_index %d end_index %d zero_padded %d buff_length %d\n", start_index, end_index, zero_padded, buff_length);
    char result_string[buff_length];
    if (zero_padded) result_string[0] = '0';
    for (int i = 0; i < end_index - start_index; i++) {
        // printf("Copy over char %c\n", expression[start_index + i]);
        result_string[i + zero_padded] = expression[start_index + i];
    };
    result_string[buff_length] = '\0';
    // printf("result_string %s\n", result_string);
    number = strtod(result_string, NULL);
    *index = end_index;
    // printf("Number read %f\n", number);
    return new(NUM_TOKEN, number);
};

// Parsing
struct Token * parse(const char * expression, int * index) {
    char init_char = expression[*index];
    int counter = 0;
    char * char_found;
    
    // printf("Init char %c at %d", init_char, *index);
    // Loop until meet an end char
    // End chars include space, \0, or operator
    if (isspace(init_char)) {
        *index = *index + 1;
        return NULL;
        };
    if (init_char == '\0') return NULL;
    
    char_found = strchr(OPERATORS, init_char);
    if (char_found) {
            struct Token * token = parse_operator(expression, index);
            return token;
            // append(list, token);
        };

    char_found = strchr(NUMERICS, init_char);
    if (char_found) {
        struct Token * token = parse_number(expression, index);
        return token;
        // append(list, token);
    };
    return NULL;
};

// Calculator
double cal_eval(struct Calculator * self, const char * expression, int debug) {
    int expression_length = strlen(expression);
    struct Token * token;
    struct classToken * token_class;
    struct Token * stack_last;          // Last token in operator stack
    struct classToken * stack_class;    // Class of the last token in the stack
    struct Token * stack_pop;           // Token to be pop out of stack into output
    struct List * output = self->output;
    struct List * stack = self->stack;
    int index = 0;

    while (1) {
        if (expression[index] == '\0' || index >= expression_length) break;
        
        // Uncomment this for defail of output
        if (debug) {
            printf("Building output\n");
            for (int i = 0; i < output->length; i++) {
                print(output->value[i], 1);
                printf(" ");
            };
            printf("\n");    
        }
        
        token = parse(expression, &index);
        if (token == NULL) continue;
        // printf("Token parsed ");
        // print(token, 1);
        // printf("\n");

        token_class = token->class;
        stack_last = get_item(stack, -1);
    
        if (stack_last != NULL) {
            stack_class = stack_last->class;
        } else {
            stack_class = NULL;
        };

        // If token is number, append to output
        if (token_class->type == NUM_TOKEN) {
            // printf("Num token ");
            // print(token, 1);
            // printf("\n");
            append(output, token);
            continue;
        };
        
        // If last operator token is NULL
        if (stack_last == NULL) {
            append(stack, token);
            continue;
        }

        // If token is left parenthese
        if (token_class->type == LPAREN) {
            append(stack, token);
            continue;
        };
        
        // If token is right parenthese
        if (token_class->type == RPAREN) {
            while (stack_class->type != LPAREN) {
                stack_pop = pop(stack, -1);
                append(output, stack_pop);
                stack_last = get_item(stack, -1);
                stack_class = stack_last->class;
            };

            // Discard both parentheses
            stack_pop = pop(stack, -1);
            free(stack_pop);
            free(token);
            continue;
        };

        // Comparing precedence
        if (stack_class->type != LPAREN) {
            if (stack_class != NULL) {
                if (token_class->evaluate == LR) {
                    // Pop stack into output until last stack > token, then put token into stack
                    while (token_class->precedence <= stack_class->precedence) {
                        stack_pop = pop(stack, -1);
                        append(output, stack_pop);
                        stack_last = get_item(stack, -1);
                        if (stack_last == NULL) break;
                        stack_class = stack_last->class;
                    };
                };
                append(stack, token);
            } else if (token_class->precedence > stack_class->precedence) {
                // Put token into stack
                append(stack, token);
            };
        } else {
            append(stack, token);
        };
        
    };

    // Pop all remaining stack into output
    while (stack->length > 0) {
        stack_pop = pop(stack, -1);
        append(output, stack_pop);
    };

    if (debug) {
        printf("Final output\n");
        for (int i = 0; i < output->length; i++) {
            print(output->value[i], 1);
            printf(" ");
        };
        printf("\n");
    };
    
    // Process the output
    index = 0;
    struct Token * left_token;
    struct Token * right_token;
    int index_left;
    int index_right;
    double result;
    
    while (output->length > 1) {
        // Uncomment this for details
        if (debug) {
            printf("Parsing output\n");
            for (int i = 0; i < output->length; i++) {
                print(output->value[i], 1);
                printf(" ");
            };
            printf("\n");
        }
        

        token = get_item(output, index);
        token_class = token->class;
        // printf("%d\n", token_class->type);
        if (token_class->type != NUM_TOKEN) {
            if (token_class->type == LPAREN) {
                printf("Missing closing parenthese, please check the expression.\n");
                return 0.0;
            };

            index_left = index - 2;
            index_right = index - 1;
            
            if (index_left < 0) {
                left_token = NULL;
            } else {
                left_token = get_item(output, index_left);
            };

            if (index_right < 0) {
                right_token = NULL;
            } else {
                right_token = get_item(output, index_right);
            };

            if (left_token == NULL || right_token == NULL) {
                // ERROR
                printf("Error while parsing the expression.");
                return -1;
            };
            process(token, left_token, right_token);
            // print(token);
            token->class = &Num; // Change class to num
            
            // Pop out two previous token
            stack_pop = pop(output, index - 1);
            stack_pop = pop(output, index - 2);
            free(left_token);
            free(right_token);

            index = index - 2;
        };
        index++;
    };
    

    result = get_item(output, 0)->value;
    reset_list(output);
    reset_list(stack);

    return result;
};

void cal_reset(struct Calculator * self) {
    reset_list(self->output);
    reset_list(self->stack);
};

double compute(struct Calculator * calculator, const char * expression, int debug) {
    return cal_eval(calculator, expression, debug);
};

struct Calculator * init_calculator() {
    struct List * output = new_list();
    struct List * stack = new_list();
    struct Calculator * my_cal = malloc(sizeof(struct Calculator));
    my_cal->output = output;
    my_cal->stack = stack;
    return my_cal;
};