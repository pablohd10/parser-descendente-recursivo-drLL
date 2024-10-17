#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define NUMERO_VARIABLES 52

#define T_NUMBER 	1001
#define T_OPERATOR	1002
#define T_VARIABLE 1003

// Prototype for forward reference
int ParseExpression () ;
int ParseParametro() ;
int ParseRestoExpression() ;
int ParseMasParametros() ;

int token ;		// Here we store the current token/literal
int number ;		// the value of the number
int token_val ;		// the arithmetic operator
int variable;  // the variable
int variable_value[NUMERO_VARIABLES]; // array to store the values of the variables. 26 for lower case and 26 for upper case

// This function initializes to -1 the array that stores the values of the variables
void initialize_variable_value() {
    for (int i = 0; i < NUMERO_VARIABLES; i++) {
        variable_value[i] = -1;
    }
}

// keeps track of the line number
int line_counter = 1 ;

// Analizador léxico
int rd_lex ()
{
    int c ;

    do {
        c = getchar () ;
        if (c == '\n')
            line_counter++ ;	// info for rd_syntax_error()
    } while (c == ' ' || c == '\t' || c == '\r') ;

    if (isdigit (c)) {
        ungetc (c, stdin) ;
        scanf ("%d", &number) ;
        token = T_NUMBER ;
        return (token) ;	// returns the Token for Number
    }

    if (c == '+' || c == '-' || c == '*' || c == '/') {
        token_val = c ;
        token = T_OPERATOR ;
        return (token) ;
    }				// returns the Token for Arithmetic Operators

    if (isalpha(c)) {
        variable = c ;
        token = T_VARIABLE ;
        return (token) ;
    }				// returns the Token for a variable

    token = c ;
    return (token) ;		// returns a literal
}

// Función para comprobar si una variable está inicializada
bool variable_is_initialized(int var) {
    int index;
    if (var >= 'A' && var <= 'Z') {
        index = var - 'A' ;  /* resta a c el valor ascii de A */
    }
    else if (var >= 'a' && var <= 'z') {
        index = var - 'a' + 26 ;  /* resta a c el valor ascii de a y sumamos el número de carácteres en mayúsculas */
    }
    return variable_value[index] != -1;
}

// Función para reportar errores
void rd_syntax_error (int expected, int token, char *output)
{
    fprintf (stderr, "ERROR in line %d ", line_counter) ;
    fprintf (stderr, output, expected, token) ;

    exit (0) ;
}

// Función para comparar símbolos (tokens). Verifica que el token leído sea el esperado
void MatchSymbol (int expected_token)
{
    if (token != expected_token) {
        rd_syntax_error (expected_token, token, "token %d expected, but %d was read") ;
    }
    rd_lex();
}


#define ParseLParen() 	MatchSymbol ('(') ; // More concise and efficient definitions
#define ParseRParen() 	MatchSymbol (')') ; // rather than using functions
#define ParseExclamacion() MatchSymbol ('!') ;


int ParseNumber () 			// Numero ::= Token_Numero	                (RE-->[0-9]+)
{
    int val = number;
    MatchSymbol (T_NUMBER) ;
    return val ;
}

int ParseOperador()         // Operador ::= Token_Operador              (RE-->[+-/*])
{
    int val = token_val;
    MatchSymbol(T_OPERATOR);
    return val;
}

int ParseVariable()            // Variable ::= Token_Variable           (RE-->[a-zA-Z])
{
    int val = variable;
    MatchSymbol(T_VARIABLE);
    return val;
}

int ParseAxiom ()       // Axiom ::= Expression
{
    int val;
    val = ParseExpression () ;
    return val;
}

int ParseExpression () {     //Expression ::= ( RestoExpression | Numero | Variable )
    int val;

    //Check the FIRST set of Expression
    if (token == T_NUMBER) {    // Check if the current token is a number
        val = ParseNumber();
    }

    else if (token==T_VARIABLE) {    // Check if the current token is a variable
        // If it is a variable, check if it is initialized
        if (variable_is_initialized(variable)) {
            // Check if it is upper or lower case
            if (variable >= 'A' && variable <= 'Z') {
                val = variable_value[variable - 'A'];
            }
            else if (variable >= 'a' && variable <= 'z') {
                val = variable_value[variable - 'a' + 26];
            }
            // Parse the variable
            ParseVariable();
        }
        // If it is not initialized, report an error
        else {
            printf("ERROR: Variable '%c' no inicializada", variable);
            exit(0);
        }
    }
    // If it is not a number or a variable, it must start with left parenthesis
    else {
        ParseLParen();
        val = ParseRestoExpression();
    }
    return val; // returns the numeric value of the Expression
}


int ParseRestoExpression()  // RestoExpression ::= ( Operador Expression Expression MasParametros ) | ( ! Variable Parámetro)
{
    int val;
    int param1;
    int param2;
    int param3;
    int operador;
    int var;

    //Check the FIRST set of RestoExpression
    if (token == T_OPERATOR) {          // Check if the current token is an operator
        operador = ParseOperador();
        param1 = ParseParametro();
        param2 = ParseParametro();
        param3 = ParseMasParametros();
        // Compute the operation of the first two parameters
        switch (operador) {
            case '+':
                val = param1 + param2;
                break;
            case '-':
                val = param1 - param2;
                break;
            case '*':
                val = param1 * param2;
                break;
            case '/':
                val = param1 / param2;
                break;
        }
        // Compute the operation of the third parameter if it exists
        if (param3 != -1) {
            switch (operador) {
                case '+':
                    val += param3;
                    break;
                case '-':
                    val -= param3;
                    break;
                case '*':
                    val *= param3;
                    break;
                case '/':
                    val /= param3;
                    break;
            }
        }
        ParseRParen();
    }

    else{                           // Asignación de un valor a una variable
        ParseExclamacion();
        var = ParseVariable();
        val = ParseParametro();
        // Guardamos el valor de la variable
        if (var >= 'A' && var <= 'Z') {
            variable_value[var - 'A'] = val;
        }
        else if (var >= 'a' && var <= 'z') {
            variable_value[var - 'a' + 26] = val;
        }
        ParseRParen();
    }
    return val;
}


