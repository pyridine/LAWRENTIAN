#include "subscription.h"

subscription::subscription()
{

}

subscription::~subscription()
{

}
string subscription::getName() const
{
    return name;
}

void subscription::setName(const string &value)
{
    name = value;
}
int subscription::getPhone() const
{
    return phone;
}

void subscription::setPhone(int value)
{
    phone = value;
}
string subscription::getEmail() const
{
    return email;
}

void subscription::setEmail(const string &value)
{
    email = value;
}
string subscription::getAddress() const
{
    return address;
}

void subscription::setAddress(const string &value)
{
    address = value;
}
int subscription::getSubscriptionLength() const
{
    return subscriptionLength;
}

void subscription::setSubscriptionLength(int value)
{
    subscriptionLength = value;
}
int subscription::getNumberOfIssues() const
{
    return numberOfIssues;
}

void subscription::setNumberOfIssues(int value)
{
    numberOfIssues = value;
}







