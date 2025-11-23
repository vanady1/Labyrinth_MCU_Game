const unsigned long updateInterval = 1000;
unsigned long lastUpdateTime = 0;

const unsigned long movementInterval = 300;
unsigned long lastMovementTime = 0;

const unsigned int mapHeight = 10;
const unsigned int mapWidth = 10;
const int moneyAmountToWin = 8;

const int buttonPort0Pin = 4;
const int buttonPort1Pin = 5;
const int buttonPort2Pin = 0;
const int buttonPort3Pin = 1;

bool isPin0Pressed = false;
bool isPin1Pressed = false;
bool isPin2Pressed = false;
bool isPin3Pressed = false;

bool gameIsntFinished = true;

char empty = ' ';
char wall = '#';
char player = '@';
char money = '$';

unsigned int moneyPosX = 5;
unsigned int moneyPosY = 5;

unsigned int moneyAmount = 0;

unsigned int playerPosX = 1;
unsigned int playerPosY = 1;

char gameMap[mapHeight][mapWidth] = {
  { wall, wall, wall, wall, wall, wall, wall, wall, wall, wall },
  { wall, empty, wall, empty, empty, empty, empty, empty, empty, wall },
  { wall, empty, wall, empty, empty, empty, empty, empty, empty, wall },
  { wall, empty, wall, empty, empty, empty, wall, wall, wall, wall },
  { wall, empty, empty, empty, empty, empty, empty, empty, empty, wall },
  { wall, empty, empty, empty, empty, empty, empty, empty, empty, wall },
  { wall, empty, empty, empty, wall, empty, empty, empty, empty, wall },
  { wall, empty, empty, empty, wall, empty, empty, empty, empty, wall },
  { wall, empty, empty, empty, wall, empty, empty, empty, empty, wall },
  { wall, wall, wall, wall, wall, wall, wall, wall, wall, wall }
};

void setup() {
  DDRB = 255;
  PORTB = 255;
  DDRE &= ~((1 << PINE4) | (1 << PINE5));
  DDRK &= ~((1 << PINK0) | (1 << PINK1));

  Serial.begin(500000);
  randomSeed(analogRead(0));
  displayGameMap();
  displayMoneyOnLED();
}

void loop() {

  while (gameIsntFinished == false) {
    _delay_ms(20);
    displayGameMap();
    playWinAnimation();
  }
  unsigned long currentTime = millis();

  // Обновление карты и денег
  if (currentTime - lastUpdateTime >= updateInterval) {
    displayGameMap();
    displayMoneyOnLED();
    lastUpdateTime = currentTime;
  }

  // Попытка движения игрока
  if (currentTime - lastMovementTime >= movementInterval) {
    lastMovementTime = currentTime;
  }

  // Обработка кнопок
  int buttonPort0State = PINE & (1 << PINE4);
  int buttonPort1State = PINE & (1 << PINE5);
  int buttonPort2State = PINK & (1 << PINK0);
  int buttonPort3State = PINK & (1 << PINK1);

  if (buttonPort0State && !isPin0Pressed) {
    isPin0Pressed = true;
    movePlayer('w');
  } else if (!buttonPort0State) {
    isPin0Pressed = false;
  }

  if (buttonPort1State && !isPin1Pressed) {
    isPin1Pressed = true;
    movePlayer('s');
  } else if (!buttonPort1State) {
    isPin1Pressed = false;
  }

  if (buttonPort2State && !isPin2Pressed) {
    isPin2Pressed = true;
    movePlayer('d');
  } else if (!buttonPort2State) {
    isPin2Pressed = false;
  }

  if (buttonPort3State && !isPin3Pressed) {
    isPin3Pressed = true;
    movePlayer('a');
  } else if (!buttonPort3State) {
    isPin3Pressed = false;
  }
}


