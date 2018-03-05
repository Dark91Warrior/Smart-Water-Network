# Smart Water Network

## Lista dei componenti

<table>
  <tr>
    <td>Quantità</td>
    <td>Nome + codice</td>
    <td>Budget</td>
  </tr>
  <tr>
    <td>4</td>
    <td>Flussometri da 1⁄2 e portata max 30 l/m (ARD09180CN )</td>
    <td>56.96 €</td>
  </tr>
  <tr>
    <td>1</td>
    <td>ESP8266
(P17100210)</td>
    <td>8,09 €</td>
  </tr>
  <tr>
    <td>1</td>
    <td>Cavo microUSB
(ICOC MUSB-A-006S)</td>
    <td>4.89 €</td>
  </tr>
  <tr>
    <td>1</td>
    <td>Arduino MEGA
(ARDUINOR2560)</td>
    <td>22 €</td>
  </tr>
  <tr>
    <td>1</td>
    <td>Breadboard
(ARD01002CN)</td>
    <td>3.16 €</td>
  </tr>
  <tr>
    <td>1m</td>
    <td>Cavo elettrico Ethernet
(V932144)</td>
    <td>2.85 €</td>
  </tr>
  <tr>
    <td>1m</td>
    <td>Tubo da giardino
(186874)</td>
    <td>5 €</td>
  </tr>
  <tr>
    <td>10</td>
    <td>Raccordi M-F
(35877)</td>
    <td>20 €</td>
  </tr>
  <tr>
    <td>6</td>
    <td>Riduttori da applicare al flussometro</td>
    <td>9 €</td>
  </tr>
  <tr>
    <td>7</td>
    <td>Raccordi M per rubinetto
(90320)</td>
    <td>10.50 €</td>
  </tr>
  <tr>
    <td>1</td>
    <td>Rubinetto ½ pollice</td>
    <td>3 €</td>
  </tr>
  <tr>
    <td>1</td>
    <td>Raccordo a T per rubinetto
(8614)</td>
    <td>3.5 €</td>
  </tr>
  <tr>
    <td>1</td>
    <td>Teflon
(SMK-Q0316)</td>
    <td>0.60 €</td>
  </tr>
  <tr>
    <td>1</td>
    <td>Nastro isolante
(62379 )</td>
    <td>2.50 €</td>
  </tr>
  <tr>
    <td>2</td>
    <td>Power bank
(YB6016-STGOL)</td>
    <td>20 €</td>
  </tr>
</table>


## Principio di funzionamento del progetto

### Esposizione del problema

Il problema principale che si intende risolvere è lo spreco d’acqua potabile in ambiente urbano, infatti l'Italia è un Paese ricco d'acqua, ma ne spreca "quantità enormi" per colpa di infrastrutture carenti, obsolete e inadeguate: le perdite di rete sono pari al 31,9%. Ciò ci costringe ad aumentare il prelievo di acqua alla fonte, impoverendo la risorsa ed esponendo alcuni territori a cronici disservizi. Servirebbero 65 miliardi di euro per recuperare il terreno perduto, rimettendo a posto acquedotti colabrodo e realizzando reti fognarie e impianti di depurazione delle acque reflue adeguati.

### Soluzione proposta

Per risolvere il problema citato nel paragrafo precedente abbiamo pensato ad un sistema che monitori continuamente il flusso dell’acqua in una rete idraulica e qualora venga rilevata una perdita superiore ad una certa portata nel (nostro caso il 10%) il sistema avvisi tramite un messaggio tramite un BOT di Telegram gli addetti al sistema comunicando in tempo reale sia che si sta verificando una perdita d’acqua sia la posizione della perdita. Inoltre tutte le informazioni riguardanti i vari flussi d’acqua e le perdite saranno consultabili in una piattaforma di IoT (nel nostro caso abbiamo utilizzato ThingSpeak) e tali informazioni potranno essere reperibili anche interrogando il sistema con delle stringhe di testo inserite nel BOT di Telegram che restituirà in output le informazioni desiderate.

