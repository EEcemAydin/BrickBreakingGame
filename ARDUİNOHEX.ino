#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define a 10
#define b 9
#define c 8
#define d 7
#define e 6
#define f 5
#define g 4
#define sev_1 3
#define sev_2 2
#define can1Led 11
#define can2Led 12
#define can3Led 13
#define potans A0
#define LDR A1
#define startButton A2
#define exitButton A3

int genislik = 128; // OLED ekran genişliği (piksel olarak)
int yukseklik = 64; // OLED ekran yüksekliği (piksel olarak)
int adres = 0x3C;  

Adafruit_SSD1306 ekran(genislik, yukseklik, &Wire, -1); 

int blokMatrisi[4][12] = {// 4x12 blok matrisi 1 olan yerlerde blok var 0 olan yerlerde blok yok
    {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

const unsigned char baslaWhite[] PROGMEM = {// 'baslaBlack2', 41x9px
    0xf8, 0x38, 0x3c, 0x40, 0x38, 0x00, 0x84, 0x44, 0x40, 0x40, 0x44, 0x00, 0x84, 0x44, 0x40, 0x40,
    0x44, 0x00, 0x84, 0x44, 0x40, 0x40, 0x44, 0x00, 0xf8, 0x7c, 0x38, 0x40, 0x7c, 0x00, 0x84, 0x44,
    0x04, 0x40, 0x44, 0x00, 0x84, 0x44, 0x04, 0x40, 0x44, 0x00, 0x84, 0x44, 0x04, 0x40, 0x44, 0x00,
    0xf8, 0x44, 0x78, 0x7c, 0x44, 0x00};

// 'cıkısBlack2', 41x9px
const unsigned char cikisWhite[] PROGMEM = {
    0xf8, 0x20, 0x84, 0x20, 0x7c, 0x00, 0x80, 0x20, 0x88, 0x20, 0x80, 0x00, 0x80, 0x20, 0x90, 0x20,
    0x80, 0x00, 0x80, 0x20, 0xa0, 0x20, 0x80, 0x00, 0x80, 0x20, 0xc0, 0x20, 0x78, 0x00, 0x80, 0x20,
    0xa0, 0x20, 0x04, 0x00, 0x80, 0x20, 0x90, 0x20, 0x04, 0x00, 0x80, 0x20, 0x88, 0x20, 0x04, 0x00,
    0xf8, 0x20, 0x84, 0x20, 0xf8, 0x00};
const unsigned char secimCerceve[] PROGMEM = {// 'secimCerceve', 45x13px
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x08, 0x80, 0x00, 0x00, 0x00, 0x00, 0x08, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8};
const unsigned char kalp[] PROGMEM = {// 'kalp', 10x10px
    0x00, 0x00, 0x21, 0x00, 0x73, 0x80, 0xff, 0xc0, 0xff, 0xc0, 0xff, 0xc0, 0x7f, 0x80, 0x3f, 0x00,
    0x1e, 0x00, 0x0c, 0x00};

const unsigned char blokWhite[] PROGMEM = {// 'blokWhite', 8x6px
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

const unsigned char tabla[] PROGMEM = { // tabla 2x16
    0xff, 0xff, 0xff, 0xff};
const unsigned char top[] PROGMEM = {// 'top', 2x2px
    0xff, 0xff};

const unsigned char *menuEkran[2] = {// 'menuEkran', 41x9px
    baslaWhite,
    cikisWhite};

int kalpVeKonumlari[3][2];

int birlerbas = 0;
int onlarbas = 0;
int yuzlerbas = 0;
int skorTemp = 0;
int puan = 0;
int hiz = 1;
int secim = 0;
int tema = 0; // siyah arkaplan 1 beyaz arkaplan 0
int blokSayisi = 4;
bool oyunDevam = false;
int topYon = 0; // 0 düz yukarı 1 sol yukarı 2 sağ yukarı 3 düz aşağı 4 sol aşağı 5 sağ aşağı
int topX = 65;
int topY = 59;
int tablaX = 58;
int tablaY = 61;
int can = 3;
int kalpSayisi = 0;
int tersTema = 0;
int kalpX;
int kalpY;
int level = 1;
int kirilanBlok = 0;
int potValue = 0;

void setup()
{
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(can1Led, OUTPUT);
  pinMode(can2Led, OUTPUT);
  pinMode(can3Led, OUTPUT);
  pinMode(sev_1, OUTPUT);
  pinMode(sev_2, OUTPUT);
  pinMode(potans, INPUT);
  pinMode(LDR, INPUT);
  pinMode(startButton, INPUT);
  pinMode(exitButton, INPUT);

  if (!ekran.begin(0x02, adres))
  {
    Serial.println(F("Ekran Bulunamadı"));
    for (;;)
      ; 
  }
  if (tema == 1)
  {
    tersTema = 0;
  }
  else
  {
    tersTema = 1;
  }

  Serial.begin(9600);
  ekran.display();
  delay(2000);
  temaKontrol();
  secim = menuGoster();
  if (tema == 0)
  {
    ekran.fillRect(0, 0, 128, 64, 1);
  }
}

void loop()
{
  if (can == 3)
  {
    digitalWrite(can1Led, HIGH);
    digitalWrite(can2Led, HIGH);
    digitalWrite(can3Led, HIGH);
  }
  else if (can == 2)
  {
    digitalWrite(can1Led, LOW);
    digitalWrite(can2Led, HIGH);
    digitalWrite(can3Led, HIGH);
  }
  else if (can == 1)
  {
    digitalWrite(can1Led, LOW);
    digitalWrite(can2Led, LOW);
    digitalWrite(can3Led, HIGH);
  }

  if (can > 0)
  {
    if (oyunDevam == true)
    {
      bloklariGetir();// blokları çiz
      tablaGuncelle();// tablayı çiz
      topHareketi();// topu hareket ettir
      tablaCarpma();// top tablaya çarptımı
      kenarCarpma();// top kenarlara çarptımı
      kalpHaraket();// kalp hareketi
      tumTuglalarKirildi();// tüm tuğlalar kırıldımı
      skorHesapla();// skoru hesapla
      if (tuglaCarpmaKirma())// top tuğlaya çarptımı
      {
        puanArttir();// puanı arttır
        temaKontrol();// tema kontrol
      }
      if (can == 0)
      {
        oyunDevam = false;
        digitalWrite(can1Led, LOW);
        digitalWrite(can2Led, LOW);
        digitalWrite(can3Led, LOW);
        oyunBitti();
      }
    }
  }
}
void temaKontrol()// tema kontrol
{
  Serial.println(analogRead(LDR));
  if (analogRead(LDR) > 200)
  {
    tema = 1;
    tersTema = 0;
    ekran.fillRect(0, 0, 128, 64, 0);
  }
  else
  {
    tema = 0;
    tersTema = 1;
    ekran.fillRect(0, 0, 128, 64, 1);
  }
}

void oyunBitti()// oyun bitti
{
  Serial.print("OyunBitti");
  if (tema == 0)
  {
    ekran.fillRect(0, 0, 128, 64, 1);
  }
  else
  {
    ekran.clearDisplay();
  }
  ekran.setTextSize(1);     // Normal 1:1 pixel scale
  ekran.setTextColor(tema); // Draw white text
  ekran.setCursor(30, 25);
  ekran.print("Oyun Bitti!");
  ekran.setCursor(45, 35);
  ekran.print("Puan: ");
  ekran.print(puan);
  ekran.display();
  delay(10000);
}

bool tumTuglalarKirildi()// tüm tuğlalar kırıldımı kontrol et ve level atlama ekranı
{

  if (kirilanBlok == blokSayisi && level != 3)
  {
    level++;
    hiz++;
    kirilanBlok = 0;
    levelAtlamaEkrani();
    // eski tablayı ve topu sil
    ekran.drawBitmap(tablaX, tablaY, tabla, 16, 2, tersTema);
    ekran.drawBitmap(topX, topY, top, 2, 2, tersTema);
    if (tema == 0)
    {
      ekran.fillRect(0, 0, 128, 64, 1);
    }
    topX = 65;
    topY = 59;
    tablaX = 58;
    tablaY = 61;
    delay(1000);
    topYon = 0;
    blokSayisi += 4;
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 12; j++)
      {
        blokMatrisi[i][j] = 0;
      }
    }
    blokOlustur();
    return true; // Matriste 1 değeri bulunmadığı için fonksiyon true döndürür
  }
  else if (kirilanBlok == blokSayisi && level == 3)
  {
    oyunDevam = false;
    digitalWrite(can1Led, LOW);
    digitalWrite(can2Led, LOW);
    digitalWrite(can3Led, LOW);
    oyunBitti();
  }

  return false; // 1 değeri bulduğumuzda fonksiyon false döndürür
}

void levelAtlamaEkrani()// level atlama ekranı göster ve puanı yazdır
{
  if (tema == 0)
  {
    ekran.fillRect(0, 0, 128, 64, 1);
  }
  else
  {
    ekran.clearDisplay();
  }
  ekran.setTextSize(1);     // Normal 1:1 pixel scale
  ekran.setTextColor(tema); // Draw white text
  ekran.setCursor(20, 25);
  ekran.print("Level Atladiniz!");
  ekran.setCursor(25, 35);
  ekran.print("Puan: ");
  ekran.print(puan);
  ekran.display();
  delay(4000);
  if (tema == 0)
  {
    ekran.fillRect(0, 0, 128, 64, 1);
  }
  else
  {
    ekran.clearDisplay();
  }
}

bool menuGoster()
{ //-1 menu göstermeye devam 1 oyuna başlax 0 cıkıs

  while (1)
  {

    ekran.clearDisplay();
    if (tema == 0)
    {
      ekran.fillRect(0, 0, 128, 64, 1);
    }
    ekran.drawBitmap(38, 30, secimCerceve, 45, 13, tema);
    ekran.drawBitmap(42, 32, menuEkran[0], 41, 9, tema);
    ekran.drawBitmap(42, 45, menuEkran[1], 41, 9, tema);
    ekran.display();

    if (digitalRead(startButton) == HIGH)
    {
      ekran.clearDisplay();
      ekran.display();
      oyunDevam = true;
      return true;
    }
    else if (digitalRead(exitButton) == HIGH)
    {
      ekran.clearDisplay();
      ekran.display();
      return false;
    }
  }
  return false;
}

void bloklariGetir()
{
  // kenarlardan 6 boşluk araları 2 12 tane yatayda
  // dikeyde 4 sıra

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 12; j++)
    {
      if (blokMatrisi[i][j] == 1)
      {
        int blokY = 6 + (i * 8);
        int blokX = 6 + (j * 10);
        ekran.drawBitmap(blokX, blokY, blokWhite, 8, 6, tema);
      }
    }
  }
  ekran.display();
}

