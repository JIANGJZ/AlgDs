#ifndef AlgDs_stack_queens_h
#define AlgDs_stack_queens_h
#include "v_stack.h"

#include <iostream>

#define QUEEN_MAX 8

typedef struct Queen {
    int x;
    int y;
    bool operator == (Queen const& q) {
        return (x == q.x) || (y == q.y) || (x + y == q.x + q.y) || (x - y == q.x - q.y);
    }
    
    bool operator != (Queen const& q) {
        return !(*this == q);
    }
}Queen;

bool collipe(int *solution, int k) {
    for (int i = 0; i < k; i++) {
        if (solution[i] == solution[k]) {
            return true;
        }
        
        if (solution[i] - solution[k] == i - k) {
            return true;
        }
        
        if (solution[i] - solution[k] == k -i) {
            return true;
        }
    }
    
    return false;
}


bool collipe(VStack<Queen> &solution, Queen q) {
    return true;
}

void displaySolution(int *solution, int nQueen) {
    for (int i = 0; i < nQueen; i++) {
        for (int j = 0; j < nQueen; j++) {
            if (j == solution[i]) {
                std::cout << "$" << " ";
            } else {
                std::cout << "[]" << " ";
            }
        }
        
        std::cout << endl;
    }
}


void displaySolution(VStack<Queen> solution) {
    
}

void placeQueen_recursive(int nQueen, int i) {
    static int solution[QUEEN_MAX];
    if (nQueen <= i) {
        displaySolution(solution, nQueen);
    } else {
        for (int j = 0; j < nQueen; j++) {
            solution[i] = j;
            if (!collipe(solution, i)) {
                placeQueen_recursive(nQueen, i+1);
            }
        }
    }
}

void placeQueen_stack(int N) {
    VStack<Queen> solution;
    Queen q;
    q.x = 0;
    q.y = 0;
    do{
        if (N <= solution.size() || N <= q.x) {
            q = solution.pop();
            q.x++;
        } else {
            while ((q.x < N) && collipe(solution, q)) {
                q.x++;
            }
            
            if (N > q.x) {
                solution.push(q);
                if (N <= solution.size()) {
                    displaySolution(solution);
                    q.y++;
                    q.x = 0;
                }
            }
        }
    }while(q.y < N || q.x > 0);
}



#endif
