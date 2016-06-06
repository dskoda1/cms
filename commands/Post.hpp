#ifndef POST_HPP
#define POST_HPP

#include "Command.hpp"

namespace cms {

  class Post : public Command {
    public:
      Post(std::string cIn) : Command{cIn} {}


      bool validate(){
        

        return true;
      }

      //Output operator for debugging 
      friend std::ostream & operator << (std::ostream & os, const Command & c){
        os << "Command type: " << c.getCommandType() << "\n";
        os << "Dealer ID: " << c.getDealerId() << "\n";
        return os;
      }

  };
}
#endif //POST_HPP
