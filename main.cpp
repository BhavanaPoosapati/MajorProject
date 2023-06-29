#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

std::map<std::string, int> relation_index = {
    {"relation_1", 0},
    {"relation_2", 2},
    {"relation_33", 33}
};

struct seg {
    float x1, y1, x2, y2;
};



bool areDisjoint(seg a, seg b) {
    bool a1_outside_b = (a.x1 < std::min(b.x1, b.x2)) || (a.x1 > std::max(b.x1, b.x2)) || (a.y1 < std::min(b.y1, b.y2)) || (a.y1 > std::max(b.y1, b.y2));
    bool a2_outside_b = (a.x2 < std::min(b.x1, b.x2)) || (a.x2 > std::max(b.x1, b.x2)) || (a.y2 < std::min(b.y1, b.y2)) || (a.y2 > std::max(b.y1, b.y2));
    return a1_outside_b && a2_outside_b;
}

bool arePolygonsDisjoint(seg s1[], seg s2[], int num) {
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (!areDisjoint(s1[i], s2[j])) {
                return false;
            }
        }
    }
    return true;
}

bool isSegmentInsideSegment(seg a, seg b) {
    // Check if the two line segments are parallel
    int d1 = (a.y2 - a.y1) * (b.x2 - b.x1);
    int d2 = (a.x2 - a.x1) * (b.y2 - b.y1);
    if (d1 != d2) {
        return false;
    }

    // Check if the endpoints of line segment b are within the bounds of line segment a
    bool b1_inside_a = (b.x1 >= std::min(a.x1, a.x2)) && (b.x1 <= std::max(a.x1, a.x2)) && (b.y1 >= std::min(a.y1, a.y2)) && (b.y1 <= std::max(a.y1, a.y2));
    bool b2_inside_a = (b.x2 >= std::min(a.x1, a.x2)) && (b.x2 <= std::max(a.x1, a.x2)) && (b.y2 >= std::min(a.y1, a.y2)) && (b.y2 <= std::max(a.y1, a.y2));

    return b1_inside_a && b2_inside_a;
}

bool isPointInsidePolygon(int x, int y, seg s[], int num) {
    bool result = false;
    for (int i = 0, j = num - 1; i < num; j = i++) {
        if (((s[i].y1 >= y) != (s[j].y1 >= y)) && (x < (s[j].x1 - s[i].x1) * (y - s[i].y1) / (s[j].y1 - s[i].y1) + s[i].x1)) {
            result = !result;
        }
    }
    return result;
}

bool isPolygonInsidePolygon(seg s1[], seg s2[], int num) {
    // Check if all vertices of s1 are inside s2
    for (int i = 0; i < num; i++) {
        if (!isPointInsidePolygon(s1[i].x1, s1[i].y1, s2, num)) {
            std::cout<<"s1[i].x1"<<std::endl;
            return false;
        }
    }

    // Check if any line segment from s1 intersects with any line segment from s2
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (!areDisjoint(s1[i], s2[j])) {
                return false;
            }
        }
    }

    return true;
}

bool seg_exists(struct seg s1[], struct seg s2[],int num) {
    // Check each segment in s1 for a match with s2
    for (int i = 0; i < num; i++) {
        if (s1[i].x1 == s2[0].x1 && s1[i].y1 == s2[0].y1 &&
            s1[i].x2 == s2[0].x2 && s1[i].y2 == s2[0].y2 &&
            s1[(i+1)%num].x1 == s2[1].x1 && s1[(i+1)%num].y1 == s2[1].y1 &&
            s1[(i+1)%num].x2 == s2[1].x2 && s1[(i+1)%num].y2 == s2[1].y2 &&
            s1[(i+2)%num].x1 == s2[2].x1 && s1[(i+2)%num].y1 == s2[2].y1 &&
            s1[(i+2)%num].x2 == s2[2].x2 && s1[(i+2)%num].y2 == s2[2].y2) {
                std::cout<<"s1[i].x1"<<std::endl;
            return true;
        }
    }
    // No match found
    return false;
}


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
std::string compute_relation(seg a[], seg b[],std::vector<seg> v1[1], std::vector<seg> v2[1],int num) {
    //  std::vector<seg> v_s1, v_s2;
    // for (int i = 0; i < num; i++) {
    //     v_s1.push_back(a[i]);
    // }
    // for (int i = 0; i < num; i++) {
    //     v_s2.push_back(b[i]);
    // }
    // std::cout << std::endl;

        if(arePolygonsDisjoint(a,b,num)){
                return "relation_1";
            }
        // else if(s2_exists_in_s1(&v_s1, &v_s2, num, num)){
        else if(s2_exists_in_s1(v1, v2, 1, 1)){
            std::cout<<"relation_2"<<std::endl;
                return "relation_2";
            }
            std::cout<<"not found"<<std::endl;

            return "relation_33";
}


