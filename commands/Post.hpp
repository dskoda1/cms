#ifndef POST_HPP
#define POST_HPP

#include "Command.hpp"
#include "../util/ParseException.hpp"
namespace cms {

  class Post : public Command {
    public:


      /*Data members
      std::string command;
      std::vector<std::string> * splitCommand;
      std::string commandType;
      std::string dealerId;
      int orderId;
      std::string commodity;
      std::string side;*/

      Post(std::string & cIn) : Command{cIn} {}

      virtual ~Post(){
      }

      //Validate the things specific to a post
      //POST {SIDE} {COMMODITY} {AMOUNT} {PRICE}
      bool validate(){
        //Ensure length first
        if(splitCommand->size() != 6){
          throw ParseException("INVALID MESSAGE\n");
        }

        side = splitCommand->at(2);
        if(!validateSide(side)){
          throw ParseException(generateError("side", side));
        }
        
        commodity = splitCommand->at(3);
        if(!validateCommodity(commodity)){
          throw ParseException(generateError("commodity", commodity));
        }

        amount = atoi(splitCommand->at(4).c_str());
        price = std::stod(splitCommand->at(5).c_str());
        return true;
      }

      void setOrderId(int id){
        orderId = id;
      }


  };
}
#endif //POST_HPP
