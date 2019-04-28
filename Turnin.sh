 
#!/bin/bash
#
# Place this in a file named: Turnin.sh
#
# To run type: ./Turnin.sh
#
# If it says permission denied then you will need to change
# the permissions with the command: chmod 777 Turnin.sh
#
# If you created the Turnin.sh file on windows or if you are using
# the windows subsystem for linux you may need to convert the text
# file to a unix/linux friendly file format. Use the command: dos2unix Turnin.sh
#

set -eu

read -p "Enter Firstname: " FNAME
read -p "Enter Lastname: " LNAME
read -p "Enter Assignment Number: " ASSIGNMENT_NUMBER
read -p "Directory to Zip: " ASSIGNMENT

if [ -z $FNAME ]
then
    echo "Please enter your firstname!"
    exit 1
fi

if [ -z $LNAME ]
then
    echo "Please enter your lastname!"
    exit 1
fi

if [ -z $ASSIGNMENT_NUMBER ]
then
    echo "Please supply an assignment number!"
    exit 1
fi

if [ -z $ASSIGNMENT ]
then
    echo "Please enter an assignment directory!"
    exit 1
fi

if [ ! -f $ASSIGNMENT/CHANGELOG ]
then
    echo "Changelog not found!"
    exit 1
fi

if [ ! -f $ASSIGNMENT/README ]
then
    echo "ReadMe file not found!"
    exit 1
fi


# Copy directory
cp -R $ASSIGNMENT/ ${FNAME}_${LNAME}.assignment-$ASSIGNMENT_NUMBER

#tar the directory
tar cvfz ${FNAME}_${LNAME}.assignment-$ASSIGNMENT_NUMBER.tar.gz ${FNAME}_${LNAME}.assignment-$ASSIGNMENT_NUMBER

# remove the temp directory
rm -r ${FNAME}_${LNAME}.assignment-$ASSIGNMENT_NUMBER
