#!/bin/sh
ps x | grep spolicy_server | awk '{print $1}' | xargs kill -TERM
ps x | grep login_server | grep "../configure/server_[group_id].xml" | awk '{print $1}' | xargs kill -TERM
ps x | grep lobby_server | grep "../configure/server_[group_id].xml" | awk '{print $1}' | xargs kill -TERM
ps x | grep gateway_server | grep "../configure/server_[group_id].xml" | awk '{print $1}' | xargs kill -TERM
ps x | grep society_server | grep "../configure/server_[group_id].xml" | awk '{print $1}' | xargs kill -TERM
ps x | grep cache_proxy_server | grep "../configure/server_[group_id].xml" | awk '{print $1}' | xargs kill -TERM
ps x | grep center_server | grep "../configure/server_[group_id].xml" | awk '{print $1}' | xargs kill -TERM
ps x | grep db_server | grep "../configure/server_[group_id].xml" | awk '{print $1}' | xargs kill -TERM
