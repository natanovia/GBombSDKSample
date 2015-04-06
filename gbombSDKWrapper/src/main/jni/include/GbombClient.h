#ifndef GBOMB_CLIENT_H
#define GBOMB_CLIENT_H

#include "IGbombClient.h"

using std::string;

class GbombClient { //: public IGbombClient {
public:
    static IGbombClient *getInstance();
    
private:
//    GbombClient();
    static IGbombClient *_instance;
};

#endif // GBOMB_GBOMB_H
