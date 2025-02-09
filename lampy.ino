// ====================================
///// WELCOME TO LAMPY!
// ====================================
// Think of this program as a digital paintbrush that can create (but is not limited to):
// - Flickering fires
// - Infinite rainbows
// - Twinkling fireflies
// - Ocean waves
// - Shooting stars
// - Matrix-style rain
// - Field of Asters
// - Orchard of Mandarin Trees

// First, we need to include some special tools (like getting art supplies ready):
#include <Adafruit_NeoPixel.h>  // This helps us control our LED light strip
#include <Preferences.h>        // This helps Lampy remember its settings, like a diary!

// Let's list all the cool things Lampy can do (like a table of contents):
void switchMode();              // Changes between different light patterns
void rainbow(int cycleSpeed);   // Makes a rainbow pattern
void fire(int Cooling, int Sparking, int SpeedDelay);  // Makes fire effects
void firefly(int sparkSpeed, int pulseSpeed, int newFlyChance, int fadeAmount);  // Makes firefly lights
void matrix(int dropSpeed, int fadeSpeed, int newDropChance);  // Makes Matrix-style rain
void water(int cycleSpeed);     // Makes ocean wave effects
void spirula(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay);  // Makes shooting stars
void kelp(int cycleSpeed); // Makes radioactive kelp waves
void aster(int cycleSpeed); // Like a field of asters
void mandarin(int cycleSpeed); // Like an orchard of mandarin trees

// ===== SETTING UP OUR LIGHT STRIP =====
#define LED_PIN    D0          // Which pin our lights are connected to 
#define LED_COUNT 72           // How many lights we have in our strip 

// Initialize our special tools
Preferences preferences;        // Like Lampy's diary to remember settings
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);  // Our LED strip controller

// ===== GLOBAL VARIABLES (Our Toolbox) =====
// Think of these like settings we can change anytime:
unsigned long previousMillis = 0;  // This is like a stopwatch to help control timing
const long interval = 10;          // How often we update our patterns (in milliseconds)
int state = 0;                    // Which light pattern we're showing (like choosing a TV channel)
// EDITED: Make the brightness be much closer to a night lamp
int brightness = 35;             // How bright our lights are (0 = off, 255 = super bright!; caution: super bright colors will seem washed out compared to the less brighter ones)
int currentBrightness = 50;      // Keeps track of current brightness while fading

// ===== GETTING STARTED =====
void setup() {
  // This is like getting dressed in the morning - we do it once when we start
  Serial.begin(115200);         // Starts communication with our computer

  preferences.begin("lampy", false);  // Opens Lampy's diary to remember settings
  state = preferences.getInt("state", 0);  // Checks what pattern we used last time
  switchMode();                 // Gets ready to show our light pattern

  strip.begin();                // Wakes up our LED strip
  strip.show();                 // Makes sure all lights start turned off

  Serial.println("Ready");      // Tells us Lampy is ready to party!
}

