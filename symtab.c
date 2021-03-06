#include <string.h>
#include <symtab.h>
#include <lexer.h>
#include <tokens.h>

int symtab[MAX_SYMTAB_ENTRIES][2];
int symtab_nextentry = 0;

char symtab_stream[MAX_SYMTAB_ENTRIES*(MAXID_SIZE+1)];
int symtab_stream_next_descriptor = 0;

// Search for a name in the symbol table, and return the index
int symtab_lookup (char const* name)
{
    int i;
    for(i = symtab_nextentry-1; i > -1; i--) {
        if(strcmp(symtab_stream + symtab[i][0], name) == 0) break;
    }
    return i;
}

//Adds in the symbol table the name of the variable and its type
int symtab_append (char const* name, int type)
{
    if(symtab_nextentry == MAX_SYMTAB_ENTRIES) return -2;
    if(symtab_lookup(name) > -1) return -3;

    strcpy(symtab_stream + symtab_stream_next_descriptor, name);
    /* store the stream position in the symtab array */
    symtab[symtab_nextentry][0] = symtab_stream_next_descriptor;
    /* preview next stream entry position */
    symtab_stream_next_descriptor += strlen(name) + 1;
    symtab[symtab_nextentry][1] = type;

    return symtab_nextentry++;
}
