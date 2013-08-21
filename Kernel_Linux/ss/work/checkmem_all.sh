#!/bin/sh
  valgrind --tool=memcheck --leak-check=yes --log-file=./memcheck/center_server.memcheck ../build/bin/center_server/center_server -configure ../configure/server.xml &

  valgrind --tool=memcheck --leak-check=yes --log-file=./memcheck/db_server.memcheck ../build/bin/db_server/db_server -auto 1 -configure ../configure/server.xml &

  valgrind --tool=memcheck --leak-check=yes --log-file=./memcheck/login_server.memcheck ../build/bin/login_server/login_server -configure ../configure/server.xml &

  valgrind --tool=memcheck --leak-check=yes --log-file=./memcheck/gateway_server.memcheck ../build/bin/gateway_server/gateway_server -auto 1 -configure ../configure/server.xml &

  valgrind --tool=memcheck --leak-check=yes --log-file=./memcheck/society_server.memcheck ../build/bin/society_server/society_server -configure ../configure/server.xml &

  valgrind --tool=memcheck --leak-check=yes --log-file=./memcheck/looby_server.memcheck ../build/bin/lobby_server/lobby_server -auto 255 -configure ../configure/server.xml &

  valgrind --tool=memcheck --leak-check=yes --log-file=./memcheck/room_server.memcheck ../build/bin/lobby_server/lobby_server -auto 1 -configure ../configure/server.xml &

  valgrind --tool=memcheck --leak-check=yes --log-file=./memcheck/cache_proxy_server.memcheck ../build/bin/cache_proxy_server/cache_proxy_server -auto 1 -configure ../configure/server.xml &
