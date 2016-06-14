//Library includes
#include <vector>


//Header file includes
#include "io/ioI.hpp"
#include "io/cli.hpp"

#include "commands/Command.hpp"
#include "commands/Post.hpp"

#include "market/Market.hpp"

//Namespaces
using namespace cms;
using namespace std;

//Function stubs
void displayCmsMenu();
string identifyCommandType(string cIn);

void memoryTest(){
  vector<Command *> comms;
  for(int i = 0; i < 10000; ++i){
    comms.push_back(new Post("Testing memory"));
  }


  for(int i = 0; i < 10000; ++i){
    delete comms.at(i);
  }
}

int main(int argc, char** argv){
  cout << "Welcome to the Commodity Market System! (CMS)" << endl;
  cout << "Ctrl + c, or simply \"e\" to exit." << endl;
  cout << "Please begin issuing commands. " << endl;

  //Initialize the communication layer of choice
  ioI * commLayer = new cli(); 
  string line = "", type = "";

  //And the market
  Market * m = new Market();
  while((line = commLayer->getMessage()) != "e"){
    Command * command;
    Post * post;
    //Identify the command type and create an instance of it
    type = identifyCommandType(line);
    if(type == "POST"){
      m->addOrder(new Post(line));
    }else if(type == "LIST"){
      
    
    
    }else if(type == "other commands here"){

    }else{
      cout << "Unrecognized command: " << endl;
      cout << line << endl;
      cout << "Please try again." << endl;
    }

  }

  delete m;
}

void displayCmsMenu(){

}

string identifyCommandType(string cIn){
  //Grab the second string in the arg
  stringstream ss(cIn);
  string temp;
  ss >> temp;
  ss >> temp;
  return temp;
}

