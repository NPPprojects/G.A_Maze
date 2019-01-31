#include "Maze.h"



Maze::Maze(std::ifstream* myfile)
{

  
  for (int i = 0; i<20; i++)
  {
    MAZEarray.push_back(std::vector<int>());
    DeadspotMap.push_back(std::vector<int>());
    for (int j = 0; j<20; j++)
    {
      MAZEarray[i].push_back(j);
      DeadspotMap[i].push_back(j);
    }
  }
  int SYSXtemp = 0;                                                            //temporary storage for the iterater when creating the maze
  int SYSYtemp = 0;
  std::string line;
  std::vector < std::string > Splitline;
  getline(*myfile, line);                                                    //moving the contents of the .txt file into a string 
  splitStringWhitespace(line, Splitline);                                    //removing the blank spaces from string
  MAZEXsize = atoi(Splitline.at(0).c_str());                                //first and second characters of the string will give the size of the maze
  MAZEYsize = atoi(Splitline.at(1).c_str());                                //so they are converted into an int and stored for later
  std::cout << "the size of the maze is(X/Y): " << MAZEXsize << "," << MAZEYsize << std::endl;
  //assigning the the .txt file information into the maze array
  for (int i = 2; i < Splitline.size(); i++)
  {
    MAZEarray[SYSXtemp][SYSYtemp] = atoi(Splitline.at(i).c_str());
    SYSXtemp++;
    //std::cout << MAZEarray[SYSXtemp][SYSYtemp] << " ";
    if (SYSXtemp >= MAZEXsize)
    {
      SYSXtemp = 0;
      SYSYtemp++;
      //        std::cout << std::endl;
    }
  }

  //finding starting point
  for (int y = 0; y < MAZEYsize; y++)
  {
    for (int x = 0; x < MAZEXsize; x++)
    {
      if (MAZEarray[x][y] == 2)
      {
        CHRYstartingPosition = y;
        CHRXstartingPosition = x;
      }
    }
  }
  std::cout << "Starting point:(X/Y) " << CHRXstartingPosition << "," << CHRYstartingPosition << std::endl;
  //finding finish point

  for (int y = 0; y < MAZEYsize; y++)
  {
    for (int x = 0; x < MAZEXsize; x++)
    {
      if (MAZEarray[x][y] == 3)
      {
        CHRYfinish = y;
        CHRXfinish = x;
      }
    }
  }
  std::cout << "Finish point:(X/Y) " << CHRXfinish << "," << CHRYfinish << std::endl;
  CHRYcurrentPosition = CHRYstartingPosition;
  CHRXcurrentPosition = CHRXstartingPosition;
  //SYSstartTime = clock();

}


Maze::~Maze()
{
}


void Maze::splitStringWhitespace(std::string& input, std::vector<std::string>& output)
{
  std::string curr;
  output.clear();
  for (size_t i = 0; i < input.length(); i++)
  {
    if (input.at(i) == ' ' ||
      input.at(i) == '\r' ||
      input.at(i) == '\n' ||
      input.at(i) == '\t')
    {
      if (curr.length() > 0)
      {
        output.push_back(curr);
        curr = "";
      }
    }
    else
    {
      curr += input.at(i);
    }
  }
  if (curr.length() > 0)
  {
    output.push_back(curr);
  }
}

int Maze::GetMazeX() 
{
  return MAZEXsize;
}
int Maze::GetMazeY() 
{
  return MAZEYsize;
}

int Maze::GetCHRYSP()
{
  return CHRYstartingPosition;
}
int Maze::GetCHRXSP()
{
  return CHRXstartingPosition;
}
int Maze::GetCHRXEP()
{
  return CHRXfinish;
}
int Maze::GetCHRYEP()
{
  return CHRYfinish;
}
int Maze::GetCHRYCP()
{
  return CHRYcurrentPosition;
}
int Maze::GetCHRXCP()
{
  return CHRXcurrentPosition;
}
void Maze::SetCHRXCP(int _current)
{
  CHRXcurrentPosition = _current;
}
void Maze::SetCHRYCP(int _current)
{
  CHRYcurrentPosition = _current;
}
std::vector<std::vector<int>> Maze::GetMAZEvector()
{
  return MAZEarray;
}

int Maze::GetDeadSpotX()
{
  return DeadspotX;
}
int Maze::GetDeadSpotY()
{
  return DeadspotY;
}

void Maze::SetDeadSpotX(int _current)
{
  DeadspotX = _current;
}

void Maze::SetDeadSpotY(int _current)
{
  DeadspotY = _current;
}
void Maze::SetDeadSpotMap(int Y, int X)
{
  DeadspotMap[Y][X];
}
std::vector<std::vector<int>> Maze::SetDeadSpotMap()
{
  return DeadspotMap;
}