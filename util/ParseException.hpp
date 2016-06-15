#ifndef PARSE_EXCEPTION_HPP
#define PARSE_EXCEPTION_HPP




namespace cms {

  class ParseException : public std::exception {

    private:
      std::string message;

    public:
      explicit ParseException(const std::string& messageIn): message{messageIn}
      {}

      virtual const char * what() const throw(){
        return message.c_str();
      }
  }; 


}

#endif //PARSE_EXCEPTION_HPP
