void analyze ()
{
  TFile * f = new TFile("../filter1_C12_2p_inc/trees/filter1_rho0_C12_2p_inc_090425.root");
  TTree * inputtree = (TTree *) f->Get("filtered_tree");

  //  TLorentzVector * pipProt_p4_kin=0; // lANDING pad for memory from this data column
  // inputtree->SetBranchAddress("pipProt_p4_kin",&pipProt_p4_kin);

  TLorentzVector * pL_p4_kin=0; // lANDING pad for memory from this data column                            
  inputtree->SetBranchAddress("pL_p4_kin",&pL_p4_kin);
  TLorentzVector * pim_p4_kin=0; // lANDING pad for memory from this data column                        
  inputtree->SetBranchAddress("pim_p4_kin",&pim_p4_kin);
 TLorentzVector * pip_p4_kin=0; // lANDING pad for memory from this data column                        
  inputtree->SetBranchAddress("pip_p4_kin",&pip_p4_kin);
  
  int Nevents = inputtree->GetEntries();

  double t;
  
  inputtree->SetBranchAddress("t",&t);
  // here's the output file
  TFile * outputfile = new TFile("output.root","RECREATE");
  
  TH1D * H_pLX01=new TH1D("pLX01","all events;Lead momentum X;counts",100,-10,10);
  TH1D * H_pimin=new TH1D("pimin","all events;pimin-protmass;counts",100,0,5);
  TH1D * H_piplus=new TH1D ("piplus","all events;piplus-protmass;counts",100, 0,5);  
  TH2D * H2_pLXvsZ=new TH2D("pLXvsZ","all events;Lead momentum X;lead momentum Z;counts",100,-10,10,100,-5,15);
  TH2D * H2_pimin=new TH2D("pipprotvspippim","all events;pipprot;pippim;counts",100,-10,10,100,-5,15);

  for (int i = 0 ; i < Nevents ; i+=1)

    {
      inputtree->GetEvent(i);

      TLorentzVector piplus_Prot = (*pL_p4_kin)+(*pip_p4_kin);
      TLorentzVector piplus_pimin = (*pim_p4_kin)+(*pip_p4_kin);

      H_piplus->Fill(piplus_Prot.M());
      H_pimin->Fill(piplus_pimin.M());
      H_pLX01->Fill(pL_p4_kin->X());
      H2_pLXvsZ->Fill(pL_p4_kin->X(),pL_p4_kin->Z());
      H2_pimin->Fill(piplus_Prot.M(),piplus_pimin.M());

      //      cout << "The mass is no longer pion-like: " <<pL_p4_kin->X() << "\n";

      //    cout << "The mass is now pion-like: " <<pim_p4_kin->X() << "\n";
  
    }
  outputfile->cd();
  H_pLX01->Write();
  H2_pLXvsZ->Write();
  H_piplus->Write();
  H_pimin->Write();
  H2_pimin->Write();
 
}
