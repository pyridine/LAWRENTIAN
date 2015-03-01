#ifndef EDITPROFILEDBC_H
#define EDITPROFILEDBC_H

#include "client.h"
#include "databasecontroller.h"

class EditProfileDBC : public DatabaseController
{
public:
    EditProfileDBC(Client *c);
    ~EditProfileDBC();

    string collectName(int luid);
    int collectLuid(int luid);
    string collectTitle(int luid);
    string collectEmail(int luid);
    string collectPhone(int luid);
    string collectUsername(int luid);
    string collectOldPassword(int luid);

    void saveEmployeeChangesWithPassword(string name, string email, string phone, string username, string newPassword, int luid);
    void saveEmployeeChangesWithoutPassword(string name, string email, string phone, string username, int luid);
};

#endif // EDITPROFILEDBC_H
