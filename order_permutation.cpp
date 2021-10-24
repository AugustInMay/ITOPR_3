//
// Created by AugustInMay on 19/10/2021.
//

#include "order_permutation.h"

order_permutation::order_permutation(const order_permutation &t): task(t.task), gen(t.gen), weight(t.weight), time(t.time){}

order_permutation::order_permutation(const order_task &t):task(t), weight(0), time(0) {
    gen.reserve(task.get_n());
}

order_permutation::order_permutation(const order_task &t, const std::vector<int> &g):task(t), gen(g) {
    time = 0;
    weight = 0;

    if(gen.empty()){
        return;
    }

    time += task.get_t0(gen[0]);

    if(time > task.get_dest_time(gen[0])){
        weight++;
    }

    for(int i=0; i<gen.size()-1; i++){
        time += task.get_t(gen[i], gen[i+1]);

        if(time > task.get_dest_time(gen[i+1])){
            weight++;
        }
    }
}


int order_permutation::get_gen_size() const{
    return static_cast<int>(gen.size());
}

const order_task &order_permutation::get_task() const {
    return task;
}

int order_permutation::get_time() const {
    return time;
}

int order_permutation::get_weight() const {
    return weight;
}

int order_permutation::operator[](int x) const{
    return gen[x];
}

bool order_permutation::operator<(const order_permutation &rhs) const {
    return weight < rhs.weight;
}

void order_permutation::push_back(const int &el) {
    gen.push_back(el);

    int gen_size = gen.size();

    if(gen_size == 1){
        time += task.get_t0(gen[0]);

        if(time > task.get_dest_time(gen[0])){
            weight++;
        }
    }
    else{
        time += task.get_t(gen[gen_size-2], gen[gen_size-1]);

        if(time > task.get_dest_time(gen[gen_size-1])){
            weight++;
        }
    }
}

void order_permutation::pop_back() {
    int gen_size = gen.size();

    if(gen_size == 0){
        return;
    }
    else if(gen_size == 1){
        time = 0;
        weight = 0;
    }
    else{
        if(time > task.get_dest_time(gen[gen_size-1])){
            weight--;
        }
        time -= task.get_t(gen[gen_size-2], gen[gen_size-1]);
    }

    gen.pop_back();
}

void order_permutation::show_permutation() const{
    for(int i=0; i<gen.size(); i++){
        std::cout<<gen[i]+1<<" ";
    }
    std::cout << "-----weight: " << weight << " time: "<< time <<std::endl;
}

order_permutation &order_permutation::operator=(const order_permutation &p) {
    gen = p.gen;
    weight = p.weight;
    time = p.time;

    return *this;
}