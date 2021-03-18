# Proyecto 1 Laboratorio Avanzado- Felipe Choy

_En este proyecto se encuentra la vida media del muon mediante el uso de C++ , Cmake y ROOT_

## Comenzando 🚀

_Navegar hacia la carpeta build y dejar los archivos de datos en la misma (también se puede dejar en una carpeta por aparte)._

### Pre-requisitos 📋

_Es necesario tener instalado ROOT, g++ y BOOST_

## Compilando  ⚙️

_Para compilar este programa se deben ejecutar las siguientes líneas de líneas de comando, OJO, esto es asumiendo que los archivos tienen el nombre de 1.paa, 2.paa,..., etc._

```
$ cmake ..
$ make
$ ./paa_reader -i 1.paa -o dato01.root
$ ./paa_reader -i 2.paa -o dato02.root
$ ./paa_reader -i 3.paa -o dato03.root
$ ./paa_reader -i 4.paa -o dato04.root
$ ./paa_reader -i 5.paa -o dato05.root
$ ./paa_reader -i 6.paa -o dato06.root
```
_Seguido de esto ejecuta en la consola el comando._
```
hadd "dato0.root" dato0*
```

_Luego se abre Root y se ajusta a la gráfica con los siguientes comandos_
```
TF1 *curva  = new TF1("Exp","[0]*TMath::Exp(-x/[1])+[2]");
curva -> SetParNames("N0 ","T ","b ");
curva -> SetParameters(275,200,10);
TFile *MyFile = new TFile("dato0.root","READ");

```

## Despliegue 📦

_Para ajustar y desplegar basta con el comando_

```
$ h1->Fit("Exp");
```


## Autor ✒️

_Menciona a todos aquellos que ayudaron a levantar el proyecto desde sus inicios_

* **Felipe Ixcamparic** - *Trabajo Completo* - [felipechoy1](https://github.com/felipechoy1)

##  🎁

* Gracias a Héctor Pérez por suministrar la mayor parte del material📢
* Salud 🍺 . 

