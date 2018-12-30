#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>

#include "lashlib.h"


int main(int argc, char *argv[])
{
    /* create lua environment */
    lua_State *lua = luaL_newstate();
    if (lua == NULL) {
        fprintf(stderr, "Could not create Lua environment!\n");
        return 1;
    }
    luaL_openlibs(lua);
    lua_pushnil(lua);
    lua_setglobal(lua, "debug");
    lashopen_env(lua);

    if (argv[1] && luaL_dofile(lua, argv[1]))
        lua_error(lua);
        
    lua_close(lua);
    return 0;
}
