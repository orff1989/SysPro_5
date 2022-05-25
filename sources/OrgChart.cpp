//
// Created by orff1 on 5/15/2022.
//

#include "OrgChart.hpp"

using namespace ariel;

////////// ORGCHART /////////////



OrgChart &OrgChart::add_root(const string &str) {
    if(root==nullptr) {
        this->root = new Node(str);
    }
    else{
        root->name=str;
    }
    return *this;
}

OrgChart &OrgChart::add_sub(const string &str1, const string &str2) {
    if (root== nullptr) { throw std::invalid_argument("the root is null");}

    Node* d = findNode(str1);
    if(d== nullptr){ throw std::invalid_argument("cant find this dad");}

    Node* n = new Node(str2,d);
    if(d->lChild!= nullptr){

        d=d->lChild;
        while (d!= nullptr && d->right!= nullptr){d=d->right;}
        d->right=n;
        n->left=d;

    } else{
            d->lChild = n;
    }
    return *this;
}

OrgChart::Node* OrgChart::findNode(const string &basicString) {
    if (root== nullptr) { throw std::invalid_argument("root is null");}

    for (auto it = this->begin_level_order(); it != this->end_level_order(); ++it)
  {
      if(it.getOrgPtr()!= nullptr && it.getOrgPtr()->name==basicString){
            return it.getOrgPtr();
        }
  }
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
            if (it.getOrgPtr()->lChild!= nullptr) {i=1;}
            it.hasNext();
        }

    }
    return  std::operator<<(os, s);
}

OrgChart::iterator OrgChart::begin_level_order() {
    if (root== nullptr){ throw std::invalid_argument("the root is null");}
    return iterator{root};
}

OrgChart::iterator OrgChart::end_level_order() {
    if (root== nullptr){ throw std::invalid_argument("the root is null");}
    return {nullptr};
}

OrgChart::iterator OrgChart::begin() {
    return begin_level_order();
}

OrgChart::iterator OrgChart::end() {
    return end_level_order();
}

OrgChart::reverse_iterator OrgChart::begin_reverse_order() {
    if (root== nullptr){ throw std::invalid_argument("the root is null");}

    Node * farest_from_root=root;

    for (auto it = begin_preorder(); it!=end_preorder() ; ++it) {
        if(it.getOrgPtr()->hight()>farest_from_root->hight()){ farest_from_root=it.getOrgPtr();}
    }

    return reverse_iterator{farest_from_root};
}

OrgChart::reverse_iterator OrgChart::end_reverse_order() {
    if (root== nullptr){ throw std::invalid_argument("the root is null");}
    return reverse_iterator{nullptr};
}

 OrgChart::reverse_iterator OrgChart::reverse_order() {
    return end_reverse_order();
}

OrgChart::preorder_iterator OrgChart::begin_preorder() {
    if (root== nullptr){ throw std::invalid_argument("the root is null");}
    return {root};
}

OrgChart::preorder_iterator OrgChart::end_preorder() {
    if (root== nullptr){ throw std::invalid_argument("the root is null");}
    return {nullptr};
}


/////////////////// ITERATOR ///////////////////

ostream &ariel::operator<<(ostream &os, const OrgChart::iterator &m) {
    return std::operator<<(os, m.getOrgPtr()->name);
}

bool OrgChart::iterator::hasNext() {
    return orgPtr->lChild!= nullptr || orgPtr->right!= nullptr || hasRCousing() || hasLNephew() || hasSonOfCousing() || hassonOfDadRCousing();
}

OrgChart::Node *OrgChart::iterator::getOrgPtr() const {
    return orgPtr;
}

OrgChart::Node *OrgChart::iterator::leftBro(OrgChart::Node *pNode) {
    Node *ptr=pNode;
    while(ptr->left!= nullptr) {ptr=ptr->left;}
    return ptr;
}

bool OrgChart::iterator::getNextCousing() {
    if( orgPtr== nullptr || orgPtr->dad== nullptr){ return false;}
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
    if( orgPtr== nullptr || orgPtr->dad== nullptr){ return false;}
    Node* d= this->orgPtr->dad;

    while(d->right!= nullptr){
        if(d->right->lChild!= nullptr) {
            return true;
        }
        d=d->right;
    }
    return false;
}

bool OrgChart::iterator::getNextNephew() {
    if(this->orgPtr== nullptr || orgPtr->left== nullptr){ return false;}

    Node *ll = leftBro(this->orgPtr);
    while (ll!= nullptr && ll!=orgPtr && ll->lChild == nullptr) { ll = ll->right; }
    if (ll!= nullptr && ll->lChild!= nullptr) {
        orgPtr=ll->lChild;
        return true;
    }
    return false;
}

