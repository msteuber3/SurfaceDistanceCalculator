/* Michael Steuber
 * 11/20/2023
 *
 * SurfaceDistanceCalculator - Calculates the difference in the surface distance between two coordinates provided by user
 * before and after the eruption of Mount St. Helens
 */
#include <iostream>
#include "utils/userInput.h"
#include "utils/writeFile.h"
#include "distanceCalc.h"
using namespace std;

int main() {

    vector<int> startCoords(2);
    vector<int> endCoords(2);
    printf("%s", "Enter x1 coordinate:");
    startCoords[0] = userIn();
    printf("%s", "Enter y1 coordinate:");
    startCoords[1] = userIn();
    printf("%s", "Enter x2 coordinate:");
    endCoords[0] = userIn();
    printf("%s", "Enter y2 coordinate:");
    endCoords[1] = userIn();


    vector<vector<int>> heightDataPre = writeFile("../data/pre.data");
    vector<vector<int>> heightDataPost = writeFile("../data/post.data");
    int surfaceDistancePre = calculateSurfaceDistance(heightDataPre, startCoords, endCoords);
    int surfaceDistancePost = calculateSurfaceDistance(heightDataPost, startCoords, endCoords);
    int changeInDistance = comparePreAndPost(surfaceDistancePre, surfaceDistancePost);
    cout << "Surface distance pre-eruption: " << surfaceDistancePre << "\n";
    cout << "Surface distance post-eruption: " << surfaceDistancePost << "\n";

    printf("There was a %i meter change in the distance between (%i, %i) and (%i, %i) after the eruption.", changeInDistance, startCoords[0], startCoords[1], endCoords[0], endCoords[1]);

    return 0;

}