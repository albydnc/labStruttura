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

void capacita()
{

  // --------------------------- DATI ------------------------------- //
  // Resistenza della lampadina, misurata in laboratorio con il multimetro

  // numero misure prese
  const int n = 12;
  ifstream file;
  file.open("capacita.txt");
  int i=0;
  double vout[n],evout[n],vlock[n],evlock[n],evin[n],vin[n];
  double freq[n];
  double sf[n];
  double rap[n],raplock[n],erap[n],eraplock[n];
  while(!file.eof()&& i<n){
    file>>freq[i]>>vin[i]>>vout[i]>>evout[i]>>vlock[i]>>evlock[i];
    i++;
  }
  file.close();

for(int j=0;j<n;j++){
   evin[j]=0.01*vin[j]+0.01;
   sf[j]=0.00001*freq[j];
   rap[j]=vout[j]/vin[j];
   raplock[j]=vlock[j]/vin[j];
   erap[j]=rap[j]*pow(pow(evout[j]/vout[j],2)+pow(evin[j]/vin[j],2),0.5);
   eraplock[j]=raplock[j]*pow(pow(evlock[j]/vlock[j],2)+pow(evin[j]/vin[j],2),0.5);
 }

  TCanvas *ciV = new TCanvas("cVe","Ve",200,10,600,400);
  // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
  ciV->SetFillColor(0);
  // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
  ciV->cd();
  ciV->SetLogx();
  // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
  // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
  // array delle  rispettive incertezze
  TGraph *giV = new TGraphErrors(n,freq,rap,sf,erap);
  // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
  // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
  giV->SetMarkerSize(0.6);
  giV->SetMarkerStyle(21);
  // Facile, titolo del grafico
  giV->SetTitle("Rapporto Capacita' Oscilloscopio");
  // Titoli degli assi
  giV->GetXaxis()->SetTitle("Frequenza [Hz]");
  //giV->GetXaxis()->SetAxisLimits(0,3000);
  giV->GetYaxis()->SetTitle("V_{OUT} / V_{IN} [x10^{-3}]");
  // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
  // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
  // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)

  cout << "\n\n --- Fit I(V) \n" <<endl;

  TF1 *funz0 = new TF1("funz0","pol1",0,100);
  funz0->SetLineStyle(1);
  funz0->SetLineColor(2);
  funz0->SetParameter(1,0);
  giV->Fit(funz0,"RM+");
  cout << "Chi^2:" << funz0->GetChisquare() << ", number of DoF: " << funz0->GetNDF() << " (Probability: " << funz0->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;
  giV->Draw("AP");
  TCanvas *ciD = new TCanvas("cV","V",200,10,600,400);
  // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
  ciD->SetFillColor(0);
  // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
  ciD->cd();
  ciD->SetLogx();
  TGraph *gtrasm = new TGraphErrors(n-1,freq,raplock,sf,eraplock);
  gtrasm->SetMarkerSize(0.6);
  gtrasm->SetMarkerStyle(21);
  // Facile, titolo del grafico
  gtrasm->SetTitle("Rapporto Capacita' Lock-In");
  // Titoli degli assi
  gtrasm->GetXaxis()->SetTitle("Frequenza [Hz]");
  //gtrasm->GetXaxis()->SetAxisLimits(0,3000);
  gtrasm->GetYaxis()->SetTitle("V_{OUT} / V_{IN} [x10^{-3}]");

  TF1 *funz1 = new TF1("funz1","pol1",0,100);
  funz1->SetLineStyle(1);
  funz1->SetLineColor(2);
  funz1->SetParameter(1,0);
  gtrasm->Fit(funz1,"RM+");
  cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;

  gtrasm->Draw("AP");
}
