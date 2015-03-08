#!/usr/bin/expect

set timeout 20
set progname [lindex $argv 0];

#start the telnet session
spawn ssh root@192.168.0.105
expect "root@192.168.0.105's password:"
send -- "\r"
expect "root@EV3:~#"
send -- "cd /media/card/\r"
expect "root@EV3:/media/card#"
send -- "./"
send -- "$progname\r"
expect "root@EV3:/media/card#"
