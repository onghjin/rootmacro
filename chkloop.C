#!$ROOTSYS/bin/root 
{
  gROOT->LoadMacro("chkcaldata.C");
  chkcaldata t;
  t.Loop();
}
