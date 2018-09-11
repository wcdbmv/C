function clever_cat {
	if [ -s $1 ]
	then
		echo -n "output_file: "
		cat $1
	else
		echo -n "stderr: "
		cat $2
	fi
}

for i in {1..5}
do
	echo "__TEST ${i}__"
	input="./tests/in_$i.txt"
	cat $input

	echo "expect:"
	output="./tests/out_$i.txt"
	cat $output

	echo "got:"
	./app.exe $input tmp 2>tmpe
	./app.exe $input tmpf f 2>tmpfe

	echo -n "-f: "
	clever_cat tmp tmpe

	echo -n "+f: "
	clever_cat tmpf tmpfe

	echo ""
done

rm tmp tmpf tmpe tmpfe
