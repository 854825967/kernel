#!/bin/bash

#���shell��������������Ӫ�汾����Ϊ���ܵ�����ctrl+cʱ����Ŀ����̸ɵ�
#see https://bugzilla.redhat.com/show_bug.cgi?format=multiple&id=276091

if [ $# != 2 ] ; then
  echo "���������: [���ʱ��(����)] [ץȡĿ��all(ץȡȫ��)��������֮һ(db center gateway login lobby room society)]"
  exit 1;
fi

#!/bin/sh
PARAM1=`echo $2 | tr "A-Z" "a-z"`

if [ "$PARAM1" != "all" ] && [ "$PARAM1" != "db" ] && [ "$PARAM1" != "center" ] && [ "$PARAM1" != "gateway" ] && [ "$PARAM1" != "login" ] && [ "$PARAM1" != "lobby" ] && [ "$PARAM1" != "room" ] && [ "$PARAM1" != "society" ]
then
  echo "�����������!"
  exit 1;
fi

SLEEP=$[$1*1000]

echo "�����$1������ץȡһ�Ρ�$2�����������̺߳�������ջ"

while :
do
  if [ "$PARAM1" == "all" ] || [ "$PARAM1" == "db" ] ; then
    pid=`ps x | grep db_server | grep -v grep | awk '{print $1}'`
    echo "-----------------------------------beg--------------------------------" >> pstack/db_server.pstack
    pstack $pid >> pstack/db_server.pstack
    echo "-----------------------------------end--------------------------------" >> pstack/db_server.pstack
  fi

  if [ "$PARAM1" == "all" ]  || [ "$PARAM1" == "center" ] ; then
    pid=`ps x | grep center_server | grep -v grep | awk '{print $1}'`
    echo "-----------------------------------beg--------------------------------" >> pstack/center_server.pstack
    pstack $pid >> pstack/center_server.pstack
    echo "-----------------------------------end--------------------------------" >> pstack/center_server.pstack
  fi

  if [ "$PARAM1" == "all" ] || [ "$PARAM1" == "gateway" ] ; then
    pid=`ps x | grep gateway_server | grep -v grep | awk '{print $1}'`
    echo "-----------------------------------beg--------------------------------" >> pstack/gateway_server.pstack
    pstack $pid >> pstack/gateway_server.pstack
    echo "-----------------------------------end--------------------------------" >> pstack/gateway_server.pstack
  fi

  if [ "$PARAM1" == "all" ] || [ "$PARAM1" == "login" ] ; then
    pid=`ps x | grep login_server | grep -v grep | awk '{print $1}'`
    echo "-----------------------------------beg--------------------------------" >> pstack/login_server.pstack
    pstack $pid >> pstack/login_server.pstack
    echo "-----------------------------------end--------------------------------" >> pstack/login_server.pstack
  fi

  if [ "$PARAM1" == "all" ]|| [ "$PARAM1" == "lobby" ] ; then
    pid=`ps x | grep "lobby_server -auto 255" | grep -v grep | awk '{print $1}'`
    echo "-----------------------------------beg--------------------------------" >> pstack/lobby_server.pstack
    pstack $pid >> pstack/lobby_server.pstack
    echo "-----------------------------------end--------------------------------" >> pstack/lobby_server.pstack
  fi

  if [ "$PARAM1" == "all" ] || [ "$PARAM1" == "room" ] ; then
    pid=`ps x | grep "lobby_server -auto 1" | grep -v grep | awk '{print $1}'`
    echo "-----------------------------------beg--------------------------------" >> pstack/room_server.pstack
    pstack $pid >> pstack/room_server.pstack
    echo "-----------------------------------end--------------------------------" >> pstack/room_server.pstack
  fi

  if [ "$PARAM1" == "all" ] || [ "$PARAM1" == "society" ] ; then
    pid=`ps x | grep society_server | grep -v grep | awk '{print $1}'`
    echo "-----------------------------------beg--------------------------------" >> pstack/society_server.pstack
    pstack $pid >> pstack/society_server.pstack
    echo "-----------------------------------end--------------------------------" >> pstack/society_server.pstack
  fi

  usleep $SLEEP
done

