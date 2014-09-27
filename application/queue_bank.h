#ifndef AlgDs_queue_bank_h
#define AlgDs_queue_bank_h
#include "l_queue.h"

#include <iostream>
#include <unistd.h>
using namespace std;

int delay = 3;

typedef struct Customer {
    int win_seq;
    int time;
}Customer;

void print_customer(Customer& c) {
    std::cout << c.time << endl;
}

int best_window(LQueue<Customer> windows[], int win_num) {
    int min_size = windows[0].size();
    int seq = 0;
    for (int i = 0; i < win_num; i++) {
        if (windows[i].size() < min_size) {
            min_size = windows[i].size();
            seq = i;
        }
    }
    return seq;
}

void display_info(LQueue<Customer> windows[], int win_num, int now) {
    cout << "=============== Time ===============  " << now << endl;
    for (int i = 0; i < win_num; i++) {
        std::cout << "window " << char('A' + i) << std::endl;
        windows[i].traverse(print_customer);
    }

}

void simulate(int win_num, int serv_time) {
    LQueue<Customer> *windows = new  LQueue<Customer> [win_num];
    for (int i = 0; i < serv_time; i++) {
        Customer c;
        c.time = 1 + rand() % 10;
        c.win_seq = best_window(windows, win_num);
        windows[c.win_seq].enqueue(c);
        for (int j = 0; j < win_num; j++) {
            if (!windows[j].empty()) {
                if (--(windows[j].front().time) < 0) {
                    windows[j].dequeue();
                }
            }
            display_info(windows, win_num, i);
            sleep(delay);
        }
    }
    delete []windows;
}

#endif
