#include "occupancy_visualizer.h"

/****************************************/
/****************************************/

COccupancyQTUserFunctions::COccupancyQTUserFunctions() :
   m_cPheraMed(CSimulator::GetInstance().GetMedium<CPheromoneMedium>("occupancy_medium"))
   {
    // get the grid size and calculate the square corners
    m_fGridSize = m_cPheraMed.GetCellSize();
    m_cSquarePoints.resize(4);
    m_cSquarePoints[1].Set(m_fGridSize,0);
    m_cSquarePoints[2].Set(m_fGridSize,m_fGridSize);
    m_cSquarePoints[3].Set(0,m_fGridSize);

    // set the orienation for the squares
    m_cOrientation.FromAngleAxis(CRadians::ZERO, CVector3::Z);
}

/****************************************/
/****************************************/

void COccupancyQTUserFunctions::Init(TConfigurationNode& t_tree){
    m_bDrawDiffusion = false;
}

/****************************************/
/****************************************/

void COccupancyQTUserFunctions::DrawInWorld() {
    const CPheromoneMedium::PheromoneMap& cPheromoneCells = m_cPheraMed.GetPheromoneMap();
    // offset is so the square is not in the same space as the floor 
    CVector3 cOffset(0,0,0.1);
    /* Go through all the cells and draw them */
    for(const auto &pair: cPheromoneCells){
        CVector3 grid_3d = CVector3(pair.first.GetX()*m_fGridSize, pair.first.GetY()*m_fGridSize, 0.1);
        DrawPolygon(grid_3d,
                    m_cOrientation, 
                    m_cSquarePoints,
                    CColor(pair.second,0,0));
    }
}

/****************************************/
/****************************************/

REGISTER_QTOPENGL_USER_FUNCTIONS(COccupancyQTUserFunctions, "occupancy_qtuser_functions")