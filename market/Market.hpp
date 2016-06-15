#ifndef MARKET_HPP
#define MARKET_HPP

#include "../commands/Command.hpp"
#include "../commands/Post.hpp"

#include "../util/Grammar.hpp"

#include <vector>
#include <string>
#include <map>

#include <iostream>

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
            std::cout << "Deleting a post" << std::endl;
            delete *j;
          }
          std::cout << "deleting a vector" << std::endl;
          //delete vector
          delete (i->second);
        }
        std::cout << "Deleting the map" << std::endl;
        //delete map
        delete orders;

      }
      void addOrder(Post * order){
        //insert into the correct vector based on orders commodity
        (*orders)[order->getCommodity()]->push_back(order);
      }

    private:
      //std::vector<Post *> * orders;
      std::map<std::string, std::vector<Post *> * > * orders;
      int orderNumber;
  };


}



#endif //MARKET_HPP
