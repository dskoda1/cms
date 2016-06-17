#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "../commands/Post.hpp"
#include "../util/MarketException.hpp"

#include <vector>
#include <map>

#include <iostream>


namespace cms {

    class Database {

      public:

        Database(){
        
          orders = new std::map<std::string, std::map<int, Post *> *>;


        }

        //Create
        void saveOrder(Post * order);

        //Read
        std::vector<Post *> getOrders();
        std::vector<Post *> getOrders(std::string commodity);
        std::vector<Post *> getOrders(std::string commodity, std::string dealerId);
        Post * getOrder(int orderId);

        //Delete
        void deleteOrder(int orderId);

        //Update
        void updateOrder(Post * newOrder);

      private:
        std::map<std::string, std::map<int, Post *> * > * orders;


    };


}




#endif //DATABASE_HPP
