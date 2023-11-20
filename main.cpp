#include <iostream>
#include<fstream>
using namespace std;


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


/* TODO - Calculate difference in surface distance between pre and post eruption data
 * Parameters - Two distance values
 * Returns - Difference between the two values
 */

 int main() {
    vector<vector<int>> heightData = writeFile("/Users/michael/Documents/Programming/SurfaceDistanceCalculator/pre.data");
    for(int i = 0; i < heightData.size(); i++){
        for(int j = 0; j < heightData[0].size(); j++){
            printf("%i",heightData[i][j]);
            printf("%s", " ");
        }
        printf("%s","\n");
    }
}