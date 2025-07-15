# 🤖 Robot Auto-Équilibré à Deux Roues

> 🎓 Projet de fin d'études – Licence 3 en Automatique  
> 👥 Réalisé par une équipe de 4 étudiants passionnés de robotique et systèmes embarqués

Ce projet a pour but de développer un robot capable de maintenir son équilibre sur deux roues en temps réel, en utilisant un capteur inertiel (MPU6050) et un algorithme de régulation PID. Le robot est contrôlé via une application Android grâce à une connexion Bluetooth.

---

## 🎯 Objectifs du Projet

- Conception d’un robot auto-équilibré basé sur Arduino
- Lecture des données d’orientation via MPU6050 (gyroscope + accéléromètre)
- Fusion des données avec un **filtre complémentaire**
- Implémentation d’un **contrôleur PID** pour stabilisation
- Commande des moteurs en PWM via un module L298N
- Communication Bluetooth via **HC-05** pour contrôle à distance

---

## ⚙️ Matériel Utilisé

| Composant              | Description                              |
|------------------------|-------------------------------------------|
| Arduino Nano           | Microcontrôleur principal                 |
| MPU6050                | IMU : accéléromètre + gyroscope           |
| L298N                  | Pont en H pour moteurs DC                 |
| 2 moteurs DC + roues   | Mouvement et équilibre                    |
| Module HC-05           | Contrôle Bluetooth via mobile             |
| Batterie Li-Po         | Alimentation autonome                     |
| Châssis fait main      | Support mécanique du robot                |

---

## 🧠 Aspects Techniques

- **Langage** : Arduino C++  
- **Bus I2C** pour lecture capteurs (MPU6050)  
- **Filtrage** des signaux avec **filtre complémentaire**  
- **Régulation PID** (Kp=40, Ki=0.05, Kd=0.8)  
- **Protection** : arrêt automatique si inclinaison > 45°  
- **Commande** : Application Android via Bluetooth

## Ajustement du PID

Le contrôleur PID est essentiel pour maintenir l’équilibre du robot. Les trois constantes suivantes doivent être ajustées en fonction du comportement réel :

- **Kp (gain proportionnel)** : augmente la réponse à l’erreur instantanée. Trop élevé → robot instable.
- **Ki (gain intégral)** : corrige l’erreur accumulée sur le temps. Trop élevé → oscillations lentes.
- **Kd (gain dérivé)** : lisse la réponse et anticipe les changements. Trop élevé → tremblements ou bruit.

### Où modifier ces valeurs ?

Dans le fichier `robot_balance.ino`, au début du code, vous trouverez :


float Kp = 40;
float Ki = 0.05;
float Kd = 0.8;
---

Vous pouvez modifier ces valeurs, téléverser à nouveau le code et observer le comportement du robot.

Exemple de réglage de base

Si le robot réagit trop lentement :

Augmenter légèrement Kp

Réduire Ki

Laisser Kd faible pour commencer


L'ajustement se fait par essais successifs (méthode empirique).




## 📷 Aperçu du Projet

![Aperçu du robot](media/photo.jpg)

---

## 🎥 Vidéo de Démonstration

[![Voir la démo vidéo](media/robot_demo.jpg)](https://www.youtube.com/watch?v=LIEN_VIDÉO_ICI)


## 👨‍💻 Membres de l’Équipe

- mansour hamza
- menai sami
- menkh elhacen
- labiod wasim

---

## 📬 Contact

Pour toute question ou collaboration, n'hésitez pas à nous contacter via LinkedIn ou GitHub.  
Merci pour votre attention !

---



`#Arduino` `#PID` `#MPU6050` `#Robotique` `#SystèmesEmbarqués` `#Bluetooth` `#HC05` `#Automatique` `#FiltreComplémentaire` `#ProjetEtudiant` `#BalanceBot` `#Mechatronics`