void blokOlustur()// blokları oluştur
{
  for (int i = 0; i < blokSayisi; i++)
  {
  yeniden:
    int y = random(0, 4);
    int x = random(0, 12);
    if (blokMatrisi[y][x] == 0)
    {

      blokMatrisi[y][x] = 1;
      int blokY = 6 + (y * 8);
      int blokX = 6 + (x * 10);
    }
    else
    {
      goto yeniden;
    }
  }
}

void tablaGuncelle()// tablayı güncelle ve potansı oku ve tablayı hareket ettir ve çiz
{
  ekran.drawBitmap(tablaX, tablaY, tabla, 16, 2, tersTema);

  potValue = analogRead(potans);           // Read the potentiometer value
  tablaX = map(potValue, 0, 1023, 1, 110); // Map the potentiometer value to the desired range

  ekran.drawBitmap(tablaX, tablaY, tabla, 16, 2, tema);
  ekran.display();
}

void topHareketi() // topu hareket ettir ve çiz   // 0 düz yukarı 1 sol yukarı 2 sağ yukarı 3 düz aşağı 4 sol aşağı 5 sağ aşağı
{

  switch (topYon)
  {
  case 0:
    ekran.drawBitmap(topX, topY, top, 2, 2, tersTema); // eski topu sil
    topY -= hiz;
    ekran.drawBitmap(topX, topY, top, 2, 2, tema); // yeni topu çiz

    break;
  case 1:
    ekran.drawBitmap(topX, topY, top, 2, 2, tersTema);
    topX -= hiz;
    topY -= hiz;
    ekran.drawBitmap(topX, topY, top, 2, 2, tema);

    break;

  case 2:
    ekran.drawBitmap(topX, topY, top, 2, 2, tersTema);
    topX += hiz;
    topY -= hiz;
    ekran.drawBitmap(topX, topY, top, 2, 2, tema);

    break;
  case 3:

    ekran.drawBitmap(topX, topY, top, 2, 2, tersTema);
    topY += hiz;
    ekran.drawBitmap(topX, topY, top, 2, 2, tema);

    break;

  case 4:
    ekran.drawBitmap(topX, topY, top, 2, 2, tersTema);
    topX -= hiz;
    topY += hiz;
    ekran.drawBitmap(topX, topY, top, 2, 2, tema);

    break;
  case 5:

    ekran.drawBitmap(topX, topY, top, 2, 2, tersTema);
    topX += hiz;
    topY += hiz;
    ekran.drawBitmap(topX, topY, top, 2, 2, tema);

    break;
  }
  ekran.display();
}

