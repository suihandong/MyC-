/**
 * @file passenger_UT.cc
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
#include "../src/passenger.h"

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <fstream>

/******************************************************
* TEST FEATURE SetUp
*******************************************************/

class PassengerTests : public ::testing::Test {
 protected:
    Passenger* passenger;
    std::vector<Passenger *> pass;

    virtual void SetUp() {
      passenger = new Passenger();

      pass.push_back(new Passenger(33, "Zoe"));
      pass.push_back(new Passenger(42, "Kaylee"));
      pass.push_back(new Passenger(50, "Wash"));
      pass.push_back(new Passenger(10, "Mal"));
      pass.push_back(new Passenger(23, "Jayne"));
    }

    virtual void TearDown() {
      delete passenger;
    }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(PassengerTests, Constructor) {
    EXPECT_EQ(passenger->IsOnBus(), false);
    passenger->GetOnBus();
    EXPECT_EQ(passenger->IsOnBus(), true);
}


// TEST_F(PassengerTests, GetTotalWait){
// int total_wait = passenger->wait_at_stop_ + passenger->time_on_bus_;
// EXPECT_EQ(passenger->GetTotalWait(),total_wait);
// }

TEST_F(PassengerTests, IsOnBus) {
  EXPECT_EQ(passenger->IsOnBus(), false);
  passenger->GetOnBus();
  EXPECT_EQ(passenger->IsOnBus(), true);
}

TEST_F(PassengerTests, GetTotalWait) {
  int time = 0;
  int wait_at_stop_0 = 0;
  int wait_at_stop_1 = 0;
  int wait_at_stop_2 = 0;
  int time_on_bus_0 = 0;
  int time_on_bus_1 = 0;
  int time_on_bus_2 = 0;

  while (time < 20) {
    if (time == 17) {
      pass[0]->GetOnBus();
      time_on_bus_0 = 1;
    } else if (time == 8) {
      pass[1]->GetOnBus();
      time_on_bus_1 = 1;
    } else if (time == 15) {
      pass[2]->GetOnBus();
      time_on_bus_2 = 1;
    }
    if (pass[0]->IsOnBus()) {
      time_on_bus_0++;
    } else {
      wait_at_stop_0++;
    }
    if (pass[1]->IsOnBus()) {
      time_on_bus_1++;
    } else {
      wait_at_stop_1++;
    }
    if (pass[2]->IsOnBus()) {
      time_on_bus_2++;
    } else {
      wait_at_stop_2++;
    }

    for (std::vector<Passenger *>::iterator it = pass.begin();
        it != pass.end(); it++) {
      if ((*it)->GetDestination() != time) {
        (*it)->Update();
      } else {
        Passenger * departing_passenger = *it;
        departing_passenger->Report();

        // When removing the passenger, the iterator gets incremented to the
        //  next element.
        // We need to push it back so that the for loop increment places the
        // iterator at the correct next element.
        it = pass.erase(it);
        it--;
        delete departing_passenger;
      }
    }

    time++;
  }

  EXPECT_EQ(pass[0]->GetTotalWait(), time_on_bus_0+wait_at_stop_0);
  EXPECT_EQ(pass[1]->GetTotalWait(), time_on_bus_1+wait_at_stop_1);
  EXPECT_EQ(pass[2]->GetTotalWait(), time_on_bus_2+wait_at_stop_2);
}

TEST_F(PassengerTests, GetDestination) {
  EXPECT_EQ(pass[0]->GetDestination(), 33);
  EXPECT_EQ(pass[0]->GetDestination(), 50);
  EXPECT_EQ(pass[1]->GetDestination(), 42);
  EXPECT_EQ(pass[2]->GetDestination(), 50);
  EXPECT_EQ(pass[3]->GetDestination(), 10);
  EXPECT_EQ(pass[4]->GetDestination(), 23);
}

TEST_F(PassengerTests, Report) {
  std::vector<Passenger *> pass;

  pass.push_back(new Passenger(50, "Wash"));
  pass.push_back(new Passenger(10, "Mal"));
  pass.push_back(new Passenger(23, "Jayne"));

  int time = 0;
  int wait_at_stop_0 = 0;
  int wait_at_stop_1 = 0;
  int wait_at_stop_2 = 0;
  int time_on_bus_0 = 0;
  int time_on_bus_1 = 0;
  int time_on_bus_2 = 0;

  while (time < 20) {
    if (time == 17) {
      pass[0]->GetOnBus();
      time_on_bus_0 = 1;
    } else if (time == 8) {
      pass[1]->GetOnBus();
      time_on_bus_1 = 1;
    } else if (time == 15) {
      pass[2]->GetOnBus();
      time_on_bus_2 = 1;
    }
    if (pass[0]->IsOnBus()) {
      time_on_bus_0++;
    } else {
      wait_at_stop_0++;
    }
    if (pass[1]->IsOnBus()) {
      time_on_bus_1++;
    } else {
      wait_at_stop_1++;
    }
    if (pass[2]->IsOnBus()) {
      time_on_bus_2++;
    } else {
      wait_at_stop_2++;
    }

    for (std::vector<Passenger *>::iterator it = pass.begin();
        it != pass.end(); it++) {
      if ((*it)->GetDestination() != time) {
        (*it)->Update();
      } else {
        Passenger * departing_passenger = *it;
        departing_passenger->Report();

        // When removing the passenger, the iterator gets incremented to the
        //  next element.
        // We need to push it back so that the for loop increment places the
        // iterator at the correct next element.
        it = pass.erase(it);
        it--;
        delete departing_passenger;
      }
    }

    time++;
  }


  std::ofstream myfile;
  myfile.open("passenger_report.txt");
  pass[0]->Report(myfile);
  myfile.close();

  int total_wait_0 = time_on_bus_0 + wait_at_stop_0;
  std::string str0 = "Name: Wash";
  std::string str1 = "Destination: 50";
  std::string str2 = "Total Wait: " + std::to_string(total_wait_0);
  std::string str3 = "\tWait at Stop: " + std::to_string(wait_at_stop_0);
  std::string str4 = "\tTime on bus: " + std::to_string(time_on_bus_0);
  std::string error = "error";
  std::string STR;
  std::ifstream infile;
  infile.open("passenger_report.txt");
  int idx = 0;
  while (!infile.eof()) {
    std::getline(infile, STR);
    if (idx == 0) {
      EXPECT_EQ(STR, str0);
      EXPECT_EQ(STR, error);
    } else if (idx == 1) {
      EXPECT_EQ(STR, str1);
    } else if (idx == 2) {
      EXPECT_EQ(STR, str2);
    } else if (idx == 3) {
      EXPECT_EQ(STR, str3);
    } else if (idx == 4) {
      EXPECT_EQ(STR, str4);
    }
    idx++;
  }
  myfile.close();
}
