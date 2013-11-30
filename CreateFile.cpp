// Author: Sean Davis
#include <iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include <iomanip>

using namespace std;

void createMountainRanges(short **map, int width)
{
  int numMountainRanges, startCol, startRow, endCol, endRow, maxElevation,
    maxElevationDelta,col, row, deltaRow, deltaCol, temp;
  double slope;
  short elevation;

  numMountainRanges = int (1 + 0.4 * width);

  for(int i = 0; i < numMountainRanges; i++)
  {
    maxElevation = rand() % 100;
    maxElevationDelta = maxElevation / 5;
    if(maxElevationDelta < 2)
      maxElevationDelta = 2;  // allows for some change in low ranges.

    startCol = rand() % width + 1;
    startRow = rand() % width + 1;
    endCol = rand() % width + 1;
    endRow = rand() % width + 1;
    if(startRow > endRow)
    {
      temp = startRow;
      startRow = endRow;
      endRow = temp;
    }
  /*
    // average half way across map
    deltaRow = abs(startRow - endRow);
    if(deltaRow < 5)
      deltaRow = 5;

    // endCol = startCol + rand() % (deltaRow / 5) - deltaRow / 10;

    if(endCol > width)
      endCol = width;

    if(endCol < 1)
      endCol = 1;
  */
    if(startCol != endCol)
      slope = (startRow - endRow) / double(startCol - endCol);
    else
      slope = 10000;  // same as infinity when row cannot be larger than 100.

    for(int row = startRow; row <= endRow; row++)
    {
     col = int((row - startRow) / slope + startCol);

      if(col < 0)
       col = 0;
      if(col >= width)
       col = width - 1;

      elevation = max(1, maxElevation - maxElevationDelta + rand() % maxElevationDelta);
      if(elevation > map[col][row])
        map[col][row] = elevation;
    } // for each row
  }  // for each mountain range
}  // createMountainRanges()

void fillMap(short** map, int width)
{
  int endCol, endRow, slopeCol, slopeRow, startCol, col;
  for(int i = 0; i < width + 2; i++)
  {  // create unseen border of 1's.
    map[i][0] = 1;
    map[0][i] = 1;
    map[width + 1][i] = 1;
    map[i][width + 1] = 1;
  } // for i


  for(int row = 1; row <= width; row++) // Set low points in valleys.
  {
    endCol = startCol = 0;
    while(endCol < width + 1)
    {
      for(endCol = startCol + 1; map[endCol][row] == 0; endCol++);  // find none zero
      col = (startCol + endCol) / 2;
      if(map[col][row] == 0)
        map[col][row] = (map[startCol][row] + map[endCol][row]) / 2 - 50;
      if(map[col][row] < 1)
        map[col][row] = rand() % 5 + 1;
      if(map[col][row] > 99)
        map[col][row] = 99;
      startCol = endCol;
    } // while have reached end of line
  } // for row

  for(int col = 1; col <= width; col++)
    for(int row = 1; row <= width; row++)
    {
      if(map[col][row] == 0)
      {
        for(endCol = col + 1; map[endCol][row] == 0; endCol++);  // find none zero
        for(endRow = row + 1; map[col][endRow] == 0; endRow++);  // find none zero
        slopeCol = (map[endCol][row] - map[col - 1][row]) / (endCol - col + 1) ;
        slopeRow = (map[col][endRow] - map[col][row - 1]) / (endRow - row + 1);
        map[col][row] = (map[col - 1][row] + slopeCol + map[col][row - 1] + slopeRow) / 2 + rand() % 5;
        if(map[col][row] > 99)
          map[col][row] = 99;
      }
    } // for row
}  // fillMap()



short** createMap(int width)
{
  short **map = new short* [width + 2];


  for(int i = 0; i < width + 2; i++)
  {
    map[i] = new short[width + 2];

    for(int j = 0; j < width + 2; j++)
      map[i][j] = 0;  // unassigned an elevation
  } // for each width

  createMountainRanges(map, width);
  fillMap(map, width);


  return map;
} // createMap()

void printMap(short **map, int width)
{
  for(int i = 1; i < width; i++)
  {
    for(int j = 1; j < width; j++)
      cout << setw(3) << map[j][i];
    cout << endl;
  } // for i
}  // printMap()

void writeCities(ofstream &outf, int cities, int width)
{
  int cityLocs[50][2], col ,row;
  bool OK;
  
  
  for(int i = 0; i < cities; i++)
  {
    do
    {
      OK = true;
      col = rand() % width;
      row = rand() % width;
      
      for(int j = 0; j < i && OK; j++)
        if(cityLocs[j][0] == row && cityLocs[j][1] == col)
          OK = false;
    } while(!OK);
  
    outf << row << ' ' << col << endl;
  } // for each city
} // writeCities()

int main()
{
  int seed;
  int width, cities;
  char filename[80], process;
  short **map;

  cout << "Number of cities > ";
  cin >> cities;
  cout << "Width > ";
  cin >> width;
  cout << "Seed> ";
  cin >> seed;
  srand(seed);
  sprintf(filename, "map-%d-%d-%d.txt", cities, width, seed);
  ofstream outf(filename);
  outf << cities << " " << width << endl;
  writeCities(outf, cities, width);
  map = createMap(width);
 // printMap(map, width);

  for(int row = 1; row <= width; row++)
  {
    for(int col = 1; col <= width; col++)
      outf << setw(3) << map[col][row];
    outf << endl;
  } // for i

  outf.close();
  for(int i = 0; i < width + 2; i++)
    delete [] map[i];

  delete [] map;
  return 0;
}