bool OrgChart::iterator::hasLNephew() {
    if(this->orgPtr== nullptr || orgPtr->left== nullptr){ return false;}

    Node *ll = leftBro(this->orgPtr);
    while (ll!= nullptr && ll!=orgPtr && ll->lChild == nullptr) { ll = ll->right; }
    return ll!= nullptr && ll->lChild!= nullptr;

}

string &OrgChart::iterator::operator*() const {
    return orgPtr->name;
}

OrgChart::iterator OrgChart::iterator::operator++() {
    iterator t = *this;
    if (orgPtr != nullptr) {
        if (orgPtr->right!= nullptr) {
            this->orgPtr = orgPtr->right;
            return t;
        }
        if (getNextCousing()){return t;}
        if(sonOfLCousing()) {return t;}
        if(getNextNephew()){return t;}
        if(sonOfDadRCousing()){return t;}
        if(orgPtr->lChild!= nullptr){
            this->orgPtr=orgPtr->lChild;
            return t;
        }
        orgPtr= nullptr;
    }
    return t;
}

OrgChart::iterator OrgChart::iterator::operator++(int) {
    if (orgPtr != nullptr) {
        if (orgPtr->right!= nullptr) {
            this->orgPtr = orgPtr->right;
            return *this;
        }
        if (getNextCousing()){return *this;}
        if(sonOfLCousing()) {return *this;}
        if(getNextNephew()){return *this;}
        if(sonOfDadRCousing()){return *this;}
        if(orgPtr->lChild!= nullptr){
            this->orgPtr=orgPtr->lChild;
            return *this;
        }
        orgPtr= nullptr;
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
    if (orgPtr!= nullptr && orgPtr->dad!= nullptr && orgPtr->dad->dad!= nullptr && orgPtr->dad->dad->lChild!= nullptr && orgPtr->dad->dad->lChild->lChild!= nullptr) {
        Node *n = orgPtr->dad->dad->lChild->lChild;

        while (n!= nullptr && n->lChild == nullptr) {
            n = n->right;
        }
        if (n!= nullptr && n->lChild!= nullptr) {
            orgPtr = n->lChild;
            return true;
        }
    }
    return false;
}

bool OrgChart::iterator::hasSonOfCousing() {
    if (this->orgPtr == nullptr) { return false; }
    if (orgPtr->dad!= nullptr && orgPtr->dad->dad!= nullptr && orgPtr->dad->dad->lChild!= nullptr && orgPtr->dad->dad->lChild->lChild!= nullptr) {
        Node *n = orgPtr->dad->dad->lChild->lChild;

        while (n!= nullptr && n->lChild == nullptr) {
            n = n->right;
        }
        if (n!= nullptr && n->lChild!= nullptr) {
            return true;
        }
    }
    return false;
}

bool OrgChart::iterator::sonOfDadRCousing() {
    if (this->getOrgPtr()!= nullptr && this->getOrgPtr()->dad!= nullptr && orgPtr->dad->getNextSonOfRCousing()!= nullptr){
        orgPtr=orgPtr->dad->getNextSonOfRCousing();
        return true;
    }
    return false;
}

bool OrgChart::iterator::hassonOfDadRCousing() {
    return this->getOrgPtr()!= nullptr && this->getOrgPtr()->dad!= nullptr && orgPtr->dad->getNextSonOfRCousing()!= nullptr;
}

/////////////////// REVERSE ITERATOR ///////////////////

OrgChart::Node *OrgChart::reverse_iterator::getOrgPtr() {
    return this->orgPtr;
}

string &OrgChart::reverse_iterator::operator*() const {
    return this->orgPtr->name;
}


bool OrgChart::reverse_iterator::hasRCousing() {
    if( orgPtr== nullptr || orgPtr->dad== nullptr) {return false;}
    Node* d= this->orgPtr->dad;

    while(d->right!= nullptr){
        if(d->right->lChild!= nullptr) {
            return true;
        }
        d=d->right;
    }
    return false;
}

bool OrgChart::reverse_iterator::getNextRCousing() {
    if( orgPtr== nullptr || orgPtr->dad== nullptr) {return false;}
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

OrgChart::reverse_iterator OrgChart::reverse_iterator::operator++(int) {
    if (orgPtr != nullptr) {
        if (orgPtr->right!= nullptr) {
            this->orgPtr = orgPtr->right;
            return *this;
        }
        if (getNextRCousing()) { return *this; }
        if(getNextRGrandpaGrandson()){return *this;}
        if (orgPtr->dad!= nullptr) {
            Node *d = orgPtr->dad;

            if(d->dad!= nullptr){
                d=d->getNextLCousing();}

            this->orgPtr=d;
            return *this;
        }
    }
    orgPtr = nullptr;
    return *this;
}

OrgChart::reverse_iterator OrgChart::reverse_iterator::operator++() {
    if (orgPtr != nullptr) {
        reverse_iterator t= *this;
        if (orgPtr->right!= nullptr) {
            this->orgPtr = orgPtr->right;
            return t;
        }
        if (getNextRCousing()) { return t; }
        if(getNextRGrandpaGrandson()){return t;}
        if (orgPtr->dad!= nullptr) {
            Node *d = orgPtr->dad;
            if (d->dad!= nullptr && d->dad->lChild!= nullptr) {
                d = d->dad->lChild;
            }

            if(d->dad!= nullptr){
            d=d->getNextLCousing();}

            this->orgPtr=d;
            return t;
        }
    }
    orgPtr = nullptr;
    return *this;
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

bool OrgChart::reverse_iterator::getNextRGrandpaGrandson() {
    if(orgPtr->dad== nullptr) {return false;}

    Node* n=orgPtr->dad->getNextSonOfRCousing();
    if(n!= nullptr){
        orgPtr=n;
        return true;
    }

    return false;
}

bool OrgChart::reverse_iterator::hasNextRGrandpaGrandson() {
    if(orgPtr->dad== nullptr) {return false;}
    Node* n=orgPtr->dad->getNextSonOfRCousing();
    return n!= nullptr;
}

/////////////// NODE /////////////////

OrgChart::Node *OrgChart::Node::getNextLCousing() {
    if(dad == nullptr) {return nullptr;}
    Node* d= dad;
    if(d->dad!= nullptr && d->dad->lChild!= nullptr && d->dad->lChild->lChild!= nullptr){
        d= d->dad->lChild->lChild;
        return d;
    }
    return this;
}

OrgChart::Node *OrgChart::Node::getNextSonOfRCousing() const {
    if (dad== nullptr || dad->right== nullptr){return nullptr;}
    Node* n=dad->right;
    while(n!= nullptr){
        if (n->lChild!= nullptr && n->lChild->lChild!= nullptr){
            return n->lChild->lChild;
        }
        n=n->right;
    }
    return nullptr;
}

size_t OrgChart::Node::hight() const {
    if(this->dad== nullptr){ return 0;}
    return dad->hight()+1;
}


//////////////// PREORDER ITERATOR ///////////

OrgChart::Node *OrgChart::preorder_iterator::getOrgPtr() {
    return this->orgPtr;
}

string &OrgChart::preorder_iterator::operator*() const {
    return this->orgPtr->name;
}

OrgChart::preorder_iterator OrgChart::preorder_iterator::operator++() {
    preorder_iterator t= *this;
    if (orgPtr != nullptr) {
        if (orgPtr->lChild!= nullptr) {
            this->orgPtr = orgPtr->lChild;
            return t;
        }
        if(orgPtr->right!= nullptr){
            orgPtr=orgPtr->right;
            return t;
        }
        if (getNextRUncle()) { return t; }

         Node* d= orgPtr->dad;

            while (d!= nullptr && d->dad!= nullptr){
                if(d->dad->right!= nullptr ){
                    orgPtr=d->dad->right;
                    return *this;
                }
                d=d->dad;
            }
            this->orgPtr= nullptr;
            return t;

        }
    this->orgPtr= nullptr;
    return t;
    }


OrgChart::preorder_iterator OrgChart::preorder_iterator::operator++(int) {
    if (orgPtr != nullptr) {
        if (orgPtr->lChild!= nullptr) {
            this->orgPtr = orgPtr->lChild;
            return *this;
        }
        if(orgPtr->right!= nullptr){
            orgPtr=orgPtr->right;
            return *this;
        }
        if (getNextRUncle()) { return *this; }

            Node* d= orgPtr->dad;

            while (d!= nullptr && d->dad!= nullptr){
                if(d->dad->right!= nullptr ){
                    orgPtr=d->dad->right;
                    return *this;
                }
                d=d->dad;
            }
            this->orgPtr= nullptr;
            return *this;

    }
    this->orgPtr= nullptr;
    return *this;
}

bool OrgChart::preorder_iterator::hasRUncle() {
    if (this->orgPtr== nullptr){ return false;}
    return orgPtr->dad!= nullptr && orgPtr->dad->right!= nullptr;
}

bool OrgChart::preorder_iterator::getNextRUncle() {
    if (this->orgPtr== nullptr){ return false;}
    if (orgPtr->dad!= nullptr && orgPtr->dad->right!= nullptr){
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


