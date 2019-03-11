

#include <iostream>           // ci serve per stampare a video il testo
#include <fstream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TLegend.h>
#include <TMath.h>
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video
using namespace std;

void calibrazione_G()
{

  // --------------------------- DATI ------------------------------- //
  // Resistenza della lampadina, misurata in laboratorio con il multimetro

  // numero misure prese
  const int n = 19;
  double lambda[]={696.54,706.72,727.29,738.40,772.40,794.82,800.62,826.45,842.46,852.14,912.30,365.01,404.66,750.39,763.51,811.53,435.84,579.07,546.08};
  //double pixel[]={1727,1780,1890,1943,2128,2257,2284,2422,2507,2568,2902,123,304,2010,2081,2338,445,1131,974};
  double fwhm[]={31.52,31.41,32.15,32.27,32.75,62.74,58.75,33.62,34.56,34.19,35.18,26.26,26.80,31.55,32.25,33.32,26.90,29.08,30.10};
  double pixel[]={1722.57, 1776.41, 1883.60, 1941.44, 2122.35, 2242.59, 2275.42, 2414.50, 2498.92, 2557.34, 2897.54, 118.33, 301.30, 2006.40, 2074.74, 2331.31, 445.29, 1127.38, 971.45};
  double sl[n];
  //double sp[] = {0.57, 0.85, 0.58, 0.50, 0.62, 0.70, 0.70, 0.47, 1.70, 0.80, 0.37, 0.49, 0.52, 0.50, 0.56, 0.65, 0.37, 0.49, 0.38};
double sp[]={12.07, 13.86, 11.02, 10.97, 11.25, 11.56, 12.34, 11.42, 12.33, 12.01, 11.95, 9.66, 10.52, 10.57, 10.76, 11.63, 8.83, 10.39, 9.81};
  for(int j = 0; j<n;j++){
    //sp[j]=1;
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
}
