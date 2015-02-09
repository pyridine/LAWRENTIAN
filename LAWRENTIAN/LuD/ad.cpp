#include "ad.h"

ad::ad()
{

}

ad::~ad()
{

}

string ad::getCompanyName()
{
    return ad::companyName;
}

void ad::setCompanyName(string companyName)
{
    ad::companyName = companyName;
}

int ad::getPhone()
{
    return ad::phone;
}

void ad::setPhone(int phone)
{
    ad::phone = phone;
}

string ad::getEmail()
{
    return ad::email;
}

void ad::setEmail(string email)
{
    ad::email = email;
}

string ad::getAddress()
{
    return ad::address;
}

void ad::setAddress(string address)
{
    ad::address = address;
}

int ad::getDealLength()
{
    return ad::dealLength;
}

void ad::setDealLength(int dealLength)
{
    ad::dealLength = dealLength;
}

int ad::getDealRequirements()
{
    return ad::dealRequirements;
}

void ad::setDealRequirements(int dealRequirements)
{
    ad::dealRequirements = dealRequirements;
}


