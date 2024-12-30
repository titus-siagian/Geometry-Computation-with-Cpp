#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
};

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; // Collinear
    return (val > 0) ? 1 : 2; // Clockwise or Counterclockwise
}

vector<Point> convexHull(vector<Point>& points) {
    int n = points.size();
    if (n < 3) return {};

    sort(points.begin(), points.end(), [](Point a, Point b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    vector<Point> hull;
    
    for (int i = 0; i < 2 * n; i++) {
        int j = (i < n) ? i : 2 * n - 1 - i;
        while (hull.size() >= 2 && orientation(hull[hull.size() - 2], hull[hull.size() - 1], points[j]) != 2) {
            hull.pop_back();
        }
        hull.push_back(points[j]);
    }
    hull.pop_back();
    return hull;
}

int main() {
    int n;
    cout << "Enter number of points: ";
    cin >> n;

    vector<Point> points(n);
    cout << "Enter the points (x y):\n";
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    vector<Point> hull = convexHull(points);

    cout << "Points in Convex Hull:\n";
    for (auto& p : hull) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }

    return 0;
}
