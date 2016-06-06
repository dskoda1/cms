#ifndef COMMAND_HPP
#define COMMAND_HPP


#include <string>
#include <vector>
#include <sstream>
#include <iostream>


namespace cms{


  /**
   * A command is the basic unit of interaction with this
   * platform. The commands fall under:
   *
   * 1. Posting orders
   *  This submits a buy/sell order to the marketplace.
   *  This is an intention to buy/sell a certain number of 
   *  contracts at a certain price.
   *  It follows this structure:
   *  "POST" SIDE COMMODITY AMOUNT PRICE
   * 
   * 2. Aggressing orders
   *  This is a request to take action on an order already
   *  in the system. It follows this structure:
   *  "AGRESS" (ORDER_ID AMOUNT)+
   *
   * 3. Revoke orders
   *
   * 4. Check orders
   *
   * 5. List orders
   */  
   class Command{
      public:
        Command(std::string cIn) : command{cIn} {
          parseCommand();
        }
        ~Command(){
          delete splitCommand;
        }


        
        /**
         * Split the command based on whitespace
         * and store the words in a vector data member.
         */
        void parseCommand(){
          splitCommand = new std::vector<std::string>();
          //Generate an string stream and iterate through it
          std::stringstream ss(command);
          std::string temp;
          while(ss >> temp){
            splitCommand->push_back(temp);
          }
          //Save a couple things we know about the command
          //to be true for all commands
          dealerId = splitCommand->at(0);
          commandType = splitCommand->at(1);
        }

        virtual bool validate() = 0;

                

        //const getters
        std::string getCommandType() const { return commandType; }
        std::string getDealerId() const { return dealerId; }
        int getOrderId() const { return orderId; }
        std::string getCommodity() const { return commodity; }
        std::string getSide() const { return side; }
      protected:
        bool validateSide(std::string side){
          bool ret = false;
          if(side == "BUY"){ ret = true; }
          else if(side == "SELL"){ ret = true; }
          return ret;

        }
        bool validateCommodity(std::string commod){
          bool ret = false;
          if(commod == "GOLD"){ ret = true; }
          else if(commod == "SILV"){ ret = true; }
          else if(commod == "PORK"){ ret = true; }
          else if(commod == "OIL"){ ret = true; }
          else if(commod == "RICE"){ ret = true; }
          return ret;

        }
        
        /*Data members*/
        std::string command;
        std::vector<std::string> * splitCommand;
        std::string commandType; 
        std::string dealerId;
        int orderId;
        std::string commodity;
        std::string side;
       


      private:



  };

}

#endif //COMMAND_HPP


