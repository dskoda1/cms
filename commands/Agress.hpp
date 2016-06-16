#ifndef AGRESS_HPP
#define AGRESS_HPP

#include "Command.hpp"
#include "../util/ParseException.hpp"

namespace cms {
  class Agress : public Command {
    public:
      Agress(std::string & cIn) : Command{cIn} {}

      virtual ~Agress(){}

      virtual bool validate() {

        return false;
      }


  };
}
#endif //AGRESS_HPP
