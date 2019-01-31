#include "Chromosome.h"



Chromosome::Chromosome()
{
   CHRsize = 20;                                                        // CHRsize/2 = the number of steps through the maze
   CHRcount = 6;                                                    // total number of chromosomes created
                                                                       //Generator for Spinning Arrow Function
   i = 0;
  // Actual working thing
   z = 0;
  //Values for Crossover Function




  //float PCHRvector[CHRsize][CHRcount] = { 0 };
  
  for (int i = 0; i<CHRcount; i++)
  {
    CHRfitnessScore.push_back(i);

  }
  //float CHRfitnessScore[CHRcount];
   CHRgenerationFitnessTotal = 0;

   CHRgene = 0;
  //starting and finishing point of the maze

  //parameters for the chromosomes fitness
                                            // x and y offset from the finishing point
   for (int i = 0; i<CHRcount; i++)
   {
     CHRYoffset.push_back(i);

   }
   for (int i = 0; i<CHRcount; i++)
   {
     CHRXoffset.push_back(i);

   }
   for (int i = 0; i<CHRcount; i++)
   {
     CHRfitness.push_back(i);

   }                                       // based on a fitness algorithm this number will be between 0 and 1 (0 is lowest, 1 is highest)
   SYSrunning = true;
   SYScontinue = true;
   SYSrunCycles = 1;
   SYSgenerationCounter = 1;
}


Chromosome::~Chromosome()
{
}

