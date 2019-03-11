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

void fondo()
{

  // --------------------------- DATI ------------------------------- //
  // Resistenza della lampadina, misurata in laboratorio con il multimetro

  // numero misure prese
  const int n1 = 43;
  ifstream file;
  file.open("fondo1.txt");
  int i=0;
  double v1[n1];
  double manopola1[n1];
  double sv1[n1];

  while(!file.eof()&& i<n1){
    file>>manopola1[i]>>v1[i];
    //x += count[i]*ch[i];
    //y += count[i];
    i++;
  }
  file.close();

  double lambda1[n1];
  double sl1[n1];
  double sm1[n1];
  double a[]={-3.63456e+001,9.92450e-001};
 double sa[]={5.38479,1.08634e-002};
for(int j=0;j<n1;j++){
   lambda1[j]=a[0]+a[1]*manopola1[j];
   sm1[j]=0.02;
   sv1[j]=0.001*v1[j]+0.005;
   sl1[j]=pow(sa[0]*sa[0]+manopola1[j]*sa[1]*manopola1[j]*sa[1]+a[1]*sm1[j]*a[1]*sm1[j],0.5);
 }

  TCanvas *ciV = new TCanvas("cVe","Ve",200,10,600,400);
  // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
  ciV->SetFillColor(0);
  // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
  ciV->cd();
  // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
  // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
  // array delle  rispettive incertezze
  TGraph *giV = new TGraphErrors(n1,lambda1,v1,sl1,sv1);
  // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
  // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
  giV->SetMarkerSize(0.6);
  giV->SetMarkerStyle(21);
  giV->SetLineColor(12);
  giV->SetFillStyle(3110);
  // Facile, titolo del grafico
  giV->SetTitle("Fondo");
  // Titoli degli assi
  giV->GetXaxis()->SetTitle("#lambda [nm]");
  //giV->GetXaxis()->SetAxisLimits(0,3000);
  giV->GetYaxis()->SetTitle("Vpp [mV]");


  const int n2 = 36;
  ifstream file2;
  file2.open("fondo2.txt");
  i=0;
  double v2[n2];
  double manopola2[n2];
  double sv2[n2];

  while(!file.eof()&& i<n2){
    file2>>manopola2[i]>>v2[i]>>sv2[i];
    cout<<manopola2[i]<<'\t'<<v2[i]<<'\t'<<sv2[i]<<endl;
    i++;
  }
  file.close();

  double lambda2[n2];
  double sl2[n2];
  double sm2[n2];
for(int j=0;j<n2;j++){
   lambda2[j]=a[0]+a[1]*manopola2[j];
   sm2[j]=0.02;
   sl2[j]=pow(sa[0]*sa[0]+manopola2[j]*sa[1]*manopola2[j]*sa[1]+a[1]*sm2[j]*a[1]*sm2[j],0.5);
 }

  TGraph *gtrasm = new TGraphErrors(n2,lambda2,v2,sl2,sv2);
  gtrasm->SetMarkerSize(0.6);
  gtrasm->SetMarkerStyle(21);
  gtrasm->SetMarkerColor(2);
  gtrasm->SetLineColor(2);
  gtrasm->SetFillStyle(3010);
  gtrasm->SetTitle("Trasmittanza GaSe Oscilloscopio");
  // Titoli degli assi
  gtrasm->GetXaxis()->SetTitle("#lambda [nm]");
  gtrasm->GetYaxis()->SetTitle("Trasmittanza");
  const int n3 = 24;
  ifstream file3;
  file3.open("fondo3.txt");
  i=0;
  double v3[n3];
  double manopola3[n3];
  double sv3[n3];

  while(!file.eof()&& i<n3){
    file3>>manopola3[i]>>v3[i]>>sv3[i];
    cout<<manopola3[i]<<'\t'<<v3[i]<<'\t'<<sv3[i]<<endl;
    i++;
  }
  file.close();

  double lambda3[n3];
  double sl3[n3];
  double sm3[n3];
for(int j=0;j<n3;j++){
   lambda3[j]=a[0]+a[1]*manopola3[j];
   sm3[j]=0.02;
   sl3[j]=pow(sa[0]*sa[0]+manopola3[j]*sa[1]*manopola3[j]*sa[1]+a[1]*sm3[j]*a[1]*sm3[j],0.5);
 }

  TGraph *g3 = new TGraphErrors(n3,lambda3,v3,sl3,sv3);
  g3->SetMarkerSize(0.6);
  g3->SetMarkerStyle(21);
  g3->SetMarkerColor(4);
  g3->SetLineColor(4);
  g3->SetFillStyle(3010);
  g3->SetTitle("3ittanza GaSe Oscilloscopio");
  // Titoli degli assi
  g3->GetXaxis()->SetTitle("#lambda [nm]");
  g3->GetYaxis()->SetTitle("3ittanza");
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(giV,"P");
  mg->Add(gtrasm,"P");
  mg->Add(g3,"P");
  mg->SetTitle("Misure di riferimento I_{0}; #lambda [nm]; Vpp [mV]");
  mg->Draw("AP");
}
