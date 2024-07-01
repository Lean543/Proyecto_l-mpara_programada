#include <Sodaq_DS3231.h>
#include <Wire.h> 
#include "U8glib.h"
#include <EEPROM.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST); // Fast I2C / TWI

String ano="",mes="", dia="", hora="",minuto="",segundos="",temperatura="";
String dia_inicio="",mes_inicia="",dia_termina="",mes_termina="",dia_inicia_flora="",mes_inicia_flora="";

int tiempo=0;
String fechac="";
String horac="";
String datosc="";
String datosc1="";
String datosc2="";

//Para la convercion a string ///////////////////////////////////////////////

int dia_inicio1 =10 ; //EEPROM.read(1);      
int mes_inicia1=6;

int dia_termina1 = 5;  //EEPROM.read(0) ;       
int mes_termina1= mes_inicia1+2;

int dia_inicia_flora1= dia_inicio1;
int dia_termina_flora1= dia_inicio1;

int mes_inicia_flora1= mes_inicia1+2;
int mes_termina_flora1=mes_inicia1+4;


int segundo1;
int minuto1;
int hora1;
int dia1;
int mes1;
///////////////////////
int boton = 6;
int estadoBoton;

int M;
int M2;
int temp;

//////////////////////////////// Horario para gladiolos/////////////////////////

int h1_c3= 16;  //hora de encendido
int h1a_c3= 10; //hora de apagado

int mes_c2 = mes_inicia_flora1; //mes
int mest_c2= mes_termina_flora1; //mes

int dia_c2=dia_inicia_flora1; //dia
int diat_c2=dia_termina_flora1;

int m1_c3=0;   
int s1_c3=0; 

int dia_c3=dia_inicio1; //dia
int diat_c3=dia_termina1;

int mes_c3=mes_inicia1; //mes en que inicia
int mest_c3=mes_termina1; // mes en que termina el ciclo automatico
 

//////////////////////////////// Horario flora /////////////////////////
int h1_c2=22;
int h1a_c2=10;

int m1_c2=0;
int s1_c2=0;







//////////////*****************/////////////////////*******************//////




/////////////////////////////////////////////////para el menu los iconos y logos////////////////////////////////
//// 'icon_1', 16x16px
const unsigned char epd_bitmap_icon_1 [] PROGMEM = { //gladiolo
	0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x0e, 0x70, 0x0e, 0x70, 0x0e, 0x70, 0x0e, 0x70, 0x0e, 0x70, 
	0x0e, 0x70, 0x1f, 0xf8, 0x0e, 0x70, 0x0e, 0x70, 0x0e, 0x70, 0x0e, 0x70, 0x0e, 0x70, 0x00, 0x00
};
// 'icon_2', 16x16px
const unsigned char epd_bitmap_icon_2 [] PROGMEM = { //datos
	0x0f, 0xe0, 0x31, 0x18, 0x60, 0x0c, 0x40, 0x04, 0x81, 0x02, 0x81, 0x02, 0x81, 0x02, 0x81, 0x02, 
	0xc1, 0x06, 0x80, 0x82, 0x80, 0x42, 0x80, 0x22, 0x40, 0x04, 0x60, 0x0c, 0x31, 0x18, 0x0f, 0xe0
};
// 'icon_3', 16x16px
const unsigned char epd_bitmap_icon_3 [] PROGMEM = { // tomaco
 0x00, 0x00, 0x00, 0x08, 0x00, 0x94, 0x10, 0x08, 0x10, 0x00, 0x6c, 0x00, 0x10, 0x10, 0x10, 0x10, 
 0x00, 0x00, 0x00, 0xc6, 0x00, 0x00, 0x00, 0x10, 0x04, 0x10, 0x0a, 0x00, 0x04, 0x00, 0x00, 0x00
};
// 'icon_4 fireworks', 16x16px
const unsigned char epd_bitmap_icon_4 [] PROGMEM = { //esta es la imagen de reset cultivo
  0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x3f, 0xe0, 0x38, 0x70, 0x38, 0x70, 0x38, 0x70, 0x38, 0x60, 
	0x3f, 0xc0, 0x3b, 0x00, 0x39, 0x80, 0x38, 0xc0, 0x38, 0x60, 0x38, 0x60, 0x38, 0x70, 0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 1184)

const unsigned char* epd_bitmap_icons[4] = {
  epd_bitmap_icon_1,
	epd_bitmap_icon_2,
	epd_bitmap_icon_3,
  epd_bitmap_icon_4,  
};

