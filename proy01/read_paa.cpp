/* 
 * read_pas.cpp: Código para lectura de archivos .paa
 * provenientes de la captura de datos de un WCD con la
 * utilidad Pulse Acquire para Red Pitaya. 
 * 
 * Felipe Ixcamparic, marzo 2021.
 * 
 * El código original es propiedad de Héctor Pérez.
 * 
 * Para el curso de Laboratorio Avanzado
 * ECFM - USAC
 * 
 */

#include <cstdio>
#include <vector>

#include "TGraph.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TFile.h"
#include "TF1.h"
#include "TROOT.h"

/* Header de la clase paa_file que maneja los archivos .paa */
#include "paa.hpp"

/* Header de la clase largs que maneja los argumentos de línea */
#include "largs.hpp"

int main(int argc, char* argv[])
{
    /* Primero se crea una instancia de la clase que hace el 
     * "parsing" de los argumentos de línea proporcionados 
     * al programa. */ 
    largs cmd_args(argc,argv);

    /* Si los argumentos de la línea de comandos no son adecuados se 
     * interrumpe la ejecución delprograma. */
    if( !cmd_args.Args_Ok() )
        return 1;

    /* Se asocia el archivo de entrada provisto en el argumento
     * de línea con una instancia de la clase paa_file. */
    paa_file mi_archivo( cmd_args.GetLArgInputFile() );

    /* Se verifica si la asociación del archivo fue exitosa, 
     * Si no, se sale del programa */
    if(!mi_archivo.Is_Open())
        return 1;

    /* Se crean dos vectores de enteros para almacenar los datos
     * del pulso que se va leer desde el archivo .paa */
    std::vector<int> * pulseData_v;
    

    /* Se obtienen los datos del pulso requerido. El pulso que a
     * obtener se especifica en la linea de comandos. */
    
    int trig= -285;
    int npulsos=mi_archivo.GetPulseEntries();
    
    int temp1=0,temp2=0;
    
    int conteo=0;

    /*Se crea un histograma con 28 bines y se le deja que luego lo 
      ajuste automáticamente */
    

    TH1D *aHist = new TH1D("h1","Histograma de pulsos dobles",25,0,0); 
   
    /*Iteración que pasa alrededor de cada pulso*/
    for (int i =0; i<npulsos ; i++)
    {

        /*Se obtiene el pulto i-ésimo por el que se esta
        recorriendo*/
        pulseData_v=mi_archivo.GetPulse(i);

        /*Programación defensiva*/
        if(!pulseData_v)
        return 1;   
        
        /*Reinicio de las variables de conteo y temporales
        para llenar el histograma*/
        temp1=0;
        temp2=0;
        conteo=0;

        /*Se hace otro cíclo que medirá si hay un pulso 
          doble recorriendo los puntos*/
        for (int j=0; j<1100; j++) //En los archivos de datos indicaba que eran los puntos por pulso (es el mismo para todos los archivos)
        {
            /*Busca los puntos en los que sobrepasan al trigger (el trigger es negativo)*/
            if((pulseData_v->at(j)< trig))
            {
                /*Ya que son 2 pulsos en este momento se encarga de detectar el primer e irá haciendo un salto de 15 puntos*/
                if (conteo==0)
                {
                    temp1=j; //Almacena el punto en la primera variable 
                    j=j+15;
                    conteo++; //Se aumenta la variable de conteo
                }
                /*  Cuando el conteo esta en 1 toca el segundo pulso  */
                else if(conteo==1)
                {
                    temp2=j; //Se almacena el punto en la variable temporal
                    conteo++;
                    break;
                }
              

            }
        
        }

        /*Cuando el conteo obtiene un valor de 2, almacena los valores de tiempo almacenado en las variables
        temporales y las resta para encontrar el valor correspondiente al pulso*/
        if(conteo==2)
        {
            aHist->Fill((temp2-temp1)*8);
        }

    }

    /*Se crea un archivo de tipo root en donde se almacenará ese archivo*/
    TFile *aFile= new TFile(cmd_args.GetLArgOutputFile().c_str(),"RECREATE"); //Es importante que al ejecutar -o se escriba .root al final del nombre
    aHist->Write(); //Se escribe y se cierra en el histograma.
    aFile->Close();
    

    return 0;

}

