struct HalfPlaneIntersection {
    struct Line {
        DPoint p, v;
        long double ang;

        Line(DPoint a, DPoint b) : p(a), v(b - a),
            ang(atan2l(v.y, v.x)) {}

        bool outside(DPoint x) const {
            return cross(v, x - p) < -GEPS;
        }
    };

    bool same_direction(const Line& a, const Line& b) {
        return fabsl(cross(a.v, b.v)) <= GEPS && dot(a.v, b.v) > 0;
    }

    DPoint intersection(const Line& a, const Line& b) {
        return line_intersection(a.p, a.v, b.p, b.v);
    }

    vector<DPoint> run(vector<Line> lines) {
        sort(lines.begin(), lines.end(), [](const Line& a, const Line& b) {
            return a.ang < b.ang;
        });

        vector<Line> unique_lines;
        for (Line l : lines) {
            if (unique_lines.empty() || !same_direction(unique_lines.back(), l))
                unique_lines.push_back(l);
            else if (l.outside(unique_lines.back().p))
                unique_lines.back() = l;
        }

        deque<Line> q;
        for (Line l : unique_lines) {
            while (q.size() >= 2 && l.outside(intersection(q[q.size() - 2], q.back())))
                q.pop_back();
            while (q.size() >= 2 && l.outside(intersection(q[0], q[1])))
                q.pop_front();
            q.push_back(l);
        }
        while (q.size() >= 3 && q.front().outside(intersection(q[q.size() - 2], q.back())))
            q.pop_back();
        while (q.size() >= 3 && q.back().outside(intersection(q[0], q[1])))
            q.pop_front();
        if (q.size() < 3) return {};

        vector<DPoint> poly;
        for (int i = 0; i < (int)q.size(); i++) {
            const Line& a = q[i];
            const Line& b = q[(i + 1) % q.size()];
            if (fabsl(cross(a.v, b.v)) <= GEPS) return {};
            poly.push_back(intersection(a, b));
        }
        return poly;
    }
};
