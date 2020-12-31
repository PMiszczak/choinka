# CHOINKA

<div align="center">
	<img src="https://i.imgur.com/Jp9iqYV.png" alt="CHOINKA - Customizable House Ornaments Indicating North-Pole Kingdom Angels" width="600">
</div>

<hr>

„CHOINKA - Customizable House Ornaments Indicating North-Pole Kingdom Angels” to projekt przygotowywany przez Pawełka Miszczaka na potrzeby każdego, kto chciałby mieć światełka choinkowe (lub niechoinkowe) sterowane inteligentną asystentką - Alexą.

<br>
<div align="center">
	<img src="https://img.shields.io/badge/Wersja-2.0.0-blue?style=for-the-badge&logo=Git&logoColor=white" alt="Wersja 2.0.0">
</div>
<br>

# Na jaką potrzebę odpowiada moje rozwiązanie?

„CHOINKA - Customizable House Ornaments Indicating North-Pole Kingdom Angels” jest projektem stworzonym czysto dla celów edukacyjnych oraz dla walorów estetycznych. Dzięki stworzeniu lampek choinkowych (lub niechoinkowych) z zastosowaniem technologii IoT użytkownik jest w stanie włączać, wyłączać, a także zmieniać animacje tworzone przez lampki za pomocą inteligentnego asystenta - Alexy.

# Opis działania mojego projektu

Projekt „CHOINKA - Customizable House Ornaments Indicating North-Pole Kingdom Angels” można podzielić na dwie główne części: fizyczną oraz  programistyczną.

<hr>

## Część fizyczna

Część fizyczna opiera się o 3 główne moduły połączone razem: zasilacz, mikrokontroler oraz pasek LED.

```mermaid
graph LR

Zasilacz --- |Zwora| Zasilacz
Zasilacz --> |Zasilanie +5Vsb| Mikrokontroler
Zasilacz --> |Zasilanie +5V| Złącza[Złącza MR60]

subgraph Obudowa
Mikrokontroler --> |DATA| Złącza[Złącza MR60]
end

Złącza[Złącza MR60] x-x LED[Pasek LED]
```

### Zasilacz

Zasilacz użyty do projektu jest zwykłym zasilaczem komputerowym (ATX) o mocy **300 [W]**. Jest potrzeby do dostarczenia energii do projektu. Ze względu na pasek LED, który zasilany musi być w tym przypadku napięciem **5 [V]** na samym początku dobranie odpowiedniego zasilacza było sporym wyzwaniem.

Pasek LED, który został zakupiony do projektu, jest paskiem inteligentnych sterowników LED ze wbudowanymi źródłami światła WS2812B na czarnym elastycznym PCB. W tym przypadku na każdy metr paska przypada 60 modułów. Długość paska jaka została zakupiona to 3 metry.

