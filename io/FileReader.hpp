#ifndef FILE_READER_HPP
#define FILE_READER_HPP


#include "ioI.hpp"
#include <string>
#include <iostream>
#include <fstream>

namespace cms {

  class FileReader : public ioI {


    public:
      std::string getMessage(){
        std::string ret;
        std::getline(inFile, ret);
        return ret;
      }

      void sendMessage(const std::string s){
        std::cout << s;

      }

      void sendLine(const std::string s){
        std::cout << s << std::endl;
      }

      FileReader(std::string nameIn): inFile{nameIn} 
      {
      }

    private:
      std::string name;
      std::ifstream inFile;



  };
}
#endif //FILE_READER_HPP
