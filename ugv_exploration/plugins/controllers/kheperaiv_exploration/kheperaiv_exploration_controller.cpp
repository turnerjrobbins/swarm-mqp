/* Include the controller definition */
#include "kheperaiv_exploration_controller.h"
#include <octomap_manager.h>
/* Function definitions for XML parsing */
#include <argos3/core/utility/configuration/argos_configuration.h>
/* 2D vector definition */
#include <argos3/core/utility/math/vector2.h>
/* Definition of ultrasound implementation */
#include <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_ultrasound_default_sensor.h>
/* Definition of ultrasound interface */
#include <argos3/plugins/robots/kheperaiv/control_interface/ci_kheperaiv_ultrasound_sensor.h>
/**/
#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_measures.h>
#include <math.h>
#include <argos3/core/control_interface/ci_sensor.h>

#include <argos3/core/control_interface/ci_sensor.h>
#include <argos3/core/utility/math/angles.h>



typedef CCI_KheperaIVUltrasoundSensor::TReadings TReadings;
typedef struct CCI_KheperaIVUltrasoundSensor::SReading SReading;
/****************************************/
/****************************************/

CKheperaExploration::CKheperaExploration() :
  m_pcWheels(NULL),
  m_pcUltrasoundSensor(NULL),
  m_cAlpha(10.0f),
  m_fDelta(0.5f),
  m_fWheelVelocity(2.5f),
  m_cGoStraightAngleRange(-ToRadians(m_cAlpha),
                         ToRadians(m_cAlpha)),
  m_localMap(octomap::OcTree(OCTCELLSIZE)),
  m_localScan(octomap::Pointcloud()),
  m_state(UGV_State::SCAN){}

/****************************************/
/****************************************/

void CKheperaExploration::Init(TConfigurationNode& t_node) {
  m_pcWheels    = GetActuator<CCI_DifferentialSteeringActuator >("differential_steering");
  m_pcUltrasoundSensor = GetSensor  <CCI_KheperaIVUltrasoundSensor         >("kheperaiv_ultrasound"  );
  m_pcProximity = GetSensor  <CCI_KheperaIVProximitySensor     >("kheperaiv_proximity" );
  m_pcPosition  = GetSensor  <CCI_PositioningSensor            >("positioning");

  GetNodeAttributeOrDefault(t_node, "alpha", m_cAlpha, m_cAlpha);
  m_cGoStraightAngleRange.Set(-ToRadians(m_cAlpha), ToRadians(m_cAlpha));
  GetNodeAttributeOrDefault(t_node, "delta", m_fDelta, m_fDelta);
  GetNodeAttributeOrDefault(t_node, "velocity", m_fWheelVelocity, m_fWheelVelocity);
}

/****************************************/
/****************************************/

void CKheperaExploration::ControlStep() {
  switch(m_state) {
    case UGV_State::SCAN:
      break;
    default:
      break;
  }
}

/****************************************/
/****************************************/

/*
 * This statement notifies ARGoS of the existence of the controller.
 * It binds the class passed as first argument to the string passed as
 * second argument.
 * The string is then usable in the configuration file to refer to this
 * controller.
 * When ARGoS reads that string in the configuration file, it knows which
 * controller class to instantiate.
 * See also the configuration files for an example of how this is used.
 */
REGISTER_CONTROLLER(CKheperaExploration, "kheperaiv_exploration_controller")