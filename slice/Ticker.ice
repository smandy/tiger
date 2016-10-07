#pragma once

#include <Ice/Identity.ice>

module argo {
    
    struct Tick {
        string symbol;
        double bidPx;
        double askPx;
    };
    
    sequence<Tick> TickSeq;
    
    sequence<TickSeq> TickImage;
    
    interface TickListener {
        void onTick( TickSeq t );

        void onImage( TickImage img);
    };
  
    interface TickerPlant {
        void subscribe( TickListener *l);

        void subscribeWithIdent( Ice::Identity ident);
    
        string sayHello();
    };

};
