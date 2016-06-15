#ifndef LIST_HPP
#define LIST_HPP

#include "../market/Market.hpp"
#include "Command.hpp"
#include "../util/Grammar.hpp"
#include "../util/ParseException.hpp"
namespace cms{

  class List : public Command{
    friend class Market;

    public:
    List(std::string & cIn) : Command{cIn} {}

    virtual ~List(){}

    /**
     * LIST [{COMMODITY} [{DEALER ID}]]
     * Commodity and dealer id are optional.
     */
    virtual bool validate(){
      bool ret = false;
      if(splitCommand->size() == 2){
        ret = true;
      }else if(splitCommand->size() == 3){
        //Validate commodity
        commodity = splitCommand->at(2);
        if(!validateCommodity(commodity)){
          throw ParseException(generateError("commodity", commodity));
        }


      }


      return true;
    }      

    private:

  };
}



#endif //LIST_HPP
