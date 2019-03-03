

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

void monocromatore()
{

  // --------------------------- DATI ------------------------------- //
  // Resistenza della lampadina, misurata in laboratorio con il multimetro

  // numero misure prese
  const int n = 26;
  double lambda[n];
  double manopola[]={1000,975,950,925,900,875,850,825,800,775,750,725,700,675,650,625,600,575,550,525,500,475,450,425,400,375};
  double pixel[]={3329,3181,3031,2887,2745,2599,2459,2323,2185,2053,1915,1788,1657,1530,1402,1279,1155,1031,909,787,669,568,433,316,198,85};
  double fwhm[]={45.20,44.87,43.06,43.02,42.06,42.56,40.64,41.11,40.24,40.28,38.43,39.20,39.06,37.72,38.10,38.09,39.12,37.86,37.38,36.49,36.07,35.86,36.49,35.87,37.29,37.87};
  double sm[n];
  double sp[n];
  double sl[n];
  for(int j = 0; j<n;j++){
    sp[j]=fwhm[j]/2.355;
    sm[j] = 0.2;
  }

  for(int j=0;j<n;j++){
    lambda[j]=337.57+0.22455*pixel[j]-1.038*pow(10,-5)*pixel[j]*pixel[j]+4.3495*pow(10,-10)*pixel[j]*pixel[j]*pixel[j];
  }

  for(int j=0;j<n;j++){
    sl[j]=pow(2.83833*2.83833+pixel[j]*pixel[j]*8.94854*pow(10,-3)*8.94854*pow(10,-3)+pixel[j]*pixel[j]*pixel[j]*pixel[j]*6.70385*pow(10,-6)*6.70385*pow(10,-6)+pixel[j]*pixel[j]*pixel[j]*pixel[j]*pixel[j]*pixel[j]*1.42258*1.42258*pow(10,-18)+pow((0.22455-2*1.038*pow(10,-5)*pixel[j]+3*4.3495*pow(10,-10)*pixel[j]*pixel[j])*sp[j],2),0.5);
  }

  TCanvas *ciV = new TCanvas("cVe","Ve",200,10,600,400);
  // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
  ciV->SetFillColor(0);
  // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
  ciV->cd();
  // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
  // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
  // array delle  rispettive incertezze
  TGraph *giV = new TGraphErrors(n,manopola,lambda,sm,sl);
  // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
  // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
  giV->SetMarkerSize(0.6);
  giV->SetMarkerStyle(21);
  // Facile, titolo del grafico
  giV->SetTitle("Conversione Unita' - lunghezza d'onda");
  // Titoli degli assi
  giV->GetXaxis()->SetTitle("Unita'");
  //giV->GetXaxis()->SetAxisLimits(0,3000);
  giV->GetYaxis()->SetTitle("#lambda [nm]");
  // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
  // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
  // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
  giV->Draw("AP");

  cout << "\n\n --- Fit I(V) \n" <<endl;
  TF1 *funz0 = new TF1("funz0","pol1",100,3000);
  funz0->SetLineStyle(1);
  funz0->SetLineColor(2);
  //funz0->SetParameter(0,341.235);
  //funz0->SetParameter(1,0.216);
  //funz0->SetParameter(2,-3e-6);
  //funz0->SetParameter(3,-1e-9);
  giV->Fit(funz0,"RM+");
  cout << "Chi^2:" << funz0->GetChisquare() << ", number of DoF: " << funz0->GetNDF() << " (Probability: " << funz0->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;
    //
    TF1 *funz1 = new TF1("funz1","pol1",100,3000);
    funz1->SetLineStyle(1);
    funz1->SetLineColor(2);
    //funz1->SetParameter(0,341.235);
    //funz1->SetParameter(1,0.216);
    giV->Fit(funz1,"RM+");
    cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}
