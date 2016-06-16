#ifndef MARKET_HPP
#define MARKET_HPP

#include "../commands/Command.hpp"
#include "../commands/Post.hpp"
#include "../commands/List.hpp"

#include "../util/Grammar.hpp"

#include <vector>
#include <string>
#include <map>

#include <iostream>
#include <sstream>
namespace cms {



  class Market {

    public:
      Market() : orders{new std::map<std::string, std::vector<Post *> * >}
      ,orderNumber{0}
      {
        for(int i = 0; i < NUM_COMMODS; ++i){
          std::pair<std::string, std::vector<Post *> *> tmp(VALID_COMMODS[i], new std::vector<Post *>);
          orders->insert(tmp);

        } 
      }

      ~Market(){
        //Loop through pairs in the map
        for(auto i = orders->begin(); i != orders->end(); ++i){
          //Loop through items in the vector in this pair
          for(auto j = i->second->begin(); j != i->second->end(); ++j){
            //delete post in vector
            delete *j;
          }
          //delete vector
          delete (i->second);
        }
        //delete map
        delete orders;
      }

      /**
       * Ingestion methods for different types of commands
       */
      std::string ingestOrder(Post * order){
        //insert into the correct vector based on orders commodity
        (*orders)[order->getCommodity()]->push_back(order);
        order->setOrderId(orderNumber++);
        return generateOrderInfo(order, " HAS BEEN POSTED") ;
      }

      /**
       * Ingestion of a list order
       * depending on the listStatus of the order,
       * generate the list of orders requested.
       */
      std::string ingestOrder(List * order){
        std::vector<Post *> ordersToPrint;

        if(order->getListStatus() == 0){
          //Get all posts
          ordersToPrint = getAllOrders();  
        }else if(order->getListStatus() == 1){
          //Get just posts from the commodity requested
          std::vector<Post *> * commodOrders = (*orders)[order->getCommodity()];
          for(auto i = commodOrders->begin(); i != commodOrders->end(); ++i){
            ordersToPrint.push_back(*i);
          }
        }else{
          //Get posts from a specific commodity and dealer
          std::vector<Post *> * commodOrders = (*orders)[order->getCommodity()];
          for(auto i = commodOrders->begin(); i != commodOrders->end(); ++i){
            if((*i)->getDealerId() == order->getDealerId()){
              ordersToPrint.push_back(*i);
            }
          }
        }  

        //generate the actual string using a ss now
        std::stringstream ss;

        for(auto it = ordersToPrint.begin(); it != ordersToPrint.end(); ++it){
          ss << generateOrderInfo(*it, "\n");
        }
        ss << "END OF LIST";
        return ss.str();
      }

      std::vector<Post *> getAllOrders(){
        std::vector<Post *> ret;
        for(auto i = orders->begin(); i != orders->end(); ++i){
          for(auto j = i->second->begin(); j != i->second->end(); ++j){
            ret.push_back(*j);
          }
        }
        return ret;
      } 
      /**
       * Ingestion of a revoke order
       * Ensure the list exists first
       * then erase it from memory
       * if dealer ids match
       */
      std::string ingestOrder(Revoke * order){



      }

      /**
       * User facing order get method
       * also used internally
       */


    private:
      std::string generateOrderInfo(Post * order, std::string optDelimit = ""){
        std::stringstream ss;
        ss << order->getOrderId() << " ";
        ss << order->getDealerId() << " ";
        ss << order->getSide() << " ";
        ss << order->getCommodity() << " ";
        ss << order->getAmount() << " ";
        ss << order->getPrice(); 
        ss << optDelimit;
        return ss.str();
      }

      std::map<std::string, std::vector<Post *> * > * orders;
      int orderNumber;
  };


}



#endif //MARKET_HPP
