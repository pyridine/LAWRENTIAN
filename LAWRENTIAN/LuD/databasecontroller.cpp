#include "databasecontroller.h"
#include "client.h"

DatabaseController::DatabaseController(Client* c){
    client = c;
}

Client* DatabaseController::getClient(){
    return client;
}
