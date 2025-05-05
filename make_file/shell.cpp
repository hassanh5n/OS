#print
echo "Welcome to Shell Printing Class:"
#take input and display outp
echo "Enter first subject marks:"
read num1
echo "Enter second subj marks:"
read num2
echo "the value of num1 is :" $num1
echo "the value of num 2 is: " $num2
#if else and relational operators
if [[ $num1 -gt $num2 ]];then
echo " num1 is greater then num 2"
elif [[ $num2 -gt $num1 ]];then
echo "num2 is greater then num1 "
else
echo "Both variables have same value:"
fi
#loop
echo "Enter num of directories you want to create :"
read -p "numDir: " numDir
until [[ $numDir -eq 0 ]]; do
 echo "Enter the name of directory :"
 read -r dirName
 mkdir "$dirName"
 ((numDir--))
done
#loop to delete
echo "Enter num of directories you want to remove :"
read -p "numDir: " numDir
until [[ $numDir -eq 0 ]]; do
 echo "Enter the name of directory :"
 read -r dirName
 rmdir "$dirName"
 ((numDir--))
done
while read line
do
 echo $line
done < file.txt 
echo $0
echo "Hello ,$1"
echo "Batch of ,$2"
echo "Hellow World"
#make variables in Shell
echo $BASH
echo $PWD

section=4A
name=BCS
numofstu=44
Course=OS Lab 
echo The name of Section is $name $section
echo "helllow"
#Another Program
echo "Enter Number "
read num
echo "You have entered number " $num
#marksheet program
echo "Enter your name"
read -p name
echo "Enter your Program "
read -p prog
echo "Enter your Fee"
read -p fee
echo "The name of student is " $name
echo "The name of Program is " $prog
echo "The Fee of student is " $fee
#Command Line Arguments:
echo $0
echo $1
echo $2
#Special Type of variables
#all arguments treated as string
echo "'$*' output is $*"
#count of arg
echo "'$#' output is $#"
#values of 1st and 2nd arguments
echo "'$1' '$2' outputs are $1 $2"
#pid of arg
echo "'$$' output is $$" 
#make arg string but treated each arg as separate arg 
echo "'$@' output is $@"
#status of command 0 means exec 1 means issue
echo "'$?' output is $?"
#pid of prev job
echo "'$!' output is $!"
#Array
name[0]="FAST"
name[1]="Bahria"
name[2]="KU"
name[3]="PAF KIET"
# Functions

Display_Filesin_Documents(){
local folderfile="/home/zainab/Documents"
if [[ -d "$folderfile" ]];then
echo "File present in folder"
ls "$folderfile"
else
echo "Not found"
fi
}
Display_Filesin_Documents
#function with parameters
important_details(){
local name="$1"
mkdir "$name"
local data="$2"
touch "$name/$data"
ls "$name"
}
important_details "mydir" "intro1.txt"
add_a_user()
{
USER=$1
PASSWORD="zajr"
echo "Adding user $USER ..."
echo useradd $USER
echo passwd $USER $PASSWORD
echo "Added user $USER with pass $PASSWORD"
}
add_a_user nufast
add_a_user hello
add_a_user newuser