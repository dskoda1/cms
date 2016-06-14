#ifndef MARKET_HPP
#define MARKET_HPP

#include "../commands/Command.hpp"
#include "../commands/Post.hpp"
#include <vector>

namespace cms {

  class Market {

    public:
      Market() : orders{new std::vector<Post *>}
      {}

      ~Market(){

        for(auto it = orders->begin(); it < orders->end(); ++it){
          delete (*it);
        }

      }
      void addOrder(Post * order){
        //Error checking here
        orders->push_back(order);
      }

    private:
      std::vector<Post *> * orders;


  };


}



#endif //MARKET_HPP
