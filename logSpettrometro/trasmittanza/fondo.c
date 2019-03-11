#include <iostream>           // ci serve per stampare a video il testo
#include <fstream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TMultiGraph.h>
#include <TLegend.h>
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
  const int n1 = 3648;
  ifstream file1;
  file1.open("riferimento.txt");
  int i1=0;
  double v1[n1],lambda1[n1];
  double pixel1[n1],count1[n1];
  double sv1[n1],sc1[n1];

  while(!file1.eof()&& i1<n1){
    file1>>pixel1[i1]>>count1[i1];
    cout<<pixel1[i1]<<'\t'<<count1[i1];
    i1++;
  }
  file1.close();
  double sp1[n1];
  double sl1[n1];
  double a[]={3.38770e+002,2.21705e-001,-8.14444e-006,-1.27348e-011};
  double sa[]={2.50540,7.77508e-003,5.74951e-006,1.21110e-009};
  for(int j=0;j<n1;j++){
    lambda1[j]=a[0]+a[1]*pixel1[j]+a[2]*pixel1[j]*pixel1[j]+a[3]*pixel1[j]*pixel1[j]*pixel1[j];
    sl1[j]=1;
    sc1[j]=pow(count1[j],0.5);
  }
  TCanvas *ciV = new TCanvas("cVe","Ve",200,10,600,400);
  // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
  ciV->SetFillColor(0);
  // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
  ciV->cd();
  // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
  // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
  // array delle  rispettive incertezze
  TGraph *giV = new TGraphErrors(n1,lambda1,count1,sl1,sc1);
  // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
  // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
  giV->SetMarkerSize(0.2);
  giV->SetMarkerStyle(21);
  giV->SetLineColor(12);
  giV->SetFillStyle(3110);

  const int n2 = 3648;
  ifstream file2;
  file2.open("GaAs.txt");
  int i2=0;
  double v2[n2],lambda2[n2];
  double pixel2[n2],count2[n2];
  double sv2[n2],sc2[n2];

  while(!file2.eof()&& i2<n2){
    file2>>pixel2[i2]>>count2[i2];
    cout<<pixel2[i2]<<'\t'<<count2[i2];
    i2++;
  }
  file2.close();
  double sp2[n2];
  double sl2[n2];
  for(int j=0;j<n2;j++){
    lambda2[j]=a[0]+a[1]*pixel2[j]+a[2]*pixel2[j]*pixel2[j]+a[3]*pixel2[j]*pixel2[j]*pixel2[j];
    sl2[j]=2;
    sc2[j]=pow(count2[j],0.5);
  }

  TGraph *giV1 = new TGraphErrors(n2,lambda2,count2,sl2,sc2);
  // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
  // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
  giV1->SetMarkerSize(0.2);
  giV1->SetMarkerStyle(21);
  giV1->SetMarkerColor(43);
  giV1->SetLineColor(43);
  giV1->SetFillStyle(3110);

  const int n3 = 3648;
  ifstream file3;
  file3.open("GaSe.txt");
  int i3=0;
  double v3[n3],lambda3[n3];
  double pixel3[n3],count3[n3];
  double sv3[n3],sc3[n3];

  while(!file3.eof()&& i3<n3){
    file3>>pixel3[i3]>>count3[i3];
    cout<<pixel3[i3]<<'\t'<<count3[i3];
    i3++;
  }
  file3.close();
  double sp3[n3];
  double sl3[n3];
  for(int j=0;j<n3;j++){
    lambda3[j]=a[0]+a[1]*pixel3[j]+a[2]*pixel3[j]*pixel3[j]+a[3]*pixel3[j]*pixel3[j]*pixel3[j];
    sl3[j]=3;
    sc3[j]=pow(count3[j],0.5);
  }

  TGraph *giV2 = new TGraphErrors(n3,lambda3,count3,sl3,sc3);
  // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
  // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
  giV2->SetMarkerSize(0.2);
  giV2->SetMarkerStyle(21);
  giV2->SetMarkerColor(8);
  giV2->SetLineColor(8);
  giV2->SetFillStyle(3110);

  const int n4 = 3648;
  ifstream file4;
  file4.open("boh.txt");
  int i4=0;
  double v4[n4],lambda4[n4];
  double pixel4[n4],count4[n4];
  double sv4[n4],sc4[n4];

  while(!file4.eof()&& i4<n4){
    file4>>pixel4[i4]>>count4[i4];
    cout<<pixel4[i4]<<'\t'<<count4[i4];
    i4++;
  }
  file4.close();
  double sp4[n4];
  double sl4[n4];
  for(int j=0;j<n4;j++){
    lambda4[j]=a[0]+a[1]*pixel4[j]+a[2]*pixel4[j]*pixel4[j]+a[3]*pixel4[j]*pixel4[j]*pixel4[j];
    sl4[j]=4;
    sc4[j]=pow(count4[j],0.5);
  }

  TGraph *giV3 = new TGraphErrors(n4,lambda4,count4,sl4,sc4);
  // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
  // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
  giV3->SetMarkerSize(0.2);
  giV3->SetMarkerStyle(21);
  giV3->SetMarkerColor(2);
  giV3->SetLineColor(2);
  giV3->SetFillStyle(3110);

  const int n5 = 3648;
  ifstream file5;
  file5.open("HgI2.txt");
  int i5=0;
  double v5[n5],lambda5[n5];
  double pixel5[n5],count5[n5];
  double sv5[n5],sc5[n5];

  while(!file5.eof()&& i5<n5){
    file5>>pixel5[i5]>>count5[i5];
    cout<<pixel5[i5]<<'\t'<<count5[i5];
    i5++;
  }
  file5.close();
  double sp5[n5];
  double sl5[n5];
  for(int j=0;j<n5;j++){
    lambda5[j]=a[0]+a[1]*pixel5[j]+a[2]*pixel5[j]*pixel5[j]+a[3]*pixel5[j]*pixel5[j]*pixel5[j];
    sl5[j]=5;
    sc5[j]=pow(count5[j],0.5);
  }

  TGraph *giV4 = new TGraphErrors(n5,lambda5,count5,sl5,sc5);
  // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
  // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
  giV4->SetMarkerSize(0.2);
  giV4->SetMarkerStyle(21);
  giV4->SetMarkerColor(4);
  giV4->SetLineColor(4);
  giV4->SetFillStyle(3110);
  //giV4->Draw("p");
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(giV,"PX");
  mg->Add(giV1,"PX");
  mg->Add(giV2,"PX");
  mg->Add(giV3,"PX");
  mg->Add(giV4,"PX");
  mg->SetTitle("Misure di spettro dei semiconduttori; #lambda [nm]; Conteggi");
  mg->Draw("APX");
  TLegend *legend = new TLegend(0.7,0.6,0.9,0.9); // option "C" allows to center the header
  legend->AddEntry((TObject*)0, "", "");
  legend->AddEntry(giV,"Rifierimento","lep");
  legend->AddEntry(giV1,"GaAs","lep");
  legend->AddEntry(giV2,"GaSe","lep");
  legend->AddEntry(giV3,"Sconosciuto","lep");
  legend->AddEntry(giV4,"HgI_{2}","lep");
  legend->AddEntry((TObject*)0, "", "");
  legend->SetTextSize(0.04);
  legend->Draw();
}
