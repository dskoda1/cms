#ifndef cli_hpp
#define cli_hpp


#include "ioI.hpp"
#include <string>
#include <iostream>
#include <istream>

namespace cms {

  class cli : public ioI {
  
    public:
      std::string getMessage(){
        std::string ret = "";
        std::getline(std::cin, ret);
        //std::getline(std::cin, &ret);
        return ret;
      }

      void sendMessage(const std::string s){
        std::cout << s;
      }
      
      void sendLine(const std::string s){
        std::cout << s << std::endl;
      }
    private:

  };

}

#endif //cli_hpp



