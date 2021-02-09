// ensure this library description is only included once
#ifndef Context_h
#define Context_h
#include "Arduino.h"
#include "Dict.h"
#include "HttpStatusCodes.h"
// #include "NetworkManager.h"

class NetworkManager;

struct Response
{
    int Code = HTTP_CODE_OK;
    String Text = "";
};

struct Context
{

    Dict<String> args;
    Dict<String> headers;
    String endpoint;
    String method;
    Response response;
    NetworkManager *netManger;
};



#endif
