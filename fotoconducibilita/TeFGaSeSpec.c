#include <iostream>           // ci serve per stampare a video il testo
#include <fstream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TMultiGraph.h>
#include <TGaxis.h>
#include <TObject.h>
#include <TMath.h>
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video
using namespace std;

void TeFGaSeSpec()
{

  // --------------------------- DATI ------------------------------- //
  // Resistenza della lampadina, misurata in laboratorio con il multimetro

  // numero misure prese
  const int n = 3584;
  ifstream file;
  file.open("GaSe_T.txt");
  int i=20;
  double st[n];
  double pixel[n];
  double sp[n];
  double trasm[n];
  double lambda[n];
  double sl[n];
  double a[]={3.38770e+002,2.21705e-001,-8.14444e-006,-1.27348e-011};
  double sa[]={2.50540,7.77508e-003,5.74951e-006,1.21110e-009};

  while(!file.eof()&& i<n){
    file>>pixel[i]>>trasm[i];

    sp[i]=1;
    cout << pixel[i]<<"\t"<<trasm[i]<<"\t"<<st[i]<<endl;
    //x += count[i]*ch[i];
    //y += count[i];
    i++;
  }
  file.close();

for(int j=0;j<n;j++){
  trasm[j]=abs(trasm[j]);
  st[j]=pow(trasm[j],0.5);
   lambda[j]=a[0]+a[1]*pixel[j]+a[2]*pixel[j]*pixel[j]+a[3]*pixel[j]*pixel[j]*pixel[j];
     sl[j]=pow(sa[0]*sa[0]+pixel[j]*sa[1]*pixel[j]*sa[1]+a[1]*sp[j]*a[1]*sp[j],0.5);
 }


  TCanvas *ciD = new TCanvas("cV","V",200,10,600,400);
  // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
  ciD->SetFillColor(0);
  // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
  ciD->cd();
  TGraph *gtrasm = new TGraphErrors(n,lambda,trasm,sl,st);
  gtrasm->SetMarkerSize(0.6);
  gtrasm->SetMarkerStyle(21);
  gtrasm->SetFillColor(12);
  gtrasm->SetFillStyle(3003);
  // Facile, titolo del grafico
  gtrasm->SetTitle("Trasmittanza GaSe spettrometro");
  // Titoli degli assi
  gtrasm->GetXaxis()->SetTitle("#lambda [nm]");
  //gtrasm->GetXaxis()->SetAxisLimits(0,3000);
  gtrasm->GetYaxis()->SetTitle("Trasmittanza");

  TF1 *funz1 = new TF1("funz1","[0]+[1]/(1+exp(-(x-[2])/[3]))",550,670);
  funz1->SetLineStyle(1);
  funz1->SetLineColor(2);
  funz1->SetParameter(0,50);
  funz1->SetParameter(1,250);
  funz1->SetParameter(2,600);
  funz1->SetParameter(3,5);
  gtrasm->Fit(funz1,"RM+");
  cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;

  gtrasm->Draw("AP3");
  double max=0;
  double tmp;
  int xmax;
  for(int i = 440.; i<780.;i++){
    tmp=funz1->Derivative(i);
    if(tmp>max){
      max=tmp;
      xmax=i;
    }
  }
  cout<<"MAX DERIVATIVE TRASMITTIVITY: "<<xmax<<endl;
  max=0;
  /*for(int i = 440.; i<780.;i++){
    tmp=funz0->Derivative(i);
    if(tmp<max){
      max=tmp;
      xmax=i;
    }
  }
  cout<<"MAX DERIVATIVE PHOTOCURRENT: "<<xmax<<endl;*/
  double hc = 1239.84;
  double Egap = hc/(funz1->GetParameter(2));
  double sEgap = Egap/xmax*(funz1->GetParameter(3));

  cout<< "ENERGY GAP: (" << Egap << "+/-"<< sEgap << "eV)"<< endl;
}