void Chromosome::Update(Maze* MyMaze, std::vector<std::vector<int>>MAZEarray, std::vector<std::vector<int>>DeadSpotMap)
{
  UpdateChromosomeSizes(MyMaze);
  
    
  
  while (SYSrunning)
 { 
    std::cout << "Current Genertaion: " << SYSgenerationCounter << std::endl;
  for (int i = 0; i < CHRcount; i++)
  {
    Movement(MyMaze, i);
    //for (int y = 0; y < CHRcount; y++)
    //{
    //  for (int x = 0; x < CHRsize; x++)
    //  {
    //    std::cout << CHRvector[y][x];
    //    if (x % 2)
    //    {
    //      std::cout << " ";
    //    }
    //  }
    //  std::cout << std::endl << std::endl;
    //}
    //std::cout << std::endl << std::endl;



    CHRgene = 0;
  
    //Set DeadSpot
    if (SYSgenerationCounter<300)
    {
      if (MyMaze->GetCHRXCP() != MyMaze->GetCHRXEP()|| MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] != 1)
      {
        MyMaze->SetDeadSpotX(MyMaze->GetCHRXCP());
      }
      if (MyMaze->GetCHRYCP() != MyMaze->GetCHRYEP()|| MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] != 1)
      {
        MyMaze->SetDeadSpotY(MyMaze->GetCHRYCP());
      }
   MAZEarray[MyMaze->GetDeadSpotX()][MyMaze->GetDeadSpotY()] = 5;
   if (MAZEarray[MyMaze->GetDeadSpotX()][MyMaze->GetDeadSpotY()] == 5)
   {
     std::cout << "Marked" << std::endl;

     for (int y = 0; y < 10; y++)
     {
       for (int x = 0; x < 10; x++)
       {
         std::cout << MAZEarray[x][y] << " ";
       }
       std::cout << std::endl;
     }
   }

    }
    if (SYSgenerationCounter>300 && SYSgenerationCounter<600)
    {
      if (MyMaze->GetCHRXCP() != MyMaze->GetCHRXEP() || MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] != 1 || MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] != 6)
      {
        MyMaze->SetDeadSpotX(MyMaze->GetCHRXCP());
      }
      if (MyMaze->GetCHRYCP() != MyMaze->GetCHRYEP() || MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] != 1 || MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] != 6)
      {
        MyMaze->SetDeadSpotY(MyMaze->GetCHRYCP());
      }
      MAZEarray[MyMaze->GetDeadSpotX()][MyMaze->GetDeadSpotY()] = 6;
      if (MAZEarray[MyMaze->GetDeadSpotX()][MyMaze->GetDeadSpotY()] == 6)
      {
        std::cout << "Marked" << std::endl;

        for (int y = 0; y < 10; y++)
        {
          for (int x = 0; x < 10; x++)
          {
            std::cout << MAZEarray[x][y] << " ";
          }
          std::cout << std::endl;
        }
      }

    }
    
      Fitness_calculation(MyMaze, MAZEarray, CHRXoffset, CHRYoffset, CHRfitness, CHRgenerationFitnessTotal, i);
    
    //Calculate the Fitness
   
    //If final chromosome position is not equal to the finish position assign this position to dead zone
    //if it finishes on the deadzone give it as worse fitness as if it landed on the furthest away from the maze finish
  
  }

  if (SYScontinue)
   
  {
    Create_Individuals(CHRfitnessScore, CHRfitness, CHRgenerationFitnessTotal, CHRvector, PCHRvector);

    //Crossover where the magic happens
    Crossover(CHRcount, CHRsize, CHRtempVector, PCHRvector, CHRvector);



    Mutation(CHRvector);

    SYSrunCycles++;
    SYSgenerationCounter = SYSrunCycles;

  }
}
std::cout << "Succesful Route(X/Y): " << std::endl;
double time_elapsed = double(SYSendTime - SYSstartTime);
while (CHRgene < CHRsize)
{
  if (CHRtempVector[CHRgene] == 1 && CHRtempVector[CHRgene + 1] == 1)
    //move up;
  {
    MyMaze->SetCHRYCP(MyMaze->GetCHRYCP() - 1);
    if (MyMaze->GetCHRYCP() < 0)              //Hack
    {
      MyMaze->SetCHRYCP(MyMaze->GetCHRYCP() * -1);
    }
    if (MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] == 1 || MyMaze->GetCHRXCP() < 0 || MyMaze->GetCHRYCP() < 0 || MyMaze->GetCHRXCP() >= MyMaze->GetMazeX() || MyMaze->GetCHRYCP() >= MyMaze->GetMazeY()) //
    {
      MyMaze->SetCHRYCP(MyMaze->GetCHRYCP() + 1);
    }
    else
    {
      MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] = 4;
    }
  }
  else if (CHRtempVector[CHRgene] == 0 && CHRtempVector[CHRgene + 1] == 1)
    //move right
  {
    MyMaze->SetCHRXCP(MyMaze->GetCHRXCP() + 1);
    if (MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] == 1 || MyMaze->GetCHRXCP() < 0 || MyMaze->GetCHRYCP() < 0 || MyMaze->GetCHRXCP() >= MyMaze->GetMazeX() || MyMaze->GetCHRYCP() >= MyMaze->GetMazeY()) //
    {
      MyMaze->SetCHRXCP(MyMaze->GetCHRXCP() - 1);
    }
    else
    {

      MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] = 4;

    }
  }
  else if (CHRtempVector[CHRgene] == 0 && CHRtempVector[CHRgene + 1] == 0)
    //move down
  {
    MyMaze->SetCHRYCP(MyMaze->GetCHRYCP() + 1);
    if (MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] == 1 || MyMaze->GetCHRXCP() < 0 || MyMaze->GetCHRYCP() < 0 || MyMaze->GetCHRXCP() >= MyMaze->GetMazeX() || MyMaze->GetCHRYCP() >= MyMaze->GetMazeY()) //
    {
      MyMaze->SetCHRYCP(MyMaze->GetCHRYCP() - 1);
    }
    else
    {

      MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] = 4;

    }
  }
  else if (CHRtempVector[CHRgene] == 1 && CHRtempVector[CHRgene + 1] == 0)
    //move left
  {
    MyMaze->SetCHRXCP(MyMaze->GetCHRXCP() - 1);
    if (MyMaze->GetCHRXCP() < 0)                //Hack
    {
      MyMaze->SetCHRXCP(MyMaze->GetCHRXCP() * -1);
    }
    if (MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] == 1 || MyMaze->GetCHRXCP() < 0 || MyMaze->GetCHRYCP() < 0 || MyMaze->GetCHRXCP() >= MyMaze->GetMazeX() || MyMaze->GetCHRYCP() >= MyMaze->GetMazeY()) //
    {
      MyMaze->SetCHRXCP(MyMaze->GetCHRXCP() + 1);
    }
    else
    {

      MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] = 4;

    }

  }
  CHRgene = CHRgene + 2;
  std::cout << MyMaze->GetCHRXCP() << "," << MyMaze->GetCHRYCP() << " ";
  std::cout << " ";
}


std::cout << std::endl;
std::cout << "Time to calculate the route (ms): " << time_elapsed << std::endl;

MAZEarray[MyMaze->GetCHRXEP()][MyMaze->GetCHRYEP()] = 3;
MAZEarray[MyMaze->GetCHRXSP()][MyMaze->GetCHRXSP()] = 2;
std::cout << std::endl;

