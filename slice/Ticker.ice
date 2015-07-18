#pragma once

module argo {

  struct Tick {
    string symbol;
    double bidPx;
    double askPx;
  };

  sequence<Tick> TickSeq;
  
  interface TickListener {
    void onTick( TickSeq t);
  };
  
  interface TickerPlant {
    void subscribe( TickListener *l);
  };

};
