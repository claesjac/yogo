#ifndef __EMITTER_H__
#define __EMITTER_H__

#include <unistd.h>
#include <stdint.h>

struct YogocFunction {
    const char *name;
};

typedef struct YogocFunction YogocFunction;

struct YogocPackage {
    const char *name;
    uint16_t    next_autogen_cnt;
};

typedef struct YogocPackage YogocPackage;

struct YogocEmitter {
    YogocPackage    **pkgs;
    YogocPackage    *current_pkg;
    uint32_t        pkg_count;
};

typedef struct YogocEmitter YogocEmitter;

YogocEmitter *yogoc_create_emitter();
void yogoc_set_package(YogocEmitter *, const char *pkgname);
void yogoc_set_sub(YogocEmitter *, const char *subname);

#endif
