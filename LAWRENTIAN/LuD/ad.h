#ifndef AD_H
#define AD_H

#include <string>

using namespace std;

class ad
{
public:
    ad();
    ~ad();

    string getCompanyName();
    void setCompanyName(string companyName);
    int getPhone();
    void setPhone(int phone);
    string getEmail();
    void setEmail(string email);
    string getAddress();
    void setAddress(string address);
    int getDealLength();
    void setDealLength(int dealLength);
    int getDealRequirements();
    void setDealRequirements(int dealRequirements);

private:
    string companyName;
    int phone;
    string email;
    string address;
    int dealLength;
    int dealRequirements;

};

#endif // AD_H
