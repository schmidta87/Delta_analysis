#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>

#include "TFile.h"
#include "TH1.h"
#include "TRandom3.h"

using namespace std;

int main(int argc, char ** argv)
{
  if (argc != 3)
    {
      cerr << "This program generates N random normally distributed events, bins them in a histogram, and writes it to a rootfile.\n"
	   << "    Call the program using:\n"
	   << "          example_root_program [N] /path/to/output/rootfile.root\n\n";
      return -1;
    }

  int Nevents = atoi(argv[1]);
  TFile * outfile = new TFile(argv[2],"RECREATE");
  TH1D * h = new TH1D("x","Gaussian Distributed Random Numbers;x;Counts",100,-5,5);
  TRandom3 rng(0);

  for (int event=0 ; event < Nevents ; event++)
    {
      h->Fill(rng.Gaus());
    }

  h->Write();
  outfile->Close();
  
  return 0;
}
