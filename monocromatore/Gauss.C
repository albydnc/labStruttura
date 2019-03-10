

#include <iostream>           // ci serve per stampare a video il testo
#include <fstream>
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TLegend.h>
#include <TMath.h>
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video
#include <cmath>
using namespace std;
// Corpo del programma. La funzione qui sotto deve avere lo stesso nome del file .C
Double_t gaus(Double_t *x,Double_t *par) {
  float result = 0.;
  float mean = 0;
    mean = par[0];
    result = par[1]*TMath::Gaus(x[0],mean,par[2],false);
  return result;
}

Double_t fpoisson(Double_t *x,Double_t *par) {
  return par[0]*TMath::Poisson(x[0],par[1]);
}

void Gauss()
{

  // --------------------------- DATI ------------------------------- //
  // Resistenza della lampadina, misurata in laboratorio con il multimetro

  // numero misure prese
  const int n = 3648;
  double ch[n];
  double count[n];
  double x = 0.;
  double y = 0.;
  ifstream a;
  a.open("output.txt");
  int i=0;
  while(!a.eof()&& i<n){
    a>>ch[i]>>count[i];
    ch[i]=i;
    cout << ch[i]<<"\t"<<count[i]<<endl;
    //x += count[i]*ch[i];
    //y += count[i];
    i++;
  }
  cout << "media "<< (x/y)<<endl;
  a.close();
  double sch[n];
  double scount[n];
  for(int j = 0; j<n;j++){
    sch[j]=5;
    scount[j]=pow(count[j],0.5);
  }
  TCanvas *ciV = new TCanvas("cVe","Ve",200,10,600,400);
  // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
  ciV->SetFillColor(0);
  // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
  ciV->cd();
  // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
  // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
  // array delle  rispettive incertezze
  TGraph *giV = new TGraphErrors(n,ch,count,sch,scount);
  // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
  // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
  giV->SetMarkerSize(0.6);
  giV->SetMarkerStyle(21);
  // Facile, titolo del grafico
  giV->SetTitle("Picchi Monocromatore");
  // Titoli degli assi
  giV->GetXaxis()->SetTitle("Pixel");
  //giV->GetXaxis()->SetAxisLimits(0,3000);
  giV->GetYaxis()->SetTitle("Conteggi");
  // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
  // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
  // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
  giV->Draw("AP");

  cout << "\n\n --- Fit I(V) \n" <<endl;
  TF1 *funz0 = new TF1("funz0","gaus",50,130);
  // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
  funz0->SetLineStyle(1);
  funz0->SetLineColor(2);
  //funz0->SetParameter(0,370);
  //funz0->SetParameter(1,22);
  giV->Fit(funz0,"RM+");
  cout << "Chi^2:" << funz0->GetChisquare() << ", number of DoF: " << funz0->GetNDF() << " (Probability: " << funz0->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;
    //
    TF1 *funz1 = new TF1("funz1","gaus",160,240);
    // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
    funz1->SetLineStyle(1);
    funz1->SetLineColor(2);
    //funz1->SetParameter(1,445);
    //funz1->SetParameter(1,22);
    giV->Fit(funz1,"RM+");
    cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
      //
      TF1 *funz2 = new TF1("funz2","gaus",280,360);
      // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
      funz2->SetLineStyle(1);
      funz2->SetLineColor(2);
      //funz2->SetParameter(1,445);
      //funz2->SetParameter(1,22);
      giV->Fit(funz2,"RM+");
      cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: " << funz2->GetNDF() << " (Probability: " << funz2->GetProb() << ")." << endl;
      cout << "--------------------------------------------------------------------------------------------------------" << endl;
        //

        TF1 *funz3 = new TF1("funz3","gaus",390,470);
        // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
        funz3->SetLineStyle(1);
        funz3->SetLineColor(2);
        //funz5->SetParameter(1,445);
        //funz5->SetParameter(1,22);
        giV->Fit(funz3,"RM+");
        cout << "Chi^2:" << funz3->GetChisquare() << ", number of DoF: " << funz3->GetNDF() << " (Probability: " << funz3->GetProb() << ")." << endl;
        cout << "--------------------------------------------------------------------------------------------------------" << endl;
          //
          TF1 *funz4 = new TF1("funz4","gaus",510, 590);
          // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
          funz4->SetLineStyle(1);
          funz4->SetLineColor(2);
          //funz4->SetParameter(1,445);
          //funz4->SetParameter(1,22);
          giV->Fit(funz4,"RM+");
          cout << "Chi^2:" << funz4->GetChisquare() << ", number of DoF: " << funz4->GetNDF() << " (Probability: " << funz4->GetProb() << ")." << endl;
          cout << "--------------------------------------------------------------------------------------------------------" << endl;
            //
            TF1 *funz5 = new TF1("funz5","gaus",620,700);
            // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
            funz5->SetLineStyle(1);
            funz5->SetLineColor(2);
            //funz5->SetParameter(1,445);
            //funz5->SetParameter(1,22);
            giV->Fit(funz5,"RM+");
            cout << "Chi^2:" << funz5->GetChisquare() << ", number of DoF: " << funz5->GetNDF() << " (Probability: " << funz5->GetProb() << ")." << endl;
            cout << "--------------------------------------------------------------------------------------------------------" << endl;
              //
              TF1 *funz6 = new TF1("funz6","gaus",740,820);
              // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
              funz6->SetLineStyle(1);
              funz6->SetLineColor(2);
              //funz6->SetParameter(1,445);
              //funz6->SetParameter(1,22);
              giV->Fit(funz6,"RM+");
              cout << "Chi^2:" << funz6->GetChisquare() << ", number of DoF: " << funz6->GetNDF() << " (Probability: " << funz6->GetProb() << ")." << endl;
              cout << "--------------------------------------------------------------------------------------------------------" << endl;
                //
                TF1 *funz7 = new TF1("funz7","gaus",870,950);
                // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                funz7->SetLineStyle(1);
                funz7->SetLineColor(2);
                //funz7->SetParameter(1,445);
                //funz7->SetParameter(1,22);
                giV->Fit(funz7,"RM+");
                cout << "Chi^2:" << funz7->GetChisquare() << ", number of DoF: " << funz7->GetNDF() << " (Probability: " << funz7->GetProb() << ")." << endl;
                cout << "--------------------------------------------------------------------------------------------------------" << endl;
                  //
                  TF1 *funz8 = new TF1("funz8","gaus",990,1070);
                  // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                  funz8->SetLineStyle(1);
                  funz8->SetLineColor(2);
                  //funz8->SetParameter(1,445);
                  //funz8->SetParameter(1,22);
                  giV->Fit(funz8,"RM+");
                  cout << "Chi^2:" << funz8->GetChisquare() << ", number of DoF: " << funz8->GetNDF() << " (Probability: " << funz8->GetProb() << ")." << endl;
                  cout << "--------------------------------------------------------------------------------------------------------" << endl;
                    //
                    TF1 *funz9 = new TF1("funz9","gaus",1110,1190);
                    // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                    funz9->SetLineStyle(1);
                    funz9->SetLineColor(2);
                    //funz9->SetParameter(1,445);
                    //funz9->SetParameter(1,22);
                    giV->Fit(funz9,"RM+");
                    cout << "Chi^2:" << funz9->GetChisquare() << ", number of DoF: " << funz9->GetNDF() << " (Probability: " << funz9->GetProb() << ")." << endl;
                    cout << "--------------------------------------------------------------------------------------------------------" << endl;
                      //
                      TF1 *funz10 = new TF1("funz10","gaus",1230,1310);
                      // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                      funz10->SetLineStyle(1);
                      funz10->SetLineColor(2);
                      //funz10->SetParameter(1,445);
                      //funz10->SetParameter(1,22);
                      giV->Fit(funz10,"RM+");
                      cout << "Chi^2:" << funz10->GetChisquare() << ", number of DoF: " << funz10->GetNDF() << " (Probability: " << funz10->GetProb() << ")." << endl;
                      cout << "--------------------------------------------------------------------------------------------------------" << endl;
                        //
                        TF1 *funz11 = new TF1("funz11","gaus",1350,1430);
                        // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                        funz11->SetLineStyle(1);
                        funz11->SetLineColor(2);
                        //funz11->SetParameter(1,445);
                        //funz11->SetParameter(1,22);
                        giV->Fit(funz11,"RM+");
                        cout << "Chi^2:" << funz11->GetChisquare() << ", number of DoF: " << funz11->GetNDF() << " (Probability: " << funz11->GetProb() << ")." << endl;
                        cout << "--------------------------------------------------------------------------------------------------------" << endl;
                          //
                          TF1 *funz12 = new TF1("funz12","gaus",1490,1570);
                          // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                          funz12->SetLineStyle(1);
                          funz12->SetLineColor(2);
                          //funz12->SetParameter(1,445);
                          //funz12->SetParameter(1,22);
                          giV->Fit(funz12,"RM+");
                          cout << "Chi^2:" << funz12->GetChisquare() << ", number of DoF: " << funz12->GetNDF() << " (Probability: " << funz12->GetProb() << ")." << endl;
                          cout << "--------------------------------------------------------------------------------------------------------" << endl;
                            //
                            TF1 *funz13 = new TF1("funz13","gaus",1610,1690);
                            // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                            funz13->SetLineStyle(1);
                            funz13->SetLineColor(2);
                            //funz13->SetParameter(1,445);
                            //funz13->SetParameter(1,22);
                            giV->Fit(funz13,"RM+");
                            cout << "Chi^2:" << funz13->GetChisquare() << ", number of DoF: " << funz13->GetNDF() << " (Probability: " << funz13->GetProb() << ")." << endl;
                            cout << "--------------------------------------------------------------------------------------------------------" << endl;
                              //
                              TF1 *funz14 = new TF1("funz14","gaus",1740,1820);
                              // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                              funz14->SetLineStyle(1);
                              funz14->SetLineColor(2);
                              //funz14->SetParameter(1,445);
                              //funz14->SetParameter(1,22);
                              giV->Fit(funz14,"RM+");
                              cout << "Chi^2:" << funz14->GetChisquare() << ", number of DoF: " << funz14->GetNDF() << " (Probability: " << funz14->GetProb() << ")." << endl;
                              cout << "--------------------------------------------------------------------------------------------------------" << endl;
                                //
                                TF1 *funz15 = new TF1("funz15","gaus",1880,1960);
                                // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                                funz15->SetLineStyle(1);
                                funz15->SetLineColor(2);
                                //funz15->SetParameter(1,445);
                                //funz15->SetParameter(1,22);
                                giV->Fit(funz15,"RM+");
                                cout << "Chi^2:" << funz15->GetChisquare() << ", number of DoF: " << funz15->GetNDF() << " (Probability: " << funz15->GetProb() << ")." << endl;
                                cout << "--------------------------------------------------------------------------------------------------------" << endl;
                                  //
                                  TF1 *funz16 = new TF1("funz16","gaus",2010,2090);
                                  // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                                  funz16->SetLineStyle(1);
                                  funz16->SetLineColor(2);
                                  //funz16->SetParameter(1,445);
                                  //funz16->SetParameter(1,22);
                                  giV->Fit(funz16,"RM+");
                                  cout << "Chi^2:" << funz16->GetChisquare() << ", number of DoF: " << funz16->GetNDF() << " (Probability: " << funz16->GetProb() << ")." << endl;
                                  cout << "--------------------------------------------------------------------------------------------------------" << endl;
                                    //
                                    TF1 *funz17 = new TF1("funz17","gaus",2150,2230);
                                    // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                                    funz17->SetLineStyle(1);
                                    funz17->SetLineColor(2);
                                    //funz17->SetParameter(1,445);
                                    //funz17->SetParameter(1,22);
                                    giV->Fit(funz17,"RM+");
                                    cout << "Chi^2:" << funz17->GetChisquare() << ", number of DoF: " << funz17->GetNDF() << " (Probability: " << funz17->GetProb() << ")." << endl;
                                    cout << "--------------------------------------------------------------------------------------------------------" << endl;
                                      //
                                      TF1 *funz18 = new TF1("funz18","gaus",2290,2370);
                                      // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                                      funz18->SetLineStyle(1);
                                      funz18->SetLineColor(2);
                                      //funz18->SetParameter(1,445);
                                      //funz18->SetParameter(1,22);
                                      giV->Fit(funz18,"RM+");
                                      cout << "Chi^2:" << funz18->GetChisquare() << ", number of DoF: " << funz18->GetNDF() << " (Probability: " << funz18->GetProb() << ")." << endl;
                                      cout << "--------------------------------------------------------------------------------------------------------" << endl;
                                        //
                                        TF1 *funz19 = new TF1("funz19","gaus",2420,2500);
                                        // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                                        funz19->SetLineStyle(1);
                                        funz19->SetLineColor(2);
                                        //funz19->SetParameter(1,445);
                                        //funz19->SetParameter(1,22);
                                        giV->Fit(funz19,"RM+");
                                        cout << "Chi^2:" << funz19->GetChisquare() << ", number of DoF: " << funz19->GetNDF() << " (Probability: " << funz19->GetProb() << ")." << endl;
                                        cout << "--------------------------------------------------------------------------------------------------------" << endl;
                                          //
                                          TF1 *funz20 = new TF1("funz20","gaus",2560,2640);
                                          // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                                          funz20->SetLineStyle(1);
                                          funz20->SetLineColor(2);
                                          //funz20->SetParameter(1,445);
                                          //funz20->SetParameter(1,22);
                                          giV->Fit(funz20,"RM+");
                                          cout << "Chi^2:" << funz20->GetChisquare() << ", number of DoF: " << funz20->GetNDF() << " (Probability: " << funz20->GetProb() << ")." << endl;
                                          cout << "--------------------------------------------------------------------------------------------------------" << endl;
                                            //
                                            TF1 *funz21 = new TF1("funz21","gaus",2690,2780);
                                            // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                                            funz21->SetLineStyle(1);
                                            funz21->SetLineColor(2);
                                            //funz21->SetParameter(1,445);
                                            //funz21->SetParameter(1,22);
                                            giV->Fit(funz21,"RM+");
                                            cout << "Chi^2:" << funz21->GetChisquare() << ", number of DoF: " << funz21->GetNDF() << " (Probability: " << funz21->GetProb() << ")." << endl;
                                            cout << "--------------------------------------------------------------------------------------------------------" << endl;
                                              //
                                              TF1 *funz22 = new TF1("funz22","gaus",2830,2930);
                                              // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                                              funz22->SetLineStyle(1);
                                              funz22->SetLineColor(2);
                                              //funz22->SetParameter(1,445);
                                              //funz22->SetParameter(1,22);
                                              giV->Fit(funz22,"RM+");
                                              cout << "Chi^2:" << funz22->GetChisquare() << ", number of DoF: " << funz22->GetNDF() << " (Probability: " << funz22->GetProb() << ")." << endl;
                                              cout << "--------------------------------------------------------------------------------------------------------" << endl;
                                                //
                                                TF1 *funz23 = new TF1("funz23","gaus",2980,3080);
                                                // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                                                funz23->SetLineStyle(1);
                                                funz23->SetLineColor(2);
                                                //funz23->SetParameter(1,445);
                                                //funz23->SetParameter(1,22);
                                                giV->Fit(funz23,"RM+");
                                                cout << "Chi^2:" << funz23->GetChisquare() << ", number of DoF: " << funz23->GetNDF() << " (Probability: " << funz23->GetProb() << ")." << endl;
                                                cout << "--------------------------------------------------------------------------------------------------------" << endl;
                                                  //
                                                  TF1 *funz24 = new TF1("funz24","gaus",3140,3240);
                                                  // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                                                  funz24->SetLineStyle(1);
                                                  funz24->SetLineColor(2);
                                                  //funz24->SetParameter(1,445);
                                                  //funz24->SetParameter(1,22);
                                                  giV->Fit(funz24,"RM+");
                                                  cout << "Chi^2:" << funz24->GetChisquare() << ", number of DoF: " << funz24->GetNDF() << " (Probability: " << funz24->GetProb() << ")." << endl;
                                                  cout << "--------------------------------------------------------------------------------------------------------" << endl;
                                                    //
                                                  /*  TF1 *funz25 = new TF1("funz25","gaus",1880,1960);
                                                    // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                                                    funz25->SetLineStyle(1);
                                                    funz25->SetLineColor(2);
                                                    //funz25->SetParameter(1,445);
                                                    //funz25->SetParameter(1,22);
                                                    giV->Fit(funz25,"RM+");
                                                    cout << "Chi^2:" << funz25->GetChisquare() << ", number of DoF: " << funz25->GetNDF() << " (Probability: " << funz25->GetProb() << ")." << endl;
                                                    cout << "--------------------------------------------------------------------------------------------------------" << endl;
                                                      //*/
//print csv
ofstream f;
f.open("fitresult.txt");
f<<funz0->GetParameter(1)<<'\t'<<funz0->GetParError(1)<<'\t'<<funz0->GetParameter(2)<<'\t'<<funz0->GetParError(2)<<'\t'<<funz0->GetChisquare()<<'\t'<<funz0->GetProb()<<endl;
f<<funz1->GetParameter(1)<<'\t'<<funz1->GetParError(1)<<'\t'<<funz1->GetParameter(2)<<'\t'<<funz1->GetParError(2)<<'\t'<<funz1->GetChisquare()<<'\t'<<funz1->GetProb()<<endl;
f<<funz2->GetParameter(1)<<'\t'<<funz2->GetParError(1)<<'\t'<<funz2->GetParameter(2)<<'\t'<<funz2->GetParError(2)<<'\t'<<funz2->GetChisquare()<<'\t'<<funz2->GetProb()<<endl;
f<<funz3->GetParameter(1)<<'\t'<<funz3->GetParError(1)<<'\t'<<funz3->GetParameter(2)<<'\t'<<funz3->GetParError(2)<<'\t'<<funz3->GetChisquare()<<'\t'<<funz3->GetProb()<<endl;
f<<funz4->GetParameter(1)<<'\t'<<funz4->GetParError(1)<<'\t'<<funz4->GetParameter(2)<<'\t'<<funz4->GetParError(2)<<'\t'<<funz4->GetChisquare()<<'\t'<<funz4->GetProb()<<endl;
f<<funz5->GetParameter(1)<<'\t'<<funz5->GetParError(1)<<'\t'<<funz5->GetParameter(2)<<'\t'<<funz5->GetParError(2)<<'\t'<<funz5->GetChisquare()<<'\t'<<funz5->GetProb()<<endl;
f<<funz6->GetParameter(1)<<'\t'<<funz6->GetParError(1)<<'\t'<<funz6->GetParameter(2)<<'\t'<<funz6->GetParError(2)<<'\t'<<funz6->GetChisquare()<<'\t'<<funz6->GetProb()<<endl;
f<<funz7->GetParameter(1)<<'\t'<<funz7->GetParError(1)<<'\t'<<funz7->GetParameter(2)<<'\t'<<funz7->GetParError(2)<<'\t'<<funz7->GetChisquare()<<'\t'<<funz7->GetProb()<<endl;
f<<funz8->GetParameter(1)<<'\t'<<funz8->GetParError(1)<<'\t'<<funz8->GetParameter(2)<<'\t'<<funz8->GetParError(2)<<'\t'<<funz8->GetChisquare()<<'\t'<<funz8->GetProb()<<endl;
f<<funz9->GetParameter(1)<<'\t'<<funz9->GetParError(1)<<'\t'<<funz9->GetParameter(2)<<'\t'<<funz9->GetParError(2)<<'\t'<<funz9->GetChisquare()<<'\t'<<funz9->GetProb()<<endl;
f<<funz10->GetParameter(1)<<'\t'<<funz10->GetParError(1)<<'\t'<<funz10->GetParameter(2)<<'\t'<<funz10->GetParError(2)<<'\t'<<funz10->GetChisquare()<<'\t'<<funz10->GetProb()<<endl;
f<<funz11->GetParameter(1)<<'\t'<<funz11->GetParError(1)<<'\t'<<funz11->GetParameter(2)<<'\t'<<funz11->GetParError(2)<<'\t'<<funz11->GetChisquare()<<'\t'<<funz11->GetProb()<<endl;
f<<funz12->GetParameter(1)<<'\t'<<funz12->GetParError(1)<<'\t'<<funz12->GetParameter(2)<<'\t'<<funz12->GetParError(2)<<'\t'<<funz12->GetChisquare()<<'\t'<<funz12->GetProb()<<endl;
f<<funz13->GetParameter(1)<<'\t'<<funz13->GetParError(1)<<'\t'<<funz13->GetParameter(2)<<'\t'<<funz13->GetParError(2)<<'\t'<<funz13->GetChisquare()<<'\t'<<funz13->GetProb()<<endl;
f<<funz14->GetParameter(1)<<'\t'<<funz14->GetParError(1)<<'\t'<<funz14->GetParameter(2)<<'\t'<<funz14->GetParError(2)<<'\t'<<funz14->GetChisquare()<<'\t'<<funz14->GetProb()<<endl;
f<<funz15->GetParameter(1)<<'\t'<<funz15->GetParError(1)<<'\t'<<funz15->GetParameter(2)<<'\t'<<funz15->GetParError(2)<<'\t'<<funz15->GetChisquare()<<'\t'<<funz15->GetProb()<<endl;
f<<funz16->GetParameter(1)<<'\t'<<funz16->GetParError(1)<<'\t'<<funz16->GetParameter(2)<<'\t'<<funz16->GetParError(2)<<'\t'<<funz16->GetChisquare()<<'\t'<<funz16->GetProb()<<endl;
f<<funz17->GetParameter(1)<<'\t'<<funz17->GetParError(1)<<'\t'<<funz17->GetParameter(2)<<'\t'<<funz17->GetParError(2)<<'\t'<<funz17->GetChisquare()<<'\t'<<funz17->GetProb()<<endl;
f<<funz18->GetParameter(1)<<'\t'<<funz18->GetParError(1)<<'\t'<<funz18->GetParameter(2)<<'\t'<<funz18->GetParError(2)<<'\t'<<funz18->GetChisquare()<<'\t'<<funz18->GetProb()<<endl;
f<<funz19->GetParameter(1)<<'\t'<<funz19->GetParError(1)<<'\t'<<funz19->GetParameter(2)<<'\t'<<funz19->GetParError(2)<<'\t'<<funz19->GetChisquare()<<'\t'<<funz19->GetProb()<<endl;
f<<funz20->GetParameter(1)<<'\t'<<funz20->GetParError(1)<<'\t'<<funz20->GetParameter(2)<<'\t'<<funz20->GetParError(2)<<'\t'<<funz20->GetChisquare()<<'\t'<<funz20->GetProb()<<endl;
f<<funz21->GetParameter(1)<<'\t'<<funz21->GetParError(1)<<'\t'<<funz21->GetParameter(2)<<'\t'<<funz21->GetParError(2)<<'\t'<<funz21->GetChisquare()<<'\t'<<funz21->GetProb()<<endl;
f<<funz22->GetParameter(1)<<'\t'<<funz22->GetParError(1)<<'\t'<<funz22->GetParameter(2)<<'\t'<<funz22->GetParError(2)<<'\t'<<funz22->GetChisquare()<<'\t'<<funz22->GetProb()<<endl;
f<<funz23->GetParameter(1)<<'\t'<<funz23->GetParError(1)<<'\t'<<funz23->GetParameter(2)<<'\t'<<funz23->GetParError(2)<<'\t'<<funz23->GetChisquare()<<'\t'<<funz23->GetProb()<<endl;
f<<funz24->GetParameter(1)<<'\t'<<funz24->GetParError(1)<<'\t'<<funz24->GetParameter(2)<<'\t'<<funz24->GetParError(2)<<'\t'<<funz24->GetChisquare()<<'\t'<<funz24->GetProb()<<endl;
f.close();
}
