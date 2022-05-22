//
// Created by orff1 on 5/15/2022.
//

#include "OrgChart.hpp"

using namespace ariel;


OrgChart::iterator OrgChart::begin_level_order() {
    return iterator{root};
}

OrgChart::iterator OrgChart::end_level_order() {
    return OrgChart::iterator(nullptr);
}


OrgChart &OrgChart::add_root(const string &str) {
    this->root= new Node(str, nullptr, this->root);
    return *this;
}



OrgChart &OrgChart::add_sub(const string &str1, const string &str2) {
    Node* d = findNode(str1);
    if(d== nullptr){std::invalid_argument("cant find this dad");}

    Node* n = new Node(str2,d);

    if(d->lChild!= nullptr){
        while (d->right!= nullptr){d=d->right;}
        d->right=n;
        n->left=d;
    } else{
        d->lChild=n;
    }
    return *this;
}

OrgChart::Node* OrgChart::findNode(const string &basicString) {
    iterator it(root);

    do{
        if(it.getOrgPtr()->name==basicString){
            return it.getOrgPtr();
        }

        ++it;
    }
    while (it.hasNext());

    if(it.getOrgPtr() && it.getOrgPtr()->name==basicString){ return it.getOrgPtr();}

    return nullptr;
}


//OrgChart::iterator *OrgChart::begin_reverse_order() {
//    return nullptr;
//}
//
//OrgChart::iterator *OrgChart::end_reverse_order() {
//    return nullptr;
//}
//
//OrgChart::iterator *OrgChart::begin_preorder() {
//    return nullptr;
//}
//
//OrgChart::iterator *OrgChart::end_preorder() {
//    return nullptr;
//}
//
//OrgChart::iterator OrgChart::begin() {
//    return OrgChart::iterator(this);
//}
//
//OrgChart::iterator OrgChart::end() {
//    OrgChart::iterator it = begin();
//    while (it.hasNext()){ it.next();}
//    return it;
//}
//
/////////////////// ITERATOR ///////////
//
//
//
//OrgChart::iterator OrgChart::iterator::next() {
//    if (org != nullptr && hasNext()) {
//        if(org->_right) {
//            this->org = org->_right;
//        } else{
//            this->org=org->_lChild;
//        }
//        return *this;
//    }
//    else{
//        throw std::invalid_argument("there are no more values");}
//}

ostream &ariel::operator<<(ostream &os, const OrgChart::iterator &m) {
    return  std::operator<<(os, m.getOrgPtr()->name);
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

bool OrgChart::iterator::hasNext() {
    return orgPtr->lChild!= nullptr || orgPtr->right!= nullptr || hasRCousing() || hasLNephew();
}

OrgChart::Node *OrgChart::iterator::getOrgPtr() const {
    return orgPtr;
}

void OrgChart::iterator::setOrgPtr(OrgChart::Node *orgPtr) {
    iterator::orgPtr = orgPtr;
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
    while (ll && ll->lChild == nullptr) { ll = ll->right; }
    if (ll->lChild!= nullptr) {
        orgPtr=ll->lChild;
        return true;
    }
    return false;
}

bool OrgChart::iterator::hasLNephew() {
    if(this->orgPtr== nullptr || orgPtr->left== nullptr) return false;

    Node *ll = leftBro(this->orgPtr);
    while (ll && ll->lChild == nullptr) { ll = ll->right; }
    if (ll->lChild!= nullptr) {
        return true;
    }
    return false;
}






////OrgChart::iterator OrgChart::iterator::operator++(int) {
////    cout<<"in ++ int"<<endl;
////    return next();
////}
////
////OrgChart::iterator OrgChart::iterator::operator++() {
////    cout<<"in ++"<<endl;
////    return next();
////}
//
//OrgChart::iterator OrgChart::iterator::operator*() {
//    return *this;
//}
//
//bool OrgChart::iterator::operator!=(const OrgChart::iterator &rhs) {
//    return this->org==rhs.org;
//}
//
//ostream &ariel::operator<<(ostream &os, const OrgChart::iterator &m) {
//    return std::operator<<(os, m.org->getName());
//}
//
//OrgChart *OrgChart::iterator::getOrg(){
//    return org;
//}
//
//
//const string &OrgChart::getName() const {
//    return _name;
//}
//
