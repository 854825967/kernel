#!/bin/sh
../build/bin/center_server/center_server -configure ../configure/server.xml
../build/bin/db_server/db_server -auto 1 -configure ../configure/server.xml
#../build/bin/db_server/db_server -auto 2 -configure ../configure/server.xml
../build/bin/login_server/login_server -configure ../configure/server.xml
../build/bin/gateway_server/gateway_server -auto 1 -configure ../configure/server.xml
../build/bin/society_server/society_server -configure ../configure/server.xml
../build/bin/cache_proxy_server/cache_proxy_server -auto 1 -configure ../configure/server.xml
../build/bin/lobby_server/lobby_server -auto 1 -configure ../configure/server.xml
../build/bin/lobby_server/lobby_server -auto 255 -configure ../configure/server.xml
