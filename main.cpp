
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "sources/OrgChart.hpp"
using namespace ariel;

int main() {
    OrgChart organization;
    organization.add_root("a1")
            .add_sub("a1", "a2")
            .add_sub("a2", "a3")
            .add_sub("a3", "a4")
            .add_sub("a1", "a6")
            .add_sub("a6", "a7");


    for (auto it=organization.begin_preorder(); it!=organization.end_preorder(); ++it) {
        cout << (*it) << " " ;
    }
    cout<<endl;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        cout << (*it) << " " ;
    }
    cout<<endl;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
    {
        cout << (*it) << " " ;
    }
    cout<<endl;
    for (auto element : organization)
    {
        cout << element << " " ;
    }

}
