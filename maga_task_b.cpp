#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <set>

std::vector<
    std::pair<
        size_t,
        size_t
    >
> people;

std::vector<
    std::pair<
        size_t,
        size_t
    >
> events;

int main(){
    size_t n;
    std::cin>>n;
    for (size_t i = 0; i < n; ++i){
        size_t d0,m0,y0, d3, m3, y3;
        std::cin>>d0>>m0>>y0>>d3>>m3>>y3;
        size_t p0 = d0 + m0 * 100 + y0 * 10000;
        size_t p3 = d3 + m3 * 100 + y3 * 10000;
        size_t p1 = p0 + 18 * 10000;
        size_t p2 = p0 + 80 * 10000;
        if (p1 >= p3){
            continue;
        }
        p2 = std::min(p2, p3);
        assert(p1 < p2);
        assert(p2 <= p3);
        people.push_back({
            p1,
            p2,
        });
    }
    for (size_t i = 0; i < people.size(); ++i){
        events.push_back({
            people[i].first, i
        });
        events.push_back({
            people[i].second, i
        });
    }
    std::sort(events.begin(), events.end());
    size_t alive = 0;
    size_t max_alive = 0;
    std::set<size_t> unique_events;
    for (auto e:events){
        unique_events.insert(e.first);
    }
    for (size_t e: unique_events){
        auto eb = std::lower_bound(events.begin(), events.end(), e, [&](auto& left, auto& right){
            return left.first < right;
        });
        auto ee = std::upper_bound(events.begin(), events.end(), e, [&](auto& left, auto& right){
            return left < right.first;
        });
        for (auto ei = eb; ei != ee; ++ei){
            if (people[ei->second].first == ei->first){
                alive += 1;
            }
            if (people[ei->second].second == ei->first){
                alive -= 1;
            }
        }
        max_alive = std::max(alive, max_alive);
    }
    std::cout << max_alive << std::endl;
}