int main() {
    const int num = 3;
    //correct

    // struct seg s1[num]={ {2,1,6,6},{6,6,7,1},{7,1,2,1} };
    // struct seg s2[num] ={ {5,2,6,4},{6,4,7,1},{7,1,5,2} };

    // struct seg s1[num]= { {3,1,6,1},{6,1,5,3},{5,3,3,1} };
    // struct seg s2[num] = { {1,1,8,1},{8,1,1,7},{1,7,1,1} };
    // struct seg s1[num] = { {2,1,6,6},{6,6,7,1},{7,1,2,1} };
    // struct seg s2[num] = { {1,1,8,1},{8,1,1,7},{1,7,1,1} };
    // struct seg s1[num]= {  {1,5,5,7},{5,7,4,2},{4,2,1,5} };
    // struct seg s2[num] = { {2,4,3,6},{3,6,4,5},{4,5,2,4} };
    // struct seg s1[num]= {  {1,2,1,6},{1,6,4,2},{4,2,1,2} };
    // struct seg s2[num] = {{2,3,1,4},{1,4,2.5,4},{2.5,4,2,3} };
    // struct seg s1[num]= {{2,4,6,4},{6,4,4,1},{4,1,2,4} };
    // struct seg s2[num] = { {3,4,5,4},{5,4,4,2},{4,2,3,4} };
    

    // struct seg s1[num] = { {2,1,3,5},{3,5,5,3},{5,3,2,1} };
    // struct seg s2[num] = { {7,1,6,3},{6,3,9,3},{9,3, 7,1} };
    // struct seg s1[num] = { {2,1,3,5},{3,5,5,3},{5,3,2,1} };
    // struct seg s2[num] = { {7,1,6,3},{6,3,9,3},{9,3, 7,1} };
    struct seg s1[num] = { {2,1,0,3},{0,3,3,3},{3,3,2,1} };
    struct seg s2[num] = { {4,3,6,6},{6,6,7,3},{7,3,4,3} };


    int numm = 1;
    std::vector<seg> v1[numm];
    for (int i = 0; i < numm; i++) {
        v1[i].push_back(s1[i]);
    }

    std::vector<seg> v2[numm];
    for (int i = 0; i < numm; i++) {
        v2[i].push_back(s2[i]);
    }




    // std::cout<<compute_relation(s1,s2,num)<<std::endl;
    // std::cout<<arePolygonsDisjoint(s1,s2,num)<<std::endl;
    // std::cout<<seg_exists(s2, s1, num)<<std::endl;

    int matrix[num][num] = {0};

for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
        std::string relation = compute_relation(s1, s2,v1,v2,num);
        if (relation == "relation_1") {
            if(i==0&&j==0 || i==1&&j==1 || i==0&&j==1 || i==1&&j==0){
                matrix[i][j] = 0;
            }
            else{
                matrix[i][j] = 1;
            }
        }
        else if (relation == "relation_2") {
            std::cout<<"a is inside b"<<std::endl;
            for (int i = 0; i < num; i++) {
                    for (int j = 0; j < num; j++) {
                        if (i == 2 || j == 2 || (i == 1 && j == 1)) {
                            matrix[i][j] = 1;
                        } else {
                            matrix[i][j] = 0;
                        }
                    }
                }
            matrix[1][2] = 0;
            }
        
        // matrix[i][j] = relation_index[relation];
    }
}

for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
        std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
}

    return 0;
}

