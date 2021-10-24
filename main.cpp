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

    std::vector<int> cache_lb;
    std::vector<int> cache_ub;

    for(auto it = V.begin(); it != V.end(); ++it){
        int it_lb = blb->count_lb(*it);
        cache_lb.push_back(it_lb);

        int it_ub = bub->count_ub(*it);
        cache_ub.push_back(it_ub);
    }


    while (true){
        int vertex = branching->branch(V);

//        std::cout<<"!!!chose vertex: ";
//        V[vertex].show_permutation();

        std::vector<order_permutation> vertex_neighbourhood = neighbourhood(V[vertex]);

        V.erase(V.begin() + vertex);
        cache_lb.erase(cache_lb.begin() + vertex);
        cache_ub.erase(cache_ub.begin() + vertex);


//        std::cout<<"!!!without it!!!"<<std::endl;
//        for(int i=0; i<V.size(); i++){
//            V[i].show_permutation();
//            std::cout<<"lb: "<<cache_lb[i]<<" ub: "<<cache_ub[i]<<std::endl;
//        }

        for(auto it = vertex_neighbourhood.begin(); it != vertex_neighbourhood.end(); ++it){
            V.emplace_back(*it);

            int it_lb = blb->count_lb(*it);
            cache_lb.push_back(it_lb);

            int it_ub = bub->count_ub(*it);
            cache_ub.push_back(it_ub);
        }

//        std::cout<<"!!!with its' neighbours!!!"<<std::endl;
//        for(int i=0; i<V.size(); i++){
//            V[i].show_permutation();
//            std::cout<<"lb: "<<cache_lb[i]<<" ub: "<<cache_ub[i]<<std::endl;
//        }

        std::set<int> discarded;

        for(int i=0; i<V.size(); i++){
            int it1_lb = cache_lb[i];

            for(int j=0; j<V.size(); j++){
                if(i != j){
                    int it2_ub = cache_ub[j];

                    if(it1_lb >= it2_ub && discarded.find(j) == discarded.end()){
                        discarded.emplace(i);
                        break;
                    }
                }
            }
        }

        for(auto it = discarded.rbegin(); it != discarded.rend(); ++it){
            V.erase(V.begin() + *it);
            cache_lb.erase(cache_lb.begin() + *it);
            cache_ub.erase(cache_ub.begin() + *it);
        }

//        std::cout<<"!!!after calculation!!!"<<std::endl;
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