// 'scrollbar_background', 8x64px
const unsigned char bitmap_scrollbar_background [] PROGMEM = {
  0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 
  0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 
  0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 
  0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00
};

// 'item_sel_outline', 128x21px
const unsigned char bitmap_item_sel_outline [] PROGMEM = {
  0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
  0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 
  0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0
};



// ------------------ end generated bitmaps from image2cpp ---------------------------------



const int NUM_ITEMS = 4; // numero de items
const int MAX_ITEM_LENGTH = 20; // maximum characters for the item name

char menu_items [NUM_ITEMS] [MAX_ITEM_LENGTH] = {  // arreglo con los nombres
  { "Tomate" }, 
  { "datos" },
  { "Gladiolo" },
  { "Reset cult" } 
  
};



#define BUTTON_UP_PIN 12 // pin for UP button 
#define BUTTON_SELECT_PIN 8 // pin for SELECT button
#define BUTTON_DOWN_PIN 4 // pin for DOWN button

//salidas
#define vegeta 5
#define flora 3
#define DEMO_PIN 2 // pin para modo directo
#define lampara 5

int button_up_clicked = 0; // only perform action when button is clicked, and wait until another press
int button_select_clicked = 0; // same as above
int button_down_clicked = 0; // same as above

int item_selected = 0; // which item in the menu is selected

int item_sel_previous; // previous item - used in the menu screen to draw the item before the selected one
int item_sel_next; // next item - used in the menu screen to draw next item after the selected one

int current_screen = 0;   // 0 = menu, 1 = referencia, 2 = saliendo
int demo_mode = 0; // when demo mode is set to 1, it automatically goes over all the screens, 0 = control menu with buttons
int demo_mode_state = 0; //  que pantalla eh item mostrar al principio
int demo_mode_delay = 0; // retraso del modo de demostración = utilizado para ralentizar el cambio de pantalla




void setup() {

  Wire.begin();                               
  rtc.begin();
  //rtc.setDateTime(fecha) ;
  
  // define pins for buttons
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP); // up button
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP); // select button
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP); // down button
  pinMode(DEMO_PIN, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(lampara, OUTPUT);
 
 dia_inicio=String(dia_inicio1, DEC);
 mes_inicia=String(mes_inicia1, DEC);
 dia_termina=String(dia_termina1, DEC);
 mes_termina=String(mes_termina1, DEC);
 dia_inicia_flora=String(dia_inicia_flora1, DEC);
 mes_inicia_flora=String(mes_termina_flora1, DEC);
 
}
  
void configuracionOled(void) {
  u8g.setFont(u8g_font_ncenB08);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();    
}

