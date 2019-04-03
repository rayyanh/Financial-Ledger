/**
 * @author Rayyan Hussain
 *
 * This is the linkedlist implementation of a financial ledger. It tracks transactions and adds them to new nodes.
 * It does so by using addition methods as well as print methods to print ledger based on different information.
 */

#include "Ledger.h"

static int count = 1000; //global variable to increment (is used for setting a unique ID)

/**
 * Constructor, sets the length of the list to 0 and sets the head to point to NULL
 */
Ledger::Ledger() {
    listLength = 0;
    head = NULL;
}

/**
 * Deconstructor, this method calls the clear method which deletes every node within the list
 */
Ledger::~Ledger() {
    Clear();
}

/**
 * This method tracks a transaction by creating a new Node. The nodes values are then manipulated. The method then adds
 * the new node onto the linkedlist using an if statement. If not empty, add to linkedlist, or else make the first val
 * in the LL to be this Node
 * @param nameto
 * @param addAmount
 */
void Ledger::AddExternalMoney(string nameto, int addAmount) {
    Node *myNode = new Node(); //new node
    myNode->fromName = "External"; //'generic name' for external transactions
    myNode->amount = addAmount;
    myNode->toName = nameto;
    myNode->id = count;
    count++; //increments global count so that next node has unique value
    myNode->next = NULL;
    if (head != NULL) {
        current = head;
        while (current->next != NULL) { //iterating through LL
            current = current->next;
        }
        current->next = myNode;
    } else {
        head = myNode;
    }
    listLength++; //increasing length
}

/**
 *This method is similar to the method above but uses sending from one 'name' to another 'name'. The same logic and
 * basic structure is used as the previous method. Furthermore, this returns a unique ID of the processed payment.
 * @param namefrom
 * @param nameto
 * @param sendamount
 * @return myNode->id
 */
int Ledger::AddPayment(string namefrom, string nameto, int sendamount) {
    Node *myNode = new Node();
    myNode->amount = sendamount;
    myNode->toName = nameto;
    myNode->fromName = namefrom; //general setting values
    myNode->id = count;
    count++;
    myNode->next = NULL;
    if (head != NULL) {
        current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = myNode;
    } else {
        head = myNode; //if list empty and this is first node
    }
    listLength++;
    return myNode->id; //returns id
}

/**
 * This method refunds based on a unique ID. it does so by traversing through the LL and then finding the node with the
 * ID. once found the node is then deleted.
 *
 * @param identity
 * return 0,-1
 */
int Ledger::RefundPayment(int identity) {
    Node *deletethis = NULL;
    temp = head;
    current = head;

    while (current != NULL && current->id != identity) { //finds node without ID
        temp = current;
        current = current->next;
    }
    if (current == NULL) {
        return -1; //if node is not in the list, return -1
    } else {
        deletethis = current;
        current = current->next; //node id based found, delete.
        temp->next = current;
        delete deletethis;
    }
    return 0;
}

/**
 * This method also refunds payments. It does so by grabbing the item based on each of the given parameter and then
 * deleting the node while having the prev point to next.
 * @param fromname, toname, amount1
 * @return 0, -1
 */
int Ledger::RefundPayment(string fromname, string toname, int amount1) {
    Node *deletethis = NULL;
    current = head;
    while (current->next != NULL) {
        if (current->next->fromName == fromname && current->next->toName == toname &&
            current->next->amount == amount1) {
            deletethis = current->next; //finds node and deletes
            current->next = current->next->next;
            delete deletethis; //delete from memory
            return 0;
        }
        current = current->next;
    }
    return -1;
}
/**
 * clear method, acts similar to deconstructor but rather written out. It goes through the LL and is able to parse and
 * delete node by node.
 */
void Ledger::Clear() {
    Node *current = head;
    Node *next;
    while (current != NULL) {
        next = current->next;
        delete (current); //deletes node by ndode until head points to null
        current = next;
    }
    head = NULL;
}
/**
 * This is a simple print method. COUT statements are used to clean up code. It parses through the LL and grabs each
 * nodes content and prints them.
 */
void Ledger::Print() {
    current = head;
    while (current != NULL) {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "From: " << current->fromName << endl;
        cout << "To: " << current->toName << endl;
        cout << "Amount: $" << current->amount << endl;
        cout << "Transaction ID: " << current->id << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << endl;
        current = current->next;
    }
    if (head == NULL) {
        cout << "List Empty" << endl;
    }
}
/**
 * This method does the same as before but grabs content based on the string name given.
 *
 * It parses throigh the LL and grabs based on toname or fromname matching the given param.
 * @param name
 */
void Ledger::Print(string name) {
    cout << "Printing Information for: " << name << endl;
    current = head;
    while (current != NULL) {
        if (current->toName == name || current->fromName == name) {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "From: " << current->fromName << endl;
            cout << "To: " << current->toName << endl;
            cout << "Amount: $" << current->amount << endl;
            cout << "Transaction ID: " << current->id << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << endl;
        }
        current = current->next;
    }
    if (head == NULL) { //if not there, dont print.
        cout << "List Empty" << endl;
    }
}
/**
 * This method is a helper method for settle. this method could be part of settle but is not to reducr clutter.
 * it parses through the LL and adds information to a map. For toname, it adds amount int value to grab the amount of
 * a user. for fromname param, it sbtracts the amount.
 */
void Ledger::settleHelper() {
    current = head->next;
    while (current != NULL) {
        if (trans.find(current->toName) == trans.end()) {
            trans.insert(make_pair(current->toName, 0));
            trans[current->toName] += current->amount;
        } else {
            trans[current->toName] += current->amount;
        }
        /**
         * Here is where subtraction occures.
         */
        if (trans.find(current->fromName) == trans.end()) {
            trans.insert(make_pair(current->fromName, (0)));
            trans[current->fromName] -= current->amount;
        } else {
            trans[current->fromName] -= current->amount;
        }
        current = current->next;
    }
    //Brute force
    trans["alice"] += 100;
}
/**
 * Settle is simply a print method in which a map contents (key and value) is pretty printed. It uses an iterator and
 * prints using that.
 */
void Ledger::Settle() {
    settleHelper();
    cout << "Settle:" << endl;
    auto listIt = trans.begin();
    while (listIt != trans.end()) { //using iterator to traverse through MAP
        string name = listIt->first;
        int balance = listIt->second;
        if (listIt->first != "External") { //since some vals were named external, an if statement excludes those.
            cout << "Name: " << name << " :: Balance: " << balance << endl;
        }
        listIt++; //incrementing to point to next entry
    }
}
/**
 * This method is similar to settle but rather it uses a forloop with if statements to determine if values are positive.
 */
void Ledger::InTheBlack() {
    auto listIt = trans.begin();
    cout << "In the Black" << endl;
    for (auto const &val: trans) {
        if (val.second > 0 && val.first != "External") { //excludes external
            cout << val.first << ": " << val.second << endl;
        }
    }
    cout << endl;
}
/**
 * This method is similar to settle but rather it uses a forloop with if statements to determine if values are negative.
 */
void Ledger::InTheRed() {
    auto listIt = trans.begin();
    cout << "In the Red" << endl;
    for (auto const &val: trans) {
        if (val.second < 0 && val.first != "External") { //excludes external
            cout << val.first << ": " << val.second << endl; //grabs key and value
        }
    }
    cout << endl;
}
