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
      Market() : db{new Database()}, orders{new std::map<std::string, std::vector<Post *> * >}
      ,orderNumber{0}
      {
        
        for(int i = 0; i < NUM_COMMODS; ++i){
          std::pair<std::string, std::vector<Post *> *> tmp(VALID_COMMODS[i], new std::vector<Post *>);
          orders->insert(tmp);
        } 
      }

      ~Market(){
        /*
        //delete database;
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
        */
        delete db;
      }

      /**
       * Ingestion methods for different types of commands
       */
      std::string ingestOrder(Post * order){
        //insert into the correct vector based on orders commodity
        order->setOrderId(orderNumber++);
        db->saveOrder(order);
        /*
        (*orders)[order->getCommodity()]->push_back(order);
        */
        
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
          //ordersToPrint = getAllOrders();  
        }else if(order->getListStatus() == 1){
          //Get just posts from the commodity requested
          //ordersToPrint = database->getOrders(order->getCommodity());
          std::vector<Post *> * commodOrders = (*orders)[order->getCommodity()];
          for(auto i = commodOrders->begin(); i != commodOrders->end(); ++i){
            ordersToPrint.push_back(*i);
          }
        }else{
          //Get posts from a specific commodity and dealer
          //ordersToPrint = database->getOrders(order->getCommodity(), order->getDealerId());
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
        /*
        Post * postRequested = getOrderById(order->getOrderId());
        
        if(postRequested->getDealerId() != order->getDealerId()){
          throw MarketException("UNAUTHORIZED inside ingest order");
        }
    
        //Call the delete method
        deleteOrder(order->getOrderId());
        */
        
        std::stringstream ss;
        ss << order->getOrderId();
        ss << " HAS BEEN REVOKED";
        throw MarketException("Unimplemted Exception"); 
        return ss.str(); 
      }

      /**
       * User facing order get methods
       * also used internally
       */
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
       * Get an order by id
       * Throw a market exception if its not there
       */
      Post * getOrderById(int orderIdIn){
        Post * ret = nullptr;
        //Do a naive O(N) search for the order
        //Could be improved in the future if we
        //store additional metadata about each post
        for(auto i = orders->begin(); i != orders->end(); ++i){
          for(auto j = i->second->begin(); j != i->second->end(); ++j){
            if((*j)->getOrderId() == orderIdIn){
              std::cout << generateOrderInfo((*j)) << std::endl;
              ret = *j;
              break;
            }  
          }
        }
        if(ret == nullptr){
          throw MarketException("UNKNOWN_ORDER inside getOrderById");
        }

        return ret;
      }

      /**
       * Delete an order by id
       * throw a market exception if post is not found
       */
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
      Database * db; 
      std::map<std::string, std::vector<Post *> * > * orders;
      int orderNumber;
  };


}



#endif //MARKET_HPP
