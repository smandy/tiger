(ns argo.icetest)

; andy@raffles:/mnt/hdd/andy/repos/tiger/discovery$ ./Server --Ice.Config=config.server
(import java.sql.DriverManager)

(let [
      db (DriverManager/getConnection
          "jdbc:postgresql://localhost/andy" "andy" "andy") 
      stmt (.createStatement db )
      rs (.executeQuery stmt "select * from foo")
      buildResult (fn [ xs ]
             (loop (if-not (.next rs)
                     xs
                     (recur (conj [ (.getInt rs 1)
                                   (.getString rs 2)
                                   (.getDate rs 3) ] ))))) ]
  (loop [] ))

  (while (.next rs)
    (printf "%s %s %s\n" (.getInt rs 1) (.getString rs 2) (.getDate rs 3)) )
  )


