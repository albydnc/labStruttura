#include <iostream>           // ci serve per stampare a video il testo
#include <fstream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TPaveText.h>
#include <TObject.h>
#include <TMath.h>
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video
using namespace std;

void trasmittanzalockGaAs()
{

  // --------------------------- DATI ------------------------------- //
  // Resistenza della lampadina, misurata in laboratorio con il multimetro

  // numero misure prese
  const int n = 36;
  double trasm[]={11090,11720,11670,13444,13691,14775,14758,14804,13500,13120,12790,11850,10583,10870,10530,10050,9574,8940,8570,8420,8165,7666,7300,6910,6450,5978,5453,4850,4270,3500,2875,2370,224,162,75,50};
  double manopola[]={1000,995,990,985,980,970,960,950,940,935,932,930,928,926,924,922,920,918,917,916,915,914,913,912,911,910,909,908,907,906,905,904,903,900,880,860};
  double st[]={160,55,83,115,276,50,56,76,46,320,400,64,509,35,65,47,61,62,107,94,42,74,34,64,50,50,41,74,590,64,62,64,208,150,90,48};
  double sm[n];
  double lambda[n];
  double sl[n];
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
  TGraph *giV = new TGraphErrors(n,lambda,trasm,sl,st);
  // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
  // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
  giV->SetMarkerSize(0.6);
  giV->SetMarkerStyle(21);
  // Facile, titolo del grafico
  giV->SetTitle("#lambda(pixel)");
  // Titoli degli assi
  giV->GetXaxis()->SetTitle("intensita");
  //giV->GetXaxis()->SetAxisLimits(0,3000);
  giV->GetYaxis()->SetTitle("#lambda [nm]");
  // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
  // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
  // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
  giV->Draw("AP");
  TF1 *funz0 = new TF1("funz0","[0]+[1]/(1+exp(-(x-[2])/[3]))",820,930);
  funz0->SetLineStyle(1);
  funz0->SetLineColor(2);
  funz0->SetParameter(0,15000);
  //funz0->SetParameter(1,-14000);
  funz0->SetParameter(2,870);
  //funz0->SetParameter(3,4);
  giV->Fit(funz0,"RM+");
  cout << "Chi^2:" << funz0->GetChisquare() << ", number of DoF: " << funz0->GetNDF() << " (Probability: " << funz0->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;

}