![60 \cdot 3 = 180](https://render.githubusercontent.com/render/math?math=60%20\cdot%203%20=%20180) - ilość modułów LED.

Powołując się na dokumentację modułów WS2812B oraz opis sprzedawcy, moc pojedynczego modułu wynosi **≈ 0,3 [W]**.

![180 \cdot 0.3\text{ }[W] = 54\text{ }[W]](https://render.githubusercontent.com/render/math?math=180%20\cdot%200.3\text{%20}[W]%20=%2054\text{%20}[W]) - moc całkowita paska LED.

Znając te wartości oraz to, że napięcie modułów jest równe **5 [V]** możemy obliczyć prąd potrzebny do zasilenia paska LED ze wzoru na moc.

![P = U \cdot I \rightarrow I = \frac{P}{U}](https://render.githubusercontent.com/render/math?math=P%20=%20U%20\cdot%20I%20\rightarrow%20I%20=%20\frac{P}{U})

![I = \frac{54\text{ }[W]}{5\text{ }[V]} = 10.8\text{ }[A]](https://render.githubusercontent.com/render/math?math=I%20=%20\frac{54\text{%20}[W]}{5\text{%20}[V]}%20=%2010.8\text{%20}[A]) - prąd całkowity paska LED.

Przyjmując straty, niedokładności modułów oraz zasilenie samego mikrokontrolera możemy spodziewać się szczytowego poboru prądu w wysokości ok. **12 [A]**.

Zasilacze o napięciu **5 [V]**, które będą w stanie wytworzyć tak wysoki prąd, są rzadkie oraz drogie. Z tego powodu w projekcie został użyty zasilacz komputerowy (ATX), który jest idealny do takich zastosowań. Na naklejce na zasilaczu możemy przeczytać, że linia **+5V** może wytworzyć nawet **25 [A]**. W dodatku w zasilaczu występuje linia **+5Vsb**, która wytwarza **5 [V]**, lecz to napięcie jest przepuszczone przez stabilizator liniowy, który zapewnia bardzo dokładną wartość napięcia oraz to, że na linii nie będzie tętnień prądu.

Linia **+5Vsb** co prawda może dostarczyć tylko **2 [A]** prądu, lecz jest to zupełnie wystarczająca wartość do zasilenia mikrokontrolera.

Do poprawnego działania zasilacz ATX potrzebuje zwartego pinu PS-ON z masą zasilacza.

### Mikrokontroler

Mikrokontroler użyty do projektu to NodeMCU. Jest on wyposażony we wbudowany moduł Wi-Fi ESP8266.

Mikrokontoler w projekcie steruje paskiem LED.

Mikrokontoler jest zasilany z zasilacza linią **+5Vsb**. Napięcie wchodzi na pin Vin, z którego następnie przechodzi na następny, wewnętrzny regulator liniowy NodeMCU.

W całym projekcie wykorzystywany jest tylko jeden pin GPIO.

Mimo braku wzmianki o tym w dokumentacji paska LED wiele stron i poradników zaleca użycie rezystora wpiętego szeregowo między mikrokontroler a pin DATA paska LED o wartości od **100 Ω** do **1000 Ω**. W projekcie użyty został rezystor o wartości **230 Ω**.

### Pasek LED

Jak już zostało wspomniane w podrozdziale _Zasilacz_ - pasek LED, który został zakupiony do projektu, jest paskiem inteligentnych sterowników LED ze wbudowanymi źródłami światła WS2812B na czarnym elastycznym PCB. W tym przypadku na każdy metr paska przypada 60 modułów. Długość paska, która została zakupiona to 3 metry.

## Część programistyczna

Część programistyczna opiera się o 2 pliki oraz 4 biblioteki.

### CHOINKA.ino

Plik „CHOINKA.ino” jest monolitycznym programem całego projektu. Cały kod został skomentowany. W dokumentacji postaram się przybliżyć zasadę działania programu tego projektu.

Na samym początku dodawane są wszystkie niezbędne biblioteki czyli:

-   ESP8266WiFi.h - biblioteka pozwalająca mikrokontrolerowi podłączenie się do internetu,
-   Adafruit_NeoPixel.h - biblioteka odpowiedziana za sterowanie diodami LED WS2812B,
-   fauxmoESP.h - biblioteka pozwalająca podszyć się za inteligentną żarówkę Philips HUE.

Dodana jest także standardowa biblioteka „Arduino.h”.

Następnie wszystkie biblioteki są inicjowane. Wybierany jest rodzaj diod LED, nazwa inteligentnego urządzenia oraz wczytywane są podstawowe informacje zaczerpnięte z stałych takich jak ilość diod LED oraz numer pinu DATA.

Po zainicjowaniu bibliotek kod wchodzi do części

```c++
void setup() {
...
}
```

W tej części na początku wyłączany oraz czyszczony jest pasek LED. Następnie mikrokontroler łączy się z Wi-Fi oraz zaczyna pokazywać się jako inteligentna żarówka. Przy okazji wszystkie czynności pokazywane są w monitorze portu szeregowego.

Następna część kodu odpowiada za zmienienie zmiennej typu INT na odpowiednią wartość względem tego czy żarówka jest włączona czy wyłączona oraz **na jaką jasność świecenia została ustawiona**.

```c++
CHOINKA.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
...
}
```

Następnie kod wchodzi do fazy

```c++
void loop() {
...
}
```

 W tej części sprawdzana jest wartość zmiennej typu INT z wcześniejszej części oraz względem niej włączany jest odpowiedni void odpowiedzany za poszczególną animację.

```c++
switch (LED_STATE) {
...
}
```

### dane.h

Plik „dane.h” jest bardzo prostym plikiem zawierającym 4 stałe.

```c++
#define WIFI_SSID "wifi_ssid"
#define WIFI_PASS "wifi_pass"

#define LED_DANE 2
#define LED_ILOSC 180
```

Dwie pierwsze stałe są loginem i hasłem dla mikrokontrolera do sieci Wi-Fi. Następne dwie stałe dotyczą paska LED. Stała LED_DANE określa, na którym pinie GPIO odbywa się komunikacja między mikrokontrolerem, a paskiem LED. Natomiast stała LED_ILOSC informuje program o ilości modułów LED w użytym pasku.

# Filmy

[![CHOINKA - Customizable House Ornaments Indicating North-Pole Kingdom Angels - Wersja 1.0.0](http://img.youtube.com/vi/IX6Z9OP_zIc/0.jpg)](http://www.youtube.com/watch?v=IX6Z9OP_zIc "CHOINKA - Customizable House Ornaments Indicating North-Pole Kingdom Angels - Wersja 1.0.0")

[![CHOINKA - Customizable House Ornaments Indicating North-Pole Kingdom Angels - Wersja 2.0.0](http://img.youtube.com/vi/KIGAfvgpNOY/0.jpg)](http://www.youtube.com/watch?v=KIGAfvgpNOY "CHOINKA - Customizable House Ornaments Indicating North-Pole Kingdom Angels - Wersja 2.0.0")

# Jak widzę dalszy rozwój?

Projekt „CHOINKA - Customizable House Ornaments Indicating North-Pole Kingdom Angels” jest, jak już zostało wspomniane w rozdziale _Na jaką potrzebę odpowiada moje rozwiązanie?_ projektem stworzonym czysto dla celów edukacyjnych oraz dla walorów estetycznych.

Osobiście z pewnością widzę przyszłość tego projektu, szczególnie w sektorach bezpieczeństwa, niezawodności oraz mechaniki.

Projekt „CHOINKA - Customizable House Ornaments Indicating North-Pole Kingdom Angels” na obecną chwilę działa oraz jest zgrabnie zabudowany w obudowę wydrukowaną w technologii druku 3D.

Do projektu prowadzona jest także niniejsza dokumentacja oraz stworzone są dwa filmy przedstawiające jego wygląd oraz działanie.

Nie widzę sensu w bezgranicznym skupianiu uwagi tylko na tym szczególnym projekcie, lecz postrzegam go jako coś, co bardzo dobrze nada się do pokazania młodszym, czy starszym uczniom szkół, aby zachęcić ich do dalszej nauki i podejmowania tego wyzwania w szkołach technicznych oraz na politechnikach.

Projekt będzie dalej rozwijany, lecz w mniejszym tempie.

# TODO

-   [ ] Poprawienie spasowania obudowy z zasilaczem,
-   [ ] PCB zaprojektowane specjalnie pod projekt,
-   [ ] Zmiana złącz typu „Gold Pin” na wytrzymalsze,
-   [ ] Większe przekroje przewodów,
-   [ ] Zmiana paska LED na łańcuch choinkowy,
-   [ ] Poprawa bezpieczeństwa układu,
-   [ ] Poprawa niezawodności układu,
-   [ ] Przejście z projektem na platformę Arduino IoT Cloud,
-   [ ] Dodanie sensorów i możliwości interakcji z nimi,
-   [ ] Dodanie funkcji działania projektu offline.

# Licencja

Projekt działa na licencji GNU (General Public License), co oznacza, że może być uruchamiany, kopiowany, rozpowszechniany, analizowany oraz zmieniany i poprawiany przez użytkowników.

**GNU** General Public License [(GPL)](https://www.gnu.org/licenses/gpl-3.0.html)
