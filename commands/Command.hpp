#ifndef COMMAND_HPP
#define COMMAND_HPP


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
        Command(std::string cIn) : command{cIn} {}

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
        std::string command;

      private:



  };

}

#endif //COMMAND_HPP


