#!/bin/sh
PARAM1=`echo $1 | tr "A-Z" "a-z"`

echo $PARAM1

if [ "$PARAM1" == "center" ]
then
  valgrind --tool=memcheck --leak-check=yes --log-file=./memcheck/center_server.memcheck ../build/bin/center_server/center_server -configure ../configure/server.xml &
fi

if [ "$PARAM1" == "db" ] 
then
  valgrind --tool=memcheck --leak-check=yes --log-file=./memcheck/db_server.memcheck ../build/bin/db_server/db_server -auto 1 -configure ../configure/server.xml &
fi

if [ "$PARAM1" == "login" ] 
then
  valgrind --tool=memcheck --leak-check=yes --log-file=./memcheck/login_server.memcheck ../build/bin/login_server/login_server -configure ../configure/server.xml &
fi

if [ "$PARAM1" == "gateway" ] 
then
  valgrind --tool=memcheck --leak-check=yes --log-file=./memcheck/gateway_server.memcheck ../build/bin/gateway_server/gateway_server -auto 1 -configure ../configure/server.xml &
fi

if [ "$PARAM1" == "society" ] 
then
  valgrind --tool=memcheck --leak-check=yes --log-file=./memcheck/society_server.memcheck ../build/bin/society_server/society_server -configure ../configure/server.xml &
fi

if [ "$PARAM1" == "lobby" ]
then
  valgrind --tool=memcheck --leak-check=yes --log-file=./memcheck/looby_server.memcheck ../build/bin/lobby_server/lobby_server -auto 255 -configure ../configure/server.xml &
fi

if [ "$PARAM1" == "room" ]
then
  valgrind --tool=memcheck --leak-check=yes --log-file=./memcheck/room_server.memcheck ../build/bin/lobby_server/lobby_server -auto 1 -configure ../configure/server.xml &
fi

if [ "$PARAM1" == "cache_proxy" ]
then
  valgrind --tool=memcheck --leak-check=yes --log-file=./memcheck/cache_proxy_server.memcheck ../build/bin/cache_proxy_server/cache_proxy_server -auto 1 -configure ../configure/server.xml &
fi
