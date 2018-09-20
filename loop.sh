#! /bin/sh
#
# Usage: ./loop.sh 
#
runmin=$1
runmax=$2
runnum=$runmin

echo runmin $runmin
echo runmax $runmax
while :
do
  if [ $runnum -lt $runmax ]; then
     echo Nex run is $runnum
     filename='pd14Jul0'$runnum'.lmd'
     echo Analyzing data_p/$filename
    ./MainUserAnalysis data_p/$filename
     let runnum=runnum+1
  else
    echo End of Analysis
    exit
  fi
done

