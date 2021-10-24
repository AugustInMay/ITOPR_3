#include <map>
#include "file_manager.h"
#include "order_permutation.h"
#include "branching.h"
#include "bounds.h"

int main() {
    std::string name;
    int size;
    std::cout<<"Enter name: ";
    std::cin>>name;
    std::cout<<"Enter size: ";
    std::cin>>size;

    file_manager fm(name + "_n" + std::to_string(size));
    order_task task(size);
    task.read_from_file(fm);
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

        std::vector<int> cache_lb;
        std::vector<int> cache_ub;

//        std::cout<<"\n------------------------------------\n";
//        std::cout<<"---FROM---"<<std::endl;
        for(auto it = V.begin(); it != V.end(); ++it){
            int it_lb = blb->count_lb(*it);
            cache_lb.push_back(it_lb);

            int it_ub = bub->count_ub(*it);
            cache_ub.push_back(it_ub);

//            it->show_permutation();
//            std::cout<<"lb: "<<it_lb<<" ub: "<<it_ub<<std::endl;
        }

        std::vector<int> indxs;
        std::set<int> discarded;

        for(int i=0; i<V.size(); i++){
            indxs.push_back(i);
            int it1_lb = cache_lb[i];

            for(int j=0; j<V.size(); j++){
                if(i != j){
                    int it2_ub = cache_ub[j];

                    if(it1_lb >= it2_ub && discarded.find(j) == discarded.end()){
                        indxs.pop_back();
                        discarded.emplace(i);
                        break;
                    }
                }
            }
        }

        std::vector<order_permutation> new_V;
        std::vector<int> new_cache_lb;
        std::vector<int> new_cache_ub;

        for(int i=0; i<indxs.size(); i++){
            int indx = indxs[i];

            new_V.emplace_back(V[indx]);
            new_cache_lb.push_back(cache_lb[indx]);
            new_cache_ub.push_back(cache_ub[indx]);
        }

        V = new_V;
        cache_lb = new_cache_lb;
        cache_ub = new_cache_ub;

//        std::cout<<"---TO---"<<std::endl;
//
//        for(int i=0; i<V.size(); i++){
//            V[i].show_permutation();
//            std::cout<<"lb: "<<cache_lb[i]<<" ub: "<<cache_ub[i]<<std::endl;
//        }

        if(V.size() == 1 && blb->count_lb(V[0]) == bub->count_ub(V[0])){
            if(V[0].get_gen_size() != task.get_n()){
                V[0] = bub->construct_ub_gen(V[0]);
            }
            break;
        }
    }

    V[0].show_permutation();

    return 0;
}
