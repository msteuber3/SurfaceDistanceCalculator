/* Michael Steuber
 * 11/20/2023
 *
 * SurfaceDistanceCalculator - Calculates the difference in the surface distance between two coordinates provided by user
 * before and after the eruption of Mount St. Helens
 */
#include <iostream>
#include<fstream>
using namespace std;

//TODO - Document this function properly
vector<vector<int>> writeFile(const char* filePath){
    /* Opens a file and writes its contents to a 2D vector
     * Parameters -
     *      filePath - the path to the file to open
     *
     * Returns -
     *      A 2D vector heightData which contains the integer representations of the height
     * values in the raw data files
     */

    fstream fileIn(filePath);
    if(!filePath){
        perror("Error: Could not open file");
    }
    int col = 512;
    int row = 512;
    vector<vector<int>> heightData(col, vector<int>(row));


    vector<char> rawData(row * col);     // Writes the raw data from the .data file into a vector rawData
    fileIn.read(rawData.data(), static_cast<long>(rawData.size()));

    for(int i = 0; i < col; i++){           //Casts the data from rawData and writes it to 2D vector heightData
        for(int j = 0; j < row; j++){
            heightData[i][j] = static_cast<unsigned char>(rawData[i * col + j]);
        }
    }
    return heightData;
}


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
int main() {

    vector<int> startCoords(2);
    vector<int> endCoords(2);
    printf("%s", "Enter x1 coordinate:");
    cin >> startCoords[0];
    printf("%s", "Enter y1 coordinate:");
    cin >> startCoords[1];
    printf("%s", "Enter x2 coordinate:");
    cin >> endCoords[0];
    printf("%s", "Enter y2 coordinate:");
    cin >> endCoords[1];


    vector<vector<int>> heightDataPre = writeFile("/Users/michael/Documents/Programming/SurfaceDistanceCalculator/pre.data");
    vector<vector<int>> heightDataPost = writeFile("/Users/michael/Documents/Programming/SurfaceDistanceCalculator/post.data");
    int surfaceDistancePre = calculateSurfaceDistance(heightDataPre, startCoords, endCoords);
    int surfaceDistancePost = calculateSurfaceDistance(heightDataPost, startCoords, endCoords);
    int changeInDistance = comparePreAndPost(surfaceDistancePre, surfaceDistancePost);
    cout << "Surface distance pre-eruption: " << surfaceDistancePre << "\n";
    cout << "Surface distance post-eruption: " << surfaceDistancePost << "\n";


    cout<< "There was a " << changeInDistance << " meter change in the distance bewtween the two coordinates before and after the eruption" << "\n";

    return 0;

}