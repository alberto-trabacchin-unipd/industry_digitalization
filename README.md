
Industry Digitalization
============
Assegnamento invernale del corso di Programmazione di Sistemi Embedded


---
## Introduzione

![Current Version](https://img.shields.io/badge/version-1.0.0-green.svg)

Lo scopo del progetto è simulare delle linee di packaging presenti in un magazzino; esse sono dotate di sistemi di visione per il rilevamento dei pezzi. Al termine di ogni linea sono poi presenti dei cobot per il trasferimento dei pezzi su un robot mobile per lo stoccaggio in magazzino. 

Viene richiesto di modellare e sincronizzare i vari elementi come dei sistemi concorrenti multithread, ed
implementare un sistema distribuito (socket TCP/IP) per la comunicazione col database del magazzino.

---
## Setup & Installazione

Per compilare il progrmma è necessario disporre della libreria `pthread`.

Si richiede **almeno la versione di C++11**.

## Compilazione

Si ricorda che, essendoci una comunicazione via socket, si otterranno due filel eseguibili al termine della compilazione:

1) Quello principale del sistema concorrente, che contiene anche il server del database del magazzino.
2) Quello che rappresenta il processo del client.

Per compilare il programma principale, creare una cartella `build` dal percorso principale, e da tale cartella eseguire il comando `cmake`:

```bash
cmake .. && make && ./app/application L1 V1 L2 V2
```
Dove $L_1$, $L_2$ sono le due lunghezze dei nastri trasportatori e $V_1$, $V_2$ le relative velocità.

In seguito a questo comando viene automaticamente compilato anche il programma del client. Per eseguirlo, eseguire il seguente comando da un secondo terminale:

```bash
./app/client localhost PORT
```
Dove **PORT**  è la porta scelta, e definita nel file `Socket.h`.

*Nota: assicurarsi di eseguire l'applicazione dalla cartella build.*

---
## Tutorial per l'utilizzo del programma

Per eseguire correttamente il programma:

1) Impostare nel programma `main.cpp` il numero di cobot **n_cobot** desiderato, **non maggiore di 6** (di default è pari a 2), e scegliere un fattore di scala **SPEED_FAC** per accelerare la simulazione (di default è pari a 10).

2) Scegliere dei valori positivi di $L_1$, $V_1$, L_2, V_2, ..., L_n, $V_n$, con n pari al numero di cobot (e linee) scelto.

3) Assicurarsi che la porta di default **8080** presente nel file Socket.h non sia già utilizzata dal sistema operativo. In tal caso sostituirla con una arbitraria, superiore a 1023.

4) Lanciare il programma principale e quello del client come indicato nella sezione "*Compilazione*".

5) Per spegnere correttamente il programma principale premere la combinazione di tasti **CTRL + C**.

6) Per interrompere la comunicazione via socket, inserire **stop** come scatola da cercare, dal processo client.

*Nota: Per terminare correttamente entrambi i programmi, arrestare prima il programma principale e poi la comunicazione socket.*
