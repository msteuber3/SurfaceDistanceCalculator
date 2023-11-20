#include <iostream>
#include<fstream>
using namespace std;

//TODO - Document this function properly
vector<vector<int>> writeFile(const char* filePath){
    fstream fileIn(filePath);
    if(!filePath){
        perror("Error: Could not open file");
    }
    int col = 512;
    int row = 512; //Consider basing this on the size of the image files
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


/* TODO - Compute distance from point A to point B
 * Parameters - Height values vector, two sets of coordinates (x, y) provided by user
 * Returns - Surface distance in meters
 */
vector<pair<int, int>> calculateSurfaceDistance(vector<vector<int>> heightData, vector<int>coordOne, vector<int>coordTwo){
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
    return heightsInPath;
}


/* TODO - Calculate difference in surface distance between pre and post eruption data
 * Parameters - Two distance values
 * Returns - Difference between the two values
 */

 int main() {
    vector<vector<int>> heightData = writeFile("/Users/michael/Documents/Programming/SurfaceDistanceCalculator/pre.data");
    vector<int> one {0, 1};
    vector<int> two {6, 4};
    vector<pair<int, int>> surfaceTest = calculateSurfaceDistance(heightData, one, two);

        for (auto iter = surfaceTest.begin(); iter != surfaceTest.end(); iter++)
        {
            cout << iter->first << iter->second << endl;
        }
    cout << floor(3.00) << endl;
    //    for(int i = 0; i < heightData.size(); i++){
//        for(int j = 0; j < heightData[0].size(); j++){
//            printf("%i",heightData[i][j]);
//            printf("%s", " ");
//        }
//        printf("%s","\n");
//    }
    return 0;

 }