for (int y = 0; y < MyMaze->GetMazeY(); y++)
{
  for (int x = 0; x < MyMaze->GetMazeX(); x++)
  {

    if (MAZEarray[x][y] == 0)
      std::cout << "0" << " ";
    else if (MAZEarray[x][y] == 1)
      std::cout << "1" << " "; //Wall
    else if (MAZEarray[x][y] == 2)
      std::cout << "2" << " "; //start
    else if (MAZEarray[x][y] == 3)
      std::cout << "3" << " "; //finish
    else if (MAZEarray[x][y] == 5)
      std::cout << "D" << " "; //route
    else if (MAZEarray[x][y] == 4)
      std::cout << "R" << " "; //route


  }
  std::cout << std::endl;
}




}


//randomly selects a number between 0 and 1
float Chromosome::randomizer()
{
  std::uniform_real_distribution<float> distribution(0, 1);
  std::random_device rd;
  std::default_random_engine generator(rd());
  return distribution(generator);
}
//recursive addition for individualSelector

//randomly choose an individual, based on their fitness, for breeding
int Chromosome::IndividualSelector(std::vector<float> CIndividual)
{
  float SpinningArrow = { 0 };
  float total = 0;
  SpinningArrow = randomizer();
  //Convert to percentage
  SpinningArrow = SpinningArrow * 100;
  for (int i = 0; i < CHRcount; i++)
  {
    if (SpinningArrow >= total && SpinningArrow < total + CIndividual[i])
    {
      return i;
    }
    else
    {
      total = total + CIndividual[i];
    }
  }
}
//find the chromosome with the best fitness and return the chromosome number. !fitness
int Chromosome::BestFitness(std::vector<float> fitness)
{
  float bestFitness = { 0 };
  float chromosomeNumber = { 0 };
  for (int i = 0; i < CHRcount; i++)
  {
    if (fitness[i] > bestFitness)                                        //if the current best chromosome is smaller that the index, store the new index in bestFitness
    {
      bestFitness = fitness[i];
      chromosomeNumber = i;
    }
  }

  return chromosomeNumber;
}
//finds the second best fitness to ensure variety

