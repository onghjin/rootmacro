#! /bin/sh
#
# Usage: ./anasetrun.sh runnumber
#
filename='pd14Jul0'$1'_CAL.root'
rm -f calFile.root 
ln -s $filename calFile.root
echo $1 > chkrun.txt
root -b chkloop.C
