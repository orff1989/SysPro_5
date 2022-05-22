#pragma once
/**
 * A template stack class.
 * Implemented as a linked list.
 *
 * AUTHOR: Ofir Pele
 * SINCE : 2017
 */
#include "string"
#include <stdexcept>
#include <iostream>

using namespace std;



namespace ariel {


    class OrgChart {
    public:

        OrgChart() : root(nullptr) {
        }

        ~OrgChart() {
            for (auto it = this->begin_level_order(); it != this->end_level_order(); ++it) {
                free(it.getOrgPtr());
            }
        }

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

            Node *leftBro(Node *pNode);

            bool hasNext();

            bool hasRCousing();

            bool hasLNephew();

            bool getNextCousing();

            bool getNextNephew();

            const iterator operator++();

            iterator operator++(int);

            bool operator==(const iterator &rhs) const;

            bool operator!=(const iterator &rhs) const;

            friend ostream &operator<<(ostream &os, const iterator &m);

        };

        class reverse_iterator {

        };



        OrgChart &add_root(const string &str);

        OrgChart &add_sub(const string &str1, const string &str2);

        Node *findNode(const string &basicString);

        friend ostream &operator<<(ostream &os, const OrgChart &m);

        iterator begin_level_order();

        iterator end_level_order();

        iterator begin();

        iterator end();

        iterator *begin_reverse_order();

        iterator *end_reverse_order();

        iterator *begin_preorder();

        iterator *end_preorder();



    };
}