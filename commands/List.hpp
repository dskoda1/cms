#ifndef LIST_HPP
#define LIST_HPP

#include "Command.hpp"
#include "../util/Grammar.hpp"
#include "../util/ParseException.hpp"
namespace cms{

  class List : public Command{

    public:
    List(std::string & cIn) : Command{cIn} {}

    virtual ~List(){}

    /**
     * LIST [{COMMODITY} [{DEALER ID}]]
     * Commodity and dealer id are optional.
     */
    virtual bool validate(){
      if(splitCommand->size() == 2){
        listStatus = 0;
        return true;
      }
      
      if(splitCommand->size() > 2){
        //Validate commodity
        commodity = splitCommand->at(2);
        if(!validateCommodity(commodity)){
          throw ParseException(generateError("commodity", commodity));
        }
        listStatus = 1;
      }

      if(splitCommand->size() > 3){
        //validate dealer id
        dealerId = splitCommand->at(3);
        if(!validateDealer(dealerId)){
          throw ParseException(generateError("UNKNOWN_DEALER", dealerId));
        }
        listStatus = 2;
      }
      return true;
    }      

    int getListStatus() const { return listStatus; }

    private:

      //0 means print all
      //1 means print only of commodity
      //2 means print only of commodity from dealerId
      int listStatus;
  };
}



#endif //LIST_HPP
