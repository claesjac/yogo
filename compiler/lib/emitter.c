#include "emitter.h"
#include "parser.h"

#include <string.h>
#include <stdio.h>

static char *gen_subname(YogocEmitter *emit) {
    char buff[24];
    
    sprintf(buff, "<sub_%d>", emit->current_pkg->next_autogen_cnt);
    emit->current_pkg->next_autogen_cnt++;
    
    return strdup(buff);
}

YogocEmitter *yogoc_create_emitter(void) {
    YogocEmitter *emit = calloc(1, sizeof(YogocEmitter));
    
    emit->pkg_count = 1;
    emit->pkgs = malloc(sizeof(YogocPackage *) * emit->pkg_count);
    emit->pkgs[0] = malloc(sizeof(YogocPackage));
    emit->current_pkg  = emit->pkgs[0];
    emit->current_pkg->name = "";
    emit->current_pkg->next_autogen_cnt = 1;
    
    return emit;
}

void yogoc_set_package(YogocEmitter *emit, const char *name) {
    int i;
    
    /* If current package is the same then ignore */
    if (strcmp(emit->current_pkg->name, name) == 0) {
        return;
    }
    
    /* Scan if there's an already existing package in file */
FIND_PACKAGE:
    for (i = 0; i < emit->pkg_count; i++) {
        if (strcmp(emit->pkgs[i]->name, name) == 0) {
            emit->current_pkg = emit->pkgs[i];
            return;
        }
    }
    
    i = emit->pkg_count++;
    emit->pkgs = realloc(emit->pkgs, sizeof(YogocPackage *) * emit->pkg_count);
    emit->pkgs[i] = malloc(sizeof(YogocPackage));
    emit->current_pkg  = emit->pkgs[i];
    emit->current_pkg->name = strdup(name);
    emit->current_pkg->next_autogen_cnt = 1;
}

void yogoc_set_sub(YogocEmitter *emit, const char *name) {
    if (name == NULL) {
        /* No name, must autogenerate one */
        name = gen_subname(emit);
    }
    
    fprintf(stderr, "Current function is: %s\n", name);
}