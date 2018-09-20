#! /bin/sh
#
# Usage: ./anasetrun.sh runnumber
#
#   .L /home/daq/Desktop/s436/offline/jin2018jan/chkcaldata.C;
filename='pd14Jul0'$1'_CAL.root'
rm -f calFile.root 
ln -s $filename calFile.root
echo $1 > chkrun.txt
root -b chkloop.C
#root -b <<EOF
#{
#  gROOT->LoadMacro("chkcaldata.C");
#  chkcaldata t;
#  t.Loop();
#}
#EOF

