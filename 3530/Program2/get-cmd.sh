#!/usr/bin/get-cmd

echo "open $1 80"
sleep 2
echo "GET / HTTP/1.1"
echo "Host: $1"
echo
echo
sleep 2
