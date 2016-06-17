#ifndef PARSE_EXCEPTION_HPP
#define PARSE_EXCEPTION_HPP


#include "MarketException.hpp"

namespace cms {

  class ParseException : public MarketException {

    public:
      explicit ParseException(const std::string& mIn) : MarketException{mIn} {} 
     

      virtual const char * what() const throw(){
        return m.c_str();
      }
  }; 


}

#endif //PARSE_EXCEPTION_HPP
