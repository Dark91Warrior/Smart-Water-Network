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

<img src="/images/image33.png" width="300">


Tubo da giardino

<img src="/images/image35.png" width="250">


Raccordi e riduttori

<img src="/images/image34.jpg" width="250">


Power Bank

<img src="/images/image11.png" width="150"> <img src="/images/image25.png" width="139">


In più, naturalmente, il nodeMCU, una breadboard e del cavo ethernet da utilizzare per i collegamenti.

<img src="/images/image4.jpg" width="170"> <img src="/images/image21.jpg" width="170"> <img src="/images/image23.jpg" width="170">

Il primo passo consiste nell’assemblaggio della struttura su cui sono posizionati i 4 flussometri e su cui, successivamente, verranno inseriti i collegamenti elettrici.

Com’è possibile notare nella figura relativa al tubo da giardino, due raccordi sono già stati inseriti; tale tubo permetterà il collegamento tra un normale rubinetto dell’acqua e la struttura che andremo a creare. Le misure del tubo sono relative allo spazio di utilizzo e alla distanza dalla fonte d’acqua; si consigliano in ogni caso una decina di metri.

Innanzitutto serviranno dei segmenti di tubo, di misura più o meno variabile (in base allo spazio in cui verrà utilizzato il progetto, in questo caso non superano i 10 cm), come rappresentati in figura.

<img src="/images/image6.png" width="200">

Tali segmenti saranno fondamentali per la creazione della struttura nella quale verranno connessi i flussometri; sarà indispensabile l’utilizzo dei raccordi per il loro assemblaggio.

Iniziamo con il montaggio del primo segmento:

<img src="/images/image38.png" width="200">

I raccordi vengono connessi come in figura; questo segmento sarà il primo segmento che permetterà la connessione alla rete idrica tramite, come detto in precedenza, il tubo da giardino.

A tale segmento, per il calcolo del flusso principale, viene connesso il primo flussometro.

<img src="/images/image31.png" width="200">

Da un lato, grazie all’utilizzo di un riduttore, viene fissato il primo flussometro, mentre dall’altro lato un raccordo, per permettere la divisione del flusso principale, della prima linea, in due linee derivate.

Nei due nuovi rami creati possono essere inseriti due nuovi segmenti (creati con le stesse modalità del primo) e in uno dei due può essere inserito il secondo flussometro, che sarà utilizzato per il calcolo del flusso d’acqua nel secondo ramo.

<img src="/images/image.png" width="200">

I due flussometri verranno in seguito connessi al nodeMCU tramite uno specifico schema elettrico mostrato successivamente nel tutorial.

Uno dei due rami viene utilizzato esclusivamente per il calcolo di un flusso, l’altro, invece, anche per la simulazione di una perdita.

In tale ramo può essere perciò posizionato il terzo flussometro, relativo al calcolo del secondo flusso derivato dal ramo principale, e, con l’utilizzo di un altro raccordo, un ulteriore ramo responsabile della perdita. A tale ramo può essere così connesso un rubinetto (grazie al quale la condizione di perdita o meno può essere arbitraria) e un ulteriore flussometro, fondamentale per il calcolo del flusso perso. Vengono perciò mostrate le due figure relative a queste ultime connessioni.

<img src="/images/image16.png" width="500">
<img src="/images/image26.png" width="500">

Effettuando queste operazioni viene perciò completata la struttura comprendente i 4 flussometri. Per creare una base su cui vengono poggiati i 2 Power Bank e il nodeMCU, viene inserito un piccolo piano in polistirolo, come in figura:

<img src="/images/image20.png" width="500">
<img src="/images/image36.jpg" width="500">

Per completare l’assemblaggio, viene ora mostrato lo schema circuitale da adottare per il conclusivo collegamento dei flussometri al nodeMCU.

<p align="center">
  <img src="/images/image7.png" width="600">
</p>

Com’è possibile osservare in figura, il nodeMCU viene alimentato indipendemente da un Power Bank (comunque sostituibile da un alimentatore connesso alla rete elettrica), in maniera separata dai flussometri. Nel caso illustrato in questo progetto, si sono scelti due differenti alimentazioni per motivi logistici, in ogni caso potrebbe essere utilizzato un unico alimentatore (importante però garantire un’alimentazione con un voltaggio di 5 V in grado di erogare almeno 15 mA x 4 per i flussometri, più la corrente necessaria per in nodeMCU, in questo caso sarebbe sufficiente 1 A); viene consigliato un alimentatore a 5 V in grado di erogare 2-3 A.

Di fondamentale importanza è il collegamento comune della massa (GND) tra l’alimentazione dei flussometri e il nodeMCU. Le misure effettuate sui pin di data del node, provenienti dai flussometri vengono processate come "confronto" con un segnale di riferimento, risulta perciò intuibile rendere comune tale riferimento.

Si consiglia l’utilizzo di un piccolo saldatore di precisione per i vari collegamenti tra i flussometri, utilizzando cavi Ethernet, grazie ai quali viene permesso un ottimo trasporto del segnale, una bassa attenuazione e una buona reiezione ai disturbi).

