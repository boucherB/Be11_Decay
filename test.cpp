#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "DecayFunctions.h"

//J = 1/2
//Jp = 3/2
//Jpp = 3/2 and 1/2

TEST_CASE("theta(u,v)") {
        // These tests will pass
        REQUIRE(theta(1,1) == 1);
        REQUIRE(theta(0,1) == 0);
        REQUIRE(theta(1,0) == -2);

}

TEST_CASE("g1(E, u, v, s)"){
    //v = Jp
    //u = J
    //s = 1
    REQUIRE(g1(1.6, 3./2., 1./2., 1) == 1.);
    REQUIRE(g1(1000., 1000., 1000., 1000.) == 1.);
    //g1 should always be 1, not dependent on any variables
}

TEST_CASE("g2(E, u, v, s)"){
    //v = Jp
    //u = J
    //s = 1
    REQUIRE(g2(1.6, 3./2., 1./2., 1) == -1./3.);
    REQUIRE(g2(1000., 1000., 1000., 1000.) == -1./3.);
    //g2 should always be -1/3, not dependent on any variables

}

TEST_CASE("g12(E, u, v, s)"){
    //v = Jp
    //u = J
    //s = 1
    REQUIRE(theta(3./2., 1./2.) == -5./4.);
    REQUIRE(theta(1./2., 3./2.) == -1./8.);
    REQUIRE(theta(1./2., 1./2.) == 1.);
    REQUIRE(g12(1.6, 3./2., 1./2., 1) == 5./4.);
}

TEST_CASE("omega(L, Jp, Jpp)"){

    REQUIRE(omega(1, 3./2., 3./2.) == 0);
    REQUIRE(omega(1, 3./2., 1./2.) == 0);


}

TEST_CASE("tau(L, Jp, Jpp)"){

    REQUIRE(tau(1, 3./2., 1./2.) == 8.); // Jp = Jpp + 1
    REQUIRE(tau(1, 3./2., 3./2.) == -6.4); // Jp = Jpp
    REQUIRE(tau(1, 3./2., 5./2.) == 1.6); // Jp = Jpp - 1

}