void displayGameMap() {
  clearScreen();

  for (int i = 0; i < mapHeight; ++i) {
    for (int j = 0; j < mapWidth; ++j) {
      if (gameIsntFinished == false) {
        Serial.print(money);
      } else if ((i == playerPosY && j == playerPosX)) {
        Serial.print(player);
      } else if (i == moneyPosY && j == moneyPosX) {
        Serial.print(money);
      } else {
        Serial.print(gameMap[i][j]);
      }
      Serial.print(' ');
    }
    if (i == 5 && gameIsntFinished == false) {
      Serial.println("  YOU WON!");
    } else if (i == 9) {
      Serial.print("  Money = ");
      Serial.print(moneyAmount);
      Serial.println("/8$");
    } else {
      Serial.println();
    }
  }
}

void movePlayer(char direction) {
  int newPlayerX = playerPosX;
  int newPlayerY = playerPosY;

  switch (direction) {
    case 'w':
      newPlayerY--;
      break;
    case 's':
      newPlayerY++;
      break;
    case 'a':
      newPlayerX--;
      break;
    case 'd':
      newPlayerX++;
      break;
  }
  if (newPlayerX >= 0 && newPlayerX < 10 && newPlayerY >= 0 && newPlayerY < 10 && gameMap[newPlayerY][newPlayerX] != wall) {
    playerPosX = newPlayerX;
    playerPosY = newPlayerY;
  }
  if (newPlayerX == moneyPosX && newPlayerY == moneyPosY) {
    resetMoneyPos();
    moneyAmount++;

    if (moneyAmount == moneyAmountToWin) {
      winGame();
    }
    displayMoneyOnLED();
  }
}

void resetMoneyPos() {
  int tryPosX = getRandomMoneyPos();
  int tryPosY = getRandomMoneyPos();

  while (gameMap[tryPosY][tryPosX] == wall || (tryPosX == playerPosX && tryPosY == playerPosY)) {
    tryPosX = getRandomMoneyPos();
    tryPosY = getRandomMoneyPos();
  }
  moneyPosX = tryPosX;
  moneyPosY = tryPosY;
}

int getRandomMoneyPos() {
  return random(1, mapWidth);
}

void displayMoneyOnLED() {
  byte mask = (1 << moneyAmount) - 1;
  PORTB = ~mask;
}

void winGame() {
  gameIsntFinished = false;
}

void playWinAnimation() {
  playRandomAnimation();
}

void playRandomAnimation() {
  int randInt = random(0, 6);
  //randInt = 3;
  switch (randInt) {
    case 0:
      waveUpLED();
      waveDownLED();
      break;
    case 1:
      fillUpRightLED();
      fillDownRightLED();
      waveUpLED();
      fillUpLeftLED();
      fillDownLeftLED();
      waveDownLED();
      break;
    case 2:
      fillUpLeftLED();
      fillDownRightLED();
      fillUpRightLED();
      fillDownLeftLED();
      break;
    case 3:
      waveDownLED();
      fillUpLeftLED();
      fillDownRightLED();
      waveUpLED();
      fillUpRightLED();
      fillDownLeftLED();
      break;
  }
}

unsigned int animationMsDelay = 65;

void fillUpRightLED() {
  for (int i = 0; i <= 8; i++) {
    byte mask = (1 << i) - 1;
    PORTB = ~mask;
    _delay_ms(animationMsDelay);
  }
}

void fillDownRightLED() {
  for (int i = 7; i > 0; i--) {
    byte mask = (1 << i) - 1;
    PORTB = ~mask;
    _delay_ms(animationMsDelay);
  }
}

void fillUpLeftLED() {
  for (int i = 8; i >= 0; i--) {
    byte mask = (1 << i) - 1;
    PORTB = mask;
    _delay_ms(animationMsDelay);
  }
}

void fillDownLeftLED() {
  for (int i = 0; i <= 8; i++) {
    byte mask = (1 << i) - 1;
    PORTB = mask;
    _delay_ms(animationMsDelay);
  }
}

void waveDownLED() {
  for (int i = 7; i >= 0; i--) {
    byte mask = 1 << i;
    PORTB = ~mask;
    _delay_ms(animationMsDelay);
  }
}

void waveUpLED() {
  for (int i = 0; i < 8; i++) {
    byte mask = 1 << i;
    PORTB = ~mask;
    _delay_ms(animationMsDelay);
  }
}

void clearScreen() {
  for (int i = 0; i < 50; ++i) {
    Serial.println();
  }
}
