/* **************************************************************************************************
 * ATTENZIONE: IL CODICE NON FUNZIONA IN QUANTO DOVETE AGGIUNGERE ALCUNI PARAMETRI IN ALCUNI PUNTI, *
 *             PERTANTO PRIMA DI AVVIARLO VI CONSIGLIAMO DI LEGGERE LA GUIDA                        *
 ****************************************************************************************************/
 
// Importo le librerie che saranno utili per far funzionare il codice
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ThingSpeak.h>
#include <ESP8266TelegramBOT.h>

/***********************
 * Smart Water Network *
 * Luca Puggioninu     *
 * Claudio Marche      *
 * Simone Madau        *
 * Roberto Piredda     *
 ***********************/

/*********************
 * Credenziali Wi-Fi *
 *********************/
const char* ssid     = "";          // Inserisci il tuo SSID di rete tra le virgolette
const char* password = "";          // Inserisci la tua password di rete tra le virgolette
bool connessione = 0;               // Inizializzo la connessione alla rete

/****************************
 * ThingSpeak configuration *
 ****************************/
unsigned long myChannelNumber = *;  // Inserisci il canale di ThingSpeak che hai configurato al posto dell'asterisco
const char* myWriteAPIKey = "";     // Inserisci le API che consentiranno la comunicazione col nostro canale ThingSpeak
int countThing = 0;                 // Inizializzo il contatore che mi servirà per gestire le chiamate al portale ThingSpeak
WiFiClient client;                  // Inizializzo la connessione
WiFiServer server(80);              // Per connettermi al server utilizzo la porta 80

/**************************************
 * Configurazione del BOT di Telegram *
 **************************************/
#define BOTtoken    ""              // Inserisci il token del BOT da te creato
#define BOTname     ""              // Inserisci il nome del BOT
#define BOTusername ""              // Inserisci l'username del BOT

// Inizializzazione della classe TelegramBot in cui i campi sono descritti nelle variabili precedentemente dichiarate
TelegramBOT bot(BOTtoken, BOTname, BOTusername);
int Bot_mtbs = 100;                 // Millisecondi dall'ultimo update dei messaggi
long Bot_lasttime;                  // L'ultima volta che è stata eseguita la scanzione dei messaggi

String utente1 = "";                // Tra i doppi apici inserire l'id dell'utente a cui si vogliono dare i permessi per comunicare col Bot
// Copiando e incollando la stringa precedente e cambiando nome della variabile e id si possono gestire permessi per più utenti

/****************************
 * Gestione dei flussometri *
 ****************************/
float         Fmax, Flux1, Flux2, Flux3; // Fmax corrisponde al flusso in ingresso. La perdita verrà gestita tra Flux2 e Flux3

const byte    flussometro1 = 5;          // Piedino di ingresso del flussometro Fmax
const byte    flussometro2 = 4;          // Piedino di ingresso del flussometro Flux1
const byte    flussometro3 = 0;          // Piedino di ingresso del flussometro Flux2
const byte    flussometro4 = 2;          // Piedino di ingresso del flussometro Flux3

// Variabili di conteggio per gestire gli interrupt dei flussometri tramite software utilizzando il NodeMCU
volatile byte count1 = 0;                // Contatore per Fmax
volatile byte count2 = 0;                // Contatore per Flux1
volatile byte count3 = 0;                // Contatore per Flux2
volatile byte count4 = 0;                // Contatore per Flux3

// Gestione della perdita
float         Loss_Consentita = 10;      // Margine di perdita consentito (in percentuale) modificabile a seconda della precisione desiderata (0 = massima precisione / 100 = nessuna precisione) 
int           countPerdita = 0;          // Contatore per la perdita
float         Loss;                      // Perdita in litri/minuto tra Flux2 e Flux3 rispetto a Fmax
float         Loss_F;                    // Percentuale di perdita  tra Flux2 e Flux3 rispetto a Fmax

// Variabili temporali per l'invio dei valori al bot di Telegram
char          temp_Fmax[5];              // Variabile per l'invio a Telegram di Fmax
char          temp_Flux1[5];             // Variabile per l'invio a Telegram di Flux1
char          temp_Flux2[5];             // Variabile per l'invio a Telegram di Flux2
char          temp_Flux3[5];             // Variabile per l'invio a Telegram di Flux3
char          temp_LossF[5];             // Variabile per l'invio a Telegram di Loss_F

/*****************************
 * Gestione del Bot Telegram *
 *****************************/

// Funzione per inviare l'avviso qualora si verificasse una perdita
void invia_avviso()
{
  // Invio un messaggio di avviso qualora il sistema percepisca una perdita
  bot.sendMessage("", "C'e' una perdita!", "");  // Inserisci al posto delle prime virgolette l'id della chat in cui desideri che sia inviato il messaggio
  // Qualora volessi aggiungere altre chat basta copiare e incollare la riga precedente e semplicemente cambiare l'id della chat
}

