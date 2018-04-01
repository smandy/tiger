#pragma once

#include <Ice/Identity.ice>

module argo {

    enum TickDirection { ZERO, UP, DOWN};
    
    struct Tick {
        long symbol;
        double bidPx;
        double askPx;

        TickDirection bidDirection;
        TickDirection askDirection;
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
