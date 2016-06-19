#ifndef COMMAND_HPP
#define COMMAND_HPP


#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "../util/Grammar.hpp"
#include "../util/ParseException.hpp"
namespace cms{


  /**
   * A command is the basic unit of interaction with this
   * platform. The commands fall under:
   *  {DEALER_ID} {COMMAND}
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
   *  This is a request to revoke a specific order that has
   *  already been submitted, out of the system.
   *  "REVOKE" {ORDER_ID}
   * 4. Check orders
   *
   * 5. List orders
   */  
  class Command{
    public:
      Command(std::string cIn) : command{cIn} {
        parseCommand();
        validate();
      }
      virtual ~Command(){
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
        //error check for at least 2 items. 
        //If command is incorrect but has more than 2 items
        //an exception will be thrown further down the parse
        //chain in subclasses.
        if(splitCommand->size() < 2){
          throw ParseException("UNKNOWN_MESSAGE");
        }


        //Save a couple things we know about the command
        //to be true for all commands

        //Also validate the dealer id and the command type
        dealerId = splitCommand->at(0);
        if(!validateDealer(dealerId)){
          throw ParseException("INVALID_DEALER");
        }

        commandType = splitCommand->at(1);
        if(!validateCommand(commandType)){
          throw ParseException("INVALID_COMMAND");
        }
      }

      virtual bool validate() = 0;



      //const getters
      std::string getCommandType() const { return commandType; }
      std::string getDealerId() const { return dealerId; }
      int getOrderId() const { return orderId; }
      std::string getCommodity() const { return commodity; }
      std::string getSide() const { return side; }
      int getAmount() const { return amount; }
      double getPrice() const { return price; }

    protected:
      //@Deprecated
      std::string generateError(std::string part, std::string partVal){
        std::string ret = "\n\tERROR THROWN PARSING COMMAND\n";
        ret += "\tError validating " + part + " of: " + partVal + "\n";
        ret += "\tOriginated from command: \n\t" + command + "\n";
        return ret;
      }
      /**
       * Validation methods to be used by derived classes
       */

      bool validateSide(std::string side){
        bool ret = false;
        for(int i = 0; i < NUM_SIDES; ++i){
          if(side == VALID_SIDES[i]){ ret = true; }
        }

        return ret;

      }
      bool validateCommodity(std::string commod){
        bool ret = false;

        for(int i = 0; i < NUM_COMMODS; ++i){
          if(commod == VALID_COMMODS[i]){ ret = true; }
        }

        return ret;
      }

      bool validateDealer(std::string dealer){
        bool ret = false;

        for(int i = 0; i < NUM_DEALERS; ++i){
          if(dealer == VALID_DEALERS[i]){ ret = true; }
        }

        return ret;
      }

      bool validateCommand(std::string command){
        bool ret = false;
        for(int i = 0; i < NUM_COMMANDS; ++i){
          if(command == VALID_COMMANDS[i]){ ret = true; }
        }
        return ret;
      }

      /*Data members*/
      std::string command;
      std::vector<std::string> * splitCommand;
      
      int orderId;
      std::string commandType; 
      std::string dealerId;
      std::string commodity;
      std::string side;
      int amount;
      double price;


    private:



  };

}

#endif //COMMAND_HPP


