#ifndef IGBOMB_CLIENT_H
#define IGBOMB_CLIENT_H

#include <iostream>

using std::string;

typedef struct {
    string data;
} APIData;

//typedef std::function<void(int error, APIData &values)> APICallback;
//typedef void (*APICallback)(const int code, const APIData &data);
typedef void (*APICallback)(const int code, const std::string data);

class IGbombClient {
public:
    virtual void init(const string gameId) = 0;
    virtual void login(const APICallback callback) = 0;

    virtual void callService(const string character_profile, const APICallback callback) = 0;
    
    virtual void getProductList(const string character_profile, const APICallback callback) = 0;
    
    virtual void purchase(const string cid,
                          const string server_id, 
                          const string item_id,
                          const string onsales_id,
                          const string provider_id,
                          const string character_profile,
                          const string token,
                          const APICallback callback) = 0;

    virtual void subPush(const string regid, const APICallback callback) = 0;
    virtual void unsubPush(const string regid, const APICallback callback) = 0;
};

#endif // IGBOMB_CLIENT_H
