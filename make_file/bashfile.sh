echo "What is your name"?
read name

read -p "what is your age?" age

echo "The name is $name and the age is $age"

if [ $age -ge 18 ]
then
	echo "$name, you are eligible to vote"
else
	echo "$name, tou are not eligible to vote"
fi
