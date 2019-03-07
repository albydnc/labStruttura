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

void fotocorrenteGaSe()
{

  // --------------------------- DATI ------------------------------- //
  // Resistenza della lampadina, misurata in laboratorio con il multimetro

  // numero misure prese
  const int n = 39;
  double fotocorrente[]={165,180,198,213,205,218,230,231,233,263,262,224,225,191,180,158,148,143,129,124,111,92,87,82,75,75,74,70,68,68,63,62,55,50,48,50,47,47,51};
  double manopola[]={500,520,540,560,570,580,590,600,610,630,635,640,641,642,643,644,645,646,647,648,649,650,651,652,653,654,655,656,657,658,659,660,665,670,680,700,730,770,800};
  double lambda[n];
  double sl[n];
  double sf[n];
  double sm[n];
  double a[]={-3.63456e+001,9.92450e-001};
 double sa[]={5.38479,1.08634e-002};

for(int j=0;j<n;j++){
   //fotocorrente[j]*=1e6;
   lambda[j]=a[0]+a[1]*manopola[j];
   sm[j]=0.02;
   sf[j]=7;
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
  TGraph *giV = new TGraphErrors(n,lambda,fotocorrente,sl,sf);
  // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
  // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
  giV->SetMarkerSize(0.6);
  giV->SetMarkerStyle(21);
  // Facile, titolo del grafico
  giV->SetTitle("Fotocorrente GaSe Oscilloscopio");
  // Titoli degli assi
  giV->GetXaxis()->SetTitle("#lambda [nm]");
  //giV->GetXaxis()->SetAxisLimits(0,3000);
  giV->GetYaxis()->SetTitle("fotocorrente [pA]");
  // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
  // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
  // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
  giV->Draw("AP");
  cout << "\n\n --- Fit I(V) \n" <<endl;

  TF1 *funz0 = new TF1("funz0","[0]+[1]/(1+exp((x-[2])/[3]))",480,780);
  funz0->SetLineStyle(1);
  funz0->SetLineColor(2);
  funz0->SetParameter(0,50);
  funz0->SetParameter(1,250);
  funz0->SetParameter(2,590);
  funz0->SetParameter(3,5);
  giV->Fit(funz0,"RM+");
  cout << "Chi^2:" << funz0->GetChisquare() << ", number of DoF: " << funz0->GetNDF() << " (Probability: " << funz0->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;

}
