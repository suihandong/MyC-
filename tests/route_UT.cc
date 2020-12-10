/**
 * @file EB_UT.cc
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
#include <vector>

#include "../src/route.h"
#include "../src/random_passenger_generator.h"
#include "../src/data_structs.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class RouteTests : public ::testing::Test {
 protected:
    virtual void SetUp() {
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

      EB = new Route("Eastbound", EB_stops, EB_distances, 6, &CC_EB_generator);
      WB = new Route("Westbound", WB_stops, WB_distances, 6, &CC_WB_generator);
    }

    Stop ** EB_stops = new Stop *[6];
    Stop ** WB_stops = new Stop *[6];
    std::list<Stop *> EB_stops_list = {};
    std::list<Stop *> WB_stops_list = {};
    double * EB_distances = new double[5];
    double * WB_distances = new double[5];
    std::list<double> EB_probs = {};
    std::list<double> WB_probs = {};

    RandomPassengerGenerator CC_EB_generator =
                  RandomPassengerGenerator(EB_probs, EB_stops_list);
    RandomPassengerGenerator CC_WB_generator =
                  RandomPassengerGenerator(WB_probs, WB_stops_list);

    Route * EB;
    Route * WB;
    int counter = 10000;
    Bus * bus = new Bus(std::to_string(counter), EB, WB, 60, 1);
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(RouteTests, Constructor) {
  Route * EB_cloned = EB->Clone();

  EXPECT_EQ(EB->IsAtEnd(), false);
  EXPECT_EQ(EB_cloned->IsAtEnd(), false);
  for (std::list<Stop *>::iterator it = EB_stops_list.begin();
       it != EB_stops_list.end(); it++) {
    EB->NextStop();
    EB_cloned->NextStop();
  }
  EXPECT_EQ(EB->IsAtEnd(), true);
  EXPECT_EQ(EB->GetName(), "Eastbound");
  EXPECT_EQ(EB->GetStops(), EB_stops_list);
  EXPECT_EQ(EB_cloned->IsAtEnd(), true);
  EXPECT_EQ(EB_cloned->GetName(), "Eastbound");
  EXPECT_EQ(EB_cloned->GetStops(), EB_stops_list);
}

TEST_F(RouteTests, GetDestinationStops) {
  Route * EB_cloned = EB->Clone();

  std::list<Stop *>::iterator it = EB_stops_list.begin();
  EXPECT_EQ(EB_cloned->GetDestinationStop(), (*it));
  EXPECT_EQ(EB->GetDestinationStop(), (*it));
  EB->NextStop();
  EB_cloned->NextStop();
  std::advance(it, 1);
  EXPECT_EQ(EB->GetDestinationStop(), (*it));
  EXPECT_EQ(EB_cloned->GetDestinationStop(), (*it));
}

TEST_F(RouteTests, GetPreviousStop) {
  Route * EB_cloned = EB->Clone();

  std::list<Stop *>::iterator it = EB_stops_list.begin();
  EXPECT_EQ(NULL, EB->GetPreviousStop());
  EXPECT_EQ(NULL, EB_cloned->GetPreviousStop());
  EB->NextStop();
  EB_cloned->NextStop();
  EXPECT_EQ(EB->GetPreviousStop(), (*it));
  EXPECT_EQ(EB_cloned->GetPreviousStop(), (*it));
}

TEST_F(RouteTests, GetCurrentStop) {
  Route * EB_cloned = EB->Clone();

  std::list<Stop *>::iterator it = EB_stops_list.begin();
  EXPECT_EQ(EB->GetCurrentStop(), (*it));
  EXPECT_EQ(EB_cloned->GetCurrentStop(), (*it));
  EB->NextStop();
  EB_cloned->NextStop();
  std::advance(it, 1);
  EXPECT_EQ(EB->GetCurrentStop(), (*it));
  EXPECT_EQ(EB_cloned->GetCurrentStop(), (*it));
}

TEST_F(RouteTests, GetNextStop) {
  Route * EB_cloned = EB->Clone();

  for (std::list<Stop *>::iterator it = EB_stops_list.begin();
       it != EB_stops_list.end(); it++) {
         std::advance(it, 1);
         EXPECT_EQ(EB->GetNextStop(), (*it));
         EXPECT_EQ(EB_cloned->GetNextStop(), (*it));
         EB->NextStop();
         EB_cloned->NextStop();
       }
    EXPECT_EQ(NULL, EB->GetNextStop());
    EXPECT_EQ(NULL, EB_cloned->GetNextStop());
}

TEST_F(RouteTests, GetTotalRouteDistance) {
  Route * EB_cloned = EB->Clone();
  double total_distance = 0;
  for (int i = 0; i < 5; i++) {
    total_distance += EB_distances[i];
  }
  EXPECT_EQ(EB->GetTotalRouteDistance(), total_distance);
  EXPECT_EQ(EB_cloned->GetTotalRouteDistance(), total_distance);
}

TEST_F(RouteTests, GetNextStopDistance) {
  Route * EB_cloned = EB->Clone();
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(EB->GetNextStopDistance(), EB_distances[i]);
    EB->NextStop();
  }
  EB->NextStop();
  EXPECT_EQ(EB->GetNextStopDistance(), 0);
}
