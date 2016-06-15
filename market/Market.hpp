#ifndef MARKET_HPP
#define MARKET_HPP

#include "../commands/Command.hpp"
#include "../commands/Post.hpp"

#include "../util/Grammar.hpp"

#include <vector>
#include <string>
#include <map>



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
        for(auto i = orders->begin(); i != orders->end(); ++i){
          for(auto j = i->second->begin(); j != i->second->end(); ++j){
            delete *j;
          }
          delete (i->second);
        }

      }
      void addOrder(Post * order){
        //Error checking here
        //orders->push_back(order);
        
      }

    private:
      //std::vector<Post *> * orders;
      std::map<std::string, std::vector<Post *> * > * orders;
      int orderNumber;
  };


}



#endif //MARKET_HPP
