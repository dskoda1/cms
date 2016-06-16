//Library includes
#include <vector>


//Header file includes
#include "io/ioI.hpp"
#include "io/cli.hpp"
#include "io/FileReader.hpp"

#include "commands/Command.hpp"
#include "commands/Post.hpp"
#include "commands/List.hpp"
#include "commands/Revoke.hpp"

#include "market/Market.hpp"

//Namespaces
using namespace cms;
using namespace std;

//Function stubs
string identifyCommandType(string &cIn);
ioI * parseArgs(int argc, char** argv);

int main(int argc, char** argv){

  //Initialize the communication layer of choice
  ioI * commLayer = parseArgs(argc, argv);

  commLayer->sendLine("Welcome to the Commodity Market System! (CMS)");
  commLayer->sendLine("Ctrl + c, or simply \"e\" to exit.");
  commLayer->sendLine("Please begin issuing commands.");
  string line = "", type = "", output = "";

  //And the market
  Market * m = new Market();


  //Loop to receive commands in
  while((line = commLayer->getMessage()) != "e"){
    Command * command;

    //Identify the command type and create an instance of it
    type = identifyCommandType(line);
    output = "";
    try{
      if(type == "POST"){
        command = new Post(line);
        command->validate();
        output = m->ingestOrder(dynamic_cast<Post *>(command));
      }else if(type == "LIST"){
        command = new List(line);
        command->validate();
        output = m->ingestOrder(dynamic_cast<List *>(command));
      }else if(type == "AGRESS"){

      }else if(type == "REVOKE"){

      }else if(type == "other commands here"){

      }else{
        commLayer->sendLine("INVALID_MESSAGE");

      }
      commLayer->sendLine(output);
    }catch(const ParseException& pe){
      commLayer->sendLine(line);
      commLayer->sendLine(pe.what());
    }
  }
  //cleanup
  delete commLayer;
  delete m;
}


string identifyCommandType(string & cIn){
  //Grab the second string in the arg
  stringstream ss(cIn);
  string temp;
  ss >> temp;
  ss >> temp;
  return temp;
}

ioI * parseArgs(int argc, char** argv){

  ioI * ret;
  if(argc == 2){
    ret = new FileReader(argv[1]);
  }else{
    ret = new cli();
  }

  return ret;
}