bool tablaCarpma()
{
  // topun herhangi bir köşesinin tablaya çarpıp çarpmadığını kontrol edin
  if (topX >= tablaX && topX <= tablaX + 16 && topY >= tablaY && topY <= tablaY + 2)
  {

    if (topYon == 3 || topYon == 4 || topYon == 5)
    {
      topYon = random(0, 3);
    }
    else if (topYon == 0 || topYon == 1 || topYon == 2)
    {
      topYon = random(3, 6);
    }
    return true;
  }

  return false;
}

bool kenarCarpma()
{ // sol yukarı gidiyosa sağ yukarı
  // sol aşağı geliyorsa sağ aşağı
  // sağ yukarı gidiyorsa sol yuarı
  // sağ aşağı gelisere sol aşagı
  // sol kenar
  if (topX <= 1)
  {
    if (topYon == 1)
    {
      topYon = 2;
    }
    else if (topYon == 4)
    {
      topYon = 5;
    }
    return true;
  }
  // sağ kenar
  else if (topX >= 125)
  {
    if (topYon == 2)
    {
      topYon = 1;
    }
    else if (topYon == 5)
    {
      topYon = 4;
    }
    return true;
  }
  // üst kenar
  else if (topY <= 0)
  {
    if (topYon == 0)
    {
      topYon = 3;
    }
    else if (topYon == 1)
    {
      topYon = 4;
    }
    else if (topYon == 2)
    {
      topYon = 5;
    }
    return true;
  }
  // alt kenar
  else if (topY >= 63)
  {
    can = canAzalt(can);
    // eski tablayı ve topu sil
    ekran.drawBitmap(tablaX, tablaY, tabla, 16, 2, tersTema);
    ekran.drawBitmap(topX, topY, top, 2, 2, tersTema);
    topX = 65;
    topY = 59;
    tablaX = 58;
    tablaY = 61;
    delay(1000);
    topYon = random(0, 3);
    return true;
  }

  return false;
}
bool tuglaCarpmaKirma()
{

  bool carpma = false;

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      if (blokMatrisi[i][j] == 1)
      {
        int blokY = 6 + (i * 8);
        int blokX = 6 + (j * 10);

        // Topun bloğun herhangi bir köşesine çarpıp çarpmadığını kontrol edin
        for (int k = 0; k < 2; k++)
        {
          for (int l = 0; l < 2; l++)
          {
            if (topX + k >= blokX && topX + k <= blokX + 8 && topY + l >= blokY && topY + l <= blokY + 6)
            {
              carpma = true;

              blokMatrisi[i][j] = 0;

              ekran.drawBitmap(blokX, blokY, blokWhite, 8, 6, tersTema);
              kirilanBlok++;
              // Topun yönünü değiştir
              if (topYon == 0 || topYon == 1 || topYon == 2)
              {
                topYon = random(3, 6);
                kalpDusur(blokX, blokY);
              }
              else if (topYon == 3 || topYon == 4 || topYon == 5)
              {
                topYon = random(0, 3);
              }

              break; // Bir blok kırıldıktan sonra diğer kontrolleri durdur
            }
          }

          if (carpma)
          {
            break; // Bir blok kırıldıktan sonra sonraki bloğa bakmaya gerek yok
          }
        }
      }
    }
  }

  return carpma;
}
// top tuğlaya çarpınca %10 ihtimalle kalp düşer,
// kalp düşerse canı 1 artırır
void kalpDusur(int blokX, int blokY)
{
  //%10 İhtimalle kalp düşür
  int sans = 0;
  if (sans == 0)
  {
    kalpX = blokX;
    kalpY = blokY + 6;
    kalpVeKonumlari[kalpSayisi][0] = kalpX;
    kalpVeKonumlari[kalpSayisi][1] = kalpY;
    Serial.println("Kalp Bulundu");
    kalpSayisi++;
  }
}
void kalpHaraket()
{
  for (int i = 0; i < kalpSayisi; i++)
  {
    if (kalpVeKonumlari[i][0] != -1)
    {
      kalpX = kalpVeKonumlari[i][0];
      kalpY = kalpVeKonumlari[i][1];
      ekran.drawBitmap(kalpX, kalpY, kalp, 10, 10, tersTema);
      kalpVeKonumlari[i][1] += 2;
      kalpX = kalpVeKonumlari[i][0];
      kalpY = kalpVeKonumlari[i][1];
      Serial.println(kalpY);
      ekran.drawBitmap(kalpX, kalpY, kalp, 10, 10, tema);
      // tabla altına düşerse kalbi sil
      if (kalpY + 10 >= 64)
      {
        kalpVeKonumlari[i][0] = -1;
        kalpVeKonumlari[i][1] = -1;
        kalpSayisi--;
        ekran.drawBitmap(kalpX, kalpY, kalp, 10, 10, tersTema);
      }
      // tablaya çarparsa canı 1 artır
      if (kalpX >= tablaX && kalpX <= tablaX + 16 && kalpY + 9 == tablaY)
      {
        if (can != 3)
        {
          can++;
        }
        ekran.drawBitmap(kalpX, kalpY, kalp, 10, 10, tersTema);
        kalpVeKonumlari[i][0] = -1;
        kalpVeKonumlari[i][1] = -1;
        kalpSayisi--;
      }
    }

    ekran.display();
  }
}

void puanArttir()
{
  puan++;
  skorHesapla();
}
int canAzalt(int can)
{
  can--;
  return can;
}

void skorHesapla()// skoru hesapla ve göster 2 7 segment displayde 
{
  skorTemp = puan;
  onlarbas = skorTemp / 10;
  skorTemp = skorTemp - (onlarbas * 10);
  birlerbas = skorTemp;

  digitalWrite(sev_1, HIGH);
  digitalWrite(sev_2, LOW);

  skorgoster(onlarbas);
  delay(5);

  digitalWrite(sev_1, LOW);
  digitalWrite(sev_2, HIGH);
  skorgoster(birlerbas);
  delay(5);
}

void skorgoster(int rakam)// 7 segment displayde rakamı göster
{
  switch (rakam)
  {
  case 0:
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
    break;
  case 1:
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    break;
  case 2:
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, HIGH);
    digitalWrite(g, LOW);
    break;
  case 3:
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, LOW);
    break;
  case 4:
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    break;
  case 5:
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    break;
  case 6:
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    break;
  case 7:
    digitalWrite(a, LOW); //
    digitalWrite(b, LOW); //
    digitalWrite(c, LOW); //
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    break;
  case 8:
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    break;
  case 9:
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
    break;
  }
}
