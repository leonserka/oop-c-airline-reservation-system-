# oop-c-airline-reservation-system-

# ✈️ Airline Reservation System (C++ OOP Project)

## 📖 Opis projekta
Ovaj projekt predstavlja **Airline Reservation System** izrađen u **C++** pomoću **objektno orijentiranog programiranja (OOP)**.  
Omogućuje korisnicima da kreiraju domaće ili međunarodne letove, rezerviraju karte, otkažu rezervacije i pregledaju sve postojeće karte.

Projekt pokazuje praktičnu primjenu svih glavnih OOP koncepata:  
- **Enkapsulacija**
- **Nasljeđivanje**
- **Polimorfizam**
- **Apstrakcija**
- **Pametni pokazivači (smart pointers)**
- **Rad s kolekcijama (std::vector, std::unordered_set)**
- **Validacija podataka pomoću Regex-a**
- **Modularnost i dinamička alokacija memorije**

---

## 🧩 Struktura sustava

### **Klase i njihova uloga**
| Klasa | Uloga | OOP koncept |
|-------|--------|-------------|
| `Flight` | Apstraktna osnovna klasa koja predstavlja let. Sadrži zajedničke podatke za sve tipove letova. | **Apstrakcija, enkapsulacija** |
| `DomesticFlight` | Nasljeđuje `Flight` i predstavlja domaći let. | **Nasljeđivanje** |
| `InternationalFlight` | Nasljeđuje `Flight` i predstavlja međunarodni let. | **Nasljeđivanje** |
| `Ticket` | Sadrži podatke o putniku i povezanom letu. | **Kompozicija, enkapsulacija** |
| `BookingSystem` | Upravljanje rezervacijama: kreiranje, otkazivanje, pregled karata. | **Polimorfizam, upravljanje objektima** |

---

## ⚙️ Funkcionalnosti

### 🧳 Korisničke mogućnosti:
- Kreiranje **domaćih** ili **međunarodnih** letova  
- **Rezervacija leta** uz unos podataka o putniku (ime, prezime, OIB/ID, e-mail, kontakt, način plaćanja, klasa sjedala)
- **Validacija e-mail adrese** pomoću `std::regex`
- **Pregled svih rezerviranih letova**
- **Provjera karte po ID-u**
- **Otkazivanje rezervacije**
- **Automatsko smanjenje broja slobodnih mjesta nakon rezervacije**

---

## 🧠 OOP Koncepti u projektu

### 🔒 Enkapsulacija
Podaci o letu i putniku su **privatni** i njima se pristupa putem javnih metoda (get/set).

```cpp
void setFlightDetails(const std::string& depCity, const std::string& arrCity, ...);
int getAvailableSeats() const;
