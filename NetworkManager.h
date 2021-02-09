// ensure this library description is only included once
#ifndef NetworkManager_h
#define NetworkManager_h

#include "Dict.h"
#include "Context.h"

// library interface description
class NetworkManager
{
  // user-accessible "public" interface
  public:
    NetworkManager();

    ~NetworkManager();
    void newMessage(arduino::Stream*);
    void setEndpoint(String method, String EndpointName, void (*f)(Context*));
  private:

    void Return(String,int ,int ,arduino::Stream*);
    Dict<void (*)(Context*)> endpoints;
    void doSomethingSecret();
    void Return(String ret);
    void ReadEntryPoint(String, Context*);
    static void showEndpoints(Context*);
};


#endif

