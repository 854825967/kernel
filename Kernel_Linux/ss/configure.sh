#!/bin/sh

if [ $# != 7 ] ; then 
echo "请输入七个参数，第一个为服务器内网IP，第二个为服务器外网IP，第三个为数据库IP，第四个参数为端口偏移值，第五个参数为cache服务器IP，第6个参数为数据库端口，第7个参数为服务器组ID 以空格分开！"
echo " 例如: $0 192.168.168.15 222.73.93.73 192.168.168.22 2 192.168.168.15 3306 1"
exit 1; 
fi 

cur_dir=`pwd $0`
dir=`pwd $0`

ip_lan=`echo $1`
ip_wan=`echo $2`
dbip=`echo $3`
memcached_ip=`echo $5`
dbport=`echo $6`
groupid=`echo $7`

cp ./configure/example_server.xml ./configure/server_$groupid.xml
cp ./configure/example_dbserver.ini ./configure/dbserver.ini
cp ./configure/example_DBEngine.scp ./configure/dbengine1.scp
cp ./configure/example_DBEngine.scp ./configure/dbengine2.scp
cp ./configure/example_memcached.xml ./configure/memcached.xml
cp ./work/example_start.sh ./work/start.sh
cp ./work/example_terminal.sh ./work/terminal.sh

dir=`pwd $0`
dir=`echo $dir | sed 's/\//\\\\\//g'`
echo "pwd is $dir"

#echo "s/\/home\/than\/msserver/$dir/g"
sed -i "s/\[msserver_directory\]/$dir/g" ./configure/server_$groupid.xml
sed -i "s/\[server_lan_ip\]/$ip_lan/g" ./configure/server_$groupid.xml
sed -i "s/\[server_wan_ip\]/$ip_wan/g" ./configure/server_$groupid.xml
sed -i "s/\[db_server_ip\]/$ip_lan/g" ./configure/dbserver.ini
sed -i "s/\[db_ip\]/$dbip/g" ./configure/dbengine1.scp
sed -i "s/\[db_ip\]/$dbip/g" ./configure/dbengine2.scp
sed -i "s/\[db_port\]/$dbport/g" ./configure/dbengine1.scp
sed -i "s/\[db_port\]/$dbport/g" ./configure/dbengine2.scp
sed -i "s/\[memcached_ip\]/$memcached_ip/g" ./configure/memcached.xml

#change port server.xml
port=$[8888+$4]
sed -i "s/port=\"8888\"/port=\"$port\"/g" ./configure/server_$groupid.xml
port=$[8000+$4]
sed -i "s/port=\"8000\"/port=\"$port\"/g" ./configure/server_$groupid.xml
port=$[8100+$4]
sed -i "s/port=\"8100\"/port=\"$port\"/g" ./configure/server_$groupid.xml
port=$[6789+$4]
sed -i "s/port=\"6789\"/port=\"$port\"/g" ./configure/server_$groupid.xml
port=$[9100+$4]
sed -i "s/port=\"9100\"/port=\"$port\"/g" ./configure/server_$groupid.xml
port=$[9500+$4]
sed -i "s/port=\"9500\"/port=\"$port\"/g" ./configure/server_$groupid.xml
port=$[8500+$4]
sed -i "s/port=\"8500\"/port=\"$port\"/g" ./configure/server_$groupid.xml
port=$[8900+$4]
sed -i "s/port=\"8900\"/port=\"$port\"/g" ./configure/server_$groupid.xml
port=$[8901+$4]
sed -i "s/port=\"8901\"/port=\"$port\"/g" ./configure/server_$groupid.xml



echo "configure server.xml complete!!"

#change port dbserver.ini
port=$[8900+$4]
sed -i "s/DBServerPort = 8900/DBServerPort = $port/g" ./configure/dbserver.ini
port=$[8901+$4]
sed -i "s/DBServerPort = 8901/DBServerPort = $port/g" ./configure/dbserver.ini

echo "configure dbserver.ini complete!!"

#change groupid start.sh
sed -i "s/\[group_id\]/$groupid/g" ./work/start.sh
echo "work start.sh complete!!"

#change groupid terminal.sh
sed -i "s/\[group_id\]/$groupid/g" ./work/terminal.sh
echo "work terminal.sh complete!!"

#change dir export
sed -i "s/\[msserver_directory\]/$dir/g" ./work/export
echo "work export complete!!"

