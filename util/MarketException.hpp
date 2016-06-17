#ifndef MARKET_EXCEPTION_HPP
#define MARKET_EXCEPTION_HPP

namespace cms{

  class MarketException : public std::exception {

    protected:
      std::string m;

    public:
      explicit MarketException(const std::string & mIn) : m{mIn} {}

      virtual const char * what() const throw(){
        return m.c_str();
      }
  };

}

#endif //MARKET_EXCEPTION_HPP
