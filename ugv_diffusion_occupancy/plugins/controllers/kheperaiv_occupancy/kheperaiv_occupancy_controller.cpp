/* Include the controller definition */
#include "kheperaiv_occupancy_controller.h"
/* Function definitions for XML parsing */
#include <argos3/core/utility/configuration/argos_configuration.h>
/* 2D vector definition */
#include <argos3/core/utility/math/vector2.h>

#include <argos3/core/utility/logging/argos_log.h>

#include <math.h>

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
   m_localMap(octomap::OcTree(0.01)) {}

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
}

/****************************************/
/****************************************/

void CKheperaOccupancy::ControlStep() {
  /* get position */
  m_position = m_pcPosition->GetReading();

   /* First, get all of the readings from the lidar sensor */
  CCI_KheperaIVLIDARSensor::TReadings lidar_readings = pcLidarSensor->GetReadings();
  Real dist = 0;
  // if(lidar_readings.size() % 2 ==1) {
  //   dist =  lidar_readings[ceil(lidar_readings.size() / 2.0)];
  //   if((dist / .01) < .5) {
  //     pcOccupancy->SetOccupancy(dist / 0.01);

  //   }
    
  // }else {
  //   LOGERR << "No front-facing lidar reading, use an odd number of rays.\n";
  //   std::exit(1);
  // }
    double angleOffset = -210.0 / 2.0;
    double angleIncrement = 210 / lidar_readings.size();
    CVector3 r_loc = m_pcPosition->GetReading().Position;
    octomap::point3d startp = octomap::point3d(r_loc.GetX(), r_loc.GetY(), r_loc.GetZ());
    CQuaternion r_angle = m_pcPosition->GetReading().Orientation;
    CRadians rob_z_rot, x, y;
    r_angle.ToEulerAngles(rob_z_rot, y, x);
    LOGERR << "Robot Global Pos: " << r_loc << std::endl;
    for(Real bad_dist: lidar_readings) {
      if(bad_dist == 0.0f) {
        angleOffset += angleIncrement;
        continue;
      }
      Real dist = bad_dist * 100.0f;
      CRadians sensor_offset;
      sensor_offset.FromValueInDegrees(angleOffset);
      //create a CVector3 with dist as it's length, and then rotate it to the global frame
      CVector3 reading = CVector3(dist, 0.0, 0.0);
      CRadians glob_rot = rob_z_rot + sensor_offset;
      reading.RotateZ(glob_rot);
      //add that to the robot's position
      CVector3 endp = CVector3(reading + r_loc);
      octomap::point3d octoEndp = octomap::point3d(endp.GetX(), endp.GetY(), endp.GetZ());
      m_localMap.insertRay(startp, octoEndp);
      angleOffset += angleIncrement;
    }

  /**************************************/
  /***********DIFFUSION******************/
  /**************************************/
  /* Get readings from proximity sensor */
  // const CCI_KheperaIVProximitySensor::TReadings& tProxReads = m_pcProximity->GetReadings();
  // /* Sum them together */
  // CVector2 cAccumulator;
  // for(size_t i = 0; i < tProxReads.size(); ++i) {
  //   cAccumulator += CVector2(tProxReads[i].Value, tProxReads[i].Angle);
  // }
  // cAccumulator /= tProxReads.size();
  // /* If the angle of the vector is small enough and the closest obstacle
  //  * is far enough, continue going straight, otherwise curve a little
  //  */
  // CRadians cAngle = cAccumulator.Angle();
  // if(m_cGoStraightAngleRange.WithinMinBoundIncludedMaxBoundIncluded(cAngle) &&
  //     (cAccumulator.Length() * 2.0) < m_fDelta ) {
  //     /* Go straight */
  //     m_pcWheels->SetLinearVelocity(m_fWheelVelocity, m_fWheelVelocity);
  // }
  // else {
  //   /* Turn, depending on the sign of the angle */
  //   if(cAngle.GetValue() > 0.0f) {
  //     m_pcWheels->SetLinearVelocity(m_fWheelVelocity, 0.0f);
  //   }
  //   else {
  //     m_pcWheels->SetLinearVelocity(0.0f, m_fWheelVelocity);
  //   }
  // }
  m_pcWheels->SetLinearVelocity(0.0f, m_fWheelVelocity / 2.0f);
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