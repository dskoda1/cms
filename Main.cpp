//Library includes



//Header file includes
#include "io/ioI.hpp"
#include "io/cli.hpp"

#include "commands/Command.hpp"
#include "commands/Post.hpp"
//Namespaces
using namespace cms;
using namespace std;

//Function stubs
void displayCmsMenu();
string identifyCommandType(string cIn);

int main(int argc, char** argv){
  cout << "Welcome to the Commodity Market System! (CMS)" << endl;
  cout << "Ctrl + c, or simply \"e\" to exit." << endl;
  cout << "Please begin issuing commands. " << endl;

  //Initialize the communication layer of choice
  ioI * commLayer = new cli(); 
  string line = "", type = "", command = "";
  while((line = commLayer->getMessage()) != "e"){
    command = string(line);
    type = identifyCommandType(line);

    Command * comm;
    //Identify the command type and create an instance of it
    if(type == "POST"){
      comm = new Post(command);
    }else if(type == "other commands here"){

    }else{
      cout << "Unrecognized command: " << endl;
      cout << command << endl;
      cout << "Please try again." << endl;
    }

  }

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