void loop() {

 DateTime now = rtc.now();
 //rtc.convertTemperature();
 //temp=rtc.getTemperature();
 tiempo=millis()/1000;
 //temperatura=String(temp, DEC);
 ano=String(now.year(), DEC);
 mes=String(now.month(), DEC);
 dia=String(now.date(), DEC);
 segundos=String(now.second(), DEC);
 minuto=String(now.minute(), DEC);
 hora=String(now.hour(), DEC);

  segundo1=now.second();
  minuto1=now.minute();
  hora1=now.hour();
  dia1=now.date();
  mes1 =now.month();
  
  
  
  if (digitalRead(DEMO_PIN) == LOW) {  ///si esta en 0
  demo_mode = 1; // enable demo mode  
  }
  else{
  demo_mode = 0; // disable demo mode
  }
    

  if (demo_mode == 1) { // cuando el modo de demostración está activo,
  Gladiolo();
  } // end demo mode section


 if (current_screen == 0) { // MENU SCREEN
   // up and down buttons only work for the menu screen
   if ((digitalRead(BUTTON_UP_PIN) == LOW) && (button_up_clicked == 0)) { // up button clicked - jump to previous menu item
     item_selected = item_selected - 1; // select previous item
     button_up_clicked = 1; // set button to clicked to only perform the action once
   if (item_selected < 0) { // if first item was selected, jump to last item
     item_selected = NUM_ITEMS-1;
   }
 }
 else if ((digitalRead(BUTTON_DOWN_PIN) == LOW) && (button_down_clicked == 0)) { // down button clicked - jump to next menu item
   item_selected = item_selected + 1; // select next item
   button_down_clicked = 1; // set button to clicked to only perform the action once
   if (item_selected >= NUM_ITEMS) { // last item was selected, jump to first menu item
     item_selected = 0;
    }
 } 

 if ((digitalRead(BUTTON_UP_PIN) == HIGH) && (button_up_clicked == 1)) { // unclick 
        button_up_clicked = 0;
 }
 if ((digitalRead(BUTTON_DOWN_PIN) == HIGH) && (button_down_clicked == 1)) { // unclick
   button_down_clicked = 0;
  }

 }
 if ((digitalRead(BUTTON_SELECT_PIN) == LOW) && (button_select_clicked == 0)) { // select button clicked, jump between screens
   button_select_clicked = 1; // set button to clicked to only perform the action once
   if (current_screen == 0) {current_screen = 1;} // menu items screen --> screenshots screen
   else if (current_screen == 1) {current_screen = 2;} // screenshots screen --> qr codes screen
   else {current_screen = 0;} // qr codes screen --> menu items screen
 }
 if ((digitalRead(BUTTON_SELECT_PIN) == HIGH) && (button_select_clicked == 1)) { // unclick 
     button_select_clicked = 0;
 }

 // set correct values for the previous and next items
 item_sel_previous = item_selected - 1;
 if (item_sel_previous < 0) {item_sel_previous = NUM_ITEMS - 1;} // previous item would be below first = make it the last
 item_sel_next = item_selected + 1;  
 if (item_sel_next >= NUM_ITEMS) {item_sel_next = 0;} // next item would be after last = make it the first
 u8g.firstPage(); // required for page drawing mode for u8g library
 
 
 
  do {
   //////////////////se encarga de dibujar el menú  ////////////////////////////////////
   if (current_screen == 0) { // MENU SCREEN
     // coloca la barr de seleccion
   u8g.drawBitmapP(0, 22, 128/8, 21, bitmap_item_sel_outline);

   // dibujar elemento anterior como icono + etiqueta
   u8g.setFont(u8g_font_7x14);
   u8g.drawStr(25, 15, menu_items[item_sel_previous]); 
   u8g.drawBitmapP( 4, 2, 16/8, 16, epd_bitmap_icons[item_sel_previous]);          

   //dibujar el elemento seleccionado como icono + etiqueta en negrita
   u8g.setFont(u8g_font_7x14B);    
   u8g.drawStr(25, 15+20+2, menu_items[item_selected]);   
   u8g.drawBitmapP( 4, 24, 16/8, 16, epd_bitmap_icons[item_selected]);     

   // draw next item as icon + label
   u8g.setFont(u8g_font_7x14);     
   u8g.drawStr(25, 15+20+20+2+2, menu_items[item_sel_next]);   
   u8g.drawBitmapP( 4, 46, 16/8, 16, epd_bitmap_icons[item_sel_next]);  

   // dibujar el fondo de la barra de desplazamiento
   u8g.drawBitmapP(128-8, 0, 8/8, 64, bitmap_scrollbar_background);

   //dibuja el identificador de la barra de desplazamiento
   u8g.drawBox(125, 64/NUM_ITEMS * item_selected, 3, 64/NUM_ITEMS); 
   } 
 
 
 

 //////////////////se encarga de la parte de las acciones del menu la segunda parte
   else if (current_screen == 1) { // SCREENSHOTS SCREEN
    switch(item_selected){
  
    case 1:  //datos
    configuracionOled() ;
    fechacor(temperatura,ano,mes,dia,hora,minuto,segundos);
    break;
  
    case 2:  //gladiolo
    Gladiolo() ;
    break;
   
    case 3:// este caso se encarga de fijar los dos parametros iniciales
    if(digitalRead(7)==0) {
    u8g.firstPage(); // required for page drawing mode for u8g library
    configuracionOled();
    do { 
    u8g.drawStr(0,22,"Almacenando los 2 datos:");  // avisar q vamos a almacenar datos
    }while(u8g.nextPage());
    delay (3000);     

    int dia_inicio1 = now.date();
    int mes_inicia1 = now.month();     
  
    EEPROM.write(0, dia_inicio1);           // Escribe datos de la memoria EEPROM
    delay (500);
    EEPROM.write(1, mes_inicia1);  
    delay (500);
  
    u8g.firstPage(); // required for page drawing mode for u8g library
    configuracionOled();
    do { 
    u8g.drawStr(0,22,"Apagar interrupotor 2");  // asegurarse de no grabar muchas veces en la memoria eprom
    }while(u8g.nextPage());
    delay (5000);     
  
    u8g.firstPage(); // comprobar
    configuracionOled();
    do {
    u8g.drawStr(0,22,"datos guardados"); 
    }while(u8g.nextPage());
    delay (2000);
    }
  
    else {
    u8g.firstPage(); // required for page drawing mode for u8g library
    configuracionOled();
    do {
    u8g.drawStr(0,22,"datos guardados"); 
    }while(u8g.nextPage());
    //delay (3000);
    }
    break;
   
    case 0:

    break; 
    }  
   } 

 //////////////////////////////////Para la tercera parte del menu o la parte ue nos avisa que salimos
 
   else if(current_screen == 2){  
   switch(item_selected){
   case 1:
   //configuracionOled() ;
   datitos(dia_inicio, mes_inicia, dia_termina, mes_termina, dia_inicia_flora, mes_inicia_flora);
   break;
   
   case 2:
   configuracionOled() ;
   u8g.drawStr(0,22,"saliendo case2");
   break; 
   
   case 3:// este caso se encarga del modo resetear datos
   configuracionOled() ;
   u8g.drawStr(0,22,"saliendo case3");
  
   break;
       
   case 0:
   u8g.drawStr(0,22,"SaliendoR");
   break; 
   } 
   }
  }
  while(u8g.nextPage());
}

