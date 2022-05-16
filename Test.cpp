#include "doctest.h"
#include "OrgChart.hpp"
#include <string>
#include <sstream>

using namespace std;
using namespace ariel;



TEST_CASE("Good input") {
    OrgChart org1;
    std::ostringstream out;
    out.str("");

    for (auto it = org1.begin_level_order(); it != org1.end_level_order(); ++it){
        CHECK_NOTHROW(out<< *it<<" ");
    }
    CHECK(out.str()=="");
    out.str("");

    CHECK_NOTHROW(org1.add_root("CEO")
            .add_sub("CEO", "subOfCEO1")
            .add_sub("CEO", "subOfCEO2")
            .add_sub("subOfCEO1", "emp1")
            .add_sub("subOfCEO2", "emp2")
            .add_sub("emp1", "emp0"));


    for (auto it = org1.begin_level_order(); it != org1.end_level_order(); ++it){
        CHECK_NOTHROW(out<< *it<<" ");
    }
    CHECK(out.str()=="CEO subOfCEO1 subOfCEO2 emp1 emp2 emp0");
    out.str("");

    for (auto it = org1.begin_reverse_order(); it != org1.end_reverse_order(); ++it){
        CHECK_NOTHROW(out<< *it<<" ");
    }
    CHECK(out.str()=="emp0 emp1 emp2 subOfCEO1 subOfCEO2 CEO");
    out.str("");

    for (auto it=org1.begin_preorder(); it!=org1.end_preorder(); ++it) {
        CHECK_NOTHROW(out<< *it<<" ");
    }
    CHECK(out.str()=="CEO subOfCEO1 emp1 emp0 subOfCEO2 emp2");
    out.str("");

    for (auto element : org1){
        CHECK_NOTHROW(out<< element<<" ");
    }
    CHECK(out.str()=="CEO subOfCEO1 subOfCEO2 emp1 emp2 emp0");
    out.str("");

    CHECK_NOTHROW(org1.add_sub("emp0", "subEmp0"));

    for (auto it = org1.begin_level_order(); it != org1.end_level_order(); ++it){
                CHECK_NOTHROW(out<< *it<<" ");
    }
    CHECK(out.str()=="CEO subOfCEO1 subOfCEO2 emp1 emp2 emp0 subEmp0");
    out.str("");

    for (auto element : org1){
        CHECK_NOTHROW(out<< element<<" ");
    }
    CHECK(out.str()=="CEO subOfCEO1 subOfCEO2 emp1 emp2 emp0 subEmp0");
    out.str("");

    CHECK_NOTHROW(org1.add_root("CEO1"));
    CHECK_NOTHROW(org1.add_root("CEO2"));
    CHECK_NOTHROW(org1.add_root("CEO3"));

}


TEST_CASE("bad input") {
    OrgChart org1;

    CHECK_NOTHROW(org1.add_root("CEO")
                          .add_sub("CEO", "subOfCEO1")
                          .add_sub("CEO", "subOfCEO2")
                          .add_sub("subOfCEO1", "emp1")
                          .add_sub("subOfCEO2", "emp2")
                          .add_sub("emp1", "emp0"));

    CHECK_THROWS(org1.add_sub("eee", "ppp1"));
    CHECK_THROWS(org1.add_sub("ceo", "ppp2"));
    CHECK_THROWS(org1.add_sub("CEo", "ppp3"));

}