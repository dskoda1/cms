#ifndef IOI_HPP
#define IOI_HPP



#include <string>

namespace cms{

  /**
   * The input/output interface to be used
   * in communicating with the user. 
   * The intent of this is to allow the use
   * of different communications with the
   * program to be transparent to the user,
   * whether it be the command line or the
   * network.
   **/
  class ioI {

    public:
      /**
       * Get a message from the communication layer
       */
      virtual std::string getMessage() = 0;
      
      /**
       * Send a message
       */
      virtual void sendMessage(const std::string) = 0;

      virtual ~ioI(){}
    private:

  };



}






#endif //IOI_HPP
