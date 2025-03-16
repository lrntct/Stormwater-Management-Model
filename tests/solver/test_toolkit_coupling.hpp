/*
 *   fixtures.hpp
 *
 *   Created: 04/16/2018
 *   Author: Bryant E. McDonnell
 *           EmNet LLC
 *
 *   Fixtures for Unit testing for SWMM-ToolkitAPI using Boost Test.
 
 Fixtures are used for building up and breaking down a simulation. 
 They simplify the workflow and help reduce duplicative code.
 
 
* TABLE OF CONTENTS AND STRUCTURE

  ->  Defining the different testing fixtures
 */
 // test_toolkit_coupling.hpp
#ifndef TEST_TOOLKIT_COUPLING_HPP
#define TEST_TOOLKIT_COUPLING_HPP

// Include standard libraries
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <math.h>

// Include SWMM libraries
#include "swmm5.h"
#include "toolkit.h"

// Include Boost test, but NOT the included version with main
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

// Test input file definitions
#define DATA_PATH_INP "test8b_drainage_ponding.inp"
#define DATA_PATH_RPT "test8b_drainage_ponding.rpt"
#define DATA_PATH_OUT "test8b_drainage_ponding.out"

// using namespace std;

// Defining Fixtures

/* Fixture Open Close
 1. Opens Model
 *. testing interactions
 2. Closes Model 
*/
struct FixtureOpenClose{
    FixtureOpenClose() {
        swmm_open((char *)DATA_PATH_INP, (char *)DATA_PATH_RPT, (char *)DATA_PATH_OUT);
    }
    ~FixtureOpenClose() {
        swmm_close();
    }
};

/* Fixture Before Start
 1. Opens Model
 *. can choose to start simulation 
 2. Starts Simulation
 3. Runs Simlation
 4. Ends simulation
 5. Closes Model 
*/
struct FixtureBeforeStart{
    FixtureBeforeStart() {
        swmm_open((char *)DATA_PATH_INP, (char *)DATA_PATH_RPT, (char *)DATA_PATH_OUT);
    }
    ~FixtureBeforeStart() {
        swmm_start(0);
        int error;
        double elapsedTime = 0.0;
        do
        {
            error = swmm_step(&elapsedTime);
        }while (elapsedTime != 0 && !error);
        if (!error) swmm_end();
        if (!error) swmm_report();

        swmm_close();
    }
};

/* Fixture Before Step
 1. Opens Model
 2. Starts Simulation
 *. can choose iterate over simulation if simulation started, 
    must call swmm_end() 
 3. Closes Model 
*/
struct FixtureBeforeStep{
    FixtureBeforeStep() {
        swmm_open((char *)DATA_PATH_INP, (char *)DATA_PATH_RPT, (char *)DATA_PATH_OUT);
        swmm_start(0);
    }
    ~FixtureBeforeStep() {
        swmm_close();
    }
};

/* Fixture Before Step
 1. Opens Model
 2. Starts Simulation
 *. can choose iterate over simulation if simulation started, 
    must call swmm_end() 
 3. Closes Model 
*/
/* struct FixtureBeforeStep_RTK{
    FixtureBeforeStep_RTK() {
        swmm_open((char *)DATA_PATH_INP_RTK, (char *)DATA_PATH_RPT_RTK, (char *)DATA_PATH_OUT_RTK);
        swmm_start(0);
    }
    ~FixtureBeforeStep_RTK() {
        swmm_close();
    }
}; */

/* Fixture Before End
 1. Opens Model
 2. Starts Simulation
 3. Runs Simlation
 * can choose to interact after simulation end
 4. Ends simulation
 5. Closes Model 
*/
struct FixtureBeforeEnd{
    FixtureBeforeEnd() {
        swmm_open((char *)DATA_PATH_INP, (char *)DATA_PATH_RPT, (char *)DATA_PATH_OUT);
        swmm_start(0);

        int error;
        double elapsedTime = 0.0;
        do
        {
            error = swmm_step(&elapsedTime);
        }while (elapsedTime != 0 && !error);
        BOOST_CHECK_EQUAL(0, error);
    }
    ~FixtureBeforeEnd() {
        swmm_end();
        swmm_close();
    }
};

/* Fixture Before Close
 1. Opens Model
 2. Starts Simulation
 3. Runs Simlation
 4. Ends simulation
 * can choose to interact after simulation end
 5. Closes Model 
*/
struct FixtureBeforeClose{
    FixtureBeforeClose() {
        swmm_open((char *)DATA_PATH_INP, (char *)DATA_PATH_RPT, (char *)DATA_PATH_OUT);
        swmm_start(0);

        int error;
        double elapsedTime = 0.0;
        do
        {
            error = swmm_step(&elapsedTime);
        }while (elapsedTime != 0 && !error);
        BOOST_CHECK_EQUAL(0, error);
        swmm_end();
    }
    ~FixtureBeforeClose() {
        swmm_close();
    }
};

#endif // TEST_TOOLKIT_COUPLING_HPP
