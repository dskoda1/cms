//Library includes



//Header file includes
#include "io/ioI.hpp"
#include "io/cli.hpp"

#include "commands/Command.hpp"
#include "commands/Post.hpp"
//Namespaces
using namespace cms;
using namespace std;

int main(int argc, char** argv){

  ioI * commLayer = new cli(); 

  string mes = "DB POST SELL GOLD 1000000 1174.6";

  Command * pc = new Post(mes);
  /*
  if(pc->validateSide("BUY")) 
   cout << "Validation passed" << endl;


  if(pc->validateCommodity("LSKDF")){

    cout << "Validation failed: good" << endl;
  }
  */
}




