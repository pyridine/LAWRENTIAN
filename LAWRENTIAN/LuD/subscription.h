#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <string>

using namespace std;

class subscription
{
public:
    subscription();
    ~subscription();

    string getName() const;
    void setName(const string &value);

    int getPhone() const;
    void setPhone(int value);

    string getEmail() const;
    void setEmail(const string &value);

    string getAddress() const;
    void setAddress(const string &value);

    int getSubscriptionLength() const;
    void setSubscriptionLength(int value);

    int getNumberOfIssues() const;
    void setNumberOfIssues(int value);

private:
    string name;
    int phone;
    string email;
    string address;
    int subscriptionLength;
    int numberOfIssues;

};

#endif // SUBSCRIPTION_H
