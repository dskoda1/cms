#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP


const std::string VALID_COMMODS[] = {"GOLD", "SILV", "PORK", "OIL", "RICE"};
const int NUM_COMMODS = 5;

const std::string VALID_DEALERS[] = {"DB","JPM","UBS","RBC","BARX","MS","CITI","BOFA","RBS","HSBC"};
const int NUM_DEALERS = 10;

const std::string VALID_SIDES[] = {"BUY", "SELL"};
const int NUM_SIDES = 2;

const std::string VALID_COMMANDS[] = {"POST", "REVOKE", "CHECK", "LIST", "AGRESS"};
const int NUM_COMMANDS = 5;

#endif //GRAMMAR_HPP