// Funzione che analizza i messaggi inviati al Bot e risponde di conseguenza
void Bot_ParseMessages()
{
  for (int i = 1; i < bot.message[0][0].toInt() + 1; i++)
  {
    String msg;                // Il messaggio inviato al Bot
    String id;                 // L'id dell'utente che invia il messaggio
    msg = bot.message[i][5];
    id = bot.message[i][1];
    msg.toUpperCase();         // Converte tutti i caratteri in maiuscolo

    /***************************************************************************************************
     * Condizione per gestire i permessi degli utenti. Per gestire più utenti, dichiarare le variabili *
     * precedentemente e aggiungerli semplicemente con degli or. Per esempio:                          *
     * if (0 == id.compareTo(utente1) || 0 == id.compareTo(utente2) || 0 == id.compareTo(utente1))     *
     * e così via per tutti gli utenti che si vogliono aggiungere                                      *
     ***************************************************************************************************/
    if (0 == id.compareTo(utente1))
    {
      // Scrivendo una delle stringhe sottoindicate (come fmax) sul bot Telegram verranno stampate sul terminale informazioni
      // utili quali id utente e id chat che potranno essere utilizzate per la gestione dei permessi degli utenti e della chat
      // a cui verranno mandati i messaggi.
      // Invio il valore relativo al flusso massimo Fmax
      if (0 == msg.compareTo("FMAX"))
      {
        bot.sendMessage(bot.message[i][4], dtostrf(Fmax, 1, 2, &temp_Fmax[5]), "");
        Serial.println(bot.message[i][4]);
      }
      // Invio il valore relativo al flussometro Flux1
      else if (0 == msg.compareTo("FLUX1"))
      {
        bot.sendMessage(bot.message[i][4], dtostrf(Flux1, 1, 2, &temp_Flux1[5]), "");
        Serial.println(bot.message[i][1]);
      }
      // Invio il valore relativo al flussometro Flux2
      else if (0 == msg.compareTo("FLUX2"))
      {
        bot.sendMessage(bot.message[i][4], dtostrf(Flux2, 1, 2, &temp_Flux2[5]), "");
        Serial.println(bot.message[i][1]);
      }
      // Invio il valore relativo al flussometro Flux3
      else if (0 == msg.compareTo("FLUX3"))
      {
        bot.sendMessage(bot.message[i][4], dtostrf(Flux3, 1, 2, &temp_Flux3[5]), "");
        Serial.println(bot.message[i][1]);
      }
      // Invio il valore relativo alla perdita Loss_F
      else if (0 == msg.compareTo("LOSSF"))
      {
        bot.sendMessage(bot.message[i][4], dtostrf(Loss_F, 1, 2, &temp_LossF[5]), "");
        Serial.println(bot.message[i][1]);
      }
    }
  }
  bot.message[0][0] = "";   // Tutti i messaggi sono stati letti - Ripristina i nuovi messaggi
}

/*********
 * SETUP *
 *********/
void setup()
{
  Serial.begin (9600);                                                      // Velocità seriale
  pinMode (flussometro1, INPUT_PULLUP);                                     // Imposta il pin 2 in ingresso
  attachInterrupt (digitalPinToInterrupt(flussometro1), impulso1, RISING);  // Configura interrupt 0 pin 2
  pinMode (flussometro2, INPUT_PULLUP);                                     // Imposta il pin 3 in ingresso
  attachInterrupt (digitalPinToInterrupt(flussometro2), impulso2, RISING);  // Configura interrupt 0 pin 2
  pinMode (flussometro3, INPUT_PULLUP);                                     // Imposta il pin 4 in ingresso
  attachInterrupt (digitalPinToInterrupt(flussometro3), impulso3, RISING);  // Configura interrupt 0 pin 2
  pinMode (flussometro4, INPUT_PULLUP);                                     // Imposta il pin 5 in ingresso
  attachInterrupt (digitalPinToInterrupt(flussometro4), impulso4, RISING);  // Configura interrupt 0 pin 2
  
  Serial.println("Sto provando a connettermi");                             // Stampa sul terminale
  delay(500);                                                               // Delay prima della connessione
  connectWifi();                                                            // Avvio la funzione di connessione al Wi-Fi

  bot.begin();      // Inizializzo le funzionalità dl Bot Telegram
  ThingSpeak.begin(client);
}

/***********************************************
 * Gestione dei contatori per ogni flussometro *
 ***********************************************/
void impulso1() {
  count1++;          // Incrementa count1 di 1 per la gestione di Fmax
}
void impulso2() {
  count2++;          // Incrementa count2 di 1 per la gestione di Flux1
}
void impulso3() {
  count3++;          // Incrementa count3 di 1 per la gestione di Flux2
}
void impulso4() {
  count4++;          // Incrementa count4 di 1 per la gestione di Flux3
}

