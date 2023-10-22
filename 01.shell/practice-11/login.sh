# !/bin/bash

function usage() {
    echo "usage: sh login.sh [ubuntu, centos, jump]"
}

function get_host() {
    input=$1
    if echo $input|grep -E "^[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}$">/dev/null; then
        tmp_host=$input
    else
        tmp_host=$(/usr/local/bin/aws ec2 describe-instances --instance-ids $input --query 'Reservations[*].Instances[*].PublicIpAddress' --output text)
    fi
    echo $tmp_host
}

if [ $# -lt 1 ]; then
    usage
    exit
else
    option=$1
    host=$2
fi

pem=""
user=""
host=""
jump_host=""
passwd=""
expect=""
input=""

case "$option" in
    live) 
        echo 'please input ubuntu host!'
        pem="~/.ssh/mengmai.pem"
        user="ubuntu"
        expect="~/.ssh/expect.sh"
        while read input; do
            host=$(get_host $input)
            ssh -i $pem -t $user@$host
            break
        done
        ;;
    vod) 
        echo 'please input centos host!'
        pem="~/.ssh/mengmai.pem"
        user="centos"
        expect="~/.ssh/expect.sh"
        while read input; do
            host=$(get_host $input)
            ssh -i $pem -t $user@$host
            break
        done
        ;;
    jump) 
        echo 'please input jump host!'
        pem="~/.ssh/mengmai.pem"
        user="linux"
        host="65.1.92.233"
        expect="~/.ssh/expect.sh"
        while read input; do
            jump_host=$(get_host $input)
            ssh -i $pem -t $user@$host "ssh -i /home/ec2-user/.ssh/mengmai.pem -t $user@$jump_host" 
            break
        done
        ;;
    *)
        usage ;;
esac