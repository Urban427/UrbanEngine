#pragma once
#include <Vector2.h>
#include <Rect.h>
#include <Mesh.h>

namespace Shapes {

class Polygon {
public:
	Polygon() { };
	Polygon(std::vector<Vector2>&& points): points(points)  { init(std::move(points)); };
	Polygon(std::vector<Vector2>&& points, std::vector<std::pair<int, int>>&& edges): points(points), edges(edges)  { };
	Polygon(const std::vector<Vector2>& points): points(points) { init(std::move(this->points)); }
	Polygon(const Polygon& polygon): points(polygon.points), edges(polygon.edges) { }
	Polygon(Polygon&& polygon): points(polygon.points), edges(polygon.edges) { }
	Polygon(const Rect& rect);
	
	void init(std::vector<Vector2>&& points);
	Rect AABB();
	bool checkPointInside(const Vector2& point);
	Mesh convertToMesh();
	void rotate(float angle);
	void sortEdges();
	void subdivide(int segments);

	inline std::vector<Vector2>&		getPoints() 					{ return points; }
	inline int 							edgeSize() 						{ return edges.size(); }
	inline std::pair<int, int> 			getEdgeIndicies(int i) 			{ return edges[i]; } 
	inline std::pair<Vector2, Vector2> 	getEdge(int i) 					{ return std::pair(points[edges[i].first], points[edges[i].second]); } 
	inline void 						addPoint(const Vector2& point) 	{  points.push_back(point); }
	inline unsigned int 				size() 							{ return points.size(); };
public:
	inline Polygon& operator=(const Polygon& polygon) 		{ points = polygon.points; edges = polygon.edges; return *this;}
	inline Polygon& operator=(const Polygon&& polygon)  	{ points = polygon.points; edges = polygon.edges; return *this;}
	inline Vector2& operator[](const unsigned int index) 	{ return points[index]; }
	inline Polygon& operator+(const Vector2 point) {
		for(int i = 0; i < points.size(); i++) {
			points[i] += point;
		}
		return *this;
	}
private:
	std::vector<Vector2> points;
	std::vector<std::pair<int, int>> edges;
};

Polygon generateRandomConvexHull(unsigned int n);
Polygon generatePlatonicSolid(int n, float radius, Vector2 center, float angleOffset);
Polygon convexHull(std::vector<Vector2>& points);
Polygon generateRect(float width, float height);
Polygon generateRandomRect(float scale, float ratio);
bool PointInQuadXZ(float x, float z, Vector3 quad[4]);
bool unionPolygons(Shapes::Polygon& out, Shapes::Polygon& a, Shapes::Polygon& b);

unsigned char getIntersectionPoints(std::vector<Vector2>& intersectionPoints, unsigned char& intersectionsCounter, Shapes::Polygon& a, Shapes::Polygon& b);
unsigned char BooleanOperation(std::vector<Shapes::Polygon>& polygons, char booleanOperation=0);
};
