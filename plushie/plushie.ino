
#include <Wire.h>

const int lightPin = 2;      // digital input
const int buzzerPin = 5;
const int tempPin = A0;
const int songLength = 18;

char notes[] = "cdfda ag cdfdg gf ";
int beats[] = {1, 1, 1, 1, 1, 1, 4, 4, 2, 1, 1, 1, 1, 1, 1, 4, 4, 2};
int tempo = 113;


void setup() {
  // configure the serial connection:
  Serial.begin(9600);
  // configure the digital input:
  pinMode(lightPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

}

// This function takes a note character (a-g), and returns the
// corresponding frequency in Hz for the tone() function.
// https://www.instructables.com/Digital-Music-Using-a-Piezo-Buzzer/

int freq(char note) {
  int i;
  const int numNotes = 8;  // number of notes we're storing
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};

  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)         // Is this the one?
    {
      return (frequencies[i]);    // Yes! Return the frequency
    }
  }
  return (0);
}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    int inByte = Serial.read();
    //Serial.write(inByte); //send it back

    //if arduino receives L, turn light on
    if (inByte == 'L') {
      analogWrite(lightPin, 255);
    }
    //if arduino receives F, turn light off
    else if (inByte == 'F') {
      analogWrite(lightPin, 0);
    }
    //if arduino receives H, play alarm tone
    else if (inByte == 'H') {
      int i, duration;
      for (i = 0; i < songLength; i++) // step through the song arrays
      {
        duration = beats[i] * tempo;  // length of note/rest in ms
        if (notes[i] == ' ')          // is this a rest?
        {
          delay(duration);            // then pause for a moment
        }
        else                          // otherwise, play the note
        {
          tone(buzzerPin, freq(notes[i]), duration);
          delay(duration);            // wait for tone to finish
        }
        delay(tempo / 10);            // brief pause between notes
      }
      // We only want to play the song once, so we'll pause forever:
      while (true) {}
      
    }
  }
  //if arduino receives anything else, play no sound, do nothing
  else {
    noTone(5);
  } 


  int sensorVal = analogRead(tempPin);
  float volt = (sensorVal / 1024.0) * 5.0;
  float temp = (volt - 0.5) * 100;
  Serial.println(temp);
  if (temp >= 20) {
    Serial.println("pet");
  }
}
