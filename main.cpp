#include <map>
#include "file_manager.h"
#include "order_permutation.h"
#include "branching.h"
#include "bounds.h"

int main() {
    file_manager fm("task_2_07_n15");
    order_task task(15);
    task.read_from_file(fm);
    order_permutation perm(task);
    abstract_lower_bound* blb = new base_lower_bound(task);
    abstract_upper_bound* bub = new base_upper_bound(task);
    abstract_branching* branching = new breadth_branching();

    std::vector<order_permutation> V;
    V.emplace_back(task);

    while (true){
        std::vector<order_permutation> to_change;

        for(order_permutation &el: V){
            std::vector<order_permutation> tmp = branching->branch(el);
            to_change.insert(to_change.end(), tmp.begin(), tmp.end());
        }

        V = to_change;

        std::map<std::vector<order_permutation>::iterator, int> cache_lb;
        std::map<std::vector<order_permutation>::iterator, int> cache_ub;

        std::cout<<"\n------------------------------------\n";
        std::cout<<"---FROM---"<<std::endl;
        for(auto it = V.begin(); it != V.end(); ++it){
            int it_lb = blb->count_lb(*it);
            cache_lb.emplace(it, it_lb);

            int it_ub = bub->count_ub(*it);
            cache_ub.emplace(it, it_ub);

            it->show_permutation();
            std::cout<<"lb: "<<it_lb<<" ub: "<<it_ub<<std::endl;
        }

        for(auto it1 = V.begin(); it1 != V.end();){
            bool erased = false;
            int it1_lb = cache_lb[it1];

            for(auto it2 = V.begin(); it2 != V.end(); ++it2){
                if(it1 != it2){
                    int it2_ub = cache_ub[it2];

                    if(it1_lb >= it2_ub){
                        it1 = V.erase(it1);
                        erased = true;
                        break;
                    }
                }
            }

            if(!erased){
                ++it1;
            }
        }

        std::cout<<"---TO---"<<std::endl;

        for(auto it = V.begin(); it != V.end(); ++it){
            it->show_permutation();
            std::cout<<"lb: "<<cache_lb[it]<<" ub: "<<cache_ub[it]<<std::endl;
        }

        if(V.size() == 1 && blb->count_lb(V[0]) == bub->count_ub(V[0])){
            if(V[0].get_gen_size() != task.get_n()){
                V[0] = bub->construct_ub_gen(V[0]);
            }
            break;
        }
    }

    return 0;
}
