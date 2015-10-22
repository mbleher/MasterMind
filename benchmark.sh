#! /bin/bash

TOTAL=0
NBITER=1
MAX=0
RES=0
BESTMAX=10
THRESH=150
MINAVG=10

echo "Launching game with every possible combination $NBITER times, this might take a while..."

for j in $(eval echo "{1..$NBITER}")
do
    ACC=0
    CPT=0
    MAX=0
    for i in {0000..9999}
    do
	./MasterMind $i $THRESH > /dev/null 2>&1
	RES=$?
	ACC=$(($ACC + $RES))
	if [ $RES -gt 0 ]
	then
	    CPT=$(($CPT + 1))
	    if [ $RES -gt $MAX ]
	    then
		MAX=$RES
	    fi
	fi
    done
    if [ $MAX -lt $BESTMAX ]
    then
	echo "Min of maximum number of guesses found for threshold $THRESH ($MAX)" >> bestmax.log
	BESTMAX=$MAX
    fi
    TMP=`bc -l <<< "$ACC / $CPT"`
    echo "Iteration $j out of $NBITER complete. Average: $TMP"
    CMP=`bc -l <<< "$TMP<$MINAVG"`
    if [ $CMP -eq '1' ]
    then
	echo "New best average found for threshold $THRESH ($TMP)" >> bestavg.log
	MINAVG=$TMP
    fi
    TOTAL=`bc -l <<< "$TOTAL + $TMP"`
    THRESH=$(($THRESH + 50))
done
echo
echo -n "Average number of guesses after $NBITER iterations: "
bc -l <<< "$TOTAL / $NBITER"
