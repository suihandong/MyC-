/**
 * @file bus_UT.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

/* STUDENTS: YOU MUST ADD YOUR PASSENGER UNIT TESTS TO THIS FILE. FORMAT YOUR
 * TESTS TO FIT THE SPECIFICATIONS GIVEN BY THE TESTS PROVIDED IN THIS FILE.
 *
 * Please note, the assessment tests for grading, will use the same include
 * files, class names, and function names for accessing students' code that you
 * find in this file.  So students, if you write your code so that it passes
 * these feedback tests, you can be assured that the auto-grader will at least
 * be able to properly link with your code.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <numeric>

#include "../src/bus.h"
#include "../src/passenger.h"
#include "../src/random_passenger_generator.h"
#include "../src/route.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class BusTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    pass.push_back(new Passenger(33, "Zoe"));
    pass.push_back(new Passenger(42, "Kaylee"));
    pass.push_back(new Passenger(50, "Wash"));
    pass.push_back(new Passenger(10, "Mal"));
    pass.push_back(new Passenger(23, "Jayne"));

    // Eastbound stops
    Stop *stop_CC_EB_1 = new Stop(0, 43, -92.5);  // West bank station
    Stop *stop_CC_EB_2 = new Stop(1);  // student union station
    Stop *stop_CC_EB_3 = new Stop(2, 44.973820, -93.227117);
    // Oak St & Washington Ave
    Stop *stop_CC_EB_4 = new Stop(3, 45, -94);  // before transit
    Stop *stop_CC_EB_5 = new Stop(4, 46, -95);  // st paul 1
    Stop *stop_CC_EB_6 = new Stop(5, 47, -96);  // st paul 2

    // Westbound stops
    Stop *stop_CC_WB_1 = new Stop(6, 47, -96);  // st paul 2
    Stop *stop_CC_WB_2 = new Stop(7, 46, -95);  // st paul 1
    Stop *stop_CC_WB_3 = new Stop(8, 45, -94);  // before transit
    Stop *stop_CC_WB_4 = new Stop(9, 44.973820, -93.227117);
    // Oak St & Washington Ave
    Stop *stop_CC_WB_5 = new Stop(10);  // student union station
    Stop *stop_CC_WB_6 = new Stop(11, 43, -92.5);  // West bank station

    EB_stops_list.push_back(stop_CC_EB_1);
    EB_stops[0] = stop_CC_EB_1;
    EB_stops_list.push_back(stop_CC_EB_2);
    EB_stops[1] = stop_CC_EB_2;
    EB_stops_list.push_back(stop_CC_EB_3);
    EB_stops[2] = stop_CC_EB_3;
    EB_stops_list.push_back(stop_CC_EB_4);
    EB_stops[3] = stop_CC_EB_4;
    EB_stops_list.push_back(stop_CC_EB_5);
    EB_stops[4] = stop_CC_EB_5;
    EB_stops_list.push_back(stop_CC_EB_6);
    EB_stops[5] = stop_CC_EB_6;
    WB_stops_list.push_back(stop_CC_WB_1);
    WB_stops[0] = stop_CC_WB_1;
    WB_stops_list.push_back(stop_CC_WB_2);
    WB_stops[1] = stop_CC_WB_2;
    WB_stops_list.push_back(stop_CC_WB_3);
    WB_stops[2] = stop_CC_WB_3;
    WB_stops_list.push_back(stop_CC_WB_4);
    WB_stops[3] = stop_CC_WB_4;
    WB_stops_list.push_back(stop_CC_WB_5);
    WB_stops[4] = stop_CC_WB_5;
    WB_stops_list.push_back(stop_CC_WB_6);
    WB_stops[5] = stop_CC_WB_6;

    EB_distances[0] = 5;
    EB_distances[1] = 4;
    EB_distances[2] = 3;
    EB_distances[3] = 10;
    EB_distances[4] = 6;

    WB_distances[0] = 6;
    WB_distances[1] = 10;
    WB_distances[2] = 3;
    WB_distances[3] = 4;
    WB_distances[4] = 5;

    EB_probs.push_back(.15);  // WB
    EB_probs.push_back(.3);  // CMU
    EB_probs.push_back(.025);  // O&W
    EB_probs.push_back(.05);  // Pre-transit
    EB_probs.push_back(.05);  // STP 1
    EB_probs.push_back(0);  // STP 1

    WB_probs.push_back(.35);  // stp 2
    WB_probs.push_back(.05);  // stp 1
    WB_probs.push_back(.01);  // post-transit
    WB_probs.push_back(.01);  // O&W
    WB_probs.push_back(.02);  // CMU
    WB_probs.push_back(0);  // WB

    EB = new Route("Eastbound", EB_stops, EB_distances, 6, CC_EB_generator);
    WB = new Route("Westbound", WB_stops, WB_distances, 6, CC_WB_generator);
  }

  std::vector<Passenger *> pass;
  Stop ** EB_stops = new Stop *[6];
  Stop ** WB_stops = new Stop *[6];
  std::list<Stop *> EB_stops_list = {};
  std::list<Stop *> WB_stops_list = {};
  double * EB_distances = new double[5];
  double * WB_distances = new double[5];
  std::list<double> EB_probs = {};
  std::list<double> WB_probs = {};

  RandomPassengerGenerator *CC_EB_generator =
                     new RandomPassengerGenerator(EB_probs, EB_stops_list);
  RandomPassengerGenerator *CC_WB_generator =
                     new RandomPassengerGenerator(WB_probs, WB_stops_list);

  Route * EB;
  Route * WB;

  int counter = 10000;
  Bus * bus = new Bus(std::to_string(counter), EB, WB, 60, 1);
  Bus * bus1 = new Bus(std::to_string(counter), EB, WB, 0, 1);
};



/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(BusTests, Constructor) {
  EXPECT_EQ(bus->GetName(), std::to_string(counter));
  EXPECT_EQ(bus->GetCapacity(), 60);
  EXPECT_EQ(bus->GetNumPassengers(), 0);
}

TEST_F(BusTests, LoadPassenger) {
  for (std::vector<Passenger *>::iterator it = pass.begin(); it != pass.end();
       it++) {
         EXPECT_EQ(bus->LoadPassenger(*it), true);
         EXPECT_EQ(bus1->LoadPassenger(*it), false);
       }
  EXPECT_EQ(bus->GetNumPassengers(), 5);
  Passenger *passenger = NULL;
  EXPECT_EQ(bus1->LoadPassenger(passenger), false);
  EXPECT_EQ(bus1->GetNumPassengers(), 0);
}

TEST_F(BusTests, GetNextStop) {
  std::list<Stop *>::iterator it = EB_stops_list.begin();
  std::advance(it, 1);
  EXPECT_EQ(EB->GetNextStop(), (*it));
}

TEST_F(BusTests, Move) {
  EXPECT_EQ(bus->Move(), false);
  EXPECT_EQ(bus->IsTripComplete(), false);
  for (std::list<Stop *>::iterator it = EB_stops_list.begin();
       it != EB_stops_list.end(); it++) {
    EB->NextStop();
    bus->Move();
    bus->Update();
  }
  bus->Update();
  EXPECT_EQ(bus->Move(), true);
  EXPECT_EQ(bus->IsTripComplete(), false);
  for (std::list<Stop *>::iterator it = WB_stops_list.begin();
        it != WB_stops_list.end(); it++) {
    WB->NextStop();
    bus->Move();
    bus->Update();
  }
  bus->Update();
  EXPECT_EQ(WB->IsAtEnd(), true);
  EXPECT_EQ(EB->IsAtEnd(), true);
  EXPECT_EQ(bus->Move(), false);
  EXPECT_EQ(bus->IsTripComplete(), true);
}
