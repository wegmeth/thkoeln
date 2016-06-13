i=0
while [ $i -le 299 ] ; do
	./cPiss $i
	echo $i $? 
	i=$(($i+1))
done
