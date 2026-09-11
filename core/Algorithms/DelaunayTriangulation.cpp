#include "Triangulation.h"
#include "Polygon.h"
#include <algorithm>
#include <optional>
#include <cstdio>
#include <cmath>
#include <queue>
#include <list>

struct Triangle {
    int a;
    int b;
    int c;
};

bool inCircumCircle(const Vector2& p, const Vector2& a, const Vector2& b, const Vector2& c) {
    const Vector2 pa = a - p;
    const Vector2 pb = b - p;
    const Vector2 pc = c - p;

    const float det = 
         (pa[0] * pa[0] + pa[1] * pa[1]) * (pb[0] * pc[1] - pb[1] * pc[0])
        -(pb[0] * pb[0] + pb[1] * pb[1]) * (pa[0] * pc[1] - pa[1] * pc[0])
        +(pc[0] * pc[0] + pc[1] * pc[1]) * (pa[0] * pb[1] - pa[1] * pb[0]);

    return counterClockwise(a, b, c) ? det > 0 : det < 0;
}

std::vector<int> DelaunayTriangulation(std::vector<Vector2>& points) {
    const int n = static_cast<int>(points.size());
    if(n < 3) return {};

    Vector2 minP = points[0];
    Vector2 maxP = points[0];
    for(auto& v : points) {
        if(minP[0] > v[0]) minP[0] = v[0];
        if(minP[1] > v[1]) minP[1] = v[1];
        if(maxP[0] < v[0]) maxP[0] = v[0];
        if(maxP[1] < v[1]) maxP[1] = v[1];
    }

    const Vector2 delta = maxP - minP;
    const float d = std::max(delta.x, delta.y);
    const Vector2 c = (minP + maxP) * 0.5f;
    
    const int s0 = n;
    const int s1 = n + 1;
    const int s2 = n + 2;

    std::vector<Vector2> p = points;
    p.push_back({ c.x - 20.0f * d,  c.y - d          });
    p.push_back({ c.x,              c.y + 20.0f * d  });
    p.push_back({ c.x + 20.0f * d,  c.y - d          });


    std::vector<Triangle> triangles;
    triangles.reserve(6 * points.size());
    triangles.push_back({ s0, s1, s2} );

    std::vector<int> bad;
    std::vector<std::pair<int, int>> polygon;
    for(int i = 0; i < n; ++i) {
        bad.clear();
        for(int j = 0; j < triangles.size(); ++j) {
            auto& t = triangles[j];
            if(inCircumCircle(p[i], p[t.a], p[t.b], p[t.c])) {
                bad.push_back(j);
            }
        }

        polygon.clear();
        auto addEdge = [&](int a, int b) {
            for(auto it = polygon.begin(); it != polygon.end(); ++it) {
                if(it->first == b && it->second == a) {
                    polygon.erase(it);
                    return;
                }
            }
            polygon.push_back({a, b});
        };
        for(const auto& badIndex: bad) {
            auto& t = triangles[badIndex];
            addEdge(t.a, t.b);
            addEdge(t.b, t.c);
            addEdge(t.c, t.a);
        }

        for(int j = bad.size() - 1; j >= 0; --j) {
            std::swap(triangles[bad[j]], triangles.back());
            triangles.pop_back();
        }

        for(const auto& e: polygon) {
            Triangle t = {e.first, e.second, i};
            if(!counterClockwise(p[t.a], p[t.b], p[t.c])) {
                std::swap(t.a, t.b);
            }
            triangles.push_back(t);
        }
    }

    std::vector<int> indexArray;
    indexArray.reserve(6 * points.size());
    for(const auto& t: triangles) {
        if(t.a >= n || t.b >= n || t.c >= n) continue;

        indexArray.push_back(t.a);
        indexArray.push_back(t.b);
        indexArray.push_back(t.c);
    }
    return indexArray;
}