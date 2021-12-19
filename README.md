# Challenger-700-Controller
Dieses Projekt dient als demonstrator für den Einsatz von IoT Tracking und Zugangskontrolle Einheiten auf Flugzeugsschlepper (Challenger 700). Das Projekt umfasst:
- ein **Web frontend controller for Challenger 700**
- eine Ionic App controller für Challenger 700 Tractor - Robot
- **Arduino Sketchs** für den **Arduino Mega 2560** und **Arduino Uno** Controller des Challenger 700 Tractor-Robot
- 3D Zeichnungen mit Inventor sowie Zusammenbauten. Für 3D Bauteilen und stl kontaktieren Sie mich unter: fokoboris@gmail.com

Eine Demo der finallen Lösung in dem Video [Demo](assets/Demo.mp4) gesehen werden


## 1. Usecase Diagramm
![Usecase](assets/Usecase.png)

## 2. Komponent Diagramm
![Komponents](assets/Komponenten.png)

## 3. Prozessüberblick: Fahrzeugsteuerung -  Workflow
![Workflow](assets/Workflow.png)

## 4. Tracking unit (IoT)
Trackunit Raw mit CAN-Bus (ME 500-4), Zubehör Dual ID Keypad
| ![Trackunit device Raw](assets/trackunit-raw.png) | ![Trackunit device Dual ID](assets/trackunit-dual-id.png) |
--- | ---|
|Tracking Raw ME 500 - 4: [Link](https://www.trackunit.com/hardware/raw-faq/)| Zubehör Dual ID Keypad: [Link](https://www.trackunit.com/hardware/accessories/trackunit-dualid-ii/)|

- Kommunikation über Wifi zwischen App und Test-Einheit (Fahrzeug) mit Hilfe eines ESP8266 
- Die Fahrzeugsteuerung soll mit Hilfe eines Arduino basierender Micro Controller umgesetzt  (Es besteht allerdings auch die Möglichkeit, diese mit einem Raspery Py 3 oder andere MicroController umzusetzen)
- Den Datenaustausch zwischen dem Raw 500 – 4 und den Trackunit – Gateway erfolgt über GSM und ist für dieses Projekt vorausgesetzt 

## 5. Schaltkreis: Fritzing Zeichnung

![Schaltplan Test Einheit](assets/HiSERV_Test_Einheit_Steckplatine.png)

## 6. Realisierung

Die Realisierung erfolgt in zwei verschiedenen Schritten. Zuerst die Konstruktion und den 3D Druck von Bauteilen und anschließend die parallele Entwicklung der Fahrzeugsteuerung und der App (iOS, Android).

### 6.1. 3D Konstruktion
Insgesamt habe ich für die Test-Einheit 28 Bauteile gezeichnet. Hier werden vor allem Baugruppen und einige der wichtigsten Teile dargestellt

#### i. Chassis

Das Chassis ist aufgrund der maximale Drucklänge von 300 mm (3D Drucker bedingt) in zwei Teile gezeichnet worden:
•	Hauptteil: umfasst die Halter für die Vorder- und Hinterräder, sowie die Fläche für den Akku (Li-Ion Batterien), die Stützen für die Motoren und den Mikrocontroller (Arduino)
•	Das vordere Chassis: trägt die Kabine und wird an dem Hauptteil des Chassis angekoppelt.

![Chassis](assets/3D/Chassis.png)

![Chassis & Cabine](assets/3D/Chassis_Cabine.png)

#### ii.Kabine und Türen

![Kabine & Türen](assets/3D/Cabine_Tueren.png)


#### iii. Rad & Reifen

![Rad & Reifen](assets/3D/Reifen.png)

#### iV. Zusammenbau

![Fahrzeugszusammenbau](assets/3D/Fahrzeugzusammenbau.png)

### 6.3. Ergebnisse

#### i.	Fahrzeug: Ergebnis
![Fahrzeug_01](assets/Fahrzeug/Fahrzeug_01.png)

![Fahrzeug_02](assets/Fahrzeug/Fahrzeug_02.png)
![Reifen](assets/Fahrzeug/Reifen.png)
![Fahrzeug_03](assets/Fahrzeug/Fahrzeug_03.png)
![Fahrzeug_04](assets/Fahrzeug/Fahrzeug_04.png)
![Fahrzeug_05](assets/Fahrzeug/Fahrzeug_05.png)

#### ii. Ionic App: Ergebnis
| Name | Image |
|---|--- |
| App Splash Screen |![App Splash Screen](assets/app/Splash-Screen.png) |
| Startbildschirm |![Startbildschirm](assets/app/Startbildschirm.png) |
| Startbildschirm MenuIcon |![Startbildschirm MenuIcon](assets/app/MenuIcon.png) |
| Über Uns |![Über Uns](assets/app/UeberUns.png) |
| Startbildschirm Kontext Menu |![StartbildschirmKontext](assets/app/StartbildschirmKontext.png) |
| Fahrzeugssteuerung |![Fahren - Steuerung](assets/app/Fahren.png) |