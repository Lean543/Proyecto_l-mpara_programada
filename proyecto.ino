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
  
  // define pins for buttons
  // INPUT_PULLUP means the button is HIGH when not pressed, and LOW when pressed
  // since it´s connected between some pin and GND
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP); // up button
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP); // select button
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP); // down button
  pinMode(DEMO_PIN, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(lampara, OUTPUT);
 
}
  
void configuracionOled(void) {
  u8g.setFont(u8g_font_ncenB08);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();    
}

void loop() {

  if (digitalRead(DEMO_PIN) == LOW) {  ///si esta en 0
  demo_mode = 1; // enable demo mode  
  }
  else{
  demo_mode = 0; // disable demo mode
  }
    

  if (demo_mode == 1) { // cuando el modo de demostración está activo,
  activar_lampara();
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
 
 