// ===== MAIN PROGRAM LOOP =====
void loop() {
  // This is Lampy's brain! It runs over and over again to create patterns.
  // Each 'state' is a different light pattern:
  // State 0 = Cozy Fire
  // State 1 = Purple Shooting Stars
  // State 2 = Rainbow Magic
  // State 3 = Gentle Fireflies
  // State 4 = Aster
  // State 5 = Ocean Waves
  // State 6 = Radioactive Kelp
  // State 7 = Mandarin Orange

  // We only update the lights every 'interval' milliseconds
  // This is like taking a tiny break between drawing each frame

  if (state == 2) {  // RAINBOW MODE
    if ((unsigned long)(millis() - previousMillis) >= interval) {
      // If we're not at full brightness yet, slowly fade up
      // EDITED: Drop the brightness ramp-up logic and just pin it to the global variable
      // if (currentBrightness < brightness) {
      //   for (int i = currentBrightness; i <= brightness; i++) {
      //     strip.setBrightness(i);
      //     rainbow(1);
      //     strip.show();
      //     currentBrightness = i;
      //   }
      // } else {
      //   rainbow(1);
      //   strip.show();
      // }
      strip.setBrightness(brightness);
      rainbow(1);
      strip.show();
      previousMillis = millis();
    }
  }
  else if (state == 1) {  // SHOOTING STARS MODE
    if ((unsigned long)(millis() - previousMillis) >= interval) {
      spirula(0xff, 0, 0xff, 30, 48, true, 60);
      previousMillis = millis();
    }
  }
  else if (state == 0) {  // FIRE MODE
    if ((unsigned long)(millis() - previousMillis) >= interval) {
      fire(5, 50, 75); // These numbers control how the fire looks
      previousMillis = millis();
    }
  }
  else if (state == 3) {  // FIREFLY MODE
    if ((unsigned long)(millis() - previousMillis) >= interval) {
      firefly(450, 10, 50, 3);  // Controls: spark rate, pulse speed, new firefly chance, fade speed
      previousMillis = millis();
    }
  }
  else if (state == 4) {  // ASTER MODE
    if ((unsigned long)(millis() - previousMillis) >= interval) {
      aster(1);  // Controls how fast the waves move
      strip.show();
      previousMillis = millis();
    }
  }
  else if (state == 5) {  // WATER MODE
    if ((unsigned long)(millis() - previousMillis) >= interval) {
      water(1);  // Controls how fast the waves move
      strip.show();
      previousMillis = millis();
    }
  }
  else if (state == 6) {  // KELP MODE
    if ((unsigned long)(millis() - previousMillis) >= interval) {
      kelp(1);  // Controls how fast the waves move
      strip.show();
      previousMillis = millis();
    }
  } else if (state == 7) {  // MANDARIN TREE MODE
    if ((unsigned long)(millis() - previousMillis) >= interval) {
      mandarin(1);  // Controls how fast the waves move
      strip.show();
      previousMillis = millis();
    }
  }
}

// ===== GAMMA CORRECTION TABLE =====
const uint8_t PROGMEM gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

// ===== PIXEL SETTING WITH GAMMA CORRECTION =====
void setGammaPixel(int Pixel, byte red, byte green, byte blue) {
  strip.setPixelColor(Pixel,
    pgm_read_byte(&gamma8[red]),
    pgm_read_byte(&gamma8[green]),
    pgm_read_byte(&gamma8[blue]));
}

// ===== PATTERN SWITCHING =====
void switchMode() {
  // This is like changing the TV channel to a different pattern
  // EDITED: Hardcode the rainbow pattern
  // state = (state + 1) % 8;  // Cycle through modes 0-5 (like a circle)
  state = 2;
  preferences.putInt("state", state);  // Write it in Lampy's diary
  Serial.printf("Switched to mode %d\n", state);  // Tell the computer what mode we're in
}

// ===== COLOR WHEEL HELPER =====
// This is like mixing paint colors to make new ones!
uint32_t Wheel(byte WheelPos, uint32_t color1, uint32_t color2, uint32_t color3) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) { // First third of the wheel
    return interpolateColor(color3, color1, (WheelPos * 3));
  }
  if (WheelPos < 170) { // Second third of the wheel
    WheelPos -= 85;
    return interpolateColor(color1, color2, (WheelPos * 3));
  }
  WheelPos -= 170;  // Last third of the wheel
  return interpolateColor(color2, color3, (WheelPos * 3));
}

// ===== COLOR MIXING HELPER =====
// This is like slowly mixing two colors of paint together
uint32_t interpolateColor(uint32_t color1, uint32_t color2, byte progress) {
  // Separate each color into its red, green, and blue parts
  uint8_t r1 = (color1 >> 16) & 0xFF;  // Red from first color
  uint8_t g1 = (color1 >> 8) & 0xFF;   // Green from first color
  uint8_t b1 = color1 & 0xFF;          // Blue from first color

  uint8_t r2 = (color2 >> 16) & 0xFF;  // Red from second color
  uint8_t g2 = (color2 >> 8) & 0xFF;   // Green from second color
  uint8_t b2 = color2 & 0xFF;          // Blue from second color

  // Mix the colors together based on how far along we are
  uint8_t r = map(progress, 0, 255, r1, r2);
  uint8_t g = map(progress, 0, 255, g1, g2);
  uint8_t b = map(progress, 0, 255, b1, b2);

  return strip.Color(r, g, b);  // Create the new mixed color
}

