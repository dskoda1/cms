#ifndef REVOKE_HPP
#define REVOKE_HPP

#include "Command.hpp"
#include "../util/ParseException.hpp"

namespace cms {
  class Revoke : public Command {
    public:
      Revoke(std::string & cIn) : Command{cIn} {}

      virtual ~Revoke(){}

      /**
       * {dealerId} REVOKE {orderId}
       */
      virtual bool validate(){
        if(splitCommand->size() != 3){
          throw ParseException("UNKNOWN_MESSAGE");
        }
        //Defer lookup of order for validation that the
        //same dealer is the one requesting a delete to
        //the market. We dont want HSBC revoking an order
        //from CITI, for example.

        return true;
      }

    private:

  };
}

#endif //REVOKE_HPP
