//
// Created by orff1 on 5/15/2022.
//

#include "OrgChart.hpp"

using namespace ariel;


OrgChart::iterator *OrgChart::begin_level_order() {
    return nullptr;
}

OrgChart::iterator *OrgChart::end_level_order() {
    return nullptr;
}

OrgChart &OrgChart::add_root(const string &str) {
    OrgChart* o= new OrgChart;
    return *o;
}

OrgChart &OrgChart::add_sub(const string &str1, const string &str2) {
    OrgChart* o= new OrgChart;
    return *o;
}

ostream &ariel::operator<<(ostream &os, const OrgChart &m) {
    return std::operator<<(os, "");
}

OrgChart::iterator *OrgChart::begin_reverse_order() {
    return nullptr;
}

OrgChart::iterator *OrgChart::end_reverse_order() {
    return nullptr;
}

OrgChart::iterator *OrgChart::begin_preorder() {
    return nullptr;
}

OrgChart::iterator *OrgChart::end_preorder() {
    return nullptr;
}

OrgChart::iterator OrgChart::begin() {
    return OrgChart::iterator();
}

OrgChart::iterator OrgChart::end() {
    return OrgChart::iterator();
}

///////////////// ITERATOR ///////////

ostream &ariel::operator<<(ostream &os, const OrgChart::iterator &m) {
    return std::operator<<(os, "");
}


OrgChart::iterator &OrgChart::iterator::operator++() {
     OrgPtr++;
     return *this;
}

OrgChart::iterator OrgChart::iterator::operator++(int) {
    return OrgChart::iterator();
}

OrgChart &OrgChart::iterator::operator*() {
    return *OrgPtr;
}

bool OrgChart::iterator::operator==(const OrgChart::iterator &rhs) {
    return false;
}

bool OrgChart::iterator::operator!=(const OrgChart::iterator &rhs) {
    return false;
}

size_t OrgChart::iterator::size() {
    return 0;
}