// ===== RAINBOW PATTERN =====
void rainbow(int cycleSpeed) {
  static int cycles = 0;  // Keeps track of where we are in the rainbow

  // These are our main colors that make up the rainbow:
  uint32_t color1 = strip.Color(255, 0, 0);    // Bright Red
  uint32_t color2 = strip.Color(0, 255, 0);    // Bright Green
  uint32_t color3 = strip.Color(0, 0, 255);    // Bright Blue

  // Color each LED in the strip
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + cycles) & 255,
                                 color1, color2, color3));
  }
  strip.show();

  // Move the rainbow pattern a little bit for next time
  cycles = (cycles + max(1, cycleSpeed / 3)) % (256 * 5);
}

// ===== WATER PATTERN =====
void water(int cycleSpeed) {
  static int cycles = 0;  // Keeps track of where we are in the wave pattern

  // Ocean colors! These make it look like moving water:
  uint32_t color1 = strip.Color(0, 0, 255);     // Deep blue (like the deep ocean)
  uint32_t color2 = strip.Color(0, 255, 140); // Cyan (like a fresh water beach)
  uint32_t color3 = strip.Color(0, 140, 255); // Sku Blue (like a deep lake)

  // Color each LED in the strip
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + cycles) & 255,
                                 color1, color2, color3));
  }
  strip.show();

  // Move the water pattern a little bit for next time
  cycles = (cycles + max(1, cycleSpeed / 3)) % (256 * 5);
}



// ===== KELP PATTERN =====
void kelp(int cycleSpeed) {
  static int cycles = 0;  // Keeps track of where we are in the wave pattern

  // Kelp colors! These make it look waves of radioactive kelp swaying in the breeze:
  uint32_t color1 = strip.Color(70, 255, 0);   // Lime (like a fresh lemon)
  uint32_t color2 = strip.Color(0, 255, 0); // Bright Green (like the forest during daylight)
  uint32_t color3 = strip.Color(0, 255, 60); // Mint Green (like a fresh leaf)

  // Color each LED in the strip
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + cycles) & 255,
                                 color1, color2, color3));
  }
  strip.show();

  // Move the water pattern a little bit for next time
  cycles = (cycles + max(1, cycleSpeed / 3)) % (256 * 5);
}


// ===== MANDARIN TREE PATTERN =====
void mandarin(int cycleSpeed) {
  static int cycles = 0;  // Keeps track of where we are in the wave pattern

  // Aster colors! Imagine an orchard of mandarins:
  uint32_t color1 = strip.Color(209, 53, 40);   // Deep Orange
  uint32_t color2 = strip.Color(6, 115, 51);   // Foliage  
  uint32_t color3 = strip.Color(3, 78, 35);   // Arbor Green

  // Color each LED in the strip
  for (int i = 0; i < strip.numPixels(); i++) {
    uint32_t color = Wheel(((i * 256 / strip.numPixels()) + cycles) & 255,
                           color1, color2, color3);

    // Extract RGB values from the color
    byte r = (color >> 16) & 0xFF;
    byte g = (color >> 8) & 0xFF;
    byte b = color & 0xFF;

    // Apply gamma correction and set the pixel
    setGammaPixel(i, r, g, b);
  }
  strip.show();

  // Move the pattern a little bit for the next frame
  cycles = (cycles + max(1, cycleSpeed / 3)) % (256 * 5);
}

// ===== ASTER PATTERN =====
void aster(int cycleSpeed) {
  static int cycles = 0;  // Keeps track of where we are in the wave pattern

  // Aster colors! Imagine a field of asters:
  uint32_t color1 = strip.Color(236, 182, 2);   // Deep Yellow (center of an aster)
  uint32_t color2 = strip.Color(85, 24, 93);   // Purple (petals of asters)
  uint32_t color3 = strip.Color(41, 8, 73);    // Violet (hues of asters)

  // Color each LED in the strip
  for (int i = 0; i < strip.numPixels(); i++) {
    uint32_t color = Wheel(((i * 256 / strip.numPixels()) + cycles) & 255,
                           color1, color2, color3);

    // Extract RGB values from the color
    byte r = (color >> 16) & 0xFF;
    byte g = (color >> 8) & 0xFF;
    byte b = color & 0xFF;

    // Apply gamma correction and set the pixel
    setGammaPixel(i, r, g, b);
  }
  strip.show();

  // Move the pattern a little bit for the next frame
  cycles = (cycles + max(1, cycleSpeed / 3)) % (256 * 5);
}

