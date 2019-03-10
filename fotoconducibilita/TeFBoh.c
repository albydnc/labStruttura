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

void TeFBoh()
{

  // --------------------------- DATI ------------------------------- //
  // Resistenza della lampadina, misurata in laboratorio con il multimetro

  // numero misure prese
  const int n = 25;
  ifstream file;
  file.open("BOH_lock.TXT");
  int i=0;
  double fototensione[n];
  double st[n];
  double manopola[n];
  double sf[n];
  double trasm[n];

  while(!file.eof()&& i<n){
    file>>manopola[i]>>fototensione[i]>>sf[i]>>trasm[i]>>st[i];
    cout << manopola[i]<<"\t"<<fototensione[i]<<"\t"<<sf[i]<<"\t"<<trasm[i]<<"\t"<<st[i]<<endl;
    //x += count[i]*ch[i];
    //y += count[i];
    i++;
  }
  file.close();

  double lambda[n];
  double sl[n];
  double sm[n];
  double a[]={-3.63456e+001,9.92450e-001};
 double sa[]={5.38479,1.08634e-002};
for(int j=0;j<n;j++){
   lambda[j]=a[0]+a[1]*manopola[j];
   sm[j]=0.02;
   sl[j]=pow(sa[0]*sa[0]+manopola[j]*sa[1]*manopola[j]*sa[1]+a[1]*sm[j]*a[1]*sm[j],0.5);
 }

  TCanvas *ciV = new TCanvas("cVe","Ve",200,10,600,400);
  // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
  ciV->SetFillColor(0);
  // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
  ciV->cd();
  // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
  // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
  // array delle  rispettive incertezze
  TGraph *giV = new TGraphErrors(n,lambda,fototensione,sl,sf);
  // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
  // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
  giV->SetMarkerSize(0.6);
  giV->SetMarkerStyle(21);
  // Facile, titolo del grafico
  giV->SetTitle("Fotocorrente Campione Sconosciuto");
  // Titoli degli assi
  giV->GetXaxis()->SetTitle("#lambda [nm]");
  //giV->GetXaxis()->SetAxisLimits(0,3000);
  giV->GetYaxis()->SetTitle("Fotocorrente [pA]");
  // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
  // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
  // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)

  cout << "\n\n --- Fit I(V) \n" <<endl;
  giV->Draw("AP");
  TF1 *funz0 = new TF1("funz0","[0]+[1]/(1+exp((x-[2])/[3]))",430,550);
  funz0->SetLineStyle(1);
  funz0->SetLineColor(2);
  funz0->SetParameter(0,15);
  funz0->SetParameter(1,70);
  funz0->SetParameter(2,470);
  funz0->SetParameter(3,20);
  giV->Fit(funz0,"RM+");
  cout << "Chi^2:" << funz0->GetChisquare() << ", number of DoF: " << funz0->GetNDF() << " (Probability: " << funz0->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;
  giV->Draw("AP");
 TCanvas *ciD = new TCanvas("cV","V",200,10,600,400);
  // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
  ciD->SetFillColor(0);
  // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
  ciD->cd();
  TGraph *gtrasm = new TGraphErrors(n,lambda,trasm,sl,st);
  gtrasm->SetMarkerSize(0.6);
  gtrasm->SetMarkerStyle(21);
  // Facile, titolo del grafico
  gtrasm->SetTitle("Trasmittanza Campione Sconosciuto");
  // Titoli degli assi
  gtrasm->GetXaxis()->SetTitle("#lambda [nm]");
  //gtrasm->GetXaxis()->SetAxisLimits(0,3000);
  gtrasm->GetYaxis()->SetTitle("Trasmittanza");

  TF1 *funz1 = new TF1("funz1","[0]+[1]/(1+exp(-(x-[2])/[3]))",430,550);
  funz1->SetLineStyle(1);
  funz1->SetLineColor(2);
  funz1->SetParameter(0,100);
  funz1->SetParameter(1,1000);
  funz1->SetParameter(2,470);
  funz1->SetParameter(3,20);
  gtrasm->Fit(funz1,"RM+");
  cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;

  gtrasm->Draw("AP");
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
  for(int i = 440.; i<780.;i++){
    tmp=funz0->Derivative(i);
    if(tmp<max){
      max=tmp;
      xmax=i;
    }
  }
  cout<<"MAX DERIVATIVE PHOTOCURRENT: "<<xmax<<endl;
  double hc = 1239.84;
  double Egap = hc/xmax;
  cout<< "ENERGY GAP: " << Egap <<" eV"<< endl;
}
