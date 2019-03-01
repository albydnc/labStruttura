

#include <iostream>           // ci serve per stampare a video il testo
#include <fstream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TLegend.h>
#include <TObject.h>
#include <TMath.h>
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video
using namespace std;

void calibrazione()
{

  // --------------------------- DATI ------------------------------- //
  // Resistenza della lampadina, misurata in laboratorio con il multimetro

  // numero misure prese
  const int n = 19;
  double lambda[]={696.54,706.72,727.29,738.40,772.40,794.82,800.62,826.45,842.46,852.14,912.30,365.01,404.66,750.39,763.51,811.53,435.84,579.07,546.08};
  double pixel[]={1727,1780,1890,1943,2128,2257,2284,2422,2507,2568,2902,123,304,2010,2081,2338,445,1131,974};
  double fwhm[]={31.52,31.41,32.15,32.27,32.75,62.74,58.75,33.62,34.56,34.19,35.18,26.26,26.80,31.55,32.25,33.32,26.90,29.08,30.10};
  double sl[n];
  double sp[n];
  for(int j = 0; j<n;j++){
    sp[j]=fwhm[j]/2.355;
    sl[j] = 0.01;
  }
  TCanvas *ciV = new TCanvas("cVe","Ve",200,10,600,400);
  // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
  ciV->SetFillColor(0);
  // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
  ciV->cd();
  // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
  // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
  // array delle  rispettive incertezze
  TGraph *giV = new TGraphErrors(n,pixel,lambda,sp,sl);
  // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
  // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
  giV->SetMarkerSize(0.6);
  giV->SetMarkerStyle(21);
  // Facile, titolo del grafico
  giV->SetTitle("#lambda(pixel)");
  // Titoli degli assi
  giV->GetXaxis()->SetTitle("pixel");
  //giV->GetXaxis()->SetAxisLimits(0,3000);
  giV->GetYaxis()->SetTitle("#lambda [nm]");
  // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
  // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
  // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
  giV->Draw("AP");

  cout << "\n\n --- Fit I(V) \n" <<endl;
  TF1 *funz0 = new TF1("funz0","pol3",100,3000);
  funz0->SetLineStyle(1);
  funz0->SetLineColor(2);
  funz0->SetParameter(0,341.235);
  funz0->SetParameter(1,0.216);
  funz0->SetParameter(2,-3e-6);
  funz0->SetParameter(3,-1e-9);
  giV->Fit(funz0,"RM+");
  cout << "Chi^2:" << funz0->GetChisquare() << ", number of DoF: " << funz0->GetNDF() << " (Probability: " << funz0->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;
    //
  TF1 *funz1 = new TF1("funz1","pol1",100,3000);
  funz1->SetLineStyle(1);
  funz1->SetLineColor(4);
  funz1->SetParameter(0,341.235);
  funz1->SetParameter(1,0.216);
  giV->Fit(funz1,"RM+");
  cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;
}