In figura viene mostrata la finale configurazione del progetto:

<p align="center">
  <img src="/images/image27.png" width="600">
</p>

Il cavo in uscita dal node può essere connesso al secondo Power Bank o ad un alimentatore precedentemente discusso.


## Sketch completo del codice o dei codici impiegati

**1. Arduino**

Andare sul sito [https://www.arduino.cc/en/Main/Software](https://www.arduino.cc/en/Main/Software) e scaricare l’ultima versione del software per poter eseguire e caricare il codice all’interno del modulo NodeMCU.

<img src="/images/image32.png" width="500">

Una volta scaricato il software, installarlo ed avviarlo. Una volta avviato creare un nuovo sketch come mostrato nell’immagine.

<img src="/images/image8.png" width="500">

Ora abbiamo creato il nostro primo sketch. Dal menù Strumenti selezionare la board di interesse e la porta di comunicazione impiegata (Porta COM). Non appena selezionate correttamente queste due impostazioni, nella parte in basso a destra della finestra della IDE di Arduino potrete trovare qualcosa simile all’immagine precedente.

**2. Installazione ed inclusione delle librerie**

**NodeMCU**

Innanzitutto bisogna scaricare la libreria del modulo ESP8266 nodeMCU. Quindi andare sul menù "Sketch->#include libreria->Gestione librerie andiamo a cercare le libreria nodeMCU sulla barra di ricerca. Dovrebbe apparire la libreria “esp8266 by ESP8266 Community" come nell’immagine seguente.

<img src="/images/image29.png" width="500">

Una volta trovata la libreria cliccare sul pulsante "Installa" e il gioco è fatto. Una volta installata la libreria andremo a selezionare dal menù: Strumenti -> Scheda -> NodeMCU 1.0 (ESP-12E Module) come raffigurato in seguito.

<img src="/images/image19.png" width="500">

Una volta installata la libreria del NodeMCU bisogna installare quelle relative a Telegram e ThingSpeak; i due portali principali di cui ci avvarremo per comunicare col nostro sistema e ricevere informazioni importanti.

**Telegram**

Come fatto precedentemente andare sulla gestione delle librerie e scrivere sulla barra di ricerca "telegram". Una volta individuata la libreria “ESP8266TelegramBOT” installarla qualora non fosse già installata. 

<img src="/images/image1.png" width="500">

**ThingSpeak**

Scrivere nella barra di ricerca: "thingspeak", individuare la libreria ed installarla

<img src="/images/image14.png" width="500">

**Includere le librerie**

Le librerie di cui ha bisogno tutto il sistema per funzionare sono quindi le seguenti:

```
#include <ESP8266WiFi.h>

#include <WiFiClientSecure.h>

#include <ThingSpeak.h>

#include <ESP8266TelegramBOT.h>
```

Notiamo le librerie di Telegram e ThingSpeak che abbiamo scaricato precedentemente.

Adesso possiamo andare ad aggiungere le informazioni mancanti all’interno del codice quali: la connessione Wi-Fi che si intende utilizzare, i canali di ThingSpeak, il Bot Telegram ecc.

**3. Download del codice da GitHub**

Andare al seguente sito [https://github.com/Dark91Warrior/Smart-Water-Network](https://github.com/Dark91Warrior/Smart-Water-Network) e scaricare tramite il pulsante Clone or Download il codice che utilizzeremo. Una volta scaricato estrarlo dall’archivio e inserire il file Smart_Water_Network in una cartella avente lo stesso nome all’interno dei progetti di Arduino che si trovano solitamente nella cartella "Documenti/Arduino/" (per chi usa Windows).

<img src="/images/image10.png" width="600">

Una volta effettuati questi passaggi possiamo andare ad analizzare il codice.

**4. Creazione dei canali ThingSpeak**

Innanzitutto andate sul sito ThingSpeak [https://thingspeak.com/](https://thingspeak.com/) e, se non lo avete già fatto, create un nuovo account cliccando il pulsante "Registrati" in alto a destra. Una volta creato l’account andate nella sezione “I miei canali” e cliccate su “New Channel”. A questo punto possiamo dare un nome e una descrizione al nostro canale oltre a selezionare i campi necessari alla visualizzazione dei dati rilevati e trasmessi alla piattaforma ThingSpeak. Nel nostro caso useremo cinque campi: Campo 1 dove inseriremo “Fmax”, Campo 2 con “Flux1”, Campo 3 con “Flux2”, Campo 4 con “Flux3” e Campo 5 con “Loss_F”. Nella figura seguente è mostrato un esempio di come appariranno i campi. Infine clicchiamo su “Save Channel” lasciando invariate le altre opzioni. A questo punto abbiamo creato il nostro canale. Affinché possa essere impiegato correttamente, occorre che il nostro modulo NodeMCU conosca il “token” associato a tale canale. Cliccate su “Chiavi API” e memorizzate l’ID Canale e la Chiave API di scrittura. Questi due valori serviranno nel momento in cui scriverete il vostro codice e cercherete di immettere nella vostra sezione personale (identificabile attraverso ID Canale e Chiave di scrittura) i valori letti dai flussometri.

<img src="/images/image2.jpg" width="300">


<img src="/images/image3.png" width="400">

Una volta creati e configurati i canali nel portale, bisogna aggiungere le informazioni del canale precedentemente citate all’interno del codice. Le variabili del codice che andremo a modificare sono quelle raffigurate nell’immagine successiva. Andremo quindi a sostituire nella variabile "myChannelNumber", l’asterisco con l’id del canale creato su ThingSpeak. Aggiungeremo poi tra i doppi apici della variabile “myWriteAPIKey” la API in scrittura del nostro canale. Queste due informazioni consentiranno al nostro modulo NodeMCU di comunicare con il canale creato sul portale web.

<img src="/images/image13.png" width="750">

**5. Creazione del Bot Telegram**

Il primo passo consiste nella creazione di un BOT e per fare ciò si utilizza un particolare BOT di Telegram. Aprire Telegram e cercare "BotFather”. La sequenza di creazione del BOT è la seguente:

1.  /newbot per iniziare la creazione di un nuovo BOT

2. Digitate il nome del vostro BOT

3. Digitare lo username del vostro bot (deve finire con _bot o bot)

4. Se la procedura è andata a buon fine, il BOT è stato creato correttamente.

Le informazioni date dal BotFather devono essere memorizzate per essere poi inserite nel codice: nome del BOT, username del BOT, token comunicato dal BotFather. Il punto del codice in cui sostituire le informazioni è raffigurato nell’immagine seguente.

<img src="/images/image37.png" width="550">

Una volta creato il Bot ci serviranno anche le informazioni della chat in cui vogliamo inviare. Possiamo inviare messaggi ad un utente in particolare o a un gruppo. In primo luogo avviamo la chat con il comando "/start". Quindi apriamo un qualsiasi browser all’indirizzo [https://api.telegram.org/bot<token>/getUpdates](https://api.telegram.org/bot<token>/getUpdates) in cui sostituiremo a <token> il codice generato in fase di creazione del bot. Per ricavare il token del Bot basta richiederlo al Bot BotFather come raffigurato nell’immagine seguente.

<img src="/images/image12.jpg" width="500">

Una volta scritto un messaggio al Bot quindi otterremo delle informazioni scritte nel formato:

```
"chat":

 {

  "username": "yourusername",

  "first_name": "yourfirstname",

  "id": XXXX

}
```

per ogni messaggio che abbiamo inviato al Bot nel sito precedentemente indicato. Per quanto riguarda l’utente, estrapoleremo l’id dell’utente o degli utenti a cui desideriamo fornire l’accesso e lo inseriremo nel codice, precisamente nella parte sottostante. Per più utenti basta dichiarare un’altra variabile (come utente2, utente3 ecc.) ed assegnargli l’id corrispondente.

<img src="/images/image17.png" width="900">

Una volta scelto il numero degli utenti a cui fornire i permessi, andremo ad aggiungerli nella relativa sezione di gestione dei messaggi di Telegram. Qualora abbiate fornito i permessi a un solo utente potete lasciare il codice invariato. Se aggiungete più utenti basta aggiungere nella condizione if l’id degli altri utenti con degli OR in questa semplice maniera:

if (0 == id.compareTo(utente1) || 0 == id.compareTo(utente2) || 0 == id.compareTo(utente3)) e così via fino a coprire il numero di utenti desiderato.

<img src="/images/image15.png" width="750">

Per quanto riguarda invece la/e chat in cui inviare il messaggio di avviso bisogna modificare il seguente pezzo di codice aggiungendo l’id della/e chat a cui volete inviare il messaggio. L’id della chat può essere estratto come abbiamo fatto con quello dell’utente. Una volta individuato dovete inserirlo all’interno della funzione bot.sendmessage("", “C’è una perdita!”, “”); e più specificatamente all’interno delle prime virgolette dentro le parentesi.

<img src="/images/image18.png" width="750">

**6. Configurazione della connessione al Wi-Fi**

Infine bisogna configurare la connessione al Wi-Fi per permettere la comunicazione del NodeMCU con le applicazioni Telegram e ThingSpeak. Nel campo ssid tra le virgolette inserite il nome della rewte Wi-Fi a cui volete connettervi e nel campo password la password relativa ad essa.

<img src="/images/image24.png" width="750">

**7. Caricamento del codice sul modulo**

Una volta effettuate tutte queste operazioni, collegate il vostro NodeMCU con un cavetto USB al vostro PC. Andate su "Strumenti" e dopo aver collegato il modulo dovrebbe apparirvi la porta a cui è connesso. Qualora non fosse già selezionata, selezionatela.

<img src="/images/image30.png" width="700">

Tramite il pulsante "Carica" a forma di freccia in alto a sinistra caricate il codice nel modulo.

<img src="/images/image9.png" width="700">

Ora dovrebbe essere tutto a posto e potrete godervi il vostro lavoro. Se avete già esperienza con questo tipo di moduli e software potete anche smanettare nel codice per modificare alcuni parametri (quali i tempi di attesa o delay ecc.). Buon divertimento!


