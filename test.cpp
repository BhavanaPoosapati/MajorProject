#include <iostream>
#include <vector>

#define num 1

struct seg {
    float x1, y1, x2, y2;
};

// Check if a pofloat is inside a polygon using the ray casting algorithm
bool pofloat_inside_polygon(float x, float y, std::vector<seg> polygon)
{
    bool inside = false;
    float n = polygon.size();
    for (float i = 0, j = n - 1; i < n; j = i++) {
        if (((polygon[i].y1 > y) != (polygon[j].y1 > y)) &&
                (x < (polygon[j].x1 - polygon[i].x1) * (y - polygon[i].y1) /
                (polygon[j].y1 - polygon[i].y1) + polygon[i].x1)) {
            inside = !inside;
        }
    }
    return inside;
}

// Check if two line segments floatersect
bool seg_floatersect(seg s1, seg s2)
{
    // Get the vectors formed by the segments
    float u1 = s1.x2 - s1.x1;
    float v1 = s1.y2 - s1.y1;
    float u2 = s2.x2 - s2.x1;
    float v2 = s2.y2 - s2.y1;

    // Compute the cross product of the vectors
    float cross = u1 * v2 - v1 * u2;

    // If the cross product is zero, the segments are parallel and may or may not floatersect
    if (cross == 0) {
        return false;
    }

    // Compute the floatersection pofloat
    float w1 = s2.x1 - s1.x1;
    float w2 = s2.y1 - s1.y1;
    double s = (double)(u2 * w2 - v2 * w1) / cross;
    double t = (double)(u1 * w2 - v1 * w1) / cross;
    if (s < 0 || s > 1 || t < 0 || t > 1) {
        return false;
    }

    return true;
}

// Check if a closed shape is inside another clos
bool closed_shape_inside_closed_shape(std::vector<seg> shape1, std::vector<seg> shape2)
{
    // Check if any segment in shape1 floatersects with any segment in shape2
    for (auto seg1 : shape1) {
        for (auto seg2 : shape2) {
            float x1 = seg1.x1, y1 = seg1.y1, x2 = seg1.x2, y2 = seg1.y2;
            float x3 = seg2.x1, y3 = seg2.y1, x4 = seg2.x2, y4 = seg2.y2;
            float d = (y4-y3)*(x2-x1)-(x4-x3)*(y2-y1);
            if (d == 0) {
                continue;
            }
            double ua = ((x4-x3)*(y1-y3)-(y4-y3)*(x1-x3)) / (double) d;
            double ub = ((x2-x1)*(y1-y3)-(y2-y1)*(x1-x3)) / (double) d;
            if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1) {
                return true;
            }
        }
    }
    return false;
}



// Check if any closed shape in s2 exists completely in any closed shape in s1
bool s2_exists_in_s1(std::vector<seg> s1[], std::vector<seg> s2[], float n1, float n2)
{
    // Check if each closed shape in s2 exists in s1
    for (int i = 0; i < n2; i++) {
        bool shape_exists = false;
        for (int j = 0; j < n1; j++) {
            if (closed_shape_inside_closed_shape(s2[i], s1[j])) {
                shape_exists = true;
                break;
            }
        }
        if (!shape_exists) {
            return false;
        }
    }
    return true;
}

int main()
{
    // correct 1
    // std::vector<seg> s1[num]= {{ {2,1,6,6},{6,6,7,1},{7,1,2,1}} };
    // std::vector<seg> s2[num] = { {{5,2,6,4},{6,4,7,1},{7,1,5,2} }};

    // correct 2
    // std::vector<seg> s1[num]= { { {1,2,1,6},{1,6,4,2},{4,2,1,2} }};
    // std::vector<seg> s2[num] = {{ {2,3,1,4},{1,4,2.5,4},{2.5,4,2,3} }};

    std::vector<seg> s1[num]= {{ {2,4,6,4},{6,4,4,1},{4,1,2,4} }};
    std::vector<seg> s2[num] = {{ {3,4,5,4},{5,4,4,2},{4,2,3,4} }};

    // std::vector<seg> s1[num]= {{ {3,1,6,1},{6,1,5,3},{5,3,3,1} }};
    // std::vector<seg> s2[num] = {{ {1,1,8,1},{8,1,1,7},{1,7,1,1} }};


    //     std::vector<seg> s1[num]= {{ {3,1,6,1},{6,1,5,3},{5,3,3,1} }};
    // std::vector<seg> s2[num] = {{ {1,1,8,1},{8,1,1,7},{1,7,1,1} }};

    // int x = 3;
    // // struct seg s1[x] =  { {3,1,6,1},{6,1,5,3},{5,3,3,1} };
    // // struct seg s2[x] = { {1,1,8,1},{8,1,1,7},{1,7,1,1} };

    // struct seg s1[x] =  { {2,4,6,4},{6,4,4,1},{4,1,2,4} };
    // struct seg s2[x] = { {3,4,5,4},{5,4,4,2},{4,2,3,4} };

    // // Convert to vector of structs
    // int num =1 ;
    // std::vector<seg> v1[num];
    // for (int i = 0; i < num; i++) {
    //     v1[i].push_back(s1[i]);
    // }

    // // // Print the vector of structs
    // // for (int i = 0; i < num; i++) {
    // //     std::cout << "Vector " << i << ": ";
    // //     for (auto s : v1[i]) {
    // //         std::cout << "(" << s.x1 << "," << s.y1 << "," << s.x2 << "," << s.y2 << ") ";
    // //     }
    // //     std::cout << std::endl;
    // // }

    //     // Convert to vector of structs
    // std::vector<seg> v2[num];
    // for (int i = 0; i < num; i++) {
    //     v2[i].push_back(s2[i]);
    // }

    // // Print the vector of structs
    // for (int i = 0; i < num; i++) {
    //     std::cout << "Vector " << i << ": ";
    //     for (auto s : v2[i]) {
    //         std::cout << "(" << s.x1 << "," << s.y1 << "," << s.x2 << "," << s.y2 << ") ";
    //     }
    //     std::cout << std::endl;
    // }
    //incorrect 
    // std::vector<seg> s1[num]= {{ {1,2,1,4},{1,4,2,3},{2,3,1,2} }};
    // std::vector<seg> s2[num] = { { {3,2,3,4},{3,4,5,5},{5,5,3,2} }};

    if (s2_exists_in_s1(s1, s2, num, num)) {
        std::cout<<s2_exists_in_s1(s1, s2, num, num);
        std::cout << "s2 exists in s1\n";
    } else {
        std::cout << "s2 does not exist in s1\n";
    }

    return 0;
}