int ParseParametro()     // Parámetro ::= ( Operador Parámetro Parámetro MásParámetros ) | Variable | Número
{
    int val;
    int param1;
    int param2;
    int param3;
    int operador;

    //Check the FIRST set of Parametro
    if (token == T_NUMBER) {        // Check if the current token is a number
        val = ParseNumber();
    }
    // Check if the current token is a variable
    else if (token==T_VARIABLE) {
        if (variable_is_initialized(variable)) {
            if (variable >= 'A' && variable <= 'Z') {
                val = variable_value[variable - 'A'];
            }
            else if (variable >= 'a' && variable <= 'z') {
                val = variable_value[variable - 'a' + 26];
            }
            ParseVariable();
        }
        else {
            printf("ERROR: Variable '%c' no inicializada", variable);
            exit(0);
        }
    }
    // If it is not a number or a variable, it must start with parenthesis
    else {
        ParseLParen();
        operador = ParseOperador();
        param1 = ParseParametro();
        param2 = ParseParametro();
        param3 = ParseMasParametros();

        // Compute the operation
        switch (operador) {
            case '+':
                val = param1 + param2;
                break;
            case '-':
                val = param1 - param2;
                break;
            case '*':
                val = param1 * param2;
                break;
            case '/':
                val = param1 / param2;
                break;
        }
        // Compute the operation of the third parameter if it exists
        if (param3 != -1) {
            switch (operador) {
                case '+':
                    val += param3;
                    break;
                case '-':
                    val -= param3;
                    break;
                case '*':
                    val *= param3;
                    break;
                case '/':
                    val /= param3;
                    break;
            }
        }
        ParseRParen();
    }
    return val;
}


int ParseMasParametros()    // MásParámetros ::= ( Operador Parámetro Parámetro MásParámetros ) |
                            //                    Variable MásParámetros | Número MásParámetros | lambda
{
    int operador;
    int param1;
    int param2;
    int param3;
    int next_val;
    int val = -1;

    // Check if lambda is derived --> check the FOLLOW set of the rule.
    if (token == ')'){
        return val;
    }

    // Check the FIRST set of MasParametros
    else
    if (token == T_NUMBER){		// If the next token is a number, we parse it
        val = ParseNumber () ;
        // Recursively call the function to parse the rest of the parameters
        if (token == '(' || token == T_NUMBER || token == T_VARIABLE) {

            next_val = ParseMasParametros() ;
            switch (token_val){
                case '+' :  val += next_val ;
                    break ;
                case '-' :  val += next_val ;
                    break ;
                case '*' :  val *= next_val ;
                    break ;
                case '/' :  val *= next_val ;
                    break ;
            }
        }
    }

    else if (token==T_VARIABLE) {            // If the next token is a variable, we parse it
        // Check if the variable has been initialized
        if (variable_is_initialized(variable)) {

            if (variable >= 'A' && variable <= 'Z') {
                val = variable_value[variable - 'A'];
            }

            else if (variable >= 'a' && variable <= 'z') {
                val = variable_value[variable - 'a' + 26];
            }
            ParseVariable();
        }
        else {
            printf("ERROR: Variable '%c' no inicializada", variable);
            exit(0);
        }
        // Recursively call the function to parse the rest of the parameters
        if (token == '(' || token == T_NUMBER || token == T_VARIABLE) {

            next_val = ParseMasParametros() ;

            switch (token_val){
                case '+' :  val += next_val ;
                    break ;
                case '-' :  val -= next_val ;
                    break ;
                case '*' :  val *= next_val ;
                    break ;
                case '/' :  val /= next_val ;
                    break ;
            }
        }
    }

    else {                             // If the next token is an operator, we parse it
        ParseLParen () ;
        operador = ParseOperador();
        param1 = ParseParametro () ;
        param2 = ParseParametro () ;

        switch (operador){
            case '+':
                val = param1 + param2;
                break;
            case '-':
                val = param1 - param2;
                break;
            case '*':
                val = param1 * param2;
                break;
            case '/':
                val = param1 / param2;
                break;
        }

        ParseRParen () ;
        // Recursively call the function to parse the rest of the parameters
        if (token == '(' || token == T_NUMBER || token == T_VARIABLE) {

            param3 = ParseMasParametros() ;
            if (param3 != -1) {
                switch (token_val) {
                    case '+':
                        val += param3;
                        break;
                    case '-':
                        val -= param3;
                        break;
                    case '*':
                        val *= param3;
                        break;
                    case '/':
                        val /= param3;
                        break;
                }
                ParseRParen();
            }
        }
    }
    return val;
}

int main (void)
{
    // Initialize the variable values
    initialize_variable_value();
    while (1) {
        rd_lex () ;
        printf ("Valor %d\n", ParseAxiom ()) ;
    }

    system ("PAUSE") ;
}
