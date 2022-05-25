#pragma once

#include "string"
#include <stdexcept>
#include <iostream>
#include "vector"

using namespace std;

namespace ariel {


    class OrgChart {
    public:

        OrgChart(){
            root= nullptr;
        }

        ~OrgChart(){
            vector<Node*> v;
            if (root!= nullptr) {
                for (auto it = this->begin_preorder(); it != this->end_preorder(); ++it) {
                    v.push_back(it.getOrgPtr());
                }
                for (size_t i = 0; i < v.size(); i++) {
                    delete v.at(i);
                }
            }
        }
        OrgChart(OrgChart& o)=default;
        OrgChart(OrgChart&& o)=default;
        OrgChart& operator =(const OrgChart& o)=default;
        OrgChart & operator =(OrgChart&&)=default;

    private:

        struct Node {
            string name;
            Node *dad;
            Node *lChild;
            Node *right;
            Node *left;

            Node(const string &v, Node *d = nullptr, Node *lch = nullptr, Node *r = nullptr, Node *l = nullptr)
                    : name(v), lChild(lch), right(r), left(l), dad(d) {
            }

            Node* getNextLCousing();

            Node* getNextSonOfRCousing() const;

            size_t hight() const;

            bool isLeftFrom(Node* n);

            Node *commadAnccestor(Node *pNode);

            bool isAnccesor(Node *pNode);

            bool lefBroOf(Node *pNode);
        };

        Node *root;

    public:

        class iterator {
        private:
            Node *orgPtr;

        public:

            iterator(Node *ptr = nullptr)
                    : orgPtr(ptr) {
            }

            Node *getOrgPtr() const;

            string &operator*() const;

            static Node *leftBro(Node *pNode);

            bool hasNext();

            bool hasRCousing();

            bool hasLNephew();

            bool getNextCousing();

            bool getNextNephew();

            iterator operator++();

            iterator operator++(int);

            bool operator==(const iterator &rhs) const;

            bool operator!=(const iterator &rhs) const;

            friend ostream &operator<<(ostream &os, const iterator &m);

            string* operator->() const;

            bool sonOfLCousing();

            bool hasSonOfCousing();

            bool sonOfDadRCousing();

            bool hassonOfDadRCousing();
        };

        class reverse_iterator {
        private:
            Node *orgPtr;

        public:

            reverse_iterator(Node *ptr = nullptr)
            : orgPtr(ptr) {
            }

            Node *getOrgPtr();

            string &operator*() const;

            Node *leftBro(Node *pNode);

            bool hasNext();

            bool hasRCousing();

            bool getNextRCousing();

            reverse_iterator operator++();

            reverse_iterator operator++(int);

            bool operator==(const reverse_iterator &rhs) const;

            bool operator!=(const reverse_iterator &rhs) const;

            friend ostream &operator<<(ostream &os, const reverse_iterator &m);

            string* operator->() const;

            bool getNextRGrandpaGrandson();

            bool hasNextRGrandpaGrandson();
        };

        class preorder_iterator {
        private:
            Node *orgPtr;

        public:

            preorder_iterator(Node* ptr= nullptr) {
                orgPtr = ptr;
            }

            Node *getOrgPtr();

            string &operator*() const;

            bool hasNext();

            bool hasRUncle();

            bool getNextRUncle();

            preorder_iterator operator++();

            preorder_iterator operator++(int);

            bool operator!=(const preorder_iterator &rhs) const;

            friend ostream &operator<<(ostream &os, const preorder_iterator &m);

            string* operator->() const;

        };

        OrgChart &add_root(const string &str);

        OrgChart &add_sub(const string &str1, const string &str2);

        Node *findNode(const string &basicString);

        friend ostream &operator<<(ostream &os, const OrgChart &m);

        iterator begin_level_order();

        iterator end_level_order();

        iterator begin();

        iterator end();

        reverse_iterator begin_reverse_order();

        reverse_iterator end_reverse_order();

        reverse_iterator reverse_order();

        preorder_iterator begin_preorder();

        preorder_iterator end_preorder();


    };
}