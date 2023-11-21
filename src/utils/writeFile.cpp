#include <iostream>
#include <fstream>
#include "writeFile.h"
using namespace std;

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