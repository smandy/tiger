# Calling stuff #

cd ~/repos/tiger/dlang

# OneShot Server #

./d_server --Ice.Config=d_server.config

./d_client 'foo:tcp -p 1099 -h ritz'

./cpp_client --Ice.Config=cpp_client.config

## Clojure ##

/home/andy/repos/tiger/clj/src/clj/dexperiment.clj

## TickServer ##

./tickserver --Ice.Config=tickserver.config

./tickerclient --Ice.Config=tickerclient.config

./cpp_tickserver_client --Ice.Config=tickerclient.config

(In python directory)

./tickerPlant.py

./tickerClient.py
