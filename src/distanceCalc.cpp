#include <iostream>
#include "distanceCalc.h"
using namespace std;


int calculateSurfaceDistance(vector<vector<int>> heightData, vector<int>coordOne, vector<int>coordTwo){
    /* Calculates a list of coordinates between two points using Bresenham's line algorithm and uses that list and the
     * 2D vector provided by the raw data files to determine the surface distance between the two points
     * Parameters -
     *      heightData - 2D vector of height data
     *      coordOne - Beginning coordinates provided by user
     *      coordTwo - End coordinates provided by user
     * Returns -
     *      Surface distance in meters as an integer
     */
    vector<pair<int, int>> heightsInPath;
    int x = coordOne[0];
    int y = coordOne[1];
    int x2 = coordTwo[0];
    int y2 = coordTwo[1];
    float slope = static_cast<float>(y2 - y) / static_cast<float>(x2 - x);
    if(slope < 0){
        x = coordTwo[0];
        y = coordTwo[1];
        x2 = coordOne[0];
        y2 = coordOne[1];
        slope = static_cast<float>(y2 - y) / static_cast<float>(x2 - x);
    }
    int dx = x2 - x;                                         //Use Bresenham's line algorithm to find all the coordinates in between the two points
    int dy = y2 - y;
    int D = 2 * dy - dx;
    if(slope < 1 && slope > -1){
        while(x <= x2){
            heightsInPath.insert(heightsInPath.end(), make_pair(x, y));
            if(D > 0){
                y++;
                D = D - 2*dx;
            }
            D = D +2*dy;
            x++;
        }
    }
    else {
        while (y <= y2) {
            heightsInPath.insert(heightsInPath.end(), make_pair(x, y));
            if (D > 0) {
                x++;
                D = D - 2 * dy;
            }
            D = D + 2 * dx;
            y++;
        }
    }

    int surfaceHeightDistance = 0;
    int currentx;
    int currenty;
    int previousx = 0;
    int previousy = 0;
    for(auto & i : heightsInPath){
        currentx = i.first;
        currenty = i.second;
        surfaceHeightDistance += (abs(heightData[currentx][currenty] - heightData[previousx][previousy]) * 11);
        previousx = currentx;
        previousy = currenty;
        surfaceHeightDistance += 30;
    }
    return surfaceHeightDistance;
}


int comparePreAndPost(int preEruption, int postEruption){
    /* Parameters -
     *      preEruption - int of the surface distance between two points before the eruption
     *      postEruption - int of the surface distance between two points after the eruption
     * Returns -
     *      Difference between the two distances
    */
    return abs(postEruption - preEruption);
}
