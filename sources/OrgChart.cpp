//
// Created by orff1 on 5/15/2022.
//

#include "OrgChart.hpp"

using namespace ariel;

////////// ORGCHART /////////////

OrgChart &OrgChart::add_root(const string &str) {
    this->root= new Node(str, nullptr, this->root);
    return *this;
}

OrgChart &OrgChart::add_sub(const string &str1, const string &str2) {
    Node* d = findNode(str1);

    if(d== nullptr){std::invalid_argument("cant find this dad");}

    Node* n = new Node(str2,d);
    if(d->lChild!= nullptr){


        d=d->lChild;
        while (d->right!= nullptr){d=d->right;}
        d->right=n;
        n->left=d;

    } else{
            d->lChild = n;
    }
    return *this;
}

OrgChart::Node* OrgChart::findNode(const string &basicString) {
    iterator it(root);

    do{
        if(it.getOrgPtr() && it.getOrgPtr()->name==basicString){
            return it.getOrgPtr();
        }
        it++;
    }
    while (it.hasNext());

    if(it.getOrgPtr() && it.getOrgPtr()->name==basicString){ return it.getOrgPtr();}

    return nullptr;
}

ostream &ariel::operator<<(ostream &os, const OrgChart &m) {
    string s;
    string space="                       ";
    int i=1;
    OrgChart::iterator it(m.root) ;
    s+=space+it.getOrgPtr()->name;
    while(i>1) {
        s+="\n"+space.substr(0,space.size()-2);
        i=0;
        while (it.hasNext()) {
            s += it.getOrgPtr()->right->name;
            if (it.getOrgPtr()->lChild) i=1;
            it.hasNext();
        }

    }
    return  std::operator<<(os, s);
}

OrgChart::iterator OrgChart::begin_level_order() {
    return iterator{root};
}

OrgChart::iterator OrgChart::end_level_order() {
    return OrgChart::iterator(nullptr);
}

OrgChart::iterator OrgChart::begin() {
    return begin_level_order();
}

OrgChart::iterator OrgChart::end() {
    return end_level_order();
}

OrgChart::reverse_iterator OrgChart::begin_reverse_order() {
    iterator it(this->root);
    while (it.hasNext()) {++it;}

    Node *n= it.getOrgPtr();
    while(n->left){n=n->left;}

    n=n->getNextLCousing();

    return reverse_iterator{n};
}

OrgChart::reverse_iterator OrgChart::end_reverse_order() {
    return reverse_iterator{nullptr};
}

const OrgChart::reverse_iterator OrgChart::reverse_order() {
    return end_reverse_order();
}

OrgChart::preorder_iterator OrgChart::begin_preorder() {
    return OrgChart::preorder_iterator(root);
}

OrgChart::preorder_iterator OrgChart::end_preorder() {
    return OrgChart::preorder_iterator(nullptr);
}

/////////////////// ITERATOR ///////////////////

ostream &ariel::operator<<(ostream &os, const OrgChart::iterator &m) {
    return std::operator<<(os, m.getOrgPtr()->name);
}

bool OrgChart::iterator::hasNext() {
    return orgPtr->lChild!= nullptr || orgPtr->right!= nullptr || hasRCousing() || hasLNephew() || hasSonOfCousing();
}

OrgChart::Node *OrgChart::iterator::getOrgPtr() const {
    return orgPtr;
}

OrgChart::Node *OrgChart::iterator::leftBro(OrgChart::Node *pNode) {
    Node *ptr=pNode;
    while(ptr->left) {ptr=ptr->left;}
    return ptr;
}

bool OrgChart::iterator::getNextCousing() {
    if( orgPtr== nullptr || orgPtr->dad== nullptr) return false;
    Node* d= this->orgPtr->dad;

    while(d->right!= nullptr){
        if(d->right->lChild!= nullptr) {
            this->orgPtr= d->right->lChild;
            return true;
        }
        d=d->right;
    }
    return false;
}

bool OrgChart::iterator::hasRCousing() {
    if( orgPtr== nullptr || orgPtr->dad== nullptr) return false;
    Node* d= this->orgPtr->dad;

    while(d->right!= nullptr){
        if(d->right->lChild) {
            return true;
        }
        d=d->right;
    }
    return false;
}

