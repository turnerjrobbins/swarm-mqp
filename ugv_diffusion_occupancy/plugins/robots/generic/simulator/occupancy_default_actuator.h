#ifndef OCCUPANCY_DEFAULT_ACTUATOR_H
#define OCCUPANCY_DEFAULT_ACTUATOR_H

#include <string>
#include <map>
#include <list>

#include <argos3/core/simulator/actuator.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/utility/math/vector2.h>
#include "../control_interface/ci_occupancy_actuator.h"
#include <occupancy_medium.h>

using namespace argos;

class CPheromoneActuator : public CSimulatedActuator,
                           public CCI_PheromoneActuator {

public:
   void SetRobot(CComposableEntity& c_entity) override;
   void Init(TConfigurationNode& t_tree) override;
   void Update() override;
   void Reset() override;
   void Destroy() override;
   void SetOccupancy(Real distance, Real angle);

private:

   /** Reference to embodied entity associated with this actuator */
   CEmbodiedEntity*     m_pcEmbodiedEntity;
   /** Reference to pheromone medium associated with this actuator */
   CPheromoneMedium*    m_pCPheromoneMedium;

   std::list<CVector2> m_occupancy_list;

};

#endif