// ===== FIRE PATTERN =====
void fire(int Cooling, int Sparking, int SpeedDelay) {
  // This array keeps track of how "hot" each LED is
  static byte heat[LED_COUNT];
  int cooldown;

  // Step 1: Cool down each pixel a little bit
  for (int i = 0; i < LED_COUNT; i++) {
    cooldown = random(0, ((Cooling * 10) / LED_COUNT) + 2);
    if (cooldown > heat[i]) {
      heat[i] = 0;
    } else {
      heat[i] = heat[i] - cooldown;
    }
  }

  // Step 2: Heat rises - make the fire move upward
  for (int k = LED_COUNT - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  // Step 3: Randomly add new sparks at the bottom
  if (random(255) < Sparking) {
    int y = random(7);
    heat[y] = heat[y] + random(160, 255);
  }

  // Step 4: Convert heat to pretty fire colors
  for (int j = 0; j < LED_COUNT; j++) {
    setPixelHeatColor(j, heat[j]);
  }

  strip.show();
  delay(SpeedDelay);
}

// ===== FIRE COLOR HELPER =====
// This turns temperature numbers into pretty fire colors
void setPixelHeatColor(int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature / 255.0) * 191);

  byte heatramp = t192 & 0x3F;  // 0..63
  heatramp <<= 2;  // scale up to 0..252

  // Choose colors based on how hot the pixel is
  if (t192 > 0x80) {                    // Super hot! White-ish yellow
    setPixel(Pixel, 255, 255, heatramp);
  } else if (t192 > 0x40) {            // Medium hot! Orange
    setPixel(Pixel, 255, heatramp, 0);
  } else {                               // Not so hot! Red
    setPixel(Pixel, heatramp, 0, 0);
  }
}

// ===== PIXEL SETTING HELPER =====
// This is like having a helper that knows exactly how to color each light
void setPixel(int Pixel, byte red, byte green, byte blue) {
  strip.setPixelColor(Pixel, strip.Color(red, green, blue));
}

// ===== ALL PIXEL SETTING HELPER =====
// This colors all the lights the same color at once
void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < LED_COUNT; i++) {
    setPixel(i, red, green, blue);
  }
  strip.show();
}

// ===== SHOOTING STAR PATTERN =====
void spirula(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay,
             boolean meteorRandomDecay, int SpeedDelay) {
  // Start with all lights off
  setAll(0, 0, 0);

  // Create the shooting star effect
  for (int i = 0; i < LED_COUNT + LED_COUNT; i++) {
    // Fade the existing trail
    for (int j = 0; j < LED_COUNT; j++) {
      if ((!meteorRandomDecay) || (random(10) > 5)) {
        fadeToBlack(j, meteorTrailDecay);
      }
    }

    // Draw the meteor and its trail
    for (int j = 0; j < meteorSize; j++) {
      if ((i - j < LED_COUNT) && (i - j >= 0)) {
        setPixel(i - j, red, green, blue);
      }
    }

    strip.show();
    delay(SpeedDelay);
  }
}

// ===== FADING HELPER =====
// This helps make lights fade out smoothly
void fadeToBlack(int ledNo, byte fadeValue) {
  uint32_t oldColor;
  uint8_t r, g, b;
  int value;

  oldColor = strip.getPixelColor(ledNo);
  r = (oldColor & 0x00ff0000UL) >> 16;
  g = (oldColor & 0x0000ff00UL) >> 8;
  b = (oldColor & 0x000000ffUL);

  r = (r <= 10) ? 0 : (int) r - (r * fadeValue / 256);
  g = (g <= 10) ? 0 : (int) g - (g * fadeValue / 256);
  b = (b <= 10) ? 0 : (int) b - (b * fadeValue / 256);

  strip.setPixelColor(ledNo, r, g, b);
}

