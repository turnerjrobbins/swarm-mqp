/* Include the controller definition */
#include "kheperaiv_occupancy_controller.h"
/* Function definitions for XML parsing */
#include <argos3/core/utility/configuration/argos_configuration.h>
/* 2D vector definition */
#include <argos3/core/utility/math/vector2.h>

#include <argos3/core/utility/logging/argos_log.h>

#include <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_lidar_default_sensor.h>

#include <argos3/plugins/robots/kheperaiv/control_interface/ci_kheperaiv_lidar_sensor.h>

#include <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_measures.h>

#include <math.h>

#include <argos3/core/control_interface/ci_sensor.h>

typedef std::vector<Real> TReadings;

/****************************************/
/****************************************/

CKheperaOccupancy::CKheperaOccupancy() :
   m_pcWheels(NULL),
   pcLidarSensor(NULL),
   pcOccupancy(NULL),
   m_cAlpha(10.0f),
   m_fDelta(0.5f),
   m_fWheelVelocity(2.5f),
   m_cGoStraightAngleRange(-ToRadians(m_cAlpha),
                           ToRadians(m_cAlpha)),
   m_localMap(octomap::OcTree(0.01)),
   m_localScan(octomap::Pointcloud()){}

/****************************************/
/****************************************/

void CKheperaOccupancy::Init(TConfigurationNode& t_node) {
   /*
    * Get sensor/actuator handles
    *
    * The passed string (ex. "differential_steering") corresponds to the
    * XML tag of the device whose handle we want to have. For a list of
    * allowed values, type at the command prompt:
    *
    * $ argos3 -q actuators
    *
    * to have a list of all the possible actuators, or
    *
    * $ argos3 -q sensors
    *
    * to have a list of all the possible sensors.
    *
    * NOTE: ARGoS creates and initializes actuators and sensors
    * internally, on the basis of the lists provided the configuration
    * file at the <controllers><kheperaiv_diffusion><actuators> and
    * <controllers><kheperaiv_diffusion><sensors> sections. If you forgot to
    * list a device in the XML and then you request it here, an error
    * occurs.
    */
   m_pcWheels    = GetActuator<CCI_DifferentialSteeringActuator >("differential_steering");
   pcLidarSensor = GetSensor  <CCI_KheperaIVLIDARSensor         >("kheperaiv_lidar"  );
   pcOccupancy   = GetActuator<CCI_OccupancyActuator            >("occupancy");
   m_pcProximity = GetSensor  <CCI_KheperaIVProximitySensor     >("kheperaiv_proximity" );
   m_pcPosition  = GetSensor  <CCI_PositioningSensor            >("positioning");

   /*
    * Parse the configuration file
    *
    * The user defines this part. Here, the algorithm accepts three
    * parameters and it's nice to put them in the config file so we don't
    * have to recompile if we want to try other settings.
    */
   GetNodeAttributeOrDefault(t_node, "alpha", m_cAlpha, m_cAlpha);
   m_cGoStraightAngleRange.Set(-ToRadians(m_cAlpha), ToRadians(m_cAlpha));
   GetNodeAttributeOrDefault(t_node, "delta", m_fDelta, m_fDelta);
   GetNodeAttributeOrDefault(t_node, "velocity", m_fWheelVelocity, m_fWheelVelocity);
  const TReadings& readings = pcLidarSensor->GetReadings();
  CRadians deltaAngle = KHEPERAIV_LIDAR_ANGLE_SPAN / readings.size();
  for(size_t i = 0; i < readings.size(); ++i) {
    /*push angle onto vector*/
    m_cAngleOffsets.push_back(-KHEPERAIV_LIDAR_ANGLE_SPAN * 0.5 + i * deltaAngle);
  }
}

/****************************************/
/****************************************/

void CKheperaOccupancy::ControlStep() {
  /**************************************/
  /***********DIFFUSION******************/
  /**************************************/
  /* Get readings from proximity sensor */
  const CCI_KheperaIVProximitySensor::TReadings& tProxReads = m_pcProximity->GetReadings();
  /* Sum them together */
  CVector2 cAccumulator;
  for(size_t i = 0; i < tProxReads.size(); ++i) {
    cAccumulator += CVector2(tProxReads[i].Value, tProxReads[i].Angle);
  }
  cAccumulator /= tProxReads.size();
  /* If the angle of the vector is small enough and the closest obstacle
   * is far enough, continue going straight, otherwise curve a little
   */
  CRadians cAngle = cAccumulator.Angle();
  if(m_cGoStraightAngleRange.WithinMinBoundIncludedMaxBoundIncluded(cAngle) &&
      (cAccumulator.Length() * 2.0) < m_fDelta ) {
      /* Go straight */
      m_pcWheels->SetLinearVelocity(m_fWheelVelocity, m_fWheelVelocity);
  }
  else {
    /* Turn, depending on the sign of the angle */
    if(cAngle.GetValue() > 0.0f) {
      m_pcWheels->SetLinearVelocity(m_fWheelVelocity, 0.0f);
    }
    else {
      m_pcWheels->SetLinearVelocity(0.0f, m_fWheelVelocity);
    }
  }
  /**************************************/
  /***********PointCloud*****************/
  /**************************************/
  /* Get robot position and orientation */
  CQuaternion r_angle = m_pcPosition->GetReading().Orientation;
  CRadians rob_z_rot, y, x;
  m_pcPosition->GetReading().Orientation.ToEulerAngles(rob_z_rot, y, x);
  /* Get readings from lidar */
  const TReadings& readings = pcLidarSensor->GetReadings();
  /* Ray start at (0,0,0) */
  CVector3 rayStart, rayEnd;
  /* How much to rotate rayEnd at each iteration */
  CRadians deltaAngle = KHEPERAIV_LIDAR_ANGLE_SPAN / readings.size();

  /* For each reading, update the octomap */
  for(size_t i = 0; i < readings.size(); ++i) {
    rayStart = m_pcPosition->GetReading().Position;

    /* Calculate ray end */
    /* The reading is in cm, rescaled to meters */
    rayEnd.Set(readings[i] / 100.0, 0.0, 0.0);
    /* Rotate it around Z */
    rayEnd.RotateZ(rob_z_rot +m_cAngleOffsets[i]);
    /* Translation */
    rayEnd += rayStart;

    /* insert end point into point cloud */
    m_localScan.push_back(rayEnd.GetX(), rayEnd.GetY(), rayEnd.GetZ());
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
REGISTER_CONTROLLER(CKheperaOccupancy, "kheperaiv_occupancy_controller")