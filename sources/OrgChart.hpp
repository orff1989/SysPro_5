#include "string"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "vector"
#include <iterator>
#define Null "null"

//
// Created by orff1 on 5/15/2022.
//

using namespace std;

static std::string nuLL = "null";

namespace ariel{

    class node{

    private:
        string _name;
        node* _dad;
        vector<node*> _children;

    public:
        node(string& name, node* dad): _name(name), _dad(dad), _children(vector<node*>()){}

        node *getDad() const {
            return _dad;
        }

        void setDad(node *dad) {
            _dad = dad;
        }

        const vector<node *> &getChildren() const {
            return _children;
        }

        void setChildren(const vector<node *> &children) {
            _children = children;
        }

        void addChild(node& n){
            _children.push_back(&n);
        }

    };

    class OrgChart{
        node* root;

    public:
        class iterator : public std::iterator<std::input_iterator_tag, OrgChart>{
            OrgChart* OrgPtr;

        public:

            iterator(OrgChart* org= nullptr) : OrgPtr(org) {}

            friend ostream& operator<< (ostream& os, const iterator& m);

            iterator& operator++();

            iterator operator++(int);

            OrgChart& operator*();

            bool operator==(const iterator& rhs);

            bool operator!=(const iterator& rhs);

            size_t size();

        };

        OrgChart() {root= nullptr;}

        OrgChart &add_root(const string& str);

        OrgChart &add_sub(const string& str1, const string& str2);

        iterator *begin_level_order();

        iterator *end_level_order();

        iterator *begin_reverse_order();

        iterator *end_reverse_order();

        iterator *begin_preorder();

        iterator *end_preorder();

        friend ostream& operator<< (ostream& os, const OrgChart& m);

        iterator begin();

        iterator end();

        node* find(const string &str);
    };



}