//////////////////////////////////////// apaga la lampara //////////////////////////////
void apagar_lampara(){
 digitalWrite(lampara, LOW);     
 delay(500); 
 u8g.firstPage(); // required for page drawing mode for u8g library
 do {
 //configuracionOled();
 u8g.drawStr(2,0,"Lampara apagada");
 u8g.drawStr(2,24,"!!NO MOLESTAR!!");
 }while(u8g.nextPage());
 delay(4000);

}

//////////////////esta la utilizo para encender el tiempo de 18 horas (automaticas o vegeta)////////////////////
void activar_lampara(){    
  digitalWrite(lampara, HIGH); 
  delay(500);
   
  configuracionOled();
  u8g.firstPage(); // required for page drawing mode for u8g library
  do {
  u8g.drawStr(2,0,"Lampara");
  u8g.setScale2x2();
  u8g.drawStr(2,10,"prendida");
  u8g.undoScale();
  }while(u8g.nextPage());
  delay(1500);
  
}
//////////////////////////////////////////////////////////////////////////////
void datitos(String dia_inicio, String mes_inicio, String dia_termina,String mes_termina,String dia_inicia_flora,String mes_inicia_flora ){

 //convertidor();
 
 datosc = "Cultivo iniciado:  " + dia_inicio+"/"+ mes_inicio;
 datosc1 = "Cultivo finaliza:  "+ dia_termina+"/"+ mes_termina;
 datosc2 = "Comienza flora:  "+ dia_inicia_flora+"/"+ mes_inicia_flora;
  
 
  const char* nuevosdatos=(const char*)datosc.c_str(); 
  const char* nuevosdatos1=(const char*)datosc1.c_str(); 
  const char* nuevosdatos2=(const char*)datosc2.c_str();
  
  u8g.drawStr(0,0,nuevosdatos);
  u8g.drawStr(0,40,nuevosdatos1);
  u8g.drawStr(0,20,nuevosdatos2);
  
}
//////////////////////////////////////////////////////////////////////////////////
void fechacor(String temperatura,String ano,String mes,String dia,String hora,String minuto,String segundos ){
 fechac = "T: "+temperatura+"C      F: "+dia+"/"+mes+"/"+ano;
 horac ="hora:  " +hora+":"+minuto+":"+segundos;
 const char* nuevafecha=(const char*)fechac.c_str();
 const char* nuevahora=(const char*)horac.c_str();
 
 
 u8g.drawStr(2,24,nuevafecha);
 u8g.drawStr(2,2,"fecha de hoy");// 
 u8g.drawStr(2,44,nuevahora);
}
///////////////////////////////////////////////////////////////////////////////
void Gladiolo(){ 

 DateTime now = rtc.now();
 u8g.firstPage(); // required for page drawing mode for u8g library
 configuracionOled();
 do { 
  //configuracionOled();
  u8g.drawStr(2,0,"Cutivando");
  u8g.setScale2x2();
  u8g.drawStr(2,10,"Gladiolos");
  u8g.undoScale();
  
  }while(u8g.nextPage());
  delay(4000);
  //convertidor();
  
  if ((hora1<h1a_c3) && (mes1==mes_c3) && (dia1>=dia_c3) ){   //h1a_c3 es hora de apagado del modo automaticas
     
   u8g.firstPage(); // required for page drawing mode for u8g library
   do {
   //configuracionOled();
   u8g.drawStr(2,0,"Horario diurno");
   u8g.drawStr(2,24,"de encendido");
   u8g.drawStr(2,44,"mes 1");
   }while(u8g.nextPage());
   delay(4000);
   activar_lampara();
    
   }
    
   if ((mes1==mes_c3)&& (dia1>=dia_c3) &&(hora1>=h1_c3)){
     
    u8g.firstPage(); // required for page drawing mode for u8g library
    do { 
    //configuracionOled();
    u8g.drawStr(2,0,"Horario nocturno");
    u8g.drawStr(2,24,"de encendido");
    u8g.drawStr(2,44,"mes 1");
    }while(u8g.nextPage());
    delay(4000);
    activar_lampara();
  
   }
 
  
   //estos tres segundos son para el segundo mes
   M = mes_inicia1+1;
   
   
   if ((mes1==M) && (hora1<h1a_c3) ){   //h1a_c3 es hora de apagado del modo automaticas
   //configuracionOled();
    u8g.firstPage(); // required for page drawing mode for u8g library
    do {
    u8g.drawStr(2,0,"Horario diurno");
    u8g.drawStr(2,24,"de encendido");
    u8g.drawStr(2,44,"mes 2");
    }while(u8g.nextPage());
    delay(4000);
    activar_lampara();
  
    
  }
   if ((mes1==M) && (hora1>=h1_c3)){
    //configuracionOled();
    u8g.firstPage(); // required for page drawing mode for u8g library
    do {
    u8g.drawStr(2,0,"Horario nocturno");
    u8g.drawStr(2,24,"de encendido");
    u8g.drawStr(2,44,"mes 2");
    }while(u8g.nextPage());
    delay(4000);
    activar_lampara();
    }
   //estos tres ultimos son para el ultimo mes de vegeta

    if ((mes1==mest_c3) && (dia1<=diat_c3) && (hora1<h1a_c3) ){
    
    u8g.firstPage(); // required for page drawing mode for u8g library
    do {
    //configuracionOled();
    u8g.drawStr(2,0,"Horario diurno");
    u8g.drawStr(2,24,"de encendido");
    u8g.drawStr(2,44,"mes 3");
    }while(u8g.nextPage());
    delay(4000);
    activar_lampara();
   }
   
   
   if ((mes1==mest_c3) && (dia1<=diat_c3)&& (hora1>=h1_c3)){
    
    u8g.firstPage(); // required for page drawing mode for u8g library
    do {
    //configuracionOled();
    u8g.drawStr(2,0,"Horario nocturno");
    u8g.drawStr(2,24,"de encendido");
    u8g.drawStr(2,44,"mes 3");
    }while(u8g.nextPage());
    delay(4000);
    activar_lampara();
    
   
    } 
  
   if ((hora1>=h1a_c3) && (hora1<h1_c3) ){ 
    apagar_lampara();
    u8g.firstPage();
    do {
    u8g.drawStr(2,0,"se apago");
    u8g.drawStr(2,24,"madafoca");
    }while(u8g.nextPage());
    delay(4000); 
   } 

}
 



