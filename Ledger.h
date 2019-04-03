//
// Created by Rayyan on 2/25/2019.
//
/**
 * @author Rayyan Hussain
 *
 * This is the H file for ledger.cpp. What is unique is that the Node struct is also defined within this h file which
 * essentially holds all the necessary information to create a linkedlist.
 */

#ifndef ASSIGNMENT4_LEDGER_H
#define ASSIGNMENT4_LEDGER_H

#include <iostream>
#include <string>
#include <map> //used this

using namespace std;

struct Node { //struct
public:
    Node *next; //has these values within it
    string toName;
    string fromName;
    int amount;
    int id; //unique id made by count
};

class Ledger {
public:
    Ledger(); //constructor

    ~Ledger(); //deconstructor

    Node *head; //points to the head
    Node *temp; //here so that I may use a temporary node pointer
    Node *current; //points to current value

    int listLength; //tracking list length in case length size is needed

    //Editing Ledger
    //adds money from no 'from name'
    void AddExternalMoney(string toName, int amount);

    //adds money to ledger with params applied
    int AddPayment(string fromName, string toName, int amount);

    //delete node based on id
    int RefundPayment(int id);

    //delete node based on params
    int RefundPayment(string fromName, string toName, int amount);

    //delete all nodes
    void Clear();

    //printing ledger
    void Print();

    //prints ledger based on unique name
    void Print(string name);

    //prints all balances
    void Settle();

    //prints positive balances
    void InTheBlack();

    //prints negative balances
    void InTheRed();

private:
    map<string, int> trans; //map to hold names and corrosponding values (balance)

    void settleHelper(); //helper method just to clean code.

};


#endif //ASSIGNMENT4_LEDGER_H