// ===== FIREFLY PATTERN =====
void firefly(int sparkSpeed, int pulseSpeed, int newFlyChance, int fadeAmount) {
  // Keep track of each firefly's state
  static byte fireflyBrightness[LED_COUNT] = {0};  // How bright each firefly is
  static float pulseCycle[LED_COUNT] = {0};        // Where each firefly is in its pulse
  static bool isActive[LED_COUNT] = {0};           // Whether each firefly is glowing
  static unsigned long lastSparkTime = 0;          // Time tracker for new fireflies
  static unsigned long lastUpdateTime = 0;         // Time tracker for updates

  unsigned long currentTime = millis();

  // Maybe create new fireflies
  if (currentTime - lastSparkTime > sparkSpeed) {
    if (random(100) > (100 - newFlyChance)) {
      int pos = random(LED_COUNT);
      if (fireflyBrightness[pos] == 0) {
        fireflyBrightness[pos] = random(220, 255);  // Start bright!
        pulseCycle[pos] = 0;
        isActive[pos] = true;
      }
    }
    lastSparkTime = currentTime;
  }

  // Update existing fireflies
  if (currentTime - lastUpdateTime > pulseSpeed) {
    for (int i = 0; i < LED_COUNT; i++) {
      if (fireflyBrightness[i] > 0) {
        if (isActive[i]) {
          // Make the firefly pulse gently
          pulseCycle[i] += 0.1;
          float pulseValue = sin(pulseCycle[i]) * 0.2 + 0.8;

          // Warm amber glow
          byte brightness = fireflyBrightness[i] * pulseValue;
          byte red = (brightness * 255) / 255;
          byte green = (brightness * 180) / 255;
          setPixel(i, red, green, 0);

          if (pulseCycle[i] > PI * 2) {
            isActive[i] = false;
          }
        } else {
          // Fade out gently
          float fadeRatio = (float)fireflyBrightness[i] / 255.0;
          byte red = (fireflyBrightness[i] * 255) / 255;
          byte green = (fireflyBrightness[i] * 180) / 255;
          setPixel(i, red * fadeRatio, green * fadeRatio, 0);

          if (fireflyBrightness[i] > 40) {
            fireflyBrightness[i] -= fadeAmount;
          } else {
            fireflyBrightness[i] = 0;
          }
        }
      } else {
        setPixel(i, 0, 0, 0);
      }
    }
    lastUpdateTime = currentTime;
    strip.show();
  }
}

// ===== MATRIX RAIN PATTERN =====
void matrix(int dropSpeed, int fadeSpeed, int newDropChance) {
  // Each raindrop needs to remember some things
  static struct Drop {
    int column;      // Which column it's in
    int pos;         // How far down it's fallen
    int length;      // How long the drop is
    int speed;       // How fast it falls
    byte brightness; // How bright it is
    bool active;     // Whether it's currently falling
  } drops[9];         // We can have up to 9 drops at once

  static unsigned long lastUpdate = 0;
  unsigned long currentTime = millis();

  if (currentTime - lastUpdate > fadeSpeed) {
    // First, fade existing drops
    for (int i = 0; i < LED_COUNT; i++) {
      uint32_t color = strip.getPixelColor(i);
      byte green = (color >> 8) & 0xFF;
      if (green > 0) {
        setPixel(i, 0, max(0, green - 8), 0);
      }
    }

    // Then update all our raindrops
    for (int i = 0; i < 9; i++) {
      if (drops[i].active) {
        // Clear the old position
        for (int j = 0; j < drops[i].length; j++) {
          int oldPos = drops[i].pos - j;
          if (oldPos >= 0) {
            int pixelIndex = LED_COUNT - 1 - ((drops[i].column + (oldPos * 9)) % LED_COUNT);
            setPixel(pixelIndex, 0, 0, 0);
          }
        }

        // Move the drop down
        drops[i].pos += drops[i].speed;

        // Draw the new position
        for (int j = 0; j < drops[i].length; j++) {
          int dropPos = drops[i].pos - j;
          if (dropPos >= 0) {
            int pixelIndex = LED_COUNT - 1 - ((drops[i].column + (dropPos * 9)) % LED_COUNT);
            if (pixelIndex >= 0) {
              byte trailBrightness = drops[i].brightness *
                                     (drops[i].length - j) / drops[i].length;
              setPixel(pixelIndex, 0, trailBrightness, 0);
            }
          }
        }

        // Check if the drop is done falling
        if (drops[i].pos - drops[i].length > (LED_COUNT / 9)) {
          drops[i].active = false;
        }
      } else if (random(100) > (100 - newDropChance)) {
        // Make a new raindrop!
        drops[i].column = i;
        drops[i].pos = -random(0, 3);
        drops[i].length = random(3, 6);
        drops[i].speed = 1;
        drops[i].brightness = random(180, 255);
        drops[i].active = true;
      }
    }

    lastUpdate = currentTime;
    strip.show();
  }
}
