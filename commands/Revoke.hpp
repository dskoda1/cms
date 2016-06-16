#ifndef REVOKE_HPP
#define REVOKE_HPP

#include "Command.hpp"
#include "../util/ParseException.hpp"

namespace cms {
  class Revoke : public Command {
    public:
      Revoke(std::string & cIn) : Command{cIn} {}

      virtual ~Revoke(){}

      virtual bool validate(){

        return false;
      }

    private:

  };
}

#endif //REVOKE_HPP
