#! /bin/sh
#
# Usage: ./anasetrun.sh runmin runmax
#
runmin=$1
runmax=$2
runnum=$runmin

echo From run$runmin to run$runmax
while :
do
  if [ $runnum -le $runmax ]; then
    echo Plot figures for run$runnum
    filename='pd14Jul0'$runnum'_CAL.root'
    rm -f calFile.root 
    ln -s $filename calFile.root
    echo $runnum > chkrun.txt
    root -b -q chkloop.C
    let runnum=runnum+1
  else
    echo End 
    exit
  fi
done
