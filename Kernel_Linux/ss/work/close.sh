#!/bin/sh
ps x | grep center_server | awk '{print $1}' | xargs kill -9
ps x | grep db_server | awk '{print $1}' | xargs kill -9
ps x | grep login_server | awk '{print $1}' | xargs kill -9
ps x | grep gateway_server | awk '{print $1}' | xargs kill -9
ps x | grep society_server | awk '{print $1}' | xargs kill -9
ps x | grep spolicy_server | awk '{print $1}' | xargs kill -9
