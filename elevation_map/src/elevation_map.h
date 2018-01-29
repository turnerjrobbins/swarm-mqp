#ifndef ELEVATION_MAP_H
#define ELEVATION_MAP_H

// Author: Turner Robbins
// Description: Simple implementation of an elevation map.
class ElevationMap {
public:
	ElevationMap() : m_map(0) {

	}
	ElevationMap(int x_size, int y_size) : 
	m_x(x_size), m_y(y_size) {
		m_map = new double*[x_size];
		for(int i=0; i < m_x; i++) {
			m_map[i] = new double[y_size];
		}
	}

	void setCell(int x, int y, double val) {
		m_map[x][y] = val;
	}

	double getCell(int x, int y) {
		return m_map[x][y];
	}

private:

	double **m_map;
	int m_x;
	int m_y;
};


#endif