bool OrgChart::iterator::getNextNephew() {
    if(this->orgPtr== nullptr || orgPtr->left== nullptr) return false;

    Node *ll = leftBro(this->orgPtr);
    while (ll && ll!=orgPtr && ll->lChild == nullptr) { ll = ll->right; }
    if (ll->lChild!= nullptr) {
        orgPtr=ll->lChild;
        return true;
    }
    return false;
}

bool OrgChart::iterator::hasLNephew() {
    if(this->orgPtr== nullptr || orgPtr->left== nullptr) return false;

    Node *ll = leftBro(this->orgPtr);
    while (ll && ll!=orgPtr && ll->lChild == nullptr) { ll = ll->right; }
    if (ll->lChild!= nullptr) {
        return true;
    }
    return false;
}

string &OrgChart::iterator::operator*() const {
    return orgPtr->name;
}

const OrgChart::iterator OrgChart::iterator::operator++() {
    iterator t = *this;
    if (orgPtr != nullptr) {
        if (orgPtr->right) {
            this->orgPtr = orgPtr->right;
        }
        else if (getNextCousing()){return t;}
        else if(getNextNephew()) {return t;}
        else if(sonOfLCousing()){return *this;}
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

OrgChart::iterator OrgChart::iterator::operator++(int) {
    if (orgPtr != nullptr) {
        if (orgPtr->right) {
            this->orgPtr = orgPtr->right;
        }
        else if (getNextCousing()){return *this;}
        else if(getNextNephew()) {return *this;}
        else if(sonOfLCousing()){return *this;}
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

bool OrgChart::iterator::operator==(const OrgChart::iterator &rhs) const {
    return orgPtr == rhs.orgPtr;
}

bool OrgChart::iterator::operator!=(const OrgChart::iterator &rhs) const {
    return orgPtr != rhs.orgPtr;
}

string *OrgChart::iterator::operator->() const {
    return &(orgPtr->name);
}

bool OrgChart::iterator::sonOfLCousing() {
    if (orgPtr && orgPtr->dad && orgPtr->dad->dad && orgPtr->dad->dad->lChild && orgPtr->dad->dad->lChild->lChild) {
        Node *n = orgPtr->dad->dad->lChild->lChild;

        while (n && n->lChild == nullptr) {
            n = n->right;
        }
        if (n && n->lChild) {
            orgPtr = n->lChild;
            return true;
        }
    }
    return false;
}

bool OrgChart::iterator::hasSonOfCousing() {
    if (this->orgPtr == nullptr) { return false; }
    if (orgPtr->dad && orgPtr->dad->dad && orgPtr->dad->dad->lChild && orgPtr->dad->dad->lChild->lChild) {
        Node *n = orgPtr->dad->dad->lChild->lChild;

        while (n && n->lChild == nullptr) {
            n = n->right;
        }
        if (n && n->lChild) {
            return true;
        }
    }
    return false;
}

/////////////////// REVERSE ITERATOR ///////////////////

OrgChart::Node *OrgChart::reverse_iterator::getOrgPtr() {
    return this->orgPtr;
}

string &OrgChart::reverse_iterator::operator*() const {
    return this->orgPtr->name;
}

OrgChart::Node *OrgChart::reverse_iterator::leftBro(OrgChart::Node *pNode) {
    Node *ptr=pNode;
    while(ptr->left) {ptr=ptr->left;}
    return ptr;
}

bool OrgChart::reverse_iterator::hasNext() {
    return this->orgPtr->right || this->orgPtr->dad || hasRCousing();
}

bool OrgChart::reverse_iterator::hasRCousing() {
    if( orgPtr== nullptr || orgPtr->dad== nullptr) return false;
    Node* d= this->orgPtr->dad;

    while(d->right!= nullptr){
        if(d->right->lChild) {
            return true;
        }
        d=d->right;
    }
    return false;
}

bool OrgChart::reverse_iterator::getNextRCousing() {
    if( orgPtr== nullptr || orgPtr->dad== nullptr) return false;
    Node* d= this->orgPtr->dad;

    while(d->right!= nullptr){
        if(d->right->lChild!= nullptr) {
            this->orgPtr= d->right->lChild;
            return true;
        }
        d=d->right;
    }
    return false;
}

const OrgChart::reverse_iterator OrgChart::reverse_iterator::operator++(int) {
    if (orgPtr != nullptr) {
        if (orgPtr->right) {
            this->orgPtr = orgPtr->right;
            return *this;
        }
        else if (getNextRCousing()) { return *this; }
        else if (orgPtr->dad!= nullptr) {
            Node *d = orgPtr->dad;
            if (d->dad!= nullptr && d->dad->lChild!= nullptr) {
                d = d->dad->lChild;
            }

            if(d->dad){
                d=d->getNextLCousing();}

            this->orgPtr=d;
            return *this;
        }
    }
    orgPtr = nullptr;
    return *this;
}

const OrgChart::reverse_iterator OrgChart::reverse_iterator::operator++() {
    reverse_iterator t= *this;
    if (orgPtr != nullptr) {
        if (orgPtr->right) {
            this->orgPtr = orgPtr->right;
            return t;
        }
        else if (getNextRCousing()) { return t; }
        else if (orgPtr->dad!= nullptr) {
            Node *d = orgPtr->dad;
            if (d->dad!= nullptr && d->dad->lChild!= nullptr) {
                d = d->dad->lChild;
            }

            if(d->dad){
            d=d->getNextLCousing();}

            this->orgPtr=d;
            return t;
        }
    }
    orgPtr = nullptr;
    return t;
}

bool OrgChart::reverse_iterator::operator!=(const OrgChart::reverse_iterator &rhs) const {
    return this->orgPtr!=rhs.orgPtr;
}

ostream &ariel::operator<<(ostream &os, const OrgChart::reverse_iterator &m) {
    return std::operator<<(os, m.orgPtr->name);
}

string *OrgChart::reverse_iterator::operator->() const {
    return &(orgPtr->name);
}

/////////////// NODE /////////////////

OrgChart::Node *OrgChart::Node::getNextLCousing() {
    if(dad == nullptr) {return nullptr;}
    Node* d= dad;
    if(d->dad && d->dad->lChild && d->dad->lChild->lChild){
        d= d->dad->lChild->lChild;
        return d;
    }
    return this;
}

//////////////// PREORDER ITERATOR ///////////

OrgChart::Node *OrgChart::preorder_iterator::getOrgPtr() {
    return this->orgPtr;
}

string &OrgChart::preorder_iterator::operator*() const {
    return this->orgPtr->name;
}

bool OrgChart::preorder_iterator::hasNext() {
    return orgPtr->lChild || orgPtr->right || hasRUncle();
}

const OrgChart::preorder_iterator OrgChart::preorder_iterator::operator++() {
    if (orgPtr != nullptr) {
        if (orgPtr->lChild) {
            this->orgPtr = orgPtr->lChild;
            return *this;
        } else if(orgPtr->right){
            orgPtr=orgPtr->right;
            return *this;
        }
        else if (getNextRUncle()) { return *this; }
        else{
            this->orgPtr= nullptr;
            return *this;
        }
    }
    this->orgPtr= nullptr;
    return *this;
}

const OrgChart::preorder_iterator OrgChart::preorder_iterator::operator++(int) {
    if (orgPtr != nullptr) {
        preorder_iterator t=*this;
        if (orgPtr->lChild) {
            this->orgPtr = orgPtr->lChild;
            return t;
        } else if(orgPtr->right){
            orgPtr=orgPtr->right;
            return *this;
        }
        else if (getNextRUncle()) { return t; }
        else{
            this->orgPtr= nullptr;
            return t;
        }
    }
    this->orgPtr= nullptr;
    return *this;
}

bool OrgChart::preorder_iterator::hasRUncle() {
    if (this->orgPtr== nullptr){ return false;}
    if (orgPtr->dad && orgPtr->dad->right){
        return true;
    }
    return false;
}

bool OrgChart::preorder_iterator::getNextRUncle() {
    if (this->orgPtr== nullptr){ return false;}
    if (orgPtr->dad && orgPtr->dad->right){
        orgPtr=orgPtr->dad->right;
        return true;
    }
    return false;
}

bool OrgChart::preorder_iterator::operator!=(const OrgChart::preorder_iterator &rhs) const {
    return this->orgPtr!=rhs.orgPtr;
}

ostream &ariel::operator<<(ostream &os, const OrgChart::preorder_iterator &m) {
    return std::operator<<(os, m.orgPtr->name);
}

string *OrgChart::preorder_iterator::operator->() const {
    return &(orgPtr->name);
}
