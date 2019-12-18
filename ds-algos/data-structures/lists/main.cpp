#include <iostream>
//#include "forward_list.h"
#include "list.h"

int main(int argc, char **argv){

    //Forward_List<int> f_list;
    //Forward_List<int> f_list2;
    // for (int i = 9; i >=1; --i) f_list2.push_front(i);
    
    // f_list.push_front(0);
    // f_list.push_front(3);
    // f_list.push_front(1);
    // f_list.push_front(2);
    // f_list.push_front(1);
    // f_list.push_front(0);
    // f_list.push_front(3);
    // f_list.push_front(2);
    
    // std::cout << "The forward_list holds: " << f_list << "\n";
    // std::cout << "The forward_list2 holds: " << f_list2 << "\n";
    // //f_list.resize(4, 1);
    // std::cout << "After resize up to 5: " << f_list << '\n';
    // //f_list.resize(2);
    // std::cout << "After resize down to 2: " << f_list << '\n';
    // //f_list.remove(2);
    // std::cout << "After remove : " << f_list << '\n';
    // //f_list.reverse();
    // std::cout << "After reverse: " << f_list << '\n';
    // //f_list.sort();
    // std::cout << "After sort: " << f_list << '\n';
    // //f_list.splice_after(f_list.begin(), f_list2);
    // std::cout << "After splice: " << f_list << '\n';
    // f_list.unique();
    // std::cout << "After unique(): " << f_list << '\n';

    List<int> list1;
    List<int> list2;
    for(int i = 5; i <= 15; ++i) list2.push_back(i);
    
    // list1.push_back(1);
    // list1.push_back(2);
    // list1.push_back(2);
    // list1.push_back(3);
    // list1.push_back(3);
    // list1.push_back(4);
    // list1.push_back(1);
    // list1.push_back(1);
    // list1.push_back(2);
     list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(4);
    list1.push_back(5);
    
    //list1.push_front(100);
     std::cout << "The list1 holds: " << list1 << "\n";
     std::cout << "The list2 holds: " << list2 << "\n";
    // list1.erase(list1.begin()+4);
    // list1.insert(list1.begin()+4,5);
    // std::cout << "The list after insert: " << list1 << "\n";
    // list1.erase(list1.begin()+4, list1.begin()+7);
    // std::cout << "The list after erase: " << list1 << "\n";
    // list1.pop_back();
    // std::cout << "The list after pop_back: " << list1 << "\n";
    // list1.pop_front();
    // std::cout << "The list after pop_back: " << list1 << "\n";
    // list1.sort();
    // std::cout << "The list after sort: " << list1 << "\n";
    // list1.reverse();

    //list1.unique();
    //std::cout << "The list unique: " << list1 << "\n";

    //list1.splice(list1.begin()+2, list2, list2.begin() + 3, list2.begin()+6);
    //std::cout << "The list1 splice: " << list1 << "\n";

    list1.sort();
    list2.sort();
    //std::cout << "The list1 sort: " << list1 << "\n";
    //std::cout << "The list2 sort: " << list2 << "\n";

    list1.merge(list2);
    std::cout << "The list1 merge: " << list1 << "\n";
    std::cout << "The list2 merge: " << list2 << "\n";
    
    



    return 0;
}