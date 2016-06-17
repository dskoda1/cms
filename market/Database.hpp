#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "../commands/Post.hpp"
#include "../util/MarketException.hpp"
#include "../util/Grammar.hpp"
#include <vector>
#include <map>

#include <iostream>


namespace cms {

  class Database {

    public:

      Database() : orders{new std::map<std::string, std::map<int, Post *> *>},
        idBuckets{new std::map<int, std::string>} {
          initOrders();
        }

      ~Database(){
        //Loop through outer map
        for(auto i = orders->begin(); i != orders->end(); ++i){
          //Loop through inner map
          for(auto j = i->second->begin(); j != i->second->end(); ++j){
            //j are pairs of <int, Post*>
            delete j->second;
          }
          //delete the inner map
          delete i->second;
        }
        //delete the outer map
        delete orders;

      }
      //Create
      void saveOrder(Post * order){
        (*orders)[order->getCommodity()]->insert(std::pair<int, Post*>(
              order->getOrderId(), order));

        //Save metadata about what bucket this order is in
        idBuckets->insert(std::pair<int, std::string>(
              order->getOrderId(), order->getCommodity()));

      }

      //Read
      std::vector<Post *> getOrders(){
        std::vector<Post *> ret;
        for(auto i = orders->begin(); i != orders->end(); ++i){
          for(auto j = i->second->begin(); j != i->second->end(); ++j){
            ret.push_back(j->second);
          }
        }
        return ret;
      }
      std::vector<Post *> getOrders(std::string commodity){
        std::vector<Post *> ret;
        auto commodMap = (*orders)[commodity];
        for(auto i = commodMap->begin(); i != commodMap->end(); ++i){
          ret.push_back(i->second);
        }           
        return ret;
      }
      std::vector<Post *> getOrders(std::string commodity, std::string dealerId){
        std::vector<Post *> ret;
        auto commodMap = (*orders)[commodity];
        for(auto i = commodMap->begin(); i != commodMap->end(); ++i){
          if(i->second->getDealerId() == dealerId){
            ret.push_back(i->second);
          }
        } 
        return ret;
      }


      Post * getOrder(int orderId){
        auto iter = idBuckets->find(orderId);
        Post * ret;
        if(iter == idBuckets->end()){
          throw MarketException("UNKNOWN_ORDER");
        }else{
          //Use iter->second to index into orders
          //and find the correct number from there
          auto bucket = orders->find(iter->second);
          ret = bucket->second->find(orderId)->second;
        }
        return ret;
      }

      //Delete
      void deleteOrder(int orderId){
        //Find it in the idBucket
        //Find it in the orders map
        //delete both entries
        auto idBucIter = idBuckets->find(orderId);
        //Make sure its valid
        if(idBucIter == idBuckets->end()){
          throw MarketException("UNKNOWN_ORDER");
        }

        auto ordersIter = orders->find(idBucIter->second);
        //Make sure its valid
        if(ordersIter == orders->end()){
          throw MarketException("UNKNOWN_ORDER");
        }

        //Find the post and make sure its valid
        auto deleteThis = ordersIter->second->find(orderId);
        if(deleteThis == ordersIter->second->end()){
          throw MarketException("UNKNOWN_ORDER");
        }

        delete deleteThis->second;
        ordersIter->second->erase(deleteThis);
        idBuckets->erase(idBucIter);
        

      }

      //Update
      void updateOrder(Post * newOrder);


      friend std::ostream& operator <<(std::ostream & os, const Database& db){
        os << "Database dump" << std::endl;
        for(auto i = db.orders->begin(); i != db.orders->end(); ++i){
          os << i->first << std::endl;
          for(auto j = i->second->begin(); j != i->second->end(); ++j){
            os << "Order num: " << j->first;
            os << "\tDealer: " << j->second->getDealerId() << std::endl; 
          }
        }

        return os;
      }
    private:
      std::map<std::string, std::map<int, Post *> * > * orders;
      std::map<int, std::string> * idBuckets;
      //Helper for inserting the maps 
      void initOrders(){
        //Insert a map for each of the commodities in the grammar
        for(int i = 0; i < NUM_COMMODS; ++i){
          std::pair<std::string, std::map<int, Post *> *> tmp(VALID_COMMODS[i], new 
              std::map<int, Post *>);
          orders->insert(tmp);
        }


      };

  };


}




#endif //DATABASE_HPP
