#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>   
#include <stdio.h>    
#include <cstring>
#include <vector>
#include "ctime"
#include "cmath"
#include "ctgmath"
class Maze
{
private: 
  int MAZEXsize = 0;
  int MAZEYsize = 0;
  int CHRYstartingPosition, CHRXstartingPosition, CHRYfinish, CHRXfinish, CHRYcurrentPosition, CHRXcurrentPosition = { 0 };
  std::vector<std::vector<int>>MAZEarray;
  std::vector< std::vector<int>>DeadspotMap;
  int DeadspotX, DeadspotY;

public:
  Maze(std::ifstream* myfile);
  ~Maze();
  void splitStringWhitespace(std::string& input, std::vector<std::string>& output);
  int GetMazeX();
  int GetMazeY();

  int GetCHRXSP();
  int GetCHRYSP();
  int GetCHRYEP();
  int GetCHRXEP();
  int GetCHRYCP();
  int GetCHRXCP();
  void SetCHRYCP(int);
  void SetCHRXCP(int);
  std::vector<std::vector<int>>GetMAZEvector();
  int GetDeadSpotX();
  int GetDeadSpotY();
  void SetDeadSpotX(int);
  void SetDeadSpotY(int);
  void SetDeadSpotMap(int Y, int X);
  std::vector<std::vector<int>>SetDeadSpotMap();
 
};

