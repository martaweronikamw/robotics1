
#include "Aria.h"
#include <math.h>
#include <iostream>  
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

using namespace std;
int main(int argc, char **argv)
{
	ArRobot robot;
	ArSonarDevice sonar;

	robot.addRangeDevice(&sonar);

	Aria::init();
	
	ArSimpleConnector connector(&argc,argv);

	if (!connector.connectRobot(&robot)){
		printf("Could not connect to robot... exiting\n");
		Aria::shutdown();
		Aria::exit(1);
	}

	robot.comInt(ArCommands::ENABLE, 1);

	robot.runAsync(false);

	// Start of controling

	// 1. Lock the robot
	robot.lock();

	// 2. Write your control code here, 
    // part E code
    // initial position
   
    //ArUtil::sleep(5000);

    // split string
    
    
    
 
	robot.setVel(0);

	// 3. Unlock the robot
	robot.unlock();

    // string input
    string stringinput;
    char space = ' ';
    string testarr[3];
    string teststring;
    int counter = 0;
    printf("Input coordinates in the format x y theta.");
    getline(cin, stringinput);
    stringstream test(stringinput);
    while (getline(test, teststring, space))
    {
        testarr[counter] = teststring;
        counter = counter+1;
    }
    
    cout << "CONTINUE ";

    double startx = 5090;
    double starty = 3580; 
    double startangle = 3093.97;
    // where we want to end up
    double stopx = atof(testarr[0].c_str());
    double stopy = atof(testarr[1].c_str());
    double stopangle = atof(testarr[2].c_str());

    printf("input: %f %f %f/n", stopx, stopy, stopangle);

    // displacement
    double distx = stopx - startx;
    double disty = stopy - starty;
    double euclidean_dist = sqrt(pow(distx,2) + pow(disty,2));


    // angle change
    double radians = atan2(disty, distx);
    double degrees = (radians*180/M_PI);

    //input of the initial position
    ArPose startpose = ArPose(startx, starty, startangle);
    robot.moveTo(startpose);

    // moving the robot
    robot.setHeading(degrees);
    ArUtil::sleep(10000);
    robot.move(euclidean_dist);
    ArUtil::sleep(10000);
    robot.setHeading(stopangle);

	// 4. Sleep a while and let the robot move
	while(true){
		printf("%f %f %f\n", robot.getX(), robot.getY(), robot.getTh());
		ArUtil::sleep(300);
	}

	// End of controling


	Aria::shutdown();

	Aria::exit(0);
}