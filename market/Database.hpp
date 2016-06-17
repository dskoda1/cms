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

        Database() : orders{new std::map<std::string, std::map<int, Post *> *>} {
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
          Post * ret;
          bool found = false;
          std::map<int, Post *>::iterator iter;
          for(auto i = orders->begin(); i != orders->end(); ++i){
            if((iter = i->second->find(orderId))  != i->second->end()){
              ret = iter->second;
              found = true;
              break;
            }
          }

          if(!found){
            throw MarketException("UNKNOWN_ORDER");
          }

          return ret;

        }

        //Delete
        void deleteOrder(int orderId);

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