//creates a random number between 0 and 1, and then checks to see if it makes the crossover rate to determin whether a two parents will breed
bool Chromosome::CHRcrossOverCheck()
{
  float CrossOverRate = 0.7;
  float CrossOverScore = 0;
  CrossOverScore = randomizer();
  if (CrossOverScore <= CrossOverRate)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
//Does Crossover by taking two parents that are next to each other and swapping half of their genes
//Create the individuals
void Chromosome::Create_Individuals(std::vector<float>& CHRfitnessScore, std::vector <float>&  CHRfitness, float& CHRgenerationFitnessTotal, std::vector< std::vector<float> > &CHRvector, std::vector< std::vector<float> > &PCHRvector)
{
  for (int i = 0; i < CHRcount; i++)
  {
    CHRfitnessScore[i] = CHRfitness[i] / CHRgenerationFitnessTotal;
    CHRfitnessScore[i] = CHRfitnessScore[i] * 100;

  }
  CHRgenerationFitnessTotal = 0;

  //Generator for Spinning Arrow Function
  i = 0;
  // Actual working thing
  z = 0;
  //Parent 1
  // Best Parent Function


  z = BestFitness(CHRfitness);
  for (int x = 0; x < CHRsize; x++)
  {
    PCHRvector[0][x] = CHRvector[z][x];

  }
  //Rest of Parents function
  //Rest of parents
  for (int y = 1; y < CHRcount; y++)
  {

    i = IndividualSelector(CHRfitnessScore);
    for (int x = 0; x < CHRsize; x++)
    {
      PCHRvector[y][x] = CHRvector[i][x];

    }

  }
}

void Chromosome::Mutation(std::vector<std::vector<float>> &CHRvector)    //this is where we bring in the x-men ;)
{
  float CHRmutationRate = 0;
  float SYSvalue = CHRsize;
  CHRmutationRate = 0.5;
  CHRmutationRate;
  for (int y = 2; y < CHRcount; y++)
  {
    for (int x = 0; x < CHRsize; x++)
    {
      if (randomizer() < CHRmutationRate)
      {

        if (CHRvector[y][x] == 1)
        {
          CHRvector[y][x] = 0;
        }
        else
        {
          CHRvector[y][x] = 1;
        }
      }
    }
  }
}

//Where Crossover Happens
void Chromosome::Crossover(int& CHRcount, int& CHRsize, std::vector <float>& CHRtempVector, std::vector< std::vector<float> >& PCHRvector, std::vector< std::vector<float> >& CHRvector)
{
  a = { 2 };
  b = { 0 };
  b = a + 1;
  for (a; a < CHRcount; a++)
  {
    if (CHRcrossOverCheck() == 1)
    {

      for (int x = 0; x < CHRsize; x++)
      {
        if (x > CHRsize / 2)
        {
          CHRtempVector[x] = PCHRvector[a][x];
        }
      }
      for (int x = 0; x < CHRsize; x++)
      {
        if (x > CHRsize / 2)
        {
          PCHRvector[a][x] = PCHRvector[b][x];
        }
      }
      for (int x = 0; x < CHRsize; x++)
      {
        if (x > CHRsize / 2)
        {
          PCHRvector[b][x] = CHRtempVector[x];
        }
      }
    }
  }
  for (int y = 0; y < CHRcount; y++)
  {
    for (int x = 0; x < CHRsize; x++)
    {
      CHRvector[y][x] = PCHRvector[y][x];
    }
  }
}

//Fitness Calculation
void Chromosome::Fitness_calculation(Maze* MyMaze, std::vector<std::vector<int>>&MAZEarray, std::vector<int>& CHRXoffset, std::vector<int> &CHRYoffset, std::vector <float> &CHRfitness, float& CHRgenerationFitnessTotal, int i)
{

  CHRXoffset[i] = MyMaze->GetCHRXEP() - MyMaze->GetCHRXCP();
  if (CHRXoffset[i] < 0)
  {
    CHRXoffset[i] = CHRXoffset[i] * -1;
  }
  CHRYoffset[i] = MyMaze->GetCHRYEP() - MyMaze->GetCHRYCP();
  if (CHRYoffset[i] < 0)
  {
    CHRYoffset[i] = CHRYoffset[i] * -1;
  }
  if (SYSgenerationCounter < 300)
  {
    CHRfitness[i] = CHRXoffset[i] + CHRYoffset[i] + 1;
    if (MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] == 2)
    {
      std::cout << "Landed on the start" << std::endl;
      CHRfitness[i] = 5000;
    }
  }
  if (SYSgenerationCounter > 300)
  {
    if (MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] ==5)
    {
      std::cout << "Landed on a deadpost" << std::endl;
      CHRfitness[i] = 5000;
    }
    else  if (MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] == 0)
    {
      std::cout << "////////////////////////////////////////////////////////////Landed on a new Spot" << std::endl;
 //     MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] = 6;
      CHRfitness[i] = CHRXoffset[i] + CHRYoffset[i]+1;
    }
    else  if (MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] == 2)
    {
      std::cout << "Landed on the start" << std::endl;
       CHRfitness[i] = 5000;
    }
    else if (MAZEarray[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] == 6)
     {
        
        if (SYSgenerationCounter < 600)
        {
          std::cout << "////////////////////////////////////////////////////////////Landed on a new deadpost" << std::endl;
          CHRfitness[i] = (CHRXoffset[i] + CHRYoffset[i] + 1) * 15;
        }
        else if (SYSgenerationCounter > 600)
        {
          std::cout << "////////////////////////////////////////////////////////////Landed on a new deadpost AND PUNISHED" << std::endl;
          CHRfitness[i] = 5000;
        }

     }
    }

 
 
   
 
  CHRfitness[i] = 1 / CHRfitness[i];
  std::cout << "Fitness of Chromosome: ";
  std::cout << CHRfitness[i] << std::endl << std::endl;
  CHRgenerationFitnessTotal += CHRfitness[i];

  //Reset the Current Position for the next chromosome
  MyMaze->SetCHRXCP(MyMaze->GetCHRXSP());
  MyMaze->SetCHRYCP(MyMaze->GetCHRYSP());

}

void Chromosome::CHRGenerator(std::vector<std::vector<float>>&CHRvector)                  // randomizing the chromosomes
{
  for (int y = 0; y < CHRcount; y++)
  {
    for (int x = 0; x < CHRsize; x++)
    {
      CHRvector[y][x] = randomizer();
      CHRvector[y][x] = (int)round(CHRvector[y][x]);
    }
  }
}

int Chromosome::MovementCount(int MazeX, int MazeY)
{
  float totalMovestemp;
  int totalMoves;
  totalMovestemp = MazeX * MazeY;
  totalMovestemp = totalMovestemp * 0.7;
  totalMovestemp = round(totalMovestemp);
  totalMoves = totalMovestemp;
  if (totalMoves % 2)
  {
    totalMoves = totalMoves - 1;
  }
  return totalMoves;
}

