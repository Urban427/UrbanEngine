#include "Polygon.h"
#include "Random.h"
#include "Triangulation.h"
#include <algorithm>
#include <math.h>
namespace Shapes {

Polygon::Polygon(const Rect& rect) {
	points.resize(4);
	points[0] = {rect.left,  rect.top};
	points[1] = {rect.left,  rect.bottom};
	points[2] = {rect.right, rect.bottom};
	points[3] = {rect.right, rect.top};
	init(std::move(points));
}


void Polygon::init(std::vector<Vector2>&& points) {
	int n = points.size();
	int size = n;
	edges.resize(n);
	for(int i = 0; i < n; ++i) {
		edges[i] = { i, (i + 1) % n }; 
	}	
}

void Polygon::rotate(float angle) {
	for(int i = 0; i < points.size(); i++) {
		points[i].rotate(angle);
	}
}

bool Polygon::checkPointInside(const Vector2& point) {
	int crossings = 0;
	for(int i = 0; i < edges.size(); i++) {
		Vector2 a = points[edges[i].first];
		Vector2 b = points[edges[i].second];
		
		if((a.y > point.y) != (b.y > point.y)) {
			float intersectionX = a.x + (b.x - a.x) * (point.y - a.y) / (b.y - a.y);
			if(point.x < intersectionX) ++crossings;
		}
	}
	return crossings & 0x1;
}

Polygon generatePlatonicSolid(int n, float radius, Vector2 center, float angleOffset) {
	std::vector<Vector2> points;
    points.resize(n);
    float angle = angleOffset;
    float delta_angle = 2 * 3.14159265f / n;

    for (int i = 0; i < n; i++) {
        points[i] = center + radius * Vector2(sin(angle), -cos(angle));
        angle += delta_angle;
    }
    return Polygon(std::move(points));
}


Rect Polygon::AABB() {
	Vector2 minBox{(float)0x7F7FFFFF, (float)0x7F7FFFFF};
	Vector2 maxBox{0, 0};
	for(int i = 0; i < points.size(); i++) {
		if(points[i].x < minBox.x) {
			minBox.x = points[i].x;
		}
		else if(points[i].x > maxBox.x) {
			maxBox.x = points[i].x;
		}
		
		if(points[i].y < minBox.y) {
			minBox.y = points[i].y;
		}
		else if(points[i].y > maxBox.y) {
			maxBox.y = points[i].y;
		}
	}
	return {minBox.x, minBox.y, maxBox.x, maxBox.y};
}

Polygon convexHull(std::vector<Vector2>& points) {
	if(points.size() < 4) {return Polygon(std::move(points));}
	
	std::sort(points.begin(), points.end());
	
	std::vector<Vector2> a;
	int n = points.size();
	a.resize(n << 1);
	int k = 0;
	for(int i = 0; i < n; ++i) {
		while (k >= 2 && clockwise(a[k - 2], a[k - 1], points[i])) --k;
		a[k++] = points[i];
	}
	
	int t = k + 1;
	for(int i = n - 2; i >= 0; --i) {
		while(k >= t && clockwise(a[k - 2], a[k - 1], points[i])) --k;
		a[k++] = points[i];
	}
	
	a.resize(k - 1);
	return Polygon(std::move(a));
}

Polygon generateRandomConvexHull(unsigned int n) {
	std::vector<float> xPool(n - 1), yPool(n - 1);
	generateSortedRandomArray(xPool.begin(), xPool.end(), 0.0f, 1.0f);
	generateSortedRandomArray(yPool.begin(), yPool.end(), 0.0f, 1.0f);
	
	float minX = xPool.front(), maxX = xPool.back();
	float minY = yPool.front(), maxY = yPool.back();
	
	std::vector<float> xVec, yVec;
    float lastTop = minX, lastBot = minX;
    float lastLeft = minY, lastRight = minY;

    for (int i = 1; i < n - 1; i++) {
		int r = rand();
        float x = xPool[i];
        if (r % 2) {
            xVec.push_back(x - lastTop);
            lastTop = x;
        } else {
            xVec.push_back(lastBot - x);
            lastBot = x;
        }
		
		float y = yPool[i];
        if (r % 4) {
            yVec.push_back(y - lastLeft);
            lastLeft = y;
        } else {
            yVec.push_back(lastRight - y);
            lastRight = y;
        }
    }

    xVec.push_back(maxX - lastTop);
    xVec.push_back(lastBot - maxX);
    yVec.push_back(maxY - lastLeft);
    yVec.push_back(lastRight - maxY);
	//std::random_shuffle(yVec.begin(), yVec.end());
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(yVec.begin(), yVec.end(), g);
    
	
	std::vector<Vector2> vec(n);
    for (int i = 0; i < n; i++) {
        vec[i] = Vector2{xVec[i], yVec[i]};
    }
	
    std::sort(vec.begin(), vec.end(), [](const Vector2& a, const Vector2& b) { return Vector2::angle(a) < Vector2::angle(b); });
	
    std::vector<Vector2> points(n);
	float x = 0, y = 0;
    for (int i = 0; i < n; i++) {
        points[i] = {x, y};
		x += vec[i].x;
        y += vec[i].y;
    }
	
	return Shapes::Polygon(std::move(points));
}


Polygon generateRect(float width, float height) {
	std::vector<Vector2> points(4);
	points[0] = {0, 0};
	points[1] = {width, 0.0f};
	points[2] = {width, height};
	points[3] = {0.0f, height};
	return Polygon(std::move(points));
}

Polygon generateRandomRect(float scale, float ratio) {
	float width  = (float)noise(1.0f, scale);
	float height = width * ratio;
	std::vector<Vector2> points(4);
	points[0] = {0, 0};
	points[1] = {width, 0.0f};
	points[2] = {width, height};
	points[3] = {0.0f, height};
	return Polygon(std::move(points));
}

void bspSplit(float xMin, float xMax, float yMin, float yMax, int depth, std::vector<Vector2>& points) {
    if (depth == 0) {
        float x = noise(xMin, xMax);
        float y = noise(yMin, yMax);
        points.push_back({x, y});
        return;
    }
	
    bool vertical = noise(0, 1) > 0.5;
    float split = vertical ? noise(xMin, xMax) : noise(yMin, yMax);
	
    if (vertical) {
        bspSplit(xMin, split, yMin, yMax, depth - 1, points);
        bspSplit(split, xMax, yMin, yMax, depth - 1, points);
    } else {
        bspSplit(xMin, xMax, yMin, split, depth - 1, points);
        bspSplit(xMin, xMax, split, yMax, depth - 1, points);
    }
}

std::vector<Vector2> sortPointsIntoPolygon(std::vector<Vector2>& points) {
    Vector2 centroid = {0, 0};
    for (const auto& p : points) centroid = centroid + p;
    centroid.x /= points.size();
    centroid.y /= points.size();
    std::sort(points.begin(), points.end(), [&centroid](const Vector2& a, const Vector2& b) {
        return atan2(a.y - centroid.y, a.x - centroid.x) < atan2(b.y - centroid.y, b.x - centroid.x);
    });
    return points;
}

void Polygon::sortEdges() {
    std::vector<std::pair<int, int>> sortedEdges;
    sortedEdges.reserve(edges.size());
    int current = 0;
    for (size_t i = 0; i < edges.size(); ++i)  {
        auto it = std::find_if(edges.begin(), edges.end(),
            [current](const auto& edge) {
                return edge.first == current;
            });

        if (it == edges.end()) break;
        sortedEdges.push_back(*it);
        current = it->second;
    }

    edges = std::move(sortedEdges);
}

Mesh Shapes::Polygon::convertToMesh() {
    Mesh mesh;
    int n = static_cast<int>(points.size());
    if (n < 3) return mesh;

    mesh.vertices.resize(n);
    float minX = points[0].x;
    float maxX = points[0].x;
    float minY = points[0].y;
    float maxY = points[0].y;
    for (int i = 1; i < n; ++i) {
        minX = std::min(minX, points[i].x);
        maxX = std::max(maxX, points[i].x);
        minY = std::min(minY, points[i].y);
        maxY = std::max(maxY, points[i].y);
    }

    float width  = maxX - minX;
    float height = maxY - minY;
    if (width == 0.0f) width = 1.0f;
    if (height == 0.0f) height = 1.0f;
    for (int i = 0; i < n; ++i) {
        float x = points[i].x;
        float y = points[i].y;

        mesh.vertices[i].pos[0] = x;
        mesh.vertices[i].pos[1] = y;
        mesh.vertices[i].pos[2] = 0.0f;
        mesh.vertices[i].uv[0] = (x - minX) / width;
        mesh.vertices[i].uv[1] = (y - minY) / height;
    }

    sortEdges();
    int indiciesSize = edges.size();
    mesh.indices.resize((indiciesSize - 2) * 3);
    std::vector<int> index_array(indiciesSize);
    for (int i = 0; i < indiciesSize; ++i) {
        // printf("%d %d\n", edges[indiciesSize - 1 - i].first, edges[indiciesSize - 1 - i].second);
        index_array[i] = edges[indiciesSize - 1 - i].second;
    }

    bool* removed = new bool[indiciesSize]();
    TriangulatePolygon2D(
        points.data(),
        removed,
        index_array.data(),
        indiciesSize,
        (int*)mesh.indices.data()
    );

    delete[] removed;
    mesh.materials.resize(1, mesh.indices.size());
    mesh.syncWithGPU();
    return mesh;
}

bool PointInQuadXZ(float x, float z, Vector3 quad[4]) {
	Vector3 p(x, 0, z);
    bool positive = false;
    bool negative = false;
    for(int i = 0; i < 4; i++) {
        Vector3 a = quad[i];
        Vector3 b = quad[(i + 1) % 4];
        Vector3 edge(b.x - a.x, 0, b.z - a.z);
        Vector3 toPoint(p.x - a.x, 0, p.z - a.z);
        float cross = edge.z * toPoint.x - edge.x * toPoint.z;
        if(cross > 0) positive = true;
        if(cross < 0) negative = true;
        if(positive && negative) return false;
    }
    return true;
}




bool unionPolygons(Shapes::Polygon& out, Shapes::Polygon& a, Shapes::Polygon& b) {
    std::vector<Vector2> points;
    std::vector<std::pair<int, int>> intersectionBelongs;

    int pointsOriginal = a.size() + b.size();
    intersectionBelongs.reserve(pointsOriginal);
    points.reserve(pointsOriginal << 1);
    for(int i = 0; i < a.size(); ++i) points.push_back(a[i]);
    for(int i = 0; i < b.size(); ++i) points.push_back(b[i]);
    
    //findIntersections
    for (int i = 0; i < a.edgeSize(); ++i) {
        auto edge = a.getEdge(i);
        for (int j = 0; j < b.edgeSize(); ++j) {
            auto otherEdge = b.getEdge(j);
            Vector2 p1;
            Vector2 p2;
            char type = Vector2::linesItersection( p1, p2, edge.first, edge.second, otherEdge.first, otherEdge.second );
            if (!type) continue;

            intersectionBelongs.push_back({ i, j });
            points.push_back(p1);
            if (type == 2) {
                points.push_back(p2);
                intersectionBelongs.push_back({ i, j });
            }
        }
    }

    //build segements
    std::vector<std::pair<int, int>> edges;
    std::vector<char> inside;
    std::vector<int> help;
    help.reserve(intersectionBelongs.size() + 2);
    for (int i = 0; i < a.edgeSize(); ++i) {
        auto edge = a.getEdgeIndicies(i);
        help.clear();
        help.push_back(edge.first);
        for (int j = 0; j < intersectionBelongs.size(); ++j) {
            if(intersectionBelongs[j].first == i) {
                help.push_back(pointsOriginal + j);
            }
        }
        help.push_back(edge.second);

        Vector2 start = points[edge.first];
        std::sort( help.begin(), help.end(), [&](const int p1, const int p2) {
            return Vector2::DistanceSquare(start, points[p1]) < Vector2::DistanceSquare(start,  points[p2]);
        });


        bool isInside = b.checkPointInside(points[help[0]]);
        for (int j = 0; j + 1 < help.size(); ++j) {
            edges.push_back({ help[j], help[j + 1] });
            inside.push_back(isInside);
            isInside = !isInside;
        }
    }

    for (int i = 0; i < b.edgeSize(); ++i) {
        auto edge = b.getEdgeIndicies(i);
        edge.first += a.size();
        edge.second += a.size();
        help.clear();
        help.push_back(edge.first);
        for (int j = 0; j < intersectionBelongs.size(); ++j) {
            if(intersectionBelongs[j].second == i) {
                help.push_back(pointsOriginal + j);
            }
        }
        help.push_back(edge.second);

        Vector2 start = points[edge.first];
        std::sort( help.begin(), help.end(), [&](const int p1, const int p2) {
            return Vector2::DistanceSquare(start, points[p1]) < Vector2::DistanceSquare(start,  points[p2]);
        });


        bool isInside = a.checkPointInside(points[help[0]]);
        for (int j = 0; j + 1 < help.size(); ++j) {
            edges.push_back({ help[j], help[j + 1] });
            inside.push_back(isInside);
            isInside = !isInside;
        }
    }

    std::vector<std::pair<int, int>> resultEdges;
    for (size_t i = 0; i < edges.size(); ++i) {
        if (inside[i]) continue;
        resultEdges.push_back(edges[i]);
    }


    std::vector<int> remap(points.size(), -1);
    std::vector<Vector2> newPoints;
    newPoints.reserve(points.size());
    for (auto& edge : resultEdges) {
        if (remap[edge.first] == -1) {
            remap[edge.first] = static_cast<int>(newPoints.size());
            newPoints.push_back(points[edge.first]);
        }
        edge.first = remap[edge.first];
        if (remap[edge.second] == -1) {
            remap[edge.second] = static_cast<int>(newPoints.size());
            newPoints.push_back(points[edge.second]);
        }
        edge.second = remap[edge.second];
    }

    if (newPoints.size() < 3 || resultEdges.size() < 3) return false;
    out = Shapes::Polygon( std::move(newPoints), std::move(resultEdges));
    return true;
}

void Shapes::Polygon::subdivide(int segments) {
    if(segments < 2) return;

    int newNumberOfEdges = segments * edges.size();
    int newPointsCount = (segments - 1) * edges.size();
    points.reserve(points.size() + newPointsCount);
    edges.reserve(newNumberOfEdges);

    int n = edges.size();
    for(int i = 0; i < n; ++i) {
        auto& e = edges[i];
        int startIndex = points.size();

        Vector2 start = points[e.first];
        Vector2 dir = (points[e.second] - start) / segments;
        for(int j = 1; j < segments; j++) {
            points.push_back(start + j * dir);
        }

        int theLast = e.second;
        e.second = startIndex;
        for(int j = 1; j < segments; ++j) {
            edges.push_back({ startIndex, startIndex + 1} );
            ++startIndex;
        }
        edges.back().second = theLast;
    }
}
};