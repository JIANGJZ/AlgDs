#ifndef AlgDs_stack_maze_h
#define AlgDs_stack_maze_h

#include "v_stack.h"

typedef enum {
    AVAILABLE,
    ROUTE,
    BACKTRACKED,
    WALL
}Status;

typedef enum {
    UNKNOWN,
    EAST,
    SOUTH,
    WEST,
    NORTH,
    NO_WAY
}Direction;

struct Cell{
    int x, y;
    Status status;
    Direction incoming;
    Direction outgoing;
};

const int ROW = 10;
Cell matrix[ROW][ROW];   /// 对格子中的内容进行初始化，主要是对状态进行赋值

Direction nextDirection(Direction dir) {
    return Direction(dir + 1);
}

/// 要对边界条件进行判断
Cell* neighbor(Cell* cell) {
    switch (cell->outgoing) {
        case EAST:
            return cell + ROW;
        case WEST:
            return cell - ROW;
        case SOUTH:
            return cell + 1;
        case NORTH:
            return cell - 1;
        default:
            exit(-1);
            break;
    }
}

/// 要判断是否出界
Cell* advance(Cell* cell) {
    Cell* next;
    switch (cell->outgoing) {
        case EAST:
            next = cell + ROW;
            next->incoming = WEST;
            break;
        case WEST:
            next = cell - ROW;
            next->incoming = EAST;
            break;
        case SOUTH:
            next = cell + 1;
            next->incoming = NORTH;
            break;
        case NORTH:
            next = cell - 1;
            next->incoming = SOUTH;
            break;
        default:
            exit(-1);
            break;
    }
    return next;
}

//找相邻节点, 保存每一个可走的状态， 判断是否到达目的地
bool findWay(Cell *s, Cell *t) {
    VStack<Cell*> path;
    s->incoming = UNKNOWN;
    s->status = ROUTE;
    path.push(s);
    do {
        Cell* c = path.top();
        if (c == t) {
            return true;
        }
        while (NO_WAY > (c->outgoing = nextDirection(c->outgoing))) {
            if(AVAILABLE == neighbor(c)->status) {
                break;
            }
        }
        
        if (NO_WAY <= c->outgoing) {
            c->status = BACKTRACKED;
            c = path.pop();
        } else {
            path.push(c = advance(c));
            c->outgoing = UNKNOWN;
            c->status = ROUTE;
        }
        
    }while(!(path.empty()));
    
    return false;
}

#endif