//Movement Function
void Chromosome::Movement(Maze* MyMaze, int i) {
  while (CHRgene < CHRsize)
  {
    if (CHRvector[i][CHRgene] == 1 && CHRvector[i][CHRgene + 1] == 1)
      //move up;
    {
      MyMaze->SetCHRYCP(MyMaze->GetCHRYCP() - 1);


      if (MyMaze->GetCHRYCP() < 0)                //Hack
      {
        MyMaze->SetCHRYCP(MyMaze->GetCHRYCP() * -1);
      }
      if (MyMaze->GetMAZEvector()[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] == 1 || MyMaze->GetCHRXCP() < 0 || MyMaze->GetCHRYCP() < 0 || MyMaze->GetCHRXCP() >= MyMaze->GetMazeX() || MyMaze->GetCHRYCP() >= MyMaze->GetMazeY()) //
      {
        MyMaze->SetCHRYCP(MyMaze->GetCHRYCP() + 1);
        if (MyMaze->GetCHRXCP() < 0)              //Hack
        {
          MyMaze->SetCHRXCP(MyMaze->GetCHRXCP()* -1);
        }
      }
    }
    else if (CHRvector[i][CHRgene] == 0 && CHRvector[i][CHRgene + 1] == 1)
      //move right
    {
      MyMaze->SetCHRXCP(MyMaze->GetCHRXCP() + 1);
      if (MyMaze->GetMAZEvector()[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] == 1 || MyMaze->GetCHRXCP() < 0 || MyMaze->GetCHRYCP() < 0 || MyMaze->GetCHRXCP() >= MyMaze->GetMazeX() || MyMaze->GetCHRYCP() >= MyMaze->GetMazeY()) //
      {
        MyMaze->SetCHRXCP(MyMaze->GetCHRXCP() - 1);
      }
    }
    else if (CHRvector[i][CHRgene] == 0 && CHRvector[i][CHRgene + 1] == 0)
      //move down
    {
      MyMaze->SetCHRYCP(MyMaze->GetCHRYCP() + 1);
      if (MyMaze->GetMAZEvector()[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] == 1 || MyMaze->GetCHRXCP() < 0 || MyMaze->GetCHRYCP() < 0 || MyMaze->GetCHRXCP() >= MyMaze->GetMazeX() || MyMaze->GetCHRYCP() >= MyMaze->GetMazeY()) //
      {
        MyMaze->SetCHRYCP(MyMaze->GetCHRYCP() - 1);
        if (MyMaze->GetCHRYCP() < 0)                //Hack
        {
          MyMaze->SetCHRYCP(MyMaze->GetCHRYCP()* -1);
        }
      }
    }
    else if (CHRvector[i][CHRgene] == 1 && CHRvector[i][CHRgene + 1] == 0)
      //move left
    {

      MyMaze->SetCHRXCP(MyMaze->GetCHRXCP() - 1);
      if (MyMaze->GetCHRXCP() < 0)              //Hack
      {
        MyMaze->SetCHRXCP(MyMaze->GetCHRXCP()* -1);
      }
      if (MyMaze->GetMAZEvector()[MyMaze->GetCHRXCP()][MyMaze->GetCHRYCP()] == 1 || MyMaze->GetCHRXCP() < 0 || MyMaze->GetCHRYCP() < 0 || MyMaze->GetCHRXCP() >= MyMaze->GetMazeX() || MyMaze->GetCHRYCP() >= MyMaze->GetMazeY()) //
      {

        MyMaze->SetCHRXCP(MyMaze->GetCHRXCP() + 1);
      }
    }
    if (MyMaze->GetCHRYCP() == MyMaze->GetCHRYEP() && MyMaze->GetCHRXCP() == MyMaze->GetCHRXEP())
    {
      std::cout << std::endl;
      std::cout << "Goal reached In Generation: " << SYSgenerationCounter << std::endl;
      for (int z = 0; z < CHRsize; z++)
      {
        CHRtempVector[z] = CHRvector[i][z];
      }
      SYSendTime = clock();
      SYSrunning = false;
      SYScontinue = false;
      break;
    }
    CHRgene = CHRgene + 2;
  }
}

void Chromosome::UpdateChromosomeSizes(Maze* MyMaze) 
{
  CHRsize = MovementCount(MyMaze->GetMazeX(), MyMaze->GetMazeY());
  
  for (int i = 0; i<CHRcount; i++)
  {
    CHRvector.push_back(std::vector<float>());
    for (int j = 0; j<CHRsize; j++)
    {
      CHRvector[i].push_back(j);
    }
  }
  CHRGenerator(CHRvector);

  for (int i = 0; i<CHRsize; i++)
  {
    CHRtempVector.push_back(i);

  }
  for (int i = 0; i<CHRcount; i++)
  {
    PCHRvector.push_back(std::vector<float>());
    for (int j = 0; j<CHRsize; j++)
    {
      PCHRvector[i].push_back(j);
    }
  }
  CHRGenerator(PCHRvector);
}