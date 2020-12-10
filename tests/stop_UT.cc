/**
 * @file stop_UT.cc
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

#include "../src/stop.h"
#include "../src/passenger.h"
#include "../src/route.h"
#include "../src/bus.h"

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class StopTests : public ::testing::Test {
 protected:
    Stop * stop;
    std::vector<Passenger *> pass;
    virtual void SetUp() {
      int id = 10;
      double longitude = 44.973723;
      double latitude = -93.235365;
      stop = new Stop(id, longitude, latitude);

      pass.push_back(new Passenger(33, "Zoe"));
      pass.push_back(new Passenger(42, "Kaylee"));
      pass.push_back(new Passenger(50, "Wash"));
      pass.push_back(new Passenger(10, "Mal"));
      pass.push_back(new Passenger(23, "Jayne"));
    }

    virtual void TearDown() {
      delete stop;
    }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(StopTests, Constructor) {
  int id = 10;
  double longitude = 44.973723;
  double latitude = -93.235365;
  stop = new Stop(id, longitude, latitude);
  EXPECT_EQ(stop->GetId(), id);
  EXPECT_EQ(stop->GetLongitude(), longitude);
  EXPECT_EQ(stop->GetLatitude(), latitude);
  EXPECT_EQ(stop->GetName(), std::to_string(id));
}

TEST_F(StopTests, Passengers) {
  Passenger * pass = new Passenger();
  Bus * bus = new Bus("mybus", NULL, NULL, 60, 1);
  EXPECT_EQ(stop->GetPassengersSize(), 0);
  EXPECT_EQ(stop->AddPassengers(pass), 0);
  EXPECT_EQ(stop->GetPassengersSize(), 1);
  EXPECT_EQ(stop->LoadPassengers(bus), 1);
}

TEST_F(StopTests, Report) {
  Bus * bus = new Bus("mybus", NULL, NULL, 60, 1);
  for (std::vector<Passenger *>::iterator it = pass.begin(); it != pass.end();
      it++) {
        stop->AddPassengers(*it);
      }
  EXPECT_EQ(stop->GetPassengersSize(), 5);
  stop->LoadPassengers(bus);
  stop->Update();

  std::ofstream myfile;
  myfile.open("stop_report.txt");
  stop->Report(myfile);
  myfile.close();

  std::string str0 = "ID: " + std::to_string(10);
  std::string str1 = "Passenger waiting: " + std::to_string(0);
  std::string error = "error";
  std::string STR;
  std::ifstream infile;
  infile.open("stop_report.txt");
  int idx = 0;
  while (!infile.eof()) {
    std::getline(infile, STR);
    if (idx == 0) {
      EXPECT_EQ(STR, str0);
      EXPECT_EQ(STR, error);
    } else if (idx == 1) {
      EXPECT_EQ(STR, str1);
    }
    idx++;
  }
  myfile.close();
}
