#ifndef PHEROMONE_QTUSER_FUNCTIONS_H
#define PHEROMONE_QTUSER_FUNCTIONS_H

#include <argos3/plugins/simulator/visualizations/qt-opengl/qtopengl_user_functions.h>
#include <occupancy_medium.h>
#include <argos3/core/utility/math/quaternion.h>
#include <argos3/core/utility/math/vector2.h>

//#include <argos3/plugins/loop_functions/diffusion_visualizer/diffusion_visualizer.h>

using namespace argos;

class COccupancyQTUserFunctions : public CQTOpenGLUserFunctions {

public:

    COccupancyQTUserFunctions();

    void Init(TConfigurationNode& t_tree) override;

    void DrawInWorld() override;

private:
    bool m_bDrawDiffusion;
    Real m_fGridSize;
    CPheromoneMedium& m_cPheraMed;
    std::vector<CVector2> m_cSquarePoints;
    CQuaternion m_cOrientation;

};

#endif