#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include "Game.h"
#include "GameTree.h"

#define GAME_PATH    "./laserchess/laserchess.so"
#define TREE_PATH    "./trees/abparallel.so"

bool linkGame(Game* (*&createGame)(void), void (*&destroyGame)(Game*))
{
    void* handle = dlopen(GAME_PATH, RTLD_LAZY);
    const char* err;
    if (!handle) {
        fputs (dlerror(), stderr);
        return false;
    }
    Game* (*__gametree_create_game)(void);
    void (*__gametree_destroy_game)(Game*);

    __gametree_create_game = (Game* (*)(void)) dlsym(handle,
            "__gametree_create_game");
    if ((err = dlerror()) != NULL)
    {
        fprintf(stderr, "Error locating symbol __gametree_create_game\
                in %s\n", err);
        return false;
    }
    createGame = __gametree_create_game;

    __gametree_destroy_game = (void (*)(Game*)) dlsym(handle,
            "__gametree_destroy_game");
    if ((err = dlerror()) != NULL)
    {
        fprintf(stderr, "Error locating symbol __gametree_destroy_game\
                in %s\n", err);
        return false;
    }
    destroyGame = __gametree_destroy_game;
    return true;
}

bool linkTree(GameTree* (*&createTree)(Game*), void (*&destroyTree)(GameTree*))
{
    void* handle = dlopen(TREE_PATH, RTLD_LAZY);
    const char* err;
    if (!handle) {
        fputs (dlerror(), stderr);
        return false;
    }
    GameTree* (*__gametree_create_tree)(Game*);
    void (*__gametree_destroy_tree)(GameTree*);

    __gametree_create_tree = (GameTree* (*)(Game*)) dlsym(handle,
            "__gametree_create_tree");
    if ((err = dlerror()) != NULL)
    {
        fprintf(stderr, "Error locating symbol __gametree_create_tree\
                in %s\n", err);
        return false;
    }
    createTree = __gametree_create_tree;

    __gametree_destroy_tree = (void (*)(GameTree*)) dlsym(handle,
            "__gametree_destroy_tree");
    if ((err = dlerror()) != NULL)
    {
        fprintf(stderr, "Error locating symbol __gametree_destroy_tree\
                in %s\n", err);
        return false;
    }
    destroyTree = __gametree_destroy_tree;
    return true;
}


int main()
{
    Game* (*createGame)(void);
    void (*destroyGame)(Game*);
    assert(linkGame(createGame, destroyGame));

    GameTree* (*createTree)(Game*);
    void (*destroyTree)(GameTree*);
    assert(linkTree(createTree, destroyTree));

    GameBoard *board, *new_board;
    GameUser* usr ;
    Game* game = createGame();
    game->init(board);
    game->initUser(usr); 
    board->display();
    GameTree* gtree = createTree(game);
    board->setTurn(WHITE);

    for (uint32_t i=0; i<20; i++) {
    //    GameMove* m = usr->getUserMove(board);
        GameMove* m = gtree->getNextMove(board, 1);
        game->applyMove(board, new_board, m);
        new_board->display();
        delete board;

        m = gtree->getNextMove(new_board, 2);
        game->applyMove(new_board, board, m);
        board->display();
        delete new_board;
    }
    destroyGame(game);
    delete gtree;
}
