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

        }

    private:

        struct Node {
            string name;
            Node* dad;
            Node *lChild;
            Node *right;
            Node* left;

            Node(const string &v, Node *d= nullptr, Node* lch= nullptr, Node *r= nullptr, Node* l= nullptr)
                    : name(v), lChild(lch), right(r),left(l), dad(d) {
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

            void setOrgPtr(Node *orgPtr);

            string &operator*() const {
                return orgPtr->name;
            }

            string *operator->() const {
                return &(orgPtr->name);
            }


            Node *leftBro(Node *pNode);

            bool hasNext();

            bool hasRCousing();

            bool hasLNephew();

            bool getNextCousing();

            bool getNextNephew();

            const iterator operator++() {
                iterator t = *this;
                if (orgPtr != nullptr) {
                    if (orgPtr->right) {
                        this->orgPtr = orgPtr->right;
                    }
                    else if (getNextCousing()){return t;}
                    else if(getNextNephew()) {return t;}
                    else if(orgPtr->lChild){
                        this->orgPtr=orgPtr->lChild;
                        return t;
                    }
                    else{
                        orgPtr= nullptr;
                        return t;
                    }
                }
                return t;
            }



            iterator operator++(int) {
                if (orgPtr != nullptr) {
                    if (orgPtr->right) {
                        this->orgPtr = orgPtr->right;
                    }
                    else if (getNextCousing()){return *this;}
                    else if(getNextNephew()) {return *this;}
                    else if(orgPtr->lChild){
                        this->orgPtr=orgPtr->lChild;
                        return *this;
                    }
                    else{
                        orgPtr= nullptr;
                        return *this;
                    }
                }
                return *this;
            }

                bool operator==(const iterator &rhs) const {
                    return orgPtr == rhs.orgPtr;
                }

                bool operator!=(const iterator &rhs) const {
                    return orgPtr != rhs.orgPtr;
                }

                friend ostream &operator<<(ostream &os, const iterator &m);



            };  // END OF CLASS ITERATOR

            OrgChart &add_root(const string &str);

            OrgChart &add_sub(const string &str1, const string &str2);

            Node *findNode(const string &basicString);

            friend ostream &operator<<(ostream &os, const OrgChart &m);

            iterator begin_level_order();

            iterator end_level_order();

            iterator *begin_reverse_order();

            iterator *end_reverse_order();

            iterator *begin_preorder();

            iterator *end_preorder();

            iterator begin() {
                return begin_level_order();
            }

            iterator end() {
                return end_level_order();
            }



        //-------------------------------------------------------------------

/*
	class reverse_iterator {
		...
	};

	reverse_iterator rbegin() {

	};

	reverse_iterator rend() {

	};
*/


        //-------------------------------------------------------------------
        // generic constructor:
        // template constructor inside a template class!
        //-------------------------------------------------------------------
//        template<typename IT>
//        OrgChart(IT begin, IT end): OrgChart() {
//            for (; begin != end; ++begin) {
//                push(*begin);
//            }
//        }
        //-------------------------------------------------------------------

    };














//#pragma once
//#include "string"
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <stdexcept>
//#include "vector"
//#include <iterator>
//#include <bits/stdc++.h>
//#define Null "null"
//
////
//// Created by orff1 on 5/15/2022.
////

//using namespace std;
//
//static std::string nuLL = "null";
//
//namespace ariel{
//
//
//
//    class OrgChart{
//        string _name;
//    public:
//        const string &getName() const;
//
//    private:
//        OrgChart* _dad;
//        OrgChart* _left;
//        OrgChart* _right;
//        OrgChart* _lChild;
//
//    public:
//
//        class iterator{
//        private:
//            OrgChart* org;
//
//
//        public:
//
//            iterator(OrgChart* o= nullptr){
//                org=o;
//            }
//
//            iterator curr();
//
//            iterator next();
//
//            bool hasNext();
//
//            OrgChart *getOrg();
//
//            friend ostream& operator<< (ostream& os, const iterator& m);
//
//            auto operator++(){
//                cout<<"hiii"<<endl;
//                if(hasNext()){
//                    next();
//                }
//                return *this;
//            }
//
//            const auto operator++(int){
//                cout<<"bbbbbbbbb"<<endl;
//                this->next();
//                return *this;
//            }
//
//            iterator operator*();
//
//            bool operator==(const iterator& rhs);
//
//            bool operator!=(const iterator& rhs);
//
//            size_t size();
//
//        };
//
//
//    public:
//        OrgChart(string& name=nuLL, OrgChart* dad= nullptr) {
//            _dad= dad;
//            _right= nullptr;
//            _left= nullptr;
//            _lChild= nullptr;
//            _name=name;
//        }
//
//        ~OrgChart(){
////        OrgChart * ptr;
////            for(auto o : *this) {
////                ptr=(OrgChart*) &o;
////                if(o._dad!= nullptr) free(ptr);
////            }
//    }
//
//        OrgChart &add_root(const string& str);
//
//        OrgChart &add_sub(const string& str1, const string& str2);
//
//        iterator *begin_level_order();
//
//        iterator *end_level_order();
//
//        iterator *begin_reverse_order();
//
//        iterator *end_reverse_order();
//
//        iterator *begin_preorder();
//
//        iterator *end_preorder();
//
//        friend ostream& operator<< (ostream& os, const OrgChart& m);
//
//        iterator begin();
//
//        iterator end();
//
//        OrgChart* findNode(const string &basicString);
//    };
//
//
//
//}

}
