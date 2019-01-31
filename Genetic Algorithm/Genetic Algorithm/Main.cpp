#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>     /* atoi */
#include <stdio.h>      /* printf, fgets */
#include <cstring>
#include <vector>
#include <random>
#include "ctime"
#include "cmath"
#include "ctgmath"
#include "Maze.h"
#include "Chromosome.h"
//SYSTEM
//boolean to be changed to false when an individual finds the finish

clock_t SYSstartTime;
clock_t SYSendTime;
std::ifstream* Mazefile = new std::ifstream("MyMaze.txtt");


Maze* MyMaze = new Maze(Mazefile);
Chromosome* GeneticAlgorithm = new Chromosome;
//MAZE
//stores the size of the maze



int main()
{
  GeneticAlgorithm->Update(MyMaze,MyMaze->GetMAZEvector(),MyMaze->SetDeadSpotMap());
                                          //2D array that stores the information of the mazes layout
  
 
  Mazefile->close();
  delete MyMaze, GeneticAlgorithm, Mazefile;
  std::cin.get();
  std::cin.get();
  
  

  return 0;
}


