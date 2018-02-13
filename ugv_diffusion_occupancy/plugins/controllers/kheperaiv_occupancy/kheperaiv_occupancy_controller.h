#ifndef KHEPERAIV_OCCUPANCY_CONTROLLER_H
#define KHEPERAIV_OCCUPANCY_CONTROLLER_H
//INCLUDE

#include <argos3/core/control_interface/ci_controller.h>
/* Definition of the differential steering actuator */
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>

/* Definition of ultrasound implementation */
#include <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_ultrasound_default_sensor.h>

/* Definition of ultrasound interface */
#include <argos3/plugins/robots/kheperaiv/control_interface/ci_kheperaiv_ultrasound_sensor.h>

/* Definition of interface for occupancy actuator */
#include <ci_occupancy_actuator.h>
/* Definition of the control interface for the position sensor and sreading */
#include <argos3/plugins/robots/generic/control_interface/ci_positioning_sensor.h>

#include <argos3/plugins/robots/kheperaiv/control_interface/ci_kheperaiv_proximity_sensor.h>

/*octomap includes for OcTree & various octomap functions*/
#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <octomap/Pointcloud.h>

//DEFINITIONS
using namespace argos;

class CKheperaOccupancy : public CCI_Controller {
//Define public members
public:
	/*Class constructor*/
	CKheperaOccupancy();

	/*Class destructor*/
	virtual ~CKheperaOccupancy(){}

	/*
    * This function initializes the controller.
    * The 't_node' variable points to the <parameters> section in the XML
    * file in the <controllers><footbot_diffusion_controller> section.
    */
   virtual void Init(TConfigurationNode& t_node);

   /*
    * This function is called once every time step.
    * The length of the time step is set in the XML file.
    */
   virtual void ControlStep();

   /*
    * This function resets the controller to its state right after the
    * Init().
    * It is called when you press the reset button in the GUI.
    * In this example controller there is no need for resetting anything,
    * so the function could have been omitted. It's here just for
    * completeness.
    */
   virtual void Reset() {}

   /*
    * Called to cleanup what done by Init() when the experiment finishes.
    * In this example controller there is no need for clean anything up,
    * so the function could have been omitted. It's here just for
    * completeness.
    */
  virtual void Destroy() {
  }

  virtual octomap::Pointcloud &getLocalScan() { 
    return m_localScan;
  }

  virtual void clearLocalScan() {
    m_localScan.clear();
  }


//Define private members
private:
	/* pointer to the lidar sensor	*/
	CCI_KheperaIVUltrasoundSensor* m_pcUltrasoundSensor;
	/* pointer to the differential steering actuator */
	CCI_DifferentialSteeringActuator* m_pcWheels;
	/* pointer to the occupancy actuator */
	CCI_OccupancyActuator* pcOccupancy;
  /* pointer to the proximity sensor */
  CCI_KheperaIVProximitySensor* m_pcProximity;
  /* pointer to the position sensor */
  CCI_PositioningSensor* m_pcPosition;

	 /*
    * The following variables are used as parameters for the
    * algorithm. You can set their value in the <parameters> section
    * of the XML configuration file, under the
    * <controllers><footbot_diffusion_controller> section.
    */

   /* Maximum tolerance for the angle between
    * the robot heading direction and
    * the closest obstacle detected. */
   CDegrees m_cAlpha;
   /* Maximum tolerance for the proximity reading between
    * the robot and the closest obstacle.
    * The proximity reading is 0 when nothing is detected
    * and grows exponentially to 1 when the obstacle is
    * touching the robot.
    */
   Real m_fDelta;
   /* Wheel speed. */
   Real m_fWheelVelocity;
   /* Angle tolerance range to go straight.
    * It is set to [-alpha,alpha]. */
   CRange<CRadians> m_cGoStraightAngleRange;
   /* octomap */
   octomap::OcTree m_localMap;
   /* current position */
   CCI_PositioningSensor::SReading m_position;

   std::vector<CRadians> m_cAngleOffsets;

   octomap::Pointcloud m_localScan;

};
#endif