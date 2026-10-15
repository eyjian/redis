/* This file is used by redis-cli in place of server.h when including commands.c
 * It contains alternative structs which omit the parts of the commands table
 * that are not suitable for redis-cli, e.g. the command proc. */

#ifndef __REDIS_CLI_COMMANDS_H
#define __REDIS_CLI_COMMANDS_H

#include <stddef.h>
#include <stdint.h>
#include "commands.h"

/* Command flags needed to compile commands.def outside of the server (the
 * values must be kept identical to the definitions in server.h). They are
 * guarded so that including this header together with server.h doesn't
 * cause redefinitions. */
#ifndef CMD_WRITE
#define CMD_WRITE (1ULL<<0)
#define CMD_READONLY (1ULL<<1)
#define CMD_DENYOOM (1ULL<<2)
#define CMD_MODULE (1ULL<<3)           /* Command exported by module. */
#define CMD_ADMIN (1ULL<<4)
#define CMD_PUBSUB (1ULL<<5)
#define CMD_NOSCRIPT (1ULL<<6)
#define CMD_BLOCKING (1ULL<<8)       /* Has potential to block. */
#define CMD_LOADING (1ULL<<9)
#define CMD_STALE (1ULL<<10)
#define CMD_SKIP_MONITOR (1ULL<<11)
#define CMD_SKIP_SLOWLOG (1ULL<<12)
#define CMD_ASKING (1ULL<<13)
#define CMD_FAST (1ULL<<14)
#define CMD_NO_AUTH (1ULL<<15)
#define CMD_MAY_REPLICATE (1ULL<<16)
#define CMD_SENTINEL (1ULL<<17)
#define CMD_ONLY_SENTINEL (1ULL<<18)
#define CMD_NO_MANDATORY_KEYS (1ULL<<19)
#define CMD_PROTECTED (1ULL<<20)
#define CMD_MODULE_GETKEYS (1ULL<<21)  /* Use the modules getkeys interface. */
#define CMD_MODULE_NO_CLUSTER (1ULL<<22) /* Deny on Redis Cluster. */
#define CMD_NO_ASYNC_LOADING (1ULL<<23)
#define CMD_NO_MULTI (1ULL<<24)
#define CMD_MOVABLE_KEYS (1ULL<<25) /* The legacy range spec doesn't cover all keys.
                                     * Populated by populateCommandLegacyRangeSpec. */
#define CMD_ALLOW_BUSY ((1ULL<<26))
#define CMD_MODULE_GETCHANNELS (1ULL<<27) /* Use the modules getchannels interface. */
#define CMD_TOUCHES_ARBITRARY_KEYS (1ULL<<28)
#define CMD_INTERNAL (1ULL<<29) /* Internal command. */
#define CMD_SCRIPT_RUNNER (1ULL<<30) /* Command that executes scripts or functions (EVAL, FCALL, etc.). */
#endif

/* Syntax specifications for a command argument. */
typedef struct cliCommandArg {
    char *name;
    redisCommandArgType type;
    char *token;
    char *since;
    int flags;
    int numsubargs;
    struct cliCommandArg *subargs;
    const char *display_text;

    /*
     * For use at runtime.
     * Fields used to keep track of input word matches for command-line hinting.
     */
    int matched;  /* How many input words have been matched by this argument? */
    int matched_token;  /* Has the token been matched? */
    int matched_name;  /* Has the name been matched? */
    int matched_all;  /* Has the whole argument been consumed (no hint needed)? */
} cliCommandArg;

/* Command documentation info used for help output */
struct commandDocs {
    char *name;
    char *summary;
    char *group;
    char *since;
    uint64_t flags; /* Command flags, see CMD_* defines above. */
    int numargs;
    cliCommandArg *args; /* An array of the command arguments. */
    struct commandDocs *subcommands;
    char *params; /* A string describing the syntax of the command arguments. */
};

extern struct commandDocs redisCommandTable[];

#endif
