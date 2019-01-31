#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <random>
#include "ctime"
#include "cmath"
#include "ctgmath"
#include "Maze.h"
class Chromosome
{
private:
  //CHROMOSOME
  //parameters for the chromosomes creation
  int CHRsize;                                                        // CHRsize/2 = the number of steps through the maze
  int CHRcount;                                                    // total number of chromosomes created
                                                                       //Generator for Spinning Arrow Function
  int i;
  // Actual working thing
  int z ;
  //Values for Crossover Function
  int a;
  int b;

  std::vector< std::vector<float> > CHRvector;
  std::vector <float> CHRtempVector;  //this keeps track of how far through the chromosome it is when stepping through the maze
  std::vector< std::vector<float> > PCHRvector;

  std::vector<float>CHRfitnessScore;
  
  float CHRgenerationFitnessTotal;

  int CHRgene = 0;
  //starting and finishing point of the maze

  //parameters for the chromosomes fitness
  std::vector<int> CHRYoffset;                                           
  std::vector<int> CHRXoffset;
  std::vector <float> CHRfitness;        

  bool SYSrunning;
  bool SYScontinue;
  int SYSrunCycles;
  int SYSgenerationCounter;
  clock_t SYSstartTime;
  clock_t SYSendTime;



public:
  Chromosome();
  ~Chromosome();
  void Update(Maze* MyMaze, std::vector<std::vector<int>>MAZEarray, std::vector<std::vector<int>>DeadSpotMap);
  void UpdateChromosomeSizes(Maze*Mymaze);

  //randomly selects a number between 0 and 1
  float randomizer();

  //recursive addition for individualSelector

  //randomly choose an individual, based on their fitness, for breeding
  int IndividualSelector(std::vector<float> CIndividual);
 
  //find the chromosome with the best fitness and return the chromosome number. !fitness
  int BestFitness(std::vector<float> fitness);
  
  //finds the second best fitness to ensure variety

  //creates a random number between 0 and 1, and then checks to see if it makes the crossover rate to determin whether a two parents will breed
  bool CHRcrossOverCheck();

  //Does Crossover by taking two parents that are next to each other and swapping half of their genes
  //Create the individuals
  void Create_Individuals(std::vector<float>& CHRfitnessScore, std::vector <float>&  CHRfitness, float& CHRgenerationFitnessTotal, std::vector< std::vector<float> > &CHRvector, std::vector< std::vector<float> > &PCHRvector);
  

  void Mutation(std::vector<std::vector<float>> &CHRvector);

  //Where Crossover Happens
  void Crossover(int& CHRcount, int& CHRsize, std::vector <float>& CHRtempVector, std::vector< std::vector<float> >& PCHRvector, std::vector< std::vector<float> >& CHRvector);

  //Fitness Calculation
  void  Fitness_calculation(Maze* MyMaze, std::vector<std::vector<int>>&MAZEarray, std::vector<int>& CHRXoffset, std::vector<int> &CHRYoffset, std::vector <float> &CHRfitness, float& CHRgenerationFitnessTotal, int i);

  void  CHRGenerator(std::vector<std::vector<float>>&CHRvector);

  int  MovementCount(int MazeX, int MazeY);

  //Movement Function
  void Movement(Maze* MyMaze, int i);
};

