
#include "Aria.h"


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

  // Used to perform actions when keyboard keys are pressed
  ArKeyHandler keyHandler;
  Aria::setKeyHandler(&keyHandler);
  
  // move
  ArFunctor1C<ArRobot, double> speedup(robot, &ArRobot::setVel, 200);
  keyHandler.addKeyHandler(ArKeyHandler::UP, &speedup);

  //stop
  ArFunctor1C<ArRobot, double> stopmove(robot, &ArRobot::setVel, 0);
  keyHandler.addKeyHandler(ArKeyHandler::DOWN, &stopmove);

  // turn left
  ArFunctor1C<ArRobot, double> turnl(robot, &ArRobot::setRotVel, 50);
  keyHandler.addKeyHandler(ArKeyHandler::LEFT, &turnl);

  // turn right
  ArFunctor1C<ArRobot, double> turnr(robot, &ArRobot::setRotVel, -50);
  keyHandler.addKeyHandler(ArKeyHandler::RIGHT, &turnr);

  // stop turning
  ArFunctor1C<ArRobot, double> turns(robot, &ArRobot::setRotVel, 0);
  keyHandler.addKeyHandler(ArKeyHandler::SPACE, &turns);

  // ArRobot contains an exit action for the Escape key. It also 
  // stores a pointer to the keyhandler so that other parts of the program can
  // use the same keyhandler.
  robot.attachKeyHandler(&keyHandler);
  printf("You may press escape to exit\n");

	// TODO: control the robot

	// Start of controling

	// 1. Lock the robot
	robot.lock();

	// 2. Write your control code here, 
    


	//    e.g. robot.setVel(150);  
	robot.setVel(0);

	// 3. Unlock the robot
	robot.unlock();

	// 4. Sleep a while and let the robot move
	while(true){
		printf("%f %f %f\n", robot.getX(), robot.getY(), robot.getTh());
		ArUtil::sleep(300);
	}

	// End of controling


	Aria::shutdown();

	Aria::exit(0);
}