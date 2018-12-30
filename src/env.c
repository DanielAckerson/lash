#define _POSIX_C_SOURCE 200112L
#include <lauxlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lashlib.h"


static int l_import(lua_State *L)
{
    char const *env = luaL_checkstring(L, 1);
    char const *val = getenv(env);
    if (val == NULL) {
        lua_pushnil(L);
    } else {
        char *token, *val_temp = (char *) calloc(strlen(val) + 1, sizeof(char));
        strcpy(val_temp, val);
        token = strtok(val_temp, ":");
        lua_newtable(L);
        for (int i = 1; token != NULL; i++) {
            lua_pushstring(L, token);
            lua_seti(L, -2, i);
            token = strtok(NULL, ":");
        }
        free(val_temp);
    }
    return 1;
}


static int l_export(lua_State *L)
{
    int i;
    char const *val, *env = luaL_checkstring(L, 1);
    luaL_checktype(L, 2, LUA_TTABLE);
    for (i = 1; lua_geti(L, 2, i) != LUA_TNIL; i++)
        lua_pushstring(L, ":");
    lua_pop(L, 1);
    lua_concat(L, i * 2 - 3);
    val = lua_tostring(L, -1);
    lua_pop(L, 1);
    setenv(env, val, 1);
    return 0;
}


static luaL_Reg const env_funcs[] = {
    {"import", l_import},
    {"export", l_export},
    {NULL, NULL}
};


void lashopen_env(lua_State *L)
{
    lua_pushglobaltable(L);
    luaL_setfuncs(L, env_funcs, 0);
    lua_pop(L, 1);
}