void fn_ini_ciclo(){
  DateTime now = rtc.now(); 
  delay(200); 
  configuracionOled();
   u8g.firstPage(); 
  do {
  u8g.drawStr(2,0,"Lampara modo");
  u8g.setScale2x2();
  u8g.drawStr(2,10,"regulares");
  u8g.undoScale();
  }while(u8g.nextPage());
  delay(3000);
  
   //estos tres primero son para el primer mes de vegeta
 while ((hora1<h1a_c3) && (mes1==mes_c3) && (dia1>=dia_c3) ){   //h1a_c3 es hora de apagado del modo automaticas
  configuracionOled();
  u8g.firstPage(); 
  do {
  u8g.drawStr(2,0,"Horario diurno");
  u8g.drawStr(2,20,"de encendido");
 u8g.drawStr(2,40,"mes 1");
  }while(u8g.nextPage());
  delay(4000);
  activar_lampara();
  }
   
   while ((mes1==mes_c3)&& (dia1>=dia_c3) &&(hora1>=h1_c3)){
     //configuracionOled();
     u8g.firstPage(); // required for page drawing mode for u8g library
     do { 
     u8g.drawStr(2,0,"Horario nocturno");
     u8g.drawStr(2,20,"de encendido");
     u8g.drawStr(2,40,"mes 1");
      }while(u8g.nextPage());
     delay(4000);
     activar_lampara();
  
   }
   //apagar_lampara();
  
  /// do {
  // u8g.drawStr(2,0,"Plantas durmiendo");
  // u8g.drawStr(2,24,"sleep");
 //}while(u8g.nextPage());
  // delay(4000);
  
   //estos tres segundos son para el segundo mes
  
   M = mes_inicia1+1;
   
   
   while ((mes1==M) && (hora1<h1a_c3) ){   //h1a_c3 es hora de apagado del modo automaticas
       u8g.firstPage(); 
      do {
   u8g.drawStr(2,0,"Horario diurno");
   u8g.drawStr(2,24,"de encendido");
   u8g.drawStr(2,40,"mes 2");
   }while(u8g.nextPage());
   delay(4000);
   activar_lampara();
   
   }
   
   while ((mes1==M) && (hora1>=h1_c3)){
      u8g.firstPage(); 
     do {
   u8g.drawStr(2,0,"Horario nocturno");
   u8g.drawStr(2,24,"de encendido");
   u8g.drawStr(2,40,"mes 2");
   }while(u8g.nextPage());
   delay(4000);
   activar_lampara();
  
  
   }
     
   //estos tres ultimos son para el ultimo mes de vegeta
   while ((mes1==mest_c3) && (dia1<=diat_c3) && (hora1<h1a_c3) ){
      u8g.firstPage(); 
     do {
   u8g.drawStr(2,0,"Horario diurno");
   u8g.drawStr(2,24,"de encendido");
   }while(u8g.nextPage());
    delay(4000);
    activar_lampara();
    
   }
   
   while ((mes1==mest_c3) && (dia1<=diat_c3)&& (hora1>=h1_c3)){
   u8g.firstPage(); 
   do {
   u8g.drawStr(2,0,"Horario nocturno");
   u8g.drawStr(2,24,"de encendido");
   }while(u8g.nextPage());
   activar_lampara();
  
   }
   apagar_lampara();
   
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////estos dos primero son para el primer mes de floracion///////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   while ((mes1==mest_c3) && (dia1>=diat_c3) && (hora1<=h1a_c2)){
     u8g.firstPage(); 
   do {
   u8g.drawStr(2,0,"Horario diurno");
   u8g.drawStr(2,24,"de encendido");
   }while(u8g.nextPage());
   delay(4000);
   activar_lampara();
   
   }
   
   while ((mes1==mest_c3) && (dia1>=diat_c3) && (hora1>h1_c2)){
    u8g.firstPage(); 
   do {
   u8g.drawStr(2,0,"Horario nocturno");
   u8g.drawStr(2,24,"de encendido");
   }while(u8g.nextPage());
   delay(4000);
   activar_lampara();
   
  

  
  }  

   M2=mes_termina1+1;
   while ((mes1==M2) && (hora1<=h1a_c2)){
   u8g.firstPage(); 
   do {
   u8g.drawStr(2,0,"Horario diurno");
   u8g.drawStr(2,24,"de encendido");
   }while(u8g.nextPage());
    delay(4000);
    activar_lampara();
  
    
  }
   while ((mes1==M2) && (hora1>h1_c2)){
   u8g.firstPage(); 
    do {
   u8g.drawStr(2,0,"Horario nocturno");
   u8g.drawStr(2,24,"de encendido");
   }while(u8g.nextPage());
   delay(4000);
    activar_lampara();
    
  
    
  } 

   while ((mes1==mest_c2) && (dia1>=diat_c2) && (hora1<=h1a_c2)){
      u8g.firstPage(); 
     do {
   u8g.drawStr(2,0,"Horario diurno");
   u8g.drawStr(2,24,"de encendido");
   }while(u8g.nextPage());
    delay(4000);
    activar_lampara();

    
  }
   while ((mes1==mest_c2) && (dia1<=diat_c2) && (hora1>h1_c2)){
      u8g.firstPage(); 
     do {
   u8g.drawStr(2,0,"Horario nocturno");
   u8g.drawStr(2,24,"de encendido");
   }while(u8g.nextPage());
    delay(4000);
    activar_lampara();
    
   
    
  } 
    
}
