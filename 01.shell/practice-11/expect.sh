# !/usr/bin/expect -f

set pem [lindex $argv 0]
set user [lindex $argv 1]
set host [lindex $argv 2]
set passwd [lindex $argv 3]
set timeout 30
spawn ssh -i $pem -t $user@$host
expect {
  "*yes/no*" {send "yes\r";exp_continue;}
  "Enter passphrase for key*" {send "$passwd\r"}
}
interact
