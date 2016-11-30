/**@<lexer.c>::**/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <tokens.h>
#include <keywords.h>
#include <lexer.h>

void skipspaces (FILE *dish)
{
	while ( isspace ( lexeme[0] = getc (dish) ) ){
		//if (lexeme[0] = '\n') break;
	}
	ungetc ( lexeme[0], dish );
}

char lexeme[MAXID_SIZE+1];//@ lexer.c

int is_assign(FILE *tape) {

	if (( lexeme[0] = getc(tape)) == ':'){
		if(( lexeme[1] = getc(tape)) == '='){
			lexeme[2] = '\0';
			return ASGN;
		}
		ungetc (lexeme[1], tape);
	}
	ungetc (lexeme[0], tape);
	return 0;
}

int is_identifier (FILE *tape) {
	int i = 0;

	lexeme[i] = getc(tape);
	if (isalpha (lexeme[i]) ) {
		for (i++; isalnum (lexeme[i] = getc(tape)); i++) {
			if(i > MAXID_SIZE) i = MAXID_SIZE;
		}
		ungetc (lexeme[i], tape);
		lexeme[i] = '\0';
		//printf("Lex: %s\n", lexeme);
		if( (i = iskeyword(lexeme)) ) return i;
		return ID;
	}
	ungetc (lexeme[i], tape);
	return 0;
}

int is_decimal (FILE *tape) {
	int i = 0;

	if (isdigit (lexeme[i] = getc(tape) ) ) {
		if (lexeme[i] == '0') {
			++i;
			lexeme[i] = getc(tape);
			return i;
		}
		// [0-9]*
		for(++i; isdigit( lexeme[i] = getc(tape) ); ++i) {
			if(i >= MAXID_SIZE) i = MAXID_SIZE;
		}
		return i;
	}
	return 0;
}

int is_exp (FILE *tape, int *count) {

	if( toupper( lexeme[(*count)] ) == 'E') {
		++(*count);
		if( (lexeme[(*count)] = getc(tape) )== '+' || lexeme[(*count)]== '-') {
				++(*count);
				if(isdigit( lexeme[(*count)]  = getc(tape) )) {
					for ( (*count)++; isdigit (lexeme[(*count)] = getc(tape)); (*count)++) {
						if( (*count) >= MAXID_SIZE) (*count) = MAXID_SIZE;
					}
					return 1;
				}
		}
		else if(isdigit(lexeme[(*count)])) {
			for ((*count)++; isdigit (lexeme[(*count)] = getc(tape)); (*count)++) {
					if((*count) >= MAXID_SIZE) (*count) = MAXID_SIZE;
			}
				return 1;
		}
		ungetc(lexeme[(*count)], tape);
		--(*count);
		return 0;
	}
	return 0;
}

int is_float(FILE *tape) {
	int i = 0;

	if( (i = is_decimal(tape)) ) { //dec
		if( lexeme[i] == '.') { //dec.
			for (i++; isdigit (lexeme[i] = getc(tape)); i++) {
				if(i >= MAXID_SIZE) i = MAXID_SIZE;
			}
			is_exp(tape, &i);
			ungetc(lexeme[i], tape);
			lexeme[i] = '\0';
			return FLT;
		}
		else if(is_exp(tape, &i)) { //dec exp
			ungetc(lexeme[i], tape);
			lexeme[i] = '\0';
//COLOQUEI ESSA PARTE
			int lexval= atoi(lexeme);
			int *intIEEE = malloc(sizeof(lexeme)+1);
			*intIEEE = ((int)&lexval);
			if(*intIEEE > MAXRAN_SIZE) return DBL;
			return FLT;
		}
		ungetc(lexeme[i], tape);
		lexeme[i] = '\0';
		return DEC;
	}
	else if(lexeme[i] == '.') {
		++i;
		lexeme[i] = getc(tape);
		if( isdigit(lexeme[i]) ) { //.digit
			for (i++; isdigit (lexeme[i] = getc(tape)); i++) {
				if(i >= MAXID_SIZE) i = MAXID_SIZE;
			}
			is_exp(tape, &i);
			ungetc(lexeme[i], tape);
			lexeme[i] = '\0';
			
			//COLOQUEI ESSA PARTE
			int lexval= atoi(lexeme);
			char *intIEEE = malloc(sizeof(lexeme)+1);
			*intIEEE = ((int)&lexval);
			if(*intIEEE > MAXRAN_SIZE) return DBL;
			return FLT;

		}
		ungetc(lexeme[i], tape);
		--i;
	}
	ungetc(lexeme[i], tape);
	lexeme[i] = '\0';
	return 0;
}

int gettoken(FILE *sourcecode) {
	int token;

	skipspaces (sourcecode);

	if( (token = is_identifier(sourcecode)) ) {
		//printf("TK: %d\n", token);
		return token;
	}

	if( (token = is_assign(sourcecode)) ) {
		return token;
	}

	if( (token = is_float (sourcecode)) ) {
		//printf("TOKEN: %d\n", token);
		return token;
	}

	lexeme[1] = 0;

	lexeme[0] = token = getc (sourcecode);

	return token;
}
