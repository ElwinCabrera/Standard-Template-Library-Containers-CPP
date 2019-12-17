#include <iostream>
#include "forward_list.h"

int main(int argc, char **argv){

    Forward_List<int> f_list;
    //for (int i = 3; i >=1; --i) f_list.push_front(i);
    f_list.push_front(0);
    f_list.push_front(3);
    f_list.push_front(1);
    f_list.push_front(2);
    f_list.push_front(1);
    f_list.push_front(0);
    f_list.push_front(3);
    f_list.push_front(2);
    std::cout << "The forward_list holds: " << f_list << "\n";
    //f_list.resize(4, 1);
    std::cout << "After resize up to 5: " << f_list << '\n';
    //f_list.resize(2);
    std::cout << "After resize down to 2: " << f_list << '\n';
    f_list.remove(2);
    std::cout << "After remove : " << f_list << '\n';
    f_list.reverse();
    std::cout << "After reverse: " << f_list << '\n';
    return 0;
}