#include<list>
#include<algorithm>
#include<iostream>
#include<iterator>

template<typename T>
std::list<T> sequential_quick_sort(std::list<T> input)
{
    if(input.empty())
    {
        return input;
    }

    std::list<T> result;
    result.splice(result.begin(), input, input.begin());

    auto divide_point = std::partition(input.begin(), input.end(), [&](T const & t) {return t <result.begin();});

    std::list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(), divide_point);

    auto new_lower(sequential_quick_sort(std::move(lower_part)));

    auto new_higher(sequential_quick_sort(std::move(input)));

    result.splice(result.end(), new_higher);
    result.splice(result.begin(), new_lower);
    return result;
}

int main(int argc, char const *argv[])
{
    std::list<int> li = {1,3,6,0,5,6};

    auto ans = sequential_quick_sort(li);

    for(auto &it : ans) {
        std::cout << it<<" ";
    }
    return 0;
}
