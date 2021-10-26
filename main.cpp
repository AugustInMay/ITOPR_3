#include <map>
#include "file_manager.h"
#include "order_permutation.h"
#include "branching.h"
#include "bounds.h"

std::pair<order_permutation, int> bb_alg(const order_task& task, abstract_lower_bound* alb, abstract_upper_bound* aub, abstract_branching *abr, std::vector<int>& cache_lb, std::vector<int>& cache_ub){
    std::vector<order_permutation> V;
    V.emplace_back(task);

    int num_processed = 0;

    for(auto it = V.begin(); it != V.end(); ++it){
        int it_lb = alb->count_lb(*it);
        cache_lb.push_back(it_lb);

        int it_ub = aub->count_ub(*it);
        cache_ub.push_back(it_ub);
    }

    unsigned long long min_ub_iter = 0;
    int min_ub = INT32_MAX;

    while (true){
        int to_minus = 0;
        int vertex = abr->branch(V);

        if(vertex < min_ub_iter){
            min_ub_iter--;
        }

//        std::cout<<"-------------------------------------------"<<std::endl;
//
//        std::cout<<"!!!chose vertex: ";
//        V[vertex].show_permutation();
//        std::cout<<"lb: "<<cache_lb[vertex]<<" ub: "<<cache_ub[vertex]<<std::endl;

        std::vector<order_permutation> vertex_neighbourhood = neighbourhood(V[vertex]);

        num_processed += vertex_neighbourhood.size();

        V.erase(V.begin() + vertex);
        cache_lb.erase(cache_lb.begin() + vertex);
        cache_ub.erase(cache_ub.begin() + vertex);


//        std::cout<<"!!!without it!!!"<<std::endl;
//        for(int i=0; i<V.size(); i++){
//            V[i].show_permutation();
//            std::cout<<"lb: "<<cache_lb[i]<<" ub: "<<cache_ub[i]<<std::endl;
//        }
//
//        std::cout<<"!!!its neighbours!!"<<std::endl;

        for(int i=0 ; i<vertex_neighbourhood.size(); i++){
            int i_lb = alb->count_lb(vertex_neighbourhood[i]);
            cache_lb.push_back(i_lb);

            int i_ub = aub->count_ub(vertex_neighbourhood[i]);
            cache_ub.push_back(i_ub);

            if(i_ub <= min_ub){
                min_ub = i_ub;
                min_ub_iter = static_cast<int>(V.size()) + i;
            }
//
//            vertex_neighbourhood[i].show_permutation();
//            std::cout<<"lb: "<<i_lb<<" ub: "<<i_ub<<std::endl;
        }

        V.insert(V.end(), std::make_move_iterator(vertex_neighbourhood.begin()), std::make_move_iterator(vertex_neighbourhood.end()));

//        std::cout<<"min ub:";
//        V[min_ub_iter].show_permutation();

        std::set<int> discarded;


        for(int i=0; i<V.size(); i++){
            int it1_lb = cache_lb[i];

            if(it1_lb >= min_ub && i != min_ub_iter){
                discarded.emplace(i);
                if(i < min_ub_iter){
                    to_minus++;
                }
            }
        }

        min_ub_iter -= to_minus;

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

        if(V.size() == 1 && alb->count_lb(V[0]) == aub->count_ub(V[0])){
            if(V[0].get_gen_size() != task.get_n()){
                V[0] = aub->construct_ub_gen(V[0]);
            }
            break;
        }
    }

    return std::make_pair(V[0], num_processed);
}

int factorial(int i)
{
    if (i==0) return 1;
    else return i*factorial(i-1);
}

int main() {
    std::ofstream table;
    table.open("table.csv");
    std::vector<std::string> names;
    names.reserve(10);
    std::vector<int> sizes={3,3,10,10,10,15,15,50,50,50};
    int fac3 = factorial(3), fac10 = factorial(10), fac15 = factorial(15), fac50 = factorial(50);
    std::vector<int> n_d={fac3, fac3, fac10, fac10, fac10, fac15, fac15, fac50, fac50, fac50};
    for(int i=0; i<9; i++){
        names.emplace_back("task_2_0"+std::to_string(i+1)+"_n"+std::to_string(sizes[i]));
    }
    names.emplace_back("task_2_10_n50");

    table<<"Size"<<";"<<"Configuration"<<";"<<"Own solution"<<";"<<"Cost"<<";"<<"Efficiency"<<std::endl;

    for(int i=0; i<9; i++){
        int cur_size = sizes[i];

        file_manager fm(names[i]);
        order_task task(cur_size);
        task.read_from_file(fm);

        bool do_branch_sort[2] = {false, true};
        int ls_cap[4] = {-1, cur_size/4, cur_size/3, cur_size/2};

        for(int do_sort=0; do_sort<2; do_sort++){
            for(int ind_cap=0; ind_cap<4; ind_cap++){
                std::vector<int> cache_lb;
                std::vector<int> cache_ub;
                abstract_lower_bound* blb = new exclusive_lower_bound(task);
                abstract_upper_bound* bub = new ls_upper_bound(task, ls_cap[ind_cap]);
                abstract_branching* branching = new hybrid_branching(&cache_lb, &cache_ub, do_branch_sort[do_sort]);

                std::pair<order_permutation, int> solution = bb_alg(task, blb, bub, branching, cache_lb, cache_ub);
                table<<cur_size<<";"<<"SORT-"+std::to_string(do_branch_sort[do_sort])+"LS_CAP"+std::to_string(ls_cap[ind_cap])<<";"<<solution.first.get_str_gen()<<";"<<solution.first.get_weight()<<";"<<solution.second<<std::endl;
            }
        }
    }

    return 0;
}
