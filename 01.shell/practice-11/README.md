# 编写简单的脚本实用工具

- [自动归档](#自动归档)
- [删除账户](#删除账户)
- [系统审计](#系统审计)

---
上一篇：[练习10 gawk进阶](../practice-10/)，[目录](#编写简单的脚本实用工具)｜[首页](../README.md)

## 自动归档

每天

```bash
#!/bin/bash
#
# Daily_Archive - Archive designated files & directories
########################################################
#
# Gather Current Date
#
today=$(date +%y%m%d)
#
# Set Archive File Name
#
backupFile=archive$today.tar.gz
#
# Set Configuration and Destination File
#
config_file=/archive/Files_To_Backup.txt
destination=/archive/$backupFile
#
######### Main Script #########################
#
# Check Backup Config file exists
#
if [ -f $config_file ]   # Make sure the config file still exists.
then                # If it exists, do nothing but continue on.
     echo
else                # If it doesn't exist, issue error & exit script.
     echo
     echo "$config_file does not exist."
     echo "Backup not completed due to missing Configuration File"
     echo
     exit
fi
#
# Build the names of all the files to backup
#
file_no=1               # Start on Line 1 of Config File.
exec 0< $config_file    # Redirect Std Input to name of Config File
#
read file_name          # Read 1st record
#
while [ $? -eq 0 ]      # Create list of files to backup.
do
        # Make sure the file or directory exists.
     if [ -f $file_name -o -d $file_name ]
     then
          # If file exists, add its name to the list.
          file_list="$file_list $file_name"
     else
          # If file doesn't exist, issue warning
          echo
          echo "$file_name, does not exist."
          echo "Obviously, I will not include it in this archive."
          echo "It is listed on line $file_no of the config file."
          echo "Continuing to build archive list..."
          echo
     fi
#
     file_no=$[$file_no + 1]  # Increase Line/File number by one.
     read file_name           # Read next record.
done
#
#######################################
#
# Backup the files and Compress Archive
#
echo "Starting archive..."
echo
#
tar -czf $destination $file_list 2> /dev/null
#
echo "Archive completed"
echo "Resulting archive file is: $destination"
echo
#
exit
```

每小时

```bash
#!/bin/bash
#
# Hourly_Archive - Every hour create an archive
#########################################################
#
# Set Configuration File
#
config_file=/archive/hourly/Files_To_Backup.txt
#
# Set Base Archive Destination Location
#
basedest=/archive/hourly
#
# Gather Current Day, Month & Time
#
day=$(date +%d)
month=$(date +%m)
time=$(date +%k%M)
#
# Create Archive Destination Directory
#
mkdir -p $basedest/$month/$day
#
# Build Archive Destination File Name
#
destination=$basedest/$month/$day/archive$time.tar.gz
#
######### Main Script #########################
#
# Check Backup Config file exists
#
if [ -f $config_file ]   # Make sure the config file still exists.
then                # If it exists, do nothing but continue on.
     echo
else                # If it doesn't exist, issue error & exit script.
     echo
     echo "$config_file does not exist."
     echo "Backup not completed due to missing Configuration File"
     echo
     exit
fi
#
# Build the names of all the files to backup
#
file_no=1               # Start on Line 1 of Config File.
exec < $config_file     # Redirect Std Input to name of Config File
#
read file_name          # Read 1st record
#
while [ $? -eq 0 ]      # Create list of files to backup.
do
        # Make sure the file or directory exists.
     if [ -f $file_name -o -d $file_name ]
     then
          # If file exists, add its name to the list.
          file_list="$file_list $file_name"
     else
          # If file doesn't exist, issue warning
          echo
          echo "$file_name, does not exist."
          echo "Obviously, I will not include it in this archive."
          echo "It is listed on line $file_no of the config file."
          echo "Continuing to build archive list..."
          echo
     fi
#
     file_no=$[$file_no + 1]  # Increase Line/File number by one.
     read file_name           # Read next record.
done
#
#######################################
#
# Backup the files and Compress Archive
#
echo "Starting archive..."
echo
#
tar -czf $destination $file_list 2> /dev/null
#
echo "Archive completed"
echo "Resulting archive file is: $destination"
echo
#
exit
```

---
上一篇：[练习10 gawk进阶](../practice-10/)，[目录](#编写简单的脚本实用工具)｜[首页](../README.md)

## 删除账户

```bash
#!/bin/bash
#
#Delete_User - Automates the 4 steps to remove an account
#
###############################################################
# Define Functions
#
#####################################################
function get_answer {
#
unset answer
ask_count=0
#
while [ -z "$answer" ]    #While no answer is given, keep asking.
do
     ask_count=$[ $ask_count + 1 ]
#
     case $ask_count in   #If user gives no answer in time allotted
     2)
          echo
          echo "Please answer the question."
          echo
     ;;
     3)
          echo
          echo "One last try...please answer the question."
          echo
     ;;
     4)
          echo
          echo "Since you refuse to answer the question..."
          echo "exiting program."
          echo
          #
          exit 
     ;;
     esac
#
     if [ -n "$line2" ]
     then               #Print 2 lines
          echo $line1
          echo -e $line2" \c"
     else                    #Print 1 line
          echo -e $line1" \c"
     fi
#
#     Allow 60 seconds to answer before time-out
     read -t 60 answer
done
# Do a little variable clean-up
unset line1
unset line2
#
}  #End of get_answer function
# 
#####################################################
function process_answer {
#
answer=$(echo $answer | cut -c1)
#
case $answer in
y|Y) 
# If user answers "yes", do nothing. 
;;
*)                   
# If user answers anything but "yes", exit script 
        echo 
        echo $exit_line1 
        echo $exit_line2
        echo 
        exit
;;
esac
#
# Do a little variable clean-up
#
unset exit_line1
unset exit_line2
#
} #End of process_answer function
#
##############################################
# End of Function Definitions
#
############# Main Script ####################
# Get name of User Account to check 
#
echo "Step #1 - Determine User Account name to Delete "
echo
line1="Please enter the username of the user " 
line2="account you wish to delete from system:"
get_answer
user_account=$answer
#
# Double check with script user that this is the correct User Account 
# 
line1="Is $user_account the user account " 
line2="you wish to delete from the system? [y/n]"
get_answer
# 
# Call process_answer funtion: 
#     if user answers anything but "yes", exit script
#
exit_line1="Because the account, $user_account, is not " 
exit_line1="the one you wish to delete, we are leaving the script..."  
process_answer
#
################################################################
# Check that user_account is really an account on the system 
# 
user_account_record=$(cat /etc/passwd | grep -w $user_account) 
# 
if [ $? -eq 1 ]          # If the account is not found, exit script 
then 
     echo 
     echo "Account, $user_account, not found. " 
     echo "Leaving the script..." 
     echo 
     exit 
fi 
# 
echo 
echo "I found this record:" 
echo $user_account_record 
echo 
# 
line1="Is this the correct User Account? [y/n]" 
get_answer
# 
# 
# Call process_answer function: 
#       if user answers anything but "yes", exit script
# 
exit_line1="Because the account, $user_account, is not "
exit_line2="the one you wish to delete, we are leaving the script..." 
process_answer
#
##################################################################
# Search for any running processes that belong to the User Account 
#
echo 
echo "Step #2 - Find process on system belonging to user account"
echo
# 
ps -u $user_account > /dev/null  #List user processes running.  

case $? in 
1)     # No processes running for this User Account 
        #  
     echo "There are no processes for this account currently running." 
     echo 
;; 
0)   # Processes running for this User Account. 
     # Ask Script User if wants us to kill the processes. 
     # 
     echo "$user_account has the following process(es) running:"
     ps -u $user_account
     #
     line1="Would you like me to kill the process(es)? [y/n]" 
     get_answer 
     # 
     answer=$(echo $answer | cut -c1)
     #
     case $answer in                  
     y|Y)   # If user answers "yes", 
            # kill User Account processes. 
            # 
            echo
            echo "Killing off process(es)..."
            #
            # List user process running code in command_1
            command_1="ps -u $user_account --no-heading"
            #
            # Create command_3 to kill processes in variable
            command_3="xargs -d \\n /usr/bin/sudo /bin/kill -9"
            #
            # Kill processes via piping commands together
            $command_1 | gawk '{print $1}' | $command_3
            #
            echo
            echo "Process(es) killed."
     ;;
     *)     #If user answers anything but "yes", do not kill.
            echo
            echo "Will not kill process(es)."
     ;;
     esac
;;
esac
#################################################################
# Create a report of all files owned by User Account 
#
echo 
echo "Step #3 - Find files on system belonging to user account"
echo 
echo "Creating a report of all files owned by $user_account." 
echo 
echo "It is recommended that you backup/archive these files," 
echo "and then do one of two things:" 
echo "  1) Delete the files" 
echo "  2) Change the files' ownership to a current user account." 
echo 
echo "Please wait. This may take a while..." 
# 
report_date=$(date +%y%m%d) 
report_file="$user_account"_Files_"$report_date".rpt 
# 
find / -user $user_account > $report_file 2>/dev/null 
# 
echo 
echo "Report is complete." 
echo "Name of report:      $report_file" 
echo -n "Location of report: "; pwd
echo
####################################
#  Remove User Account
echo 
echo "Step #4 - Remove user account"
echo
# 
line1="Do you wish to remove $user_account's account from system? [y/n]"
get_answer
# 
# Call process_answer function: 
#       if user answers anything but "yes", exit script
# 
exit_line1="Since you do not wish to remove the user account,"
exit_line2="$user_account at this time, exiting the script..."
process_answer
#
userdel $user_account          #delete user account
echo
echo "User account, $user_account, has been removed"
echo
#
exit
```

---
上一篇：[练习10 gawk进阶](../practice-10/)，[目录](#编写简单的脚本实用工具)｜[首页](../README.md)

## 系统审计

```bash
#!/bin/bash
#
# Audit_System.sh - Audit system files and accounts
####################################################
#
### Intialize variables #######################
#
runAccountAudit="false"
runPermAudit="false"
#
reportDir="/home/christine/scripts/AuditReports"
#
### Get options (if provided) #################
#
while getopts :Ap opt
do
     case "$opt" in
          A) runAccountAudit="true" ;;
          p) runPermAudit="true" ;;
          *) echo "Not a valid option."
             echo "Valid options are: -A, -p, or -Ap" 
             exit
          ;;
     esac
done
#
### Determine if no options ##################
#
if [ $OPTIND -eq 1 ]
then
     # No options were provided; set all to "true" 
     runAccountAudit="true"
     runPermAudit="true"
fi
#
### Run selected audits #######################
#
## Account Audit ##################
#
if [ $runAccountAudit = "true" ]
then
    echo
    echo "****** Account Audit *****"
    echo
#
# Determine current false/nologin shell count
#
    echo "Number of current false/nologin shells: "
#
    reportDate="$(date +%F%s)"
    accountReport=$reportDir/AccountAudit$reportDate.rpt
#
    # Create current report
    cat /etc/passwd | cut -d: -f7 |
    grep -E "(nologin|false)" | wc -l |
    tee $accountReport
#
    # Change report's attributes:
    sudo chattr +i  $accountReport
#
# Show past false/nologin shell count
#
    prevReport="$(ls -1t $reportDir/AccountAudit*.rpt | sed -n '2p')"
    if [ -z $prevReport ]
    then
         echo
         echo "No previous false/nologin report exists to compare."
    else
         echo
         echo "Previous report's false/nologin shells: "
         cat $prevReport
    fi
fi
#
## Permissions Audit ##############
#
if [ $runPermAudit = "true" ]
then
    echo
    echo "****** SUID/SGID Audit *****"
    echo
    reportDate="$(date +%F%s)"
    permReport=$reportDir/PermissionAudit$reportDate.rpt
#
    # Create current report
    echo "Creating report. This may take a while..."
    sudo find / -perm /6000 >$permReport 2>/dev/null  
#
    # Change report's attributes:
    sudo chattr +i  $permReport
#
# Compare to last permission report
#
    #
    prevReport="$(ls -1t $reportDir/PermissionAudit*.rpt | sed -n '2p')"
    #
    if [ -z $prevReport ]
    then
         echo
         echo "No previous permission report exists to compare."
    else
         echo
         echo "Differences between this report and the last: "
         #
         differences=$(diff $permReport $prevReport)
         #
         if [ -z "$differences" ]
         then
             echo "No differences exist."
         else
             echo $differences
         fi
    fi
fi
#
exit
```
---
上一篇：[练习10 gawk进阶](../practice-10/)，[目录](#编写简单的脚本实用工具)｜[首页](../README.md)