### Procedura impiegata per ottenere la soluzione richiesta

Per ottenere la soluzione proposta abbiamo realizzato un prototipo di una rete idraulica per poter monitorare il flusso dell’acqua attraverso 4 flussometri posizionati in maniera strategica all’interno della rete. La rete è costituita dai seguenti componenti: dispositivo Arduino e un modulo ESP8266, 4 flussometri, del tubo da giardino, un rubinetto e vari raccordi. Con questo materiale abbiamo realizzato una rete idraulica per poter monitorare il flusso dell’acqua. 
Nel dettaglio abbiamo un raccordo che funziona da ingresso al quale è collegato il primo flussometro (Fmax), a questo segue uno sdoppiatore dal quale escono due tratti di tubo che terminano con due ulteriori flussometri (Flux1) e (Flux2). A valle di Flux2, collegati tramite dei tubi, abbiamo un rubinetto con il quale simuleremo la nostra perdita e dopo il quale abbiamo posizionato il quarto ed ultimo flussometro (Flux3). 
Prima dell’installazione abbiamo provveduto a tarare i singoli flussometri, facendo passare un quantitativo d’acqua noto attraverso la valvola e verificando il numero di impulsi che ci venivano restituiti. Abbiamo poi sviluppato un algoritmo con cui  riusciamo ad avere le informazioni per quanto riguarda la portata dei 4 flussometri e inoltre ad avere una notifica quando la perdita simulata supera il 10% della portata massima. In quest’ultimo caso viene inviata una notifica attraverso un bot di Telegram ad una chat scelta in fase di progetto. Il bot ci permette anche di richiedere in tempo reale i flussi dei singoli flussometri.


## Assemblaggio Hardware

Analizzato il problema che si intende risolvere si può passare all’assemblaggio, vero e proprio, del progetto.
II montaggio verrà spiegato passo passo con l’ausilio di immagini; prima di tutto occorre mostrare una panoramica del materiale, precedentemente analizzato, che è stato utilizzato.

Flussometri
![flussometri](/images/image33.png?raw=true "Flussometri")

Tubo da giardino
![tubo](/images/image35.png?raw=true "Tubo da giardino")

Raccordi e riduttori
![raccordi](/images/image34.jpg?raw=true "Raccordi e riduttori")

Power Bank
![raccordi](/images/image11.png?raw=true "Power Bank")
![raccordi](/images/image25.png?raw=true "Power Bank")

In più, naturalmente, il nodeMCU, una breadboard e del cavo ethernet da utilizzare per i collegamenti.

![node](/images/image4.jpg?raw=true "NodeMCU"){:height="50%" width="50%"}
![test image size](/images/image21.jpg?raw=true "Breadboard"){:height="50%" width="50%"}
![ethernet](/images/image23.jpg?raw=true "Cavo Ethernet")

Il primo passo consiste nell’assemblaggio della struttura su cui sono posizionati i 4 flussometri e su cui, successivamente, verranno inseriti i collegamenti elettrici.

Com’è possibile notare nella figura relativa al tubo da giardino, due raccordi sono già stati inseriti; tale tubo permetterà il collegamento tra un normale rubinetto dell’acqua e la struttura che andremo a creare. Le misure del tubo sono relative allo spazio di utilizzo e alla distanza dalla fonte d’acqua; si consigliano in ogni caso una decina di metri.

Innanzitutto serviranno dei segmenti di tubo, di misura più o meno variabile (in base allo spazio in cui verrà utilizzato il progetto, in questo caso non superano i 10 cm), come rappresentati in figura.

Tali segmenti saranno fondamentali per la creazione della struttura nella quale verranno connessi i flussometri; sarà indispensabile l’utilizzo dei raccordi per il loro assemblaggio.

Iniziamo con il montaggio del primo segmento:

![segmento](/images/image4.jpg?raw=true "Primo Segmento")