void loop()
{
  interrupts();                     // Abilita gli interrupt
  delay (100);                      // Pausa di 0,1 secondi
  noInterrupts();                   // Disabilita gli interrupt
  countThing++;                     // Incrementa il contatore tempo per inviare i dati a ThingSpeak
  
  // Conteggio dei litri al flussometro di ingresso
  if (count1 > 0)
  {
    Fmax = (count1 * 2.25);      // 2.25mL per ogni impulso
    Fmax = Fmax * 60;            // Trasforma i secondi in minuti
    Fmax = Fmax / 1000;          // Trasforma i mL in litri
    
    count1 = 0;
    
    //Serial.print ("Litri Max (l/m): ");
    //Serial.println (Fmax);       // Scrive a schermo la variabile flusso
  }

  // Conteggio dei litri al flussometro 1
  if (count2 > 0)
  {
    Flux1 = (count2 * 2.25);     // 2.25mL per ogni impulso
    Flux1 = Flux1 * 60;          // Trasforma i secondi in minuti
    Flux1 = Flux1 / 1000;        // Trasforma i mL in litri
    
    count2 = 0;
    
    //Serial.print ("Flussometro 1 (l/m): ");
    //Serial.println (Flux1);      // Scrive a schermo la variabile flusso
  }
  
  // Conteggio dei litri al flussometro 2
  if (count3 > 0)
  {
    Flux2 = (count3 * 2.25);     // 2.25mL per ogni impulso
    Flux2 = Flux2 * 60;          // Trasforma i secondi in minuti
    Flux2 = Flux2 / 1000;        // Trasforma i mL in litri
  
    count3 = 0;
  
    //Serial.print ("Flussometro 2 (l/m): ");
    //Serial.println (Flux2);     // Scrive a schermo la variabile flusso
  }
  
  // Conteggio dei litri al flussometro 3
  if (count4 > 0)
  {
    Flux3 = (count4 * 2.25);     // 2.25mL per ogni impulso
    Flux3 = Flux3 * 60;          // Trasforma i secondi in minuti
    Flux3 = Flux3 / 1000;        // Trasforma i mL in litri
    
    count4 = 0;
  
    // Serial.print ("Flussometro 3 (l/m): ");
    // Serial.println (Flux3);      // Scrive a schermo la variabile flusso

    // Controllo la perdita tra i flussometri 3 e 4
    Loss = Flux2 - Flux3;         // Calcola la perdita tra Flux2 e Flux3
    Loss_F = Loss / Fmax * 100;   // Calcolo la percentuale di perdita rispetto a Fmax
    // Serial.print ("Perdita: ");
    // Serial.println (Loss);        // Scrive a schermo la variabile flusso
    // Se la perdita tra i flussometri 3 e 4 è maggiore di quella consentita, segnalo la perdita
    if (Loss_F > Loss_Consentita)
    {
      countPerdita++;
      if (countPerdita == 6)
        invia_avviso();    // Indica che c'è una perdita (> al 10%)
    }
    else
      countPerdita = 0;    // Indica che non c'è perdita (< al 10%)
  }

  // Richiamo la funzione per gestire il Bot di Telegram
  if (millis() > Bot_lasttime + Bot_mtbs) {
    bot.getUpdates(bot.message[0][1]);   // launch API GetUpdates up to xxx message
    Bot_ParseMessages();                 // parse messages
    Bot_lasttime = millis();
  }

  // Invio i dati a ThingSpeak dopo un tot di tempo
  if (countThing == 3)
  {
    // Setto i campi da inviare al portale ThingSpeak
    ThingSpeak.setField(1, Fmax);
    ThingSpeak.setField(2, Flux1);
    ThingSpeak.setField(3, Flux2);
    ThingSpeak.setField(4, Flux3);
    ThingSpeak.setField(5, Loss_F);

    // Invio i dati al portale ThingSpeak
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    // Una volta inviati i dati azzero il contatore/tempo
    countThing = 0;
  }
}

/***********************************
 * Funzione di connessione al WiFi *
 ***********************************/
void connectWifi()
{
  Serial.print("Connessione a "+*ssid); // Stampo sul terminale che il modulo sta provando a connettersi all'ssid specificato nella variabile ssid
  WiFi.begin(ssid, password);           // Inizializzo la conbnessione al Wi-Fi con le variabili precedentemente inizializzate
  while (WiFi.status() != WL_CONNECTED) // Fintanto che il modulo non riesce a connettersi rimani nel ciclo
  {
    delay(500);
    Serial.print(".");                  // Scrivo sul terminale un puntino ogni mezzo secondo fino a quando non mi connetto al Wi-Fi. Oltretutto il NodeMCU continuerà a lampeggiare fino a quando non viene stabilita la connessione
    connessione = 0;                    // Se non riesco a connettermi assegno 0 alla variabile connessione che starà ad indicare che non c'è appunto connessione
  }
  
  Serial.println("");
  Serial.println("Connesso");           // Stampo sul terminale la conferma che è stata stabilita la connessione
  connessione = 1;                      // Se riesco a connettermi assegno 1 alla variabile connessione che starà ad indicare che è stata stabilita la connessione
  Serial.println("");
}
