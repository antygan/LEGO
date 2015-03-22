#!/usr/bin/expect

set timeout 20

#start the telnet session
spawn telnet 192.168.0.105

expect "login:"
send -- "root\r"
expect "root@EV3:~#"
send -- "dropbear\r"
expect "root@EV3:~#"
