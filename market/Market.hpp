#ifndef MARKET_HPP
#define MARKET_HPP

#include "../commands/Command.hpp"
#include "../commands/Post.hpp"
#include "../commands/List.hpp"

#include "../util/Grammar.hpp"
#include "../util/MarketException.hpp"

#include "Database.hpp"

#include <vector>
#include <string>
#include <map>

#include <iostream>
#include <sstream>
namespace cms {

  class Market {

    public:
      Market() : db{new Database()}
      ,orderNumber{0} {}

      ~Market(){
        delete db;
      }

      /**
       * Ingestion methods for different types of commands
       */
      std::string ingestOrder(Post * order){
        //Save the order number and post to DB
        order->setOrderId(orderNumber++);
        db->saveOrder(order);
        
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
          ordersToPrint = db->getOrders();
        }else if(order->getListStatus() == 1){
          //Get just posts from the commodity requested
          ordersToPrint = db->getOrders(order->getCommodity());
        }else{
          //Get posts from a specific commodity and dealer
          ordersToPrint = db->getOrders(order->getCommodity(), order->getDealerId());
        }  

        //generate the actual string using a ss now
        std::stringstream ss;
        for(auto it = ordersToPrint.begin(); it != ordersToPrint.end(); ++it){
          ss << generateOrderInfo(*it, "\n");
        }
        ss << "END OF LIST";
        return ss.str();

      }




      /**
       * Ingestion of a revoke order
       * 1. Find the post with matching orderId
       *    could throw UNKNOWN_ORDER exception 
       *    inside getOrderById routine
       * 2. Verify the dealerId's match
       *    could throw UNAUTHORIZED exception
       * 3. Erase the order
       */
      std::string ingestOrder(Revoke * order){

        Post * postReq = db->getOrder(order->getOrderId());
        
        //Ensure authorization now
        if(order->getDealerId() != postReq->getDealerId()){
          throw MarketException("UNAUTHORIZED");
        } 

        //Got to this point, remove the order
        db->deleteOrder(order->getOrderId());

        std::stringstream ss;
        ss << order->getOrderId();
        ss << " HAS BEEN REVOKED";
        return ss.str();  
      }

      /**
       * Delete an order by id
       * throw a market exception if post is not found
      void deleteOrder(int orderIdIn){
        bool deleted = false;

        for(auto i = orders->begin(); i != orders->end(); ++i){
          for(auto j = i->second->begin(); j != i->second->end(); ++j){
            if((*j)->getOrderId() == orderIdIn){
              i->second->erase(j);
              deleted = true;
            }
          }
        }
        
        if(!deleted){
          throw MarketException("UNKNOWN_ORDER insde delete order");
        }
      }
       */

      friend std::ostream& operator <<(std::ostream & os, const Market& m){

        os << *(m.db) << std::endl;
        return os;
      }
    private:
      std::string generateOrderInfo(Post * order, std::string optDelimit = ""){
        std::stringstream ss;
        ss << order->getOrderId() << " ";
        ss << order->getDealerId() << " ";
        ss << order->getSide() << " ";
        ss << order->getCommodity() << " ";
        ss << order->getAmount() << " ";
        ss << std::to_string(order->getPrice()); 
        ss << optDelimit;
        return ss.str();
      }
      Database * db; 
      int orderNumber;
  };


}



#endif //MARKET_HPP
