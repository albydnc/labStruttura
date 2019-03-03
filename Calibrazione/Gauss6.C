

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

void Gauss6()
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
  a.open("CAL6PIX.txt");
  int i=0;
  while(!a.eof()&& i<n){
    a>>ch[i]>>count[i];
    cout << ch[i]<<"\t"<<count[i]<<endl;
    x += count[i]*ch[i];
    y += count[i];
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
  giV->SetTitle("Spettro di calibrazione - 6 ms / 100");
  // Titoli degli assi
  giV->GetXaxis()->SetTitle("Pixel");
  //giV->GetXaxis()->SetAxisLimits(0,3000);
  giV->GetYaxis()->SetTitle("Conteggi");
  // Do istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd()
  // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
  // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
  giV->Draw("AP");

  cout << "\n\n --- Fit I(V) \n" <<endl;
  TF1 *funz0 = new TF1("funz0","gaus",90,150);
  // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
  funz0->SetLineStyle(1);
  funz0->SetLineColor(2);
  funz0->SetParameter(1,445);
  //funz0->SetParameter(1,22);
  giV->Fit(funz0,"RM+");
  cout << "Chi^2:" << funz0->GetChisquare() << ", number of DoF: " << funz0->GetNDF() << " (Probability: " << funz0->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;
    //
    TF1 *funz1 = new TF1("funz1","gaus",270,330);
    // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
    funz1->SetLineStyle(1);
    funz1->SetLineColor(2);
    //funz1->SetParameter(1,445);
    //funz1->SetParameter(1,22);
    giV->Fit(funz1,"RM+");
    cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
      //
      TF1 *funz2 = new TF1("funz2","gaus",1690,1750);
      // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
      funz2->SetLineStyle(1);
      funz2->SetLineColor(2);
      //funz2->SetParameter(1,445);
      //funz2->SetParameter(1,22);
      giV->Fit(funz2,"RM+");
      cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: " << funz2->GetNDF() << " (Probability: " << funz2->GetProb() << ")." << endl;
      cout << "--------------------------------------------------------------------------------------------------------" << endl;
        //

        TF1 *funz3 = new TF1("funz3","gaus",1760,1810);
        // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
        funz3->SetLineStyle(1);
        funz3->SetLineColor(2);
        //funz5->SetParameter(1,445);
        //funz5->SetParameter(1,22);
        giV->Fit(funz3,"RM+");
        cout << "Chi^2:" << funz3->GetChisquare() << ", number of DoF: " << funz3->GetNDF() << " (Probability: " << funz3->GetProb() << ")." << endl;
        cout << "--------------------------------------------------------------------------------------------------------" << endl;
          //
          TF1 *funz4 = new TF1("funz4","gaus",1860,1910);
          // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
          funz4->SetLineStyle(1);
          funz4->SetLineColor(2);
          //funz4->SetParameter(1,445);
          //funz4->SetParameter(1,22);
          giV->Fit(funz4,"RM+");
          cout << "Chi^2:" << funz4->GetChisquare() << ", number of DoF: " << funz4->GetNDF() << " (Probability: " << funz4->GetProb() << ")." << endl;
          cout << "--------------------------------------------------------------------------------------------------------" << endl;
            //
            TF1 *funz5 = new TF1("funz5","gaus",1920,1970);
            // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
            funz5->SetLineStyle(1);
            funz5->SetLineColor(2);
            //funz5->SetParameter(1,445);
            //funz5->SetParameter(1,22);
            giV->Fit(funz5,"RM+");
            cout << "Chi^2:" << funz5->GetChisquare() << ", number of DoF: " << funz5->GetNDF() << " (Probability: " << funz5->GetProb() << ")." << endl;
            cout << "--------------------------------------------------------------------------------------------------------" << endl;
              //
              TF1 *funz6 = new TF1("funz6","gaus",1980,2040);
              // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
              funz6->SetLineStyle(1);
              funz6->SetLineColor(2);
              //funz6->SetParameter(1,445);
              //funz6->SetParameter(1,22);
              giV->Fit(funz6,"RM+");
              cout << "Chi^2:" << funz6->GetChisquare() << ", number of DoF: " << funz6->GetNDF() << " (Probability: " << funz6->GetProb() << ")." << endl;
              cout << "--------------------------------------------------------------------------------------------------------" << endl;
                //
                TF1 *funz7 = new TF1("funz7","gaus",2050,2100);
                // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                funz7->SetLineStyle(1);
                funz7->SetLineColor(2);
                //funz7->SetParameter(1,445);
                //funz7->SetParameter(1,22);
                giV->Fit(funz7,"RM+");
                cout << "Chi^2:" << funz7->GetChisquare() << ", number of DoF: " << funz7->GetNDF() << " (Probability: " << funz7->GetProb() << ")." << endl;
                cout << "--------------------------------------------------------------------------------------------------------" << endl;
                  //
                  TF1 *funz8 = new TF1("funz8","gaus",2110,2160);
                  // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                  funz8->SetLineStyle(1);
                  funz8->SetLineColor(2);
                  //funz8->SetParameter(1,445);
                  //funz8->SetParameter(1,22);
                  giV->Fit(funz8,"RM+");
                  cout << "Chi^2:" << funz8->GetChisquare() << ", number of DoF: " << funz8->GetNDF() << " (Probability: " << funz8->GetProb() << ")." << endl;
                  cout << "--------------------------------------------------------------------------------------------------------" << endl;
                    //
                    TF1 *funz9 = new TF1("funz9","gaus",2210,2258);
                    // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                    funz9->SetLineStyle(1);
                    funz9->SetLineColor(2);
                    //funz9->SetParameter(1,445);
                    //funz9->SetParameter(1,22);
                    giV->Fit(funz9,"RM+");
                    cout << "Chi^2:" << funz9->GetChisquare() << ", number of DoF: " << funz9->GetNDF() << " (Probability: " << funz9->GetProb() << ")." << endl;
                    cout << "--------------------------------------------------------------------------------------------------------" << endl;
                      //
                      TF1 *funz10 = new TF1("funz10","gaus",2260,2305);
                      // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                      funz10->SetLineStyle(1);
                      funz10->SetLineColor(2);
                      //funz10->SetParameter(1,445);
                      //funz10->SetParameter(1,22);
                      giV->Fit(funz10,"RM+");
                      cout << "Chi^2:" << funz10->GetChisquare() << ", number of DoF: " << funz10->GetNDF() << " (Probability: " << funz10->GetProb() << ")." << endl;
                      cout << "--------------------------------------------------------------------------------------------------------" << endl;
                        //
                        TF1 *funz11 = new TF1("funz11","gaus",2310,2360);
                        // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                        funz11->SetLineStyle(1);
                        funz11->SetLineColor(2);
                        //funz11->SetParameter(1,445);
                        //funz11->SetParameter(1,22);
                        giV->Fit(funz11,"RM+");
                        cout << "Chi^2:" << funz11->GetChisquare() << ", number of DoF: " << funz11->GetNDF() << " (Probability: " << funz11->GetProb() << ")." << endl;
                        cout << "--------------------------------------------------------------------------------------------------------" << endl;
                          //
                          TF1 *funz12 = new TF1("funz12","gaus",2390,2440);
                          // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                          funz12->SetLineStyle(1);
                          funz12->SetLineColor(2);
                          //funz12->SetParameter(1,445);
                          //funz12->SetParameter(1,22);
                          giV->Fit(funz12,"RM+");
                          cout << "Chi^2:" << funz12->GetChisquare() << ", number of DoF: " << funz12->GetNDF() << " (Probability: " << funz12->GetProb() << ")." << endl;
                          cout << "--------------------------------------------------------------------------------------------------------" << endl;
                            //
                            TF1 *funz13 = new TF1("funz13","gaus",2470,2525);
                            // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                            funz13->SetLineStyle(1);
                            funz13->SetLineColor(2);
                            //funz13->SetParameter(1,445);
                            //funz13->SetParameter(1,22);
                            giV->Fit(funz13,"RM+");
                            cout << "Chi^2:" << funz13->GetChisquare() << ", number of DoF: " << funz13->GetNDF() << " (Probability: " << funz13->GetProb() << ")." << endl;
                            cout << "--------------------------------------------------------------------------------------------------------" << endl;
                              //
                              TF1 *funz14 = new TF1("funz14","gaus",2530,2580);
                              // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                              funz14->SetLineStyle(1);
                              funz14->SetLineColor(2);
                              //funz14->SetParameter(1,445);
                              //funz14->SetParameter(1,22);
                              giV->Fit(funz14,"RM+");
                              cout << "Chi^2:" << funz14->GetChisquare() << ", number of DoF: " << funz14->GetNDF() << " (Probability: " << funz14->GetProb() << ")." << endl;
                              cout << "--------------------------------------------------------------------------------------------------------" << endl;
                                //
                                TF1 *funz15 = new TF1("funz15","gaus",2870,2930);
                                // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
                                funz15->SetLineStyle(1);
                                funz15->SetLineColor(2);
                                //funz15->SetParameter(1,445);
                                //funz15->SetParameter(1,22);
                                giV->Fit(funz15,"RM+");
                                cout << "Chi^2:" << funz15->GetChisquare() << ", number of DoF: " << funz15->GetNDF() << " (Probability: " << funz15->GetProb() << ")." << endl;
                                cout << "--------------------------------------------------------------------------------------------------------" << endl;
                                  //


}
