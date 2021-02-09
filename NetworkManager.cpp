// include core Wiring API
#include "Arduino.h"
// #include "Stream.h"
// include this library's description file
#include "NetworkManager.h"
#include "Message.h"
#include "Dict.h"
#include "Context.h"


// include description files for other libraries used (if any)
#include "HardwareSerial.h"


NetworkManager::NetworkManager()
{
    endpoints = Dict<void (*)(Context*)>();

    endpoints.add("GET_showfunctions", showEndpoints);

}

NetworkManager::~NetworkManager()
{

}

void NetworkManager::setEndpoint(String method, String EndpointName, void (*f)(Context*))
{

  endpoints.add(method+"_"+EndpointName, f);

}

void NetworkManager::newMessage(arduino::Stream *s)
{

    int start = millis();   
    Message mes = Message(s);
    String str = mes.ctx.method + "_" + mes.ctx.endpoint;
    void (**myFuncName)(Context*) = endpoints.getValue(str);
    if (myFuncName == nullptr)
    {
        mes.ctx.response.Code = HTTP_CODE_NotFound;
        mes.ctx.response.Text = reasonPhrase(HTTP_CODE_NotFound);

    } else {
        mes.ctx.netManger = this;
        (*myFuncName)(&(mes.ctx));
    }

    int fin = (millis() - start);


    Return(mes.ctx.response.Text,mes.ctx.response.Code, fin, s);
}

void NetworkManager::Return(String ret,int Code, int duration, arduino::Stream *s)
{
   // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  s->println("HTTP/1.1 "+String(Code)+" "+reasonPhrase(Code));
  s->println("Content-type:text/html");
  s->println("Executaion Duration in ms:"+String(duration));
  s->println();

  // the content of the HTTP response follows the header:
  s->print(ret);

  // The HTTP response ends with another blank line:
  s->println();
  s->println();
  // break out of the while loop:
}

void NetworkManager::showEndpoints(Context *ctx)
{
    String st = "";
    int funcSize = ctx->netManger->endpoints.Size();
    for(int i=0;i<funcSize;i++){
        
        st = st + (*ctx->netManger->endpoints.getKey(i)+"\n");
        // st = *ctx->netManger->endpoints.getKey(i);
    }
    ctx->response.Text = st;

}



