#!/bin/sh
ps x | grep spolicy_server | awk '{print $1}' | xargs kill -TERM
ps x | grep login_server | awk '{print $1}' | xargs kill -TERM
ps x | grep lobby_server | awk '{print $1}' | xargs kill -TERM
ps x | grep gateway_server | awk '{print $1}' | xargs kill -TERM
ps x | grep society_server | awk '{print $1}' | xargs kill -TERM
ps x | grep cache_proxy_server | awk '{print $1}' | xargs kill -TERM
ps x | grep center_server | awk '{print $1}' | xargs kill -TERM
ps x | grep db_server | awk '{print $1}' | xargs kill -